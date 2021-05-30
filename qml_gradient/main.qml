import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12
import QtQuick.Shapes 1.12

Window {
    visible: true
    width: 1024
    height: 30

    Shape {
        id: shape
        anchors.fill: parent
        layer.enabled: true
        layer.samples: 4
        ShapePath {
            strokeWidth: 1
            strokeColor: "red"
            fillGradient: LinearGradient {
                x1: shape.width/2
                y1: 20
                x2: x1
                y2: shape.height-40
                GradientStop { position: 0; color: "transparent" }
                GradientStop { position: 1.0; color: "#FF4E40" }
            }
            startX: shape.width/2; startY: 20
            PathLine { x: shape.width-40; y: shape.height-40 }
            PathLine { x: 20; y: shape.height-40 }
            PathLine { x: shape.width/2; y: 20 }
        }
    }
}