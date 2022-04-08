#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

#include "headers/user.h"
#include "headers/filehandler.h"

User::User(QObject *parent)
    : QObject{parent}
{

}

bool User::authenticate(QString email, QString password)
{

    QFile file(QStringLiteral("./data.json"));
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open data file.");
        return false;
    }
    QByteArray saveData = file.readAll();
    file.close();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    QJsonArray users = loadDoc["users"].toArray();
    QTextStream(stdout) << "Login attempt with credentials:" << email << password << "\n";

    for (int i = 0; i < users.size(); i++) {
        QJsonObject user = users[i].toObject();
        if (user.contains("email") && user["email"].isString()
                && user.contains("password") && user["password"].isString()) {
            if (user["email"].toString() == email && user["password"].toString() == password) {
                QTextStream(stdout) << "Authenticated user with email:" << user["email"].toString() << "\n";
                QTextStream(stdout) << "Password:" << user["password"].toString() << "\n";

                QJsonArray blogs = loadDoc["blogs"].toArray();
                for (int i = 0; i < blogs.size(); i++) {
                    QJsonObject blog = blogs[i].toObject();
                    if (blog.contains("owner") && blog["owner"].isString()
                            && blog["owner"].toString() == email && blog.contains("blogName")
                            && blog["blogName"].isString()) {
                        QString blogName = blog["blogName"].toString();
                        this->set(true, email, blogName);
                        return true;
                    }
                }

            }
        }
    }
    return false;
}

bool User::isAuthenticated()
{
    return this->authenticated;
}

QString User::getAuthenticatedEmail() const
{
    if (this->authenticated) {
        QTextStream(stdout) << "getAuthenticatedEmail():" << this->email << "\n";
        return this->email;
    } else {
        QTextStream(stdout) << "getAuthenticatedEmail(): failed, this->authenticated=false, this->email=" << this->email << "\n";
        return "Logged out";
    }
}

QString User::getBlogName()
{
    QTextStream(stdout) << "getBlogName():" << this->blogName << "\n";
    return this->blogName;
}

void User::logout()
{
    this->set(false);
}

bool User::createAccount(QString email, QString blogName, QString password)
{
    qWarning("createAccount() invoked");

    QFile file(QStringLiteral("./data.json"));
    if (!file.open(QIODeviceBase::ReadWrite)) {
        qWarning("createAccount(): Couldn't open data file.");
        return false;
    }

    QByteArray data = file.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(data));

    QJsonArray users = loadDoc["users"].toArray();
    for (int i = 0; i < users.size(); i++) {
        QJsonObject user = users[i].toObject();
        if (user.contains("email") && user["email"].isString()
                && user.contains("password") && user["password"].isString()) {
            if (user["email"].toString() == email) {
                QTextStream(stdout) << "User with such an email already exists:" << user["email"].toString() << "\n";
                file.close();
                return false;
            }
        }
    }

    QJsonArray blogs = loadDoc["blogs"].toArray();
    for (int i = 0; i < blogs.size(); i++) {
        QJsonObject blog = blogs[i].toObject();
        if (blog.contains("blogName") && blog["blogName"].isString()
                && blog.contains("owner") && blog["owner"].isString()) {
            if (blog["blogName"].toString() == blogName) {
                QTextStream(stdout) << "Blog with such a name already exists:" << blog["blogName"].toString() << "\n";
                file.close();
                return false;
            }
        }
    }

    QJsonObject newUser {
        {"email", email},
        {"password", password}
    };
    users.append(newUser);

    QJsonObject newBlog {
        {"blogName", blogName},
        {"owner", email}
    };
    blogs.append(newBlog);

    QJsonObject docObject = loadDoc.object();
    docObject.insert("users", users);
    docObject.insert("blogs", blogs);

    file.resize(0);
    file.write(QJsonDocument(docObject).toJson());
    file.close();

    this->set(true, email, blogName);
    return true;

}

// private setter function
void User::set(bool authenticated, QString email, QString blogName)
{
    if (this->authenticated != authenticated) {
        this->authenticated = authenticated;
        this->email= email;
        this->blogName = blogName;
        emit this->dataChanged(this->email, this->blogName);
    }
}
