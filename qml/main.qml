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

    menuBar: MenuBar {
        Menu {
            title: "File"

            Action {
                text: "New"
                onTriggered: {
                    console.log("New file action triggered");
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
} 
