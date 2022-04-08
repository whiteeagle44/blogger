#ifndef ARTICLE_H
#define ARTICLE_H

#include <QObject>
#include <QDate>

class Article
{
public:
    Article();
    Article(QString title, QString content);
    Article(QString title, QString content, QDateTime modificationDateTime);
    const QString getTitle() const;
    const QString getContent() const;
    const QDateTime getModificationDateTime() const;

private:
    QString title;
    QString content;
    QDateTime modificationDateTime;
};

#endif // ARTICLE_H
