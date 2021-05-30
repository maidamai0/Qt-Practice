#include "qapplication.h"
#include "qjsvalue.h"
#include "qobject.h"
#include "qquickwindow.h"
#include "quick_item_snapshot.h"
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWidget>
#include <iostream>

auto main(int argc, char* argv[]) -> int {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QApplication app(argc, argv);

  auto* q = new QQuickWidget;
  q->setResizeMode(QQuickWidget::SizeRootObjectToView);

  QuickItemSnapShot snap_shot;
  q->rootContext()->setContextProperty("Snapshot", &snap_shot);
  q->setSource(QUrl("qrc:///main.qml"));
  q->show();

  return QApplication::exec();
}