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
                    createCanvasDialog.open();
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

                Button {
                    id: lineTool
                    text: "Line"
                    checkable: true
                    checked: false
                    onClicked: {
                        if (checked) {
                            canvasManager.activeTool = CanvasManager.ToolLine
                        }
                    }
                }
            }

            Rectangle {
                id: workspace
                implicitWidth: 800
                color: "transparent"
                clip: true

                Item {
                    id: canvasArea
                    width: canvas.width
                    height: canvas.height
                    x: (workspace.width - width * scale) / 2
                    y: (workspace.height - height * scale) / 2
                    scale: 1

                    property real minScale: 0.1
                    property real maxScale: 10.0
                    property real scaleFactor: 1.1 
                    
                    focus: true

                    CanvasItem {
                        id: canvas
                        width: canvasManager.width
                        height: canvasManager.height
                        image: canvasManager.currentImage

                        MouseArea {
                            anchors.fill: parent
                            acceptedButtons: Qt.LeftButton
                            
                            onPressed: (mouse) => {
                                if (canvasManager.activeTool === CanvasManager.ToolLine) {
                                    var point = Qt.vector3d(mouse.x, mouse.y, 1)
                                    canvasManager.startDrawingLine(point)
                                }
                            }
                            
                            onPositionChanged: (mouse) => {
                                if ((mouse.buttons & Qt.LeftButton) && 
                                    canvasManager.activeTool === CanvasManager.ToolLine) {
                                    var point = Qt.vector3d(mouse.x, mouse.y, 1)
                                    canvasManager.updateDrawingLine(point)
                                }
                            }
                            
                            onReleased: (mouse) => {
                                if (canvasManager.activeTool === CanvasManager.ToolLine) {
                                    var point = Qt.vector3d(mouse.x, mouse.y, 1)
                                    canvasManager.finishDrawingLine(point)
                                }
                            }
                        }
                    }

                    WheelHandler {
                        id: scaling
                        acceptedModifiers: Qt.ControlModifier
                        acceptedDevices: PointerDevice.Mouse | PointerDevice.TouchPad

                        onWheel: (wheel) => {
                            const pLocal = Qt.point(wheel.x, wheel.y);
                            const before = canvasArea.mapToItem(workspace, pLocal);

                            const dir = (wheel.angleDelta.y || wheel.pixelDelta.y) > 0 ? 1 : -1;
                            let newScale = canvasArea.scale * (dir > 0 ? canvasArea.scaleFactor : 1 / canvasArea.scaleFactor);
                            newScale = Math.max(canvasArea.minScale, Math.min(canvasArea.maxScale, newScale));
                            if (newScale === canvasArea.scale)
                                return;

                            canvasArea.scale = newScale;

                            const after = canvasArea.mapToItem(workspace, pLocal);

                            canvasArea.x += before.x - after.x;
                            canvasArea.y += before.y - after.y;

                            wheel.accepted = true;
                        }
                    }

                    DragHandler {
                        id: moving
                        target: canvasArea
                        acceptedDevices: PointerDevice.Mouse | PointerDevice.TouchPad
                        acceptedButtons: Qt.MiddleButton
                        grabPermissions: PointerHandler.CanTakeOverFromAnything
                                        | PointerHandler.ApprovesTakeOverByAnything
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
