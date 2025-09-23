import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts
import CanvasUtils

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
            implicitHeight: 600 

            Rectangle {
                id: toolBar
                implicitWidth: 50
                color: "transparent"
            }

            Rectangle {
                id: workspace
                implicitWidth: 800
                color: "transparent"
                clip: true

                Item {
                    id: canvas_area
                    width: canvas.width
                    height: canvas.height
                    x: (workspace.width  - width*scale)  / 2
                    y: (workspace.height - height*scale) / 2
                    scale: 1
                    CanvasItem {
                        id: canvas
                        width: canvasManager.width
                        height: canvasManager.height
                        image: canvasManager.currentImage
                    }

                    MouseArea {
                        anchors.fill: parent
                        
                        onWheel: (wheel) => {
                            if (wheel.modifiers & Qt.ControlModifier) {
                                var cursorX = wheel.x
                                var cursorY = wheel.y
                                var oldScale = canvas_area.scale

                                var newScale = (wheel.angleDelta.y > 0)
                                    ? Math.min(10, oldScale + 0.1)
                                    : Math.max(0.1, oldScale - 0.1)

                                var scaleFactor = newScale / oldScale

                                canvas_area.scale = newScale

                                canvas_area.x -= (cursorX - canvas_area.x) * (scaleFactor - 1)
                                canvas_area.y -= (cursorY - canvas_area.y) * (scaleFactor - 1)
                            }
                        }
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
