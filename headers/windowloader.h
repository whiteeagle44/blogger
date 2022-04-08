#ifndef WINDOWLOADER_H
#define WINDOWLOADER_H

#include <QObject>

class WindowLoader : public QObject
{
    Q_OBJECT
    Q_PROPERTY(CurrentWindow currentWindow READ getCurrentWindow WRITE setCurrentWindow NOTIFY currentWindowChanged)
public:
    explicit WindowLoader(QObject *parent = nullptr);

    enum CurrentWindow {
        Login, Main, Create
    };
    Q_ENUM(CurrentWindow)

    CurrentWindow getCurrentWindow() const;



public slots:
    void setCurrentWindow(WindowLoader::CurrentWindow currentWindow);

signals:
    void currentWindowChanged();

private:
    CurrentWindow currentWindow = CurrentWindow::Login;
};

#endif // WINDOWLOADER_H
