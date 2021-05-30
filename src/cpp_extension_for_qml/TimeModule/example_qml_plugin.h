#pragma once

#include <QQmlEngine>
#include <QQmlExtensionPlugin>

#include "time_model.h"

class example_qml_plugin : public QQmlExtensionPlugin {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)
public:
  example_qml_plugin() = default;
  ~example_qml_plugin() override = default;

  void registerTypes(const char* uri) override;
};
