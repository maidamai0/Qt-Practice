#include "time_model.h"

#include <QDateTime>
#include <QTime>

TimeModel::TimeModel() {
  const auto now = QDateTime::currentDateTime().time();
  hour_ = now.hour();
  minute_ = now.minute();
  second_ = now.second();

  timer_.start(1000);
  connect(&timer_, &QTimer::timeout, this, &TimeModel::on_time_out);
}

auto TimeModel::hour() -> int {
  return hour_;
}

auto TimeModel::minute() -> int {
  return minute_;
}

auto TimeModel::second() -> int {
  return second_;
}

void TimeModel::on_time_out() {
  const auto now = QDateTime::currentDateTime().time();
  hour_ = now.hour();
  emit hourChanged();

  minute_ = now.minute();
  emit minuteChanged();

  second_ = now.second();
  emit secondChanged();
}