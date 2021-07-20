#include "qcoreapplication.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>

auto main(int argc, char* argv[]) -> int {
  QGuiApplication app(argc, argv);
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QQmlApplicationEngine engine;
  const QUrl url(QStringLiteral("qrc:/main.qml"));
  QObject::connect(
    &engine, &QQmlApplicationEngine::objectCreated, &app,
    [url](QObject* obj, const QUrl& objUrl) {
      if (!obj && url == objUrl)
        QCoreApplication::exit(-1);
    },
    Qt::QueuedConnection);
  engine.load(url);

  return QGuiApplication::exec();
}
