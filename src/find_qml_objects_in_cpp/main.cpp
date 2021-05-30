#include <QApplication>
#include <QQuickItem>
#include <QQuickView>

#include <cassert>

auto main(int argc, char** argv) -> int {
  QApplication app(argc, argv);
  auto* q = new QQuickView;
  q->setResizeMode(QQuickView::SizeRootObjectToView);
  q->setSource(QUrl("qrc:main.qml"));

  auto rectangle = q->rootObject()->findChild<QQuickItem*>("rectangle");
  assert(rectangle && "child not found");

  QObject::connect(rectangle, &QQuickItem::widthChanged,
                   [=]() { qDebug() << "width is " << rectangle->width(); });
  QObject::connect(rectangle, &QQuickItem::heightChanged,
                   [=]() { qDebug() << "height is " << rectangle->height(); });
  q->show();
  QApplication::exec();
}