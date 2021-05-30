# Create a qml plugin with c++

## Environment

windows 10 1909 64 bit && msvc_2013

## Create a **Qt Quick 2 Extension Plugin** project

## Choose a class to sub-class

    1. Visual item and need draw operations with QPainter API:QQuickPaintedItem
    2. Visual item without the need of QPainter API:QQuickItem
    3. Non-visual item: any QObject-based class.

## Register your type

## Create a qmldir file

1. The module name is specified with module keyword in qmldir
2. module name must be the same with module uri

## Create a qmltypes file(optinal, for qtcreator)

## Reference

1. [Extending QML with C++](https://doc.qt.io/qt-5/qtqml-tutorials-extending-qml-example.html)
