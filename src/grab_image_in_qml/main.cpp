#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQuickWidgets/QQuickWidget>
#include <qquickview.h>

auto main(int argc, char* argv[]) -> int {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QApplication app(argc, argv);

  // auto* q = new QQuickWidget;
  // q->setResizeMode(QQuickWidget::SizeRootObjectToView);
  // q->setSource(QUrl("qrc:///main.qml"));
  // q->show();

  // auto* q = new QQuickView;
  // q->setResizeMode(QQuickView::SizeRootObjectToView);
  // q->setSource(QUrl("qrc:///main.qml"));

  // QWidget* container = QWidget::createWindowContainer(q);
  // container->show();

  QQmlApplicationEngine engine;
  const QUrl url(QStringLiteral("qrc:///main.qml"));
  QObject::connect(
    &engine, &QQmlApplicationEngine::objectCreated, &app,
    [url](QObject* obj, const QUrl& objUrl) {
      if (!obj && url == objUrl)
        QCoreApplication::exit(-1);
    },
    Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
}