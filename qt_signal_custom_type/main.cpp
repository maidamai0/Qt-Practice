#include "custom_type.h"
#include <memory>

auto main(int argc, char** argv) -> int {
  auto sender = new Sender;

  QObject::connect(sender, &Sender::custom_type_signal, sender,
                   &Sender::on_custm_type);
  QObject::connect(sender, &Sender::shared_ptr_signal, sender,
                   &Sender::on_shared_ptr);

  CustomType payload(0, "custom type");
  emit sender->custom_type_signal(payload);

  auto shared_custom_type
    = std::make_shared<CustomType>(1, "Shared custom type");
  emit sender->shared_ptr_signal(shared_custom_type);
}