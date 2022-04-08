#include "headers/articlemodel.h"
#include "QDate"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

ArticleModel::ArticleModel(QObject *parent)
{
}

// necessary for qml QAbstractListModel:
int ArticleModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return articles.size();
}

// necessary for qml QAbstractListModel:
QVariant ArticleModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const Article article = articles.at(index.row());

    switch(role) {
        case TitleRole:
            return QVariant(article.getTitle());
        case ContentRole:
            return QVariant(article.getContent());
        case ModificationDateTimeRole:
            return QVariant(article.getModificationDateTime());
    }
    return QVariant();
}


bool ArticleModel::getArticles(QString email)
{
    QFile file(QStringLiteral("./data.json"));
    if (!file.open(QIODeviceBase::ReadOnly)) {
        qWarning("getArticles(): Couldn't open data file.");
        return false;
    }

    QByteArray data = file.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(data));

    QJsonArray blogs = loadDoc["blogs"].toArray();
    for (int i = 0; i < blogs.size(); i++) {
        QJsonObject blog = blogs[i].toObject();
        if (blog.contains("owner") && blog["owner"].isString()
                && blog["owner"].toString() == email) {
            if (blog.contains("articles") && blog["articles"].isArray()) {
                QJsonArray jsonArticles = blog["articles"].toArray();
                this->articles.clear();
                for (int i = 0; i < jsonArticles.size(); i++) {
                    QJsonObject jsonArticle = jsonArticles[i].toObject();
                    this->addArticle(Article(jsonArticle["title"].toString(), jsonArticle["content"].toString(),
                            QDateTime::fromString(jsonArticle["modificationDateTime"].toString())));
                }
                file.close();
                return true;
            } else {
                QTextStream(stdout) << "getArticles(): User does not have any articles" << "\n";
                this->setArticles(QVector<Article>());
                file.close();
                return true;
            }
        }
    }
    file.close();
    return false;
}

bool ArticleModel::putArticle(QString email, QString title, QString content)
{
    qWarning("putArticle() invoked");

    QFile file(QStringLiteral("./data.json"));
    if (!file.open(QIODeviceBase::ReadWrite)) {
        qWarning("putArticle(): Couldn't open data file.");
        return false;
    }

    QByteArray data = file.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(data));

    QJsonArray blogs = loadDoc["blogs"].toArray();
    for (int i = 0; i < blogs.size(); i++) {
        QJsonObject blog = blogs[i].toObject();
        if (blog.contains("owner") && blog["owner"].isString()
                && blog["owner"].toString() == email) {
            if (blog.contains("articles") && blog["articles"].isArray()) {
                QJsonArray jsonArticles = blog["articles"].toArray();
                Article newArticle(title, content);
                QJsonObject newJsonArticle {
                    {"title", newArticle.getTitle()},
                    {"content", newArticle.getContent()},
                    {"modificationDateTime", newArticle.getModificationDateTime().toString()}
                };
                if (this->editMode) {
                QTextStream(stdout) << "putArticle(): Edit mode" << "\n";
                  for (int j = 0; j < jsonArticles.size(); j++) {
                      QJsonObject currentJsonArticle = jsonArticles[j].toObject();
                     if (currentJsonArticle["title"].toString() == this->titleOfArticleToEdit) {
                        jsonArticles.replace(j, newJsonArticle);

                     QJsonObject newBlog {
                         {"blogName", blog["name"].toString()},
                         {"owner", blog["owner"].toString()},
                         {"articles", jsonArticles}
                     };
                     blogs.replace(i, newBlog);

                     QJsonObject docObject = loadDoc.object();
                     docObject.insert("blogs", blogs);

                     file.resize(0);
                     file.write(QJsonDocument(docObject).toJson());
                     file.close();

                     this->replaceArticle(newArticle, this->titleOfArticleToEdit);
                     this->disableEditMode();
                     file.close();
                     return true;
                     }
                  }
                } else {
                    jsonArticles.append(newJsonArticle);
                    QJsonObject newBlog {
                        {"blogName", blog["name"].toString()},
                        {"owner", blog["owner"].toString()},
                        {"articles", jsonArticles}
                    };
                    blogs.replace(i, newBlog);
                    QJsonObject docObject = loadDoc.object();
                    docObject.insert("blogs", blogs);

                    file.resize(0);
                    file.write(QJsonDocument(docObject).toJson());
                    file.close();

                    this->addArticle(newArticle);
                    file.close();
                    return true;
                }

            } else {
                QTextStream(stdout) << "getArticles(): User does not have any articles" << "\n";
                this->setArticles(QVector<Article>());
                file.close();
                return true;
            }
        }
    }
    return false;
}

