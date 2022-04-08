import QtQuick
import QtQuick.Window
import QtQuick.Controls.Material
import QtQuick.Layouts

Item {
    anchors.fill: parent

    ColumnLayout {
        anchors.topMargin: 10
        anchors.bottomMargin: 10
        anchors.fill: parent

        Rectangle {
            id: articleEditBg
            color: "#1d1d1d"
            radius: 5
            implicitWidth: Window.width < 800 ? parent.width : 0.6 * parent.width
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignHCenter

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 10

                Text {
                    text: "Create/edit article"
                    font.pixelSize: 20
                    color: "white"
                    opacity: 0.87
                    Layout.alignment: Qt.AlignHCenter
                }

                Text {
                    text: "Title"
                    color: "white"
                    opacity: 0.87
                }

                TextField {
                    id: createTitle
                    placeholderText: "Type title here"
                    color: "white"
                    background: Rectangle {
                        color: "#212121"
                        radius: 5
                    }
                    Layout.fillWidth: true
                    selectByMouse: true
                }

                Text {
                    text: "Content"
                    color: "white"
                    opacity: 0.87
                }

                ScrollView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    TextArea {
                        id: createContent
                        placeholderText: "Type content here"
                        wrapMode: TextEdit.Wrap
                        color: "white"
                        background: Rectangle {
                            color: "#212121"
                            radius: 5
                        }
                        selectByMouse: true
                    }
                }

                RowLayout {
                    Layout.alignment: Qt.AlignRight

                    Button {
                        text: "Discard"
                        Material.background: Material.primary
                        onClicked: windowLoader.currentWindow = 1
                    }

                    Button {
                        text: "Save"
                        Material.background: Material.primary
                        onClicked: {
                            articleModel.putArticle(user.email, createTitle.text, createContent.text);
                            articleModel.getArticles(user.email);
                            windowLoader.currentWindow = 1;
                        }
                    }
                }
            }

        }

    }



}
