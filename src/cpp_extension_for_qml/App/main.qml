import QtQuick 2.13
import QtQuick.Window 2.13
import code.cpp_extension_for_qml.TimeModule 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Time {
        id:time
    }

    Text {
        anchors.centerIn: parent
        id: text
        text: qsTr("Now is " + time.hour + ":" + time.minute + ":" + time.second)
        font.pixelSize: 60
        font.bold: true
        color: "red"
    }
}
