import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15

ApplicationWindow {
    visible: true
    width: 1024
    height: 768

    function createModel() {
        for (var i = 4; i < 50; ++i) {
            list_model.append({
                                  "col1": "row" + i + " col1",
                                  "col2": "row" + i + " col2",
                                  "col3": "row" + i + " col3"
                              })
        }
    }

    ListModel {
        id: list_model
        ListElement {
            col1: "row1 col1"
            col2: "row1, col2"
            col3: "row1, col3"
        }

        ListElement {
            col1: "row2 col1"
            col2: "row2, col2"
            col3: "row2, col3"
        }

        ListElement {
            col1: "row3 col1"
            col2: "row3, col2"
            col3: "row3, col3"
        }

        Component.onCompleted: {
            createModel()
        }
    }

    ListView {
        id: view
        anchors.fill: parent
        model: list_model
        delegate: Text {
            text: col1 + " " + col2 + " " + col3
        }
    }
}
