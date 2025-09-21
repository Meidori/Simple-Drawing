import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts

Dialog {
    id: createCanvasDialog
    modal: true
    width: 600
    height: 400

    anchors.centerIn: parent

    property int canvasWidthValue
    property int canvasHeightValue

    ColumnLayout {
        anchors.centerIn: parent
        width: Math.min(parent.width, 160)

        Label {
            Layout.alignment: Qt.AlignHCenter
            font.pointSize: 14
            font.bold: true
            text: "Image Size\n"
        }

        RowLayout {
            spacing: 20
            Layout.fillWidth: true

            Label {
                font.bold: true
                Layout.preferredWidth: 40
                text: "Width"
            }

            TextField {
                id: canvasWidth
                Layout.fillWidth: true
                Layout.preferredWidth: 60
                horizontalAlignment: Text.AlignHCenter
                validator: IntValidator { bottom: 1; top: 10000 }
                placeholderText: qsTr("Width px")
                text: "800"
            }
        }

        RowLayout {
            spacing: 20
            Layout.fillWidth: true

            Label {
                font.bold: true
                Layout.preferredWidth: 40
                text: "Height"
            }

            TextField {
                id: canvasHeight
                Layout.fillWidth: true
                Layout.preferredWidth: 60
                horizontalAlignment: Text.AlignHCenter
                validator: IntValidator { bottom: 1; top: 10000 }
                placeholderText: qsTr("Height px")
                text: "600"
            }
        }
    }

    RowLayout {
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        spacing: 10

        Button {
            text: "Cancel"
            onClicked: createCanvasDialog.close()
        }

        Button {
            text: "OK"
            onClicked: {
                createCanvasDialog.canvasWidthValue = parseInt(canvasWidth.text);
                createCanvasDialog.canvasHeightValue = parseInt(canvasHeight.text);

                console.log("New canvas w/h value", "width =", createCanvasDialog.canvasWidthValue, "height =", createCanvasDialog.canvasHeightValue);

                createCanvasDialog.close();
            }
        }
    }
}
