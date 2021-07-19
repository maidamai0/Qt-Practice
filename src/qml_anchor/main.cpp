#include <QGuiApplication>
#include <QMessageLogContext>
#include <QQmlApplicationEngine>
#include <QQmlContext>

class Foo : public QObject {
  Q_OBJECT;
public slots:
  void hello() {
    qDebug() << __FUNCTION__;
  }
};

auto main(int argc, char* argv[]) -> int {
  QGuiApplication app(argc, argv);
  qSetMessagePattern("%{threadid} %{type} %{file}:%{function}@%{line}  ==>  %{message}");
  qDebug() << "Hello World!";

  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("foo", QVariant::fromValue(new Foo()));
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
#include "main.moc"
