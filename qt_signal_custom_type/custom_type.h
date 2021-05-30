#pragma once

/**
 * @file custom_type.h
 * @author tonghao.yuan (tonghao.yuan@csdental.com)
 * @brief   pass custom type in qt signal
 * @version 0.1
 * @date 2020-03-20
 *
 * @copyright Copyright (c) 2020 Carestream Dental,LLC. All Rights Reserved
 *
 */

#include <QObject>

#include <iostream>
#include <memory>
#include <string>

class CustomType {
public:
  CustomType() = default;
  ~CustomType() = default;
  CustomType(const int& int_v, std::string&& string_v);
  CustomType(const CustomType&) = default;
  CustomType(CustomType&&) = default;
  auto operator=(const CustomType&) -> CustomType& = default;

  auto Print() const;

private:
  int int_ = 0;
  std::string string_;
};

class Sender : public QObject {
  Q_OBJECT
public:
  Sender() = default;

signals:
  void custom_type_signal(CustomType);
  void shared_ptr_signal(std::shared_ptr<CustomType>);

public slots:
  void on_custm_type(CustomType type);
  void on_shared_ptr(std::shared_ptr<CustomType>);
};