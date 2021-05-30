#pragma once

#include <QQuickItem>
#include <QString>
#include <QtCore/QObject>
#include <QtQml/QJSValue>

#include <iostream>
#include <memory>

class QuickItemSnapShotPrivate;
class QSGLayer;

class QuickItemSnapShot final : public QObject {
  Q_OBJECT
  Q_DECLARE_PRIVATE(QuickItemSnapShot)
public:
  QuickItemSnapShot();
  ~QuickItemSnapShot() final = default;

  Q_INVOKABLE void
  grabToImage(QQuickItem* item, QString file_name, const QJSValue& callback);

signals:
  void ready();

private:
  void setup();
  void render();
  void save_to_file();

private:
  std::shared_ptr<QuickItemSnapShot> result_;
  QString file_name_;
};