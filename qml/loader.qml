import QtQuick
import QtQuick.Window
import QtQuick.Controls.Material
import QtQuick.Layouts

ApplicationWindow {
    id: root
    width: 1280
    height: 720
    visible: true
    title: "Blogger"

    ColumnLayout {
        spacing: 2
        anchors.fill: parent

        Header {
            id: myHeader
        }

        Loader {
            Layout.fillHeight: true
            Layout.fillWidth: true
            source: {
                switch (windowLoader.currentWindow) {
                    case 0: // show login.qml
                        return "qrc:/Blog/qml/login.qml";
                    case 1: // show main.qml
                        return "qrc:/Blog/qml/main.qml";
                    case 2: // show create.qml
                        return "qrc:/Blog/qml/create.qml";
                    default:
                        console.log("Current window unrecognized.");
                        return "qrc:/Blog/qml/main.qml";
                }
            }
        }

    }



}