bool ArticleModel::deleteArticle(QString email)
{
    qWarning("deleteArticle() invoked");

    QFile file(QStringLiteral("./data.json"));
    if (!file.open(QIODeviceBase::ReadWrite)) {
        qWarning("deleteArticle(): Couldn't open data file.");
        return false;
    }

    QByteArray data = file.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(data));

    QJsonArray blogs = loadDoc["blogs"].toArray();
    for (int i = 0; i < blogs.size(); i++) {
        QJsonObject blog = blogs[i].toObject();
        if (blog.contains("owner") && blog["owner"].isString()
                && blog["owner"].toString() == email) {
            if (blog.contains("articles") && blog["articles"].isArray()) {
                QJsonArray jsonArticles = blog["articles"].toArray();
                  for (int j = 0; j < jsonArticles.size(); j++) {
                      QJsonObject currentJsonArticle = jsonArticles[j].toObject();
                      QTextStream(stdout) << "currentJsonArticle title" << currentJsonArticle["title"].toString() << "\n";
                      QTextStream(stdout) << "this->modificationDateTimeOfArticleToEdit():" << this->titleOfArticleToEdit << "\n";
                     if (currentJsonArticle["title"].toString() == this->titleOfArticleToEdit) {
                         jsonArticles.removeAt(j);

                         QJsonObject newBlog {
                             {"blogName", blog["name"].toString()},
                             {"owner", blog["owner"].toString()},
                             {"articles", jsonArticles}
                         };
                        blogs.replace(i, newBlog);
     //                     blogs.insert(i, newBlog);

                        QJsonObject docObject = loadDoc.object();
                        docObject.insert("blogs", blogs);

                        file.resize(0);
                        file.write(QJsonDocument(docObject).toJson());
                        file.close();

                        this->deleteArticleLocal(this->titleOfArticleToEdit);
                        this->disableEditMode();
                        file.close();
                        return true;
                    }
                }
            } else {
                QTextStream(stdout) << "getArticles(): User does not have any articles" << "\n";
                this->setArticles(QVector<Article>());
                file.close();
                return true;
            }
        }
    }
    return false;
}

void ArticleModel::enableEditMode(QString modificationDateTimeOfArticleToEdit, QString titleOfArticleToEdit)
{
    this->editMode = true;
    this->modificationDateTimeOfArticleToEdit = modificationDateTimeOfArticleToEdit;
    this->titleOfArticleToEdit = titleOfArticleToEdit;
}

void ArticleModel::disableEditMode()
{
    this->editMode = false;
}

// necessary for qml QAbstractListModel:
QHash<int, QByteArray> ArticleModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TitleRole] = "title";
    roles[ContentRole] = "content";
    roles[ModificationDateTimeRole] = "modificationDateTime";
    return roles;
}

void ArticleModel::setArticles(QVector<Article> articles)
{
    this->articles = articles;
}

void ArticleModel::addArticle(Article article)
{
    QTextStream(stdout) << "addArticle() title: " << article.getTitle() << "\n";
    beginInsertRows({}, articles.size(), articles.size());
    this->articles.append(article);
    endInsertRows();
}

void ArticleModel::replaceArticle(Article newArticle, QString title)
{
    for (int i = 0; i < this->articles.size(); i++) {
        if (this->articles.at(i).getTitle() == title) {
            this->articles.replace(i, newArticle);
        }
    }
}

void ArticleModel::deleteArticleLocal(QString title)
{
    for (int i = 0; i < this->articles.size(); i++) {
        if (this->articles.at(i).getTitle() == title) {
            this->articles.remove(i);
        }
    }
}

//void ArticleModel::putExampleArticles()
//{
//    articles.push_back(Article("New EU law could require iMessage and WhatsApp to work with other, smaller platforms", "Lorem ipsum lso"));
//    articles.push_back(Article("New EU law could require iMessage and WhatsApp to work with other, smaller platforms", "Lorem ipsum lso"));
//    articles.push_back(Article("New EU law could require iMessage and WhatsApp to work with other, smaller platforms", "Lorem ipsum lso"));
//    articles.push_back(Article("New EU law could require iMessage and WhatsApp to work with other, smaller platforms", "Lorem ipsum lso"));
//    articles.push_back(Article("New EU law could require iMessage and WhatsApp to work with other, smaller platforms", "Lorem ipsum lso"));
//    articles.push_back(Article("New EU law could require iMessage and WhatsApp to work with other, smaller platforms", "Lorem ipsum lso"));
//    articles.push_back(Article("New EU law could require iMessage and WhatsApp to work with other, smaller platforms", "Lorem ipsum lso"));
//    articles.push_back(Article("New EU law could require iMessage and WhatsApp to work with other, smaller platforms", "Lorem ipsum lso"));
//    articles.push_back(Article("New EU law could require iMessage and WhatsApp to work with other, smaller platforms", "Lorem ipsum lso"));
//    articles.push_back(Article("New EU law could require iMessage and WhatsApp to work with other, smaller platforms", "Lorem ipsum lso"));
//}
