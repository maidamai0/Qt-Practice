import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15

ApplicationWindow {
    visible: true
    width: 1024
    height: 768

    color: "red"

    Rectangle {
        anchors.fill: parent
        anchors.margins: 20
        // margins is substracted from anchors.fill
        color: "blue"
        opacity: 0.5
    }
}
