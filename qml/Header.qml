import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls.Material

Rectangle {
    color: "#1d1d1d"
//    border.color: "gray"
        /*Qt.lighter("#121212")*/
    implicitHeight: headerBlogName.height
    Layout.fillWidth: true

    RowLayout {
        width: parent.width

        RowLayout {
            Text {
                id: headerBlogName

                text: user.blogName;
                font.pixelSize: 25
                padding: 10
                color: 'white'

            }
        }

        RowLayout {
                Layout.alignment: Qt.AlignRight

                Text {
                    text: user.email
                    color: 'white'
                }

                Button {
                    text: "Log out"
                    Material.background: Material.primary
                    opacity: {
                        if (user.email === "Logged out") {
                            return 0.5;
                        } else {
                            return 1;
                        }
                    }

                    Layout.rightMargin: 10
                    onClicked: {
                        user.logout();
                        windowLoader.currentWindow = 0;
                    }
                }
        }
    }

}
