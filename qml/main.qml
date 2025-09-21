import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts

ApplicationWindow {
    visible: true

    property bool isDarkMode: true
    Material.theme: isDarkMode ? Material.Dark : Material.Light
    Material.primary: Material.Purple
    Material.accent: Material.Pink

    CreateCanvas {
        id: createCanvasDialog
    }

    menuBar: MenuBar {
        Menu {
            title: "File"

            Action {
                text: "New"
                onTriggered: {
                    createCanvasDialog.open()
                }
            }
            Action {
                text: "Open"
                onTriggered: {
                    console.log("Open file action triggered");
                }
            }
            Action {
                text: "Save"
                onTriggered: {
                    console.log("Save file action triggered");
                }
            }
        }

        Menu {
            title: "Window"

            Action {
                text: "Dark Mode"
                checkable: true
                checked: isDarkMode
                onTriggered: {
                    isDarkMode = checked;
                }
            }
        }
    }

    SplitView {
        id: allWorkspaces
        anchors.fill: parent
        orientation: Qt.Vertical

        SplitView {
            orientation: Qt.Horizontal
            implicitHeight: 800

            Rectangle {
                id: toolBar
                implicitWidth: 50
                color: "transparent"
            }

            Rectangle {
                id: workspace
                implicitWidth: 1400
                color: "transparent"
                clip: true

                Item {
                    Rectangle {
                        id: canvas
                        x: (workspace.width  - width*scale)  / 2
                        y: (workspace.height - height*scale) / 2
                        width: canvasManager.width
                        height: canvasManager.height
                        color: "white"
                        border.color: "black"
                        anchors.centerIn: parent
                        visible: canvasManager.width > 0
                    }
                }
            }

            Rectangle {
                id: docBar
                color: "transparent"
            }
        }

        Rectangle {
            id: statusBar
            implicitHeight: 50
            color: "transparent"
        }
    }

} 
