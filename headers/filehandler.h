#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QJsonArray>

class FileHandler
{
public:
    FileHandler();
    static QJsonArray loadUsers();
};

#endif // FILEHANDLER_H
