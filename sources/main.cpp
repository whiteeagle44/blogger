#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>

#include "headers/articlemodel.h"
#include "headers/windowloader.h"
#include "headers/user.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    ArticleModel articleModel;
//    articleModel.putExampleArticles();

    WindowLoader windowLoader;

    User user;
//    user.authenticate("john@gmail.com", "abcdefgh");
//    QTextStream(stdout) << "Authenticated?: " << user.isAuthenticated()<< "\n";
//    user.authenticate("john@gmail.com", "abcdefghij");
//    QTextStream(stdout) << "Authenticated?: " << user.isAuthenticated()<< "\n";


    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("articleModel", QVariant::fromValue(&articleModel));
    engine.rootContext()->setContextProperty("windowLoader", &windowLoader);
    engine.rootContext()->setContextProperty("user", QVariant::fromValue(&user));

//    const QUrl url(u"qrc:/Blog/main.qml"_qs);
    const QUrl url(QStringLiteral("qrc:/Blog/qml/loader.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);



    return app.exec();
}
