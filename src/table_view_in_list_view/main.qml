import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.15

Window {
    id: root
    visible: true
    width: 300
    height: 600

    ListView {
        anchors.fill: parent
        model: compositeModel
        spacing: 50
        delegate: ColumnLayout {
            Layout.margins: 50

            RowLayout {
                Layout.preferredWidth: root.width

                CheckBox{
                    Layout.alignment: Qt.AlignLeft
                }

                Text {
                    Layout.alignment: Qt.AlignHCenter
                    text: "Middle"
                }

                Text {
                    Layout.alignment: Qt.AlignRight
                    text:  "Right"
                }
            }

            TableView {
                Layout.fillWidth: true
                model: individualModel

                TableViewColumn {
                    role: "title"
                    title: "Title"
                    // width: 100
                }

                TableViewColumn {
                    role: "author"
                    title: "Author"
                    // width: 200
                }
            }
        }
    }
}