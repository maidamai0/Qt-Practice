import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 1024
    height: 768

    Flickable {
        id:rect
        anchors.fill: parent
        contentWidth:_image.width
        contentHeight: _image.height

        Image {
            id:_image
            source:"qrc:image.jpg"
        }
    }
}
