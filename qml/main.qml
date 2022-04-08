import QtQuick
import QtQuick.Window
import QtQuick.Controls.Material
import QtQuick.Layouts

ColumnLayout {

        ToolBar {
            id: myToolbar
            Layout.fillWidth: true
            position: ToolBar.Header
            width: parent.width

            background: Rectangle {
                anchors.fill: parent
                color: "#1d1d1d"
            }

            RowLayout {
                width: parent.width * 0.4
                anchors.horizontalCenter: parent.horizontalCenter

                ToolButton {
                    id: create
                    text: "Create"
                    Layout.fillWidth: true
                    opacity: 0.87
                    onClicked: {
                        articleModel.disableEditMode();
                        onClicked: windowLoader.currentWindow = 2
                    }
                }

                ToolButton {
                    text: "View"
                    Layout.fillWidth: true
                    opacity: 0.38
                }

                ToolButton {
                    text: "Edit"
                    Layout.fillWidth: true
                    onClicked: {
                        console.log(articles.currentItem.children[1].text);
                        articleModel.enableEditMode(articles.currentItem.children[1].text, articles.currentItem.children[0  ].text);
                        return windowLoader.currentWindow = 2;
                    }
                    opacity: 0.87
                }

                ToolButton {
                    text: "Delete"
                    Layout.fillWidth: true
                    opacity: 0.87
                    onClicked: {
                        articleModel.enableEditMode(articles.currentItem.children[1].text, articles.currentItem.children[0].text);
                        articleModel.deleteArticle(user.email);
                        articleModel.getArticles(user.email);
                    }
                }
            }
        }

        ColumnLayout {

            ListView {
                id: articles

                clip: true
                topMargin: 10
                bottomMargin: 10
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter

                spacing: 10
                highlight: Rectangle { color: "#00000000"; border.color: "white"; z:3; radius: 5; anchors.horizontalCenter: parent.horizontalCenter}
                highlightMoveDuration: 1
                focus: true
                model: articleModel
                delegate: Rectangle {
                    id: myArticle

                    height: articleTitle.height
                    width: articles.width * 0.8
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "#1d1d1d"
    //                border.color: ListView.isCurrentItem ? "white" : "#1d1d1d";
                    radius: 5

                    required property string title
                    required property date modificationDateTime

                            Text {
                                id: articleTitle

                                padding: 20
                                font.pixelSize: 18
                                anchors.verticalCenter: parent.verticalCenter
                                color: "white"
                                text: title
                                opacity: 0.87
                                wrapMode: Text.Wrap
                                width: parent.width - articleModifiedAt.width
                            }

                            Text {
                                id: articleModifiedAt

                                z: 3
                                padding: 20
                                font.pixelSize: 18
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                color: "white"
                                opacity: 0.6
                                text: modificationDateTime
                            }
                }
            }
        }

}
