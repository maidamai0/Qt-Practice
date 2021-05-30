#include "QtWidgets/qapplication.h"
#include "qobject.h"
#include "qobjectdefs.h"
#include "qqmlapplicationengine.h"
#include "qquickwindow.h"
#include "qurl.h"
#include <QQmlContext>
#include <QQuickItem>

#include <cassert>
#include <iostream>
#include <string>

#include "image_compare.hpp"

class Sync : public QObject {
  Q_OBJECT
public:
signals:
  void complete();
};

#include "main.moc"

auto main(int argc, char** argv) -> int {
  QApplication app(argc, argv);
  QQmlApplicationEngine engine;
  const QUrl url("qrc:///main.qml");
  QObject::connect(
    &engine, &QQmlApplicationEngine::objectCreated, &app,
    [=](QObject* obj, const QUrl& objUrl) {
      if (!obj && objUrl == url) {
        QApplication::exit(-1);
      }
    },
    Qt::QueuedConnection);
  engine.load(url);

  auto window = qobject_cast<QQuickWindow*>(engine.rootObjects()[0]);
  assert(window && "object not found");
  Sync sync;
  engine.rootContext()->setContextProperty("SyncObject", &sync);

  QObject::connect(&sync, &Sync::complete, []() {
    qDebug() << "complete";
    const auto image_base_name = "test_image_";
    for (auto i = 0; i < 2; ++i) {
      const auto expected = image_base_name + std::to_string(i) + ".png";
      const auto actual = image_base_name + std::to_string(i + 1) + ".png";
      std::cout << "is " << i << " and " << i + 1 << " the same? "
                << image_diff(expected, actual) << std::endl;
    }
  });

  return QApplication::exec();
}