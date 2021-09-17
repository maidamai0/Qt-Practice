import QtQuick 2.13
import QtQuick.Window 2.13
import org.company.module as Company

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Company.TimeModel {
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
