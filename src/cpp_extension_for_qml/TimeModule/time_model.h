#pragma once

#include <QObject>
#include <QTimer>

class TimeModel : public QObject {
  Q_OBJECT
  Q_PROPERTY(int hour READ hour NOTIFY hourChanged)
  Q_PROPERTY(int minute READ minute NOTIFY minuteChanged)
  Q_PROPERTY(int second READ second NOTIFY secondChanged)

public:
  TimeModel();

signals:
  void hourChanged();
  void minuteChanged();
  void secondChanged();

public:
  auto hour() -> int;
  auto minute() -> int;
  auto second() -> int;

private slots:
  void on_time_out();

private:
  int hour_ = 0;
  int minute_ = 0;
  int second_ = 0;
  QTimer timer_;
};
