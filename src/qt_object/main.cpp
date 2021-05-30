#include <QDebug>
#include <QObject>
#include <iostream>

auto main(int argc, char** argv) -> int {
  auto object = new QObject();
  qDebug() << "dumpObjectInfo";
  object->dumpObjectInfo();
  qDebug() << "dumpObjectTree";
  object->dumpObjectTree();
}