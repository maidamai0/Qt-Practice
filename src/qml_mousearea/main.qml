import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 1024
    height: 768

    Rectangle {
        anchors.fill: parent
        anchors.margins: 20
        color: "cornflowerblue"

        MouseArea {
            anchors.fill: parent
            onPressed: {
                console.log("cornflowerblue pressed")
            }

            onClicked: {
                console.log("cornflowerblue clicked")
            }

            onDoubleClicked: {
                console.log("cornflowerblue double clicked")
            }

            onReleased: {
                console.log("cornflowerblue released")
            }
        }

        Rectangle {
            anchors.centerIn: parent
            width: parent.width / 2
            height: parent.height / 2
            color: "hotpink"

            MouseArea {
                anchors.fill: parent
                propagateComposedEvents: true
                onClicked: {
                    console.log("hotpink clicked")
                    //                    mouse.accepted = false
                }

                onDoubleClicked: {
                    console.log("hotpink double clicked")
                    //                    mouse.accepted = false
                }

                onPressed: {
                    console.log("hotpink pressed")
                    //                    mouse.accepted = false
                }

                onReleased: {
                    console.log("hotpink released")
                    //                    mouse.accepted = false
                }
            }
        }
    }
}
