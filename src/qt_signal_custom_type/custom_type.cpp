#include "custom_type.h"
#include <QMetaType>
#include <iostream>

Q_DECLARE_METATYPE(CustomType);

CustomType::CustomType(const int& int_v, std::string&& string_v)
  : int_(int_v), string_(string_v) {
}

auto CustomType::Print() const {
  std::cout << "int is " << int_ << " string is " << string_ << std::endl;
}

void Sender::on_custm_type(CustomType type) {
  std::cout << __FUNCTION__ << std::endl;
  type.Print();
}

void Sender::on_shared_ptr(std::shared_ptr<CustomType> type) {
  std::cout << __FUNCTION__ << std::endl;
  type->Print();
}