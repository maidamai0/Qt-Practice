
#include "quick_item_snapshot.h"

#include <QQuickWindow>
#include <QSize>
#include <QtQml>

#include <QtQml/QQmlEngine>
#include <QtQml/QQmlInfo>

#include <private/qquickitem_p.h>
#include <private/qquickpixmapcache_p.h>
#include <private/qsgadaptationlayer_p.h>
#include <private/qsgcontext_p.h>

#include <memory>

class QuickItemSnapShotPrivate final : public QObjectPrivate {
public:
  QuickItemSnapShotPrivate() = default;
  ~QuickItemSnapShotPrivate() final = default;

  static auto create(QQuickItem* item) -> std::shared_ptr<QuickItemSnapShot>;

  QImage image_;

  QQmlEngine* qml_engine_{};
  QJSValue callback_;

  QPointer<QQuickItem> item_;
  QPointer<QQuickWindow> window_;
  QSGLayer* texture_{};
  QSizeF item_size_;
  QSize texture_size_;
};

auto QuickItemSnapShotPrivate::create(QQuickItem* item)
  -> std::shared_ptr<QuickItemSnapShot> {
  if (item->window() == nullptr) {
    qmlWarning(item) << "grabToImage: item is not attached to a window";
    return nullptr;
  }

  auto size = QSize(item->width(), item->height());

  if (size.width() < 1 || size.height() < 1) {
    qmlWarning(item) << "grabToImage: item has invalid dimensions";
    return nullptr;
  }

  auto result = std::make_shared<QuickItemSnapShot>();
  QuickItemSnapShotPrivate* d = result->d_func();
  d->item_ = item;
  d->window_ = item->window();
  d->texture_size_ = size;

  QQuickItemPrivate::get(item)->refFromEffectItem(false);

  // trigger sync & render
  item->window()->update();

  return result;
}

QuickItemSnapShot::QuickItemSnapShot()
  : QObject(*new QuickItemSnapShotPrivate) {
}

void QuickItemSnapShot::setup() {
  Q_D(QuickItemSnapShot);
  if (d->item_ == nullptr) {
    disconnect(d->window_.data(), &QQuickWindow::beforeSynchronizing, this,
               &QuickItemSnapShot::setup);
    disconnect(d->window_.data(), &QQuickWindow::afterRendering, this,
               &QuickItemSnapShot::render);
    disconnect(result_.get(), &QuickItemSnapShot::ready, this,
               &QuickItemSnapShot::save_to_file);
    return;
  }

  QSGRenderContext* rc = QQuickWindowPrivate::get(d->window_.data())->context;
  d->texture_ = rc->sceneGraphContext()->createLayer(rc);
  d->texture_->setItem(QQuickItemPrivate::get(d->item_)->itemNode());
  d->item_size_ = QSizeF(d->item_->width(), d->item_->height());
}

void QuickItemSnapShot::render() {
  Q_D(QuickItemSnapShot);
  if (d->texture_ == nullptr)
    return;

  d->texture_->setRect(QRectF(0, d->item_size_.height(), d->item_size_.width(),
                              -d->item_size_.height()));
  const QSize minSize = QQuickWindowPrivate::get(d->window_.data())
                          ->context->sceneGraphContext()
                          ->minimumFBOSize();
  d->texture_->setSize(
    QSize(qMax(minSize.width(), d->texture_size_.width()),
          qMax(minSize.height(), d->texture_size_.height())));
  d->texture_->scheduleUpdate();
  d->texture_->updateTexture();
  d->image_ = d->texture_->toImage();

  delete d->texture_;
  d->texture_ = nullptr;

  disconnect(d->window_.data(), &QQuickWindow::beforeSynchronizing, this,
             &QuickItemSnapShot::setup);
  disconnect(d->window_.data(), &QQuickWindow::afterRendering, this,
             &QuickItemSnapShot::render);
  emit ready();
}

auto QuickItemSnapShot::save_to_file() -> void {
  result_->d_func()->image_.save(file_name_);
  auto d = result_->d_func();
  if (d->callback_.isCallable()) {
    d->callback_.call();
  }
}

void QuickItemSnapShot::grabToImage(QQuickItem* item, QString file_name,
                                    const QJSValue& callback) {
  result_ = QuickItemSnapShotPrivate::create(item);
  if (result_ == nullptr)
    return;

  QuickItemSnapShotPrivate* d = result_->d_func();
  d->callback_ = callback;
  d->qml_engine_ = qmlEngine(item);
  file_name_ = std::move(file_name);

  connect(item->window(), &QQuickWindow::beforeSynchronizing, result_.get(),
          &QuickItemSnapShot::setup, Qt::DirectConnection);
  connect(item->window(), &QQuickWindow::afterRendering, result_.get(),
          &QuickItemSnapShot::render, Qt::DirectConnection);
  connect(result_.get(), &QuickItemSnapShot::ready, this,
          &QuickItemSnapShot::save_to_file);
}
