#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

#include "headers/filehandler.h"

FileHandler::FileHandler()
{

}

QJsonArray FileHandler::loadUsers()
{
    QFile file(QStringLiteral(":/data.json"));
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open data file.");
        return QJsonArray();
    }

    QByteArray saveData = file.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    return loadDoc["users"].toArray();
}
