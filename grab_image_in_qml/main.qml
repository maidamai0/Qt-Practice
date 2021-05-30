import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 1024
    height: 768
Item {
    id: rect
    anchors.fill:parent
    visible: true

    
    Rectangle {

        anchors.fill: parent
        
        color: "red"
        
        Button {
            id: saveToDisk
            text: qsTr("Pick")
            onClicked: {
                rect.grabToImage(function (result) {
                    console.log('saving to disk..')
                    result.saveToFile("pick.png")
                })
            }
        }
    }
}
}