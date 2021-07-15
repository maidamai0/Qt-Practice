import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15

ApplicationWindow {
    visible: true
    width: 1024
    height: 768

    property int cnt: 1

    Column {
        anchors.centerIn: parent
        spacing: 20
        Repeater {
            model: 3
            ComboBox {
                model: comboModel.strings
                onModelChanged: {
                    console.log(index + ": model changed to", model)
                }

                onCurrentIndexChanged: {
                    console.log(index + ": index changed to", currentIndex)
                    if (currentIndex == count - 1) {
                        var new_index = comboModel.addString("new " + cnt)
                        console.log(index + ": new idex is", new_index)
                        model = comboModel.strings
                        cnt = cnt + 1
                        currentIndex = new_index
                    } else {
                        model = comboModel.strings
                    }
                }

                Component.onCompleted: {
                    model = comboModel.strings
                }
            }
        }
    }
}
