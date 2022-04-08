#include "headers/article.h"

Article::Article()
{

}

Article::Article(QString title, QString content) : title(title),
    content(content),
    modificationDateTime(QDateTime::currentDateTime())
{}

Article::Article(QString title, QString content, QDateTime modificationDateTime) : title(title),
    content(content),
    modificationDateTime(modificationDateTime)
{}

const QString Article::getTitle() const
{
    return title;
}

const QString Article::getContent() const
{
    return content;
}

const QDateTime Article::getModificationDateTime() const
{
    return modificationDateTime;
}
