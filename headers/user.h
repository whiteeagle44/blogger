#ifndef USER_H
#define USER_H

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QString>

class User : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString email READ getAuthenticatedEmail NOTIFY dataChanged)
    Q_PROPERTY(QString blogName READ getBlogName NOTIFY dataChanged)
public:
    explicit User(QObject *parent = nullptr);
    void write(QJsonArray jsonArray) const;


public slots:
    bool authenticate(QString email, QString password);
    bool isAuthenticated();
    QString getAuthenticatedEmail() const;
    QString getBlogName();
    void logout();

    bool createAccount(QString email, QString blogName, QString password);

signals:
    void dataChanged(QString email, QString blogName);

private:
    void set(bool authenticated, QString email = "Logged out", QString blogName = "Blogger");

    QString email = "Logged out";
    QString blogName = "Blogger";
    bool authenticated = false;
};

#endif // USER_H
