#include "headers/windowloader.h"
#include <QDebug>

WindowLoader::WindowLoader(QObject *parent)
    : QObject{parent}
{
}

WindowLoader::CurrentWindow WindowLoader::getCurrentWindow() const
{
    return currentWindow;
}

void WindowLoader::setCurrentWindow(WindowLoader::CurrentWindow currentWindow)
{
    if (currentWindow != this->currentWindow) {
        this->currentWindow = currentWindow;
        emit currentWindowChanged();
    }
}
