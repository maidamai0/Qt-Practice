#include <QGuiApplication>
#include <QQmlComponent>
#include <QQuickView>

#include <string>

const std::string text_qml = R"(
  import QtQuick 2.12;
  
  Text {
    text: "Hello, World!"
    color: "red"
  }
)";

int main(int argc, char* argv[]) {
  QGuiApplication app(argc, argv);

  QQuickView view;
  QQmlComponent* component = new QQmlComponent(view.engine());

  component->setData(text_qml.c_str(), QUrl());
  const auto object = component->create();

  // setContent() is marked as an internal Qt method (but it's public)
  // see source for qmlscene for why I'm using it here
  view.setContent(QUrl(), component, object);

  view.show();

  app.exec();

  delete object;
  delete component;
}