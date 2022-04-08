import QtQuick
import QtQuick.Window
import QtQuick.Controls.Material
import QtQuick.Layouts

Item {
    anchors.fill: parent

    RowLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20

        Rectangle {
            color: "#1d1d1d"
            radius: 5
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignCenter

            ColumnLayout {
                spacing: 8
                width: Window.width < 800 ? 0.9 * parent.width : 0.6 * parent.width
                anchors.centerIn: parent

                Text {
                    text: "Login"
                    font.pixelSize: 20
                    color: "white"
                    opacity: 0.87
                    Layout.alignment: Qt.AlignHCenter
                }

                Text {
                    text: "Email"
                    color: "white"
                    opacity: 0.87
                }

                TextField {
                    id: loginEmail
                    Layout.fillWidth: true
                    placeholderText: "Type email here"
                    color: "white"
                    background: Rectangle {
                        width: parent.width
                        color: "#212121"
                        radius: 5
                    }
                    selectByMouse: true
                }

                Text {
                    text: "Password"
                    color: "white"
                    opacity: 0.87
                }

                TextField {
                    id: loginPassword
                    Layout.fillWidth: true
                    placeholderText: "Type password here"
                    color: "white"
                    background: Rectangle {
                        color: "#212121"
                        radius: 5
                    }
                    selectByMouse: true
                }

                Button {
                    Material.background: Material.primary
                    width: 100
                    height: 50
                    text: "Login"
                    onClicked: {
                        if(user.authenticate(loginEmail.text, loginPassword.text)) {
                            articleModel.getArticles(user.email);
                            windowLoader.currentWindow = 1;
                            console.log("Logged in successfully.");
                        } else {
                            console.log("Login or password incorrect.");
                            console.log("Given login:" + loginEmail.text);
                            console.log("Given password:" + loginPassword.text);
                        }
                    }
                }
            }
        }

        Rectangle {
            color: "#1d1d1d"
            radius: 5
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignCenter

            ColumnLayout {
                spacing: 8
                width: Window.width < 800 ? 0.9 * parent.width : 0.6 * parent.width
                anchors.centerIn: parent

                Text {
                    text: "Register"
                    font.pixelSize: 20
                    color: "white"
                    opacity: 0.87
                    Layout.alignment: Qt.AlignHCenter
                }

                Text {
                    text: "Email"
                    color: "white"
                    opacity: 0.87
                }

                TextField {
                    id: registerEmail
                    Layout.fillWidth: true
                    placeholderText: "Type email here"
                    color: "white"
                    background: Rectangle {
                        width: parent.width
                        color: "#212121"
                        radius: 5
                    }
                    selectByMouse: true
                }


                Text {
                    text: "You can use letters, numbers & periods"
                    color: "#636363"
                }

                Text {
                    text: "Blog name"
                    color: "white"
                    opacity: 0.87
                }

                TextField {
                    id: registerBlogName
                    Layout.fillWidth: true
                    placeholderText: "Type blog name here"
                    color: "white"
                    background: Rectangle {
                        color: "#212121"
                        radius: 5
                    }
                    selectByMouse: true
                }

                Text {
                    text: "Characters: " + registerBlogName.length + "/50"
                    color: "#636363"
                }

                Text {
                    text: "Password"
                    color: "white"
                    opacity: 0.87
                }

                TextField {
                    id: registerPassword
                    Layout.fillWidth: true
                    placeholderText: "Type password here"
                    color: "white"
                    background: Rectangle {
                        color: "#212121"
                        radius: 5
                    }
                    selectByMouse: true
                }

                Text {
                    text: "Use 8 or more characters"
                    color: "#636363"
                }

                Text {
                    text: "Repeat password"
                    color: "white"
                    opacity: 0.87
                }

                TextField {
                    id: registerPasswordRepeated
                    Layout.fillWidth: true
                    placeholderText: "Type password once again"
                    color: "white"
                    background: Rectangle {
                        color: "#212121"
                        radius: 5
                    }
                    selectByMouse: true
                }

                Button {
                    Material.background: Material.primary
                    width: 100
                    height: 50
                    text: "Register"
                    onClicked: {
                        if(user.createAccount(registerEmail.text, registerBlogName.text, registerPassword.text)) {
                            windowLoader.currentWindow = 1
                        }

                    }
                }
            }
        }

    }

}
