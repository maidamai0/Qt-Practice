import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12


Item {
    id: rect
    // anchors.fill:parent
    width: 1024
    height: 768
    visible: true
    objectName: "root"

    
    Rectangle {

        anchors.fill: parent
        objectName: "rect"
        color: "red"
        
        Button {
            id: saveToDisk
            text: qsTr("Pick")

            onClicked: {
                Snapshot.grabToImage(rect,"SnapshotQml.png",function () {
                    console.log('SnapshotQml saving to disk..')
                })
            }
        }
    }
}