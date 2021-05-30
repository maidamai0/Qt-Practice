import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQml 2.12
import QtQuick.Window 2.12

Window {
    id: root
    visible: true
    width: 200
    height: 200
    
    Rectangle {
        id: rectangle
        objectName: "rectangle"
        anchors.fill: parent
        color: "lightBlue"
        property string image_name: qsTr("test_image_")

        Timer {
            running:true
            repeat:true
            interval: 1000
            property int index: 0
            onTriggered: {
                rectangle.grabToImage(function(result) {
                            var file_name = rectangle.image_name+index.toLocaleString() + ".png"
                            console.info("image is ", file_name)
                            result.saveToFile(file_name);
                            index += 1
                            if(index == 2) {
                                content.text = "Second"
                            }

                            if(index == 3) {
                                running = false
                                root.close()
                                SyncObject.complete()
                            }
                        })
            }
        }

        Text {
            id:content
            anchors.centerIn: parent
            text: "First"
        }
    }
}
