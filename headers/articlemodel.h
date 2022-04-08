#ifndef ARTICLEMODEL_H
#define ARTICLEMODEL_H

#include <QAbstractListModel>
#include <QJsonArray>
#include <QJSValue>

#include "article.h"
#include "user.h"

class ArticleModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit ArticleModel(QObject *parent = nullptr);
//    explicit ArticleModel(QVector<Article> articles, QObject *parent = nullptr);
//    explicit ArticleModel(QJsonArray jsonArray, QObject *parent = nullptr);
    enum {
        TitleRole,
        ContentRole,
        ModificationDateTimeRole
    };

    // necessary for qml QAbstractListModel:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

public slots:
    bool getArticles(QString email);
    bool putArticle(QString email, QString title, QString content);
    bool deleteArticle(QString email);
    void enableEditMode(QString modificationDateTimeOfArticleToEdit, QString titleOfArticleToEdit);
    void disableEditMode();
//    void putExampleArticles();


protected:
    // necessary for qml QAbstractListModel:
    QHash<int, QByteArray> roleNames() const override;

private:
    void setArticles(QVector<Article> articles);
    void addArticle(Article article);
    void replaceArticle(Article newArticle, QString modificationDateTime);
    void deleteArticleLocal(QString modificationDateTime);

    QVector<Article> articles;
    bool editMode = false;
    QString titleOfArticleToEdit;
    QString modificationDateTimeOfArticleToEdit;

};

#endif // ARTICLEMODEL_H
