#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQuickWidgets/QQuickWidget>

auto main(int argc, char* argv[]) -> int {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QApplication app(argc, argv);

  QQmlApplicationEngine engine;
  const QUrl url(QStringLiteral("qrc:///main.qml"));
  QObject::connect(
    &engine, &QQmlApplicationEngine::objectCreated, &app,
    [url](QObject* obj, const QUrl& objUrl) {
      if ((obj == nullptr) && url == objUrl)
        QCoreApplication::exit(-1);
    },
    Qt::QueuedConnection);
  engine.load(url);

  return QApplication::exec();
}