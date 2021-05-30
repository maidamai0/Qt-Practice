import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12
import QtMultimedia 5.12

Window {
    visible: true
    width: 1024
    height: 768

    Video {
        id:rect
        anchors.centerIn: parent
        width: parent.width * 0.9
        height: parent.height * 0.9
        // source:"file:///D:/open_source_project/maidamai0.github.io/build/code/qml_video/anterior_ridge_scanning.avi.avi"
        source:"file:///D:/csd/csscanflow/build/resources/tutorials/anterior_ridge_scanning.avi"
        autoPlay: true
        // seekable: true
        flushMode: VideoOutput.FirstFrame
    //   loops: MediaPlayer.Infinite

        property bool initialized: false

        onStatusChanged:{
            console.warn("status is", status);
        }

        onPositionChanged: {
            console.warn("position changed to", position)
            if(position > 1 && !initialized) {
                rect.stop()
                initialized = true
            }
        }

        onErrorStringChanged: {
            console.warn("error is", errorString);
        }

        Component.onCompleted:{
            console.warn("meta data", metaData);
        }

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            hoverEnabled: true
            onEntered: {
                rect.play()
            }
            onExited: {
                rect.stop()
            }
            onClicked: {
                rect.play()
            }
        }
        
    }

    Component.onCompleted: {
        console.log("completed")
    }
    
}