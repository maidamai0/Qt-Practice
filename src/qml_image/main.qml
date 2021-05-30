import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 1024
    height: 768

    Rectangle {
        id:rect
        anchors.centerIn: parent
        width: parent.width * 0.9
        height: parent.height * 0.9
        ScrollView {
            anchors.fill: parent
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            clip: true
            Image {
                width: rect.width
                fillMode:Image.PreserveAspectFit
                source:"qrc:image.jpg"
            }
        }
    }
}