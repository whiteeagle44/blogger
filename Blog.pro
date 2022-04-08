QT += quick quickcontrols2

SOURCES += \
        sources/article.cpp \
        sources/articlemodel.cpp \
        sources/filehandler.cpp \
        sources/main.cpp \
        sources/user.cpp \
        sources/windowloader.cpp

resources.files += qml/main.qml qml/login.qml qml/Header.qml qml/create.qml qml/loader.qml
resources.prefix = /$${TARGET}/
RESOURCES += resources \
    qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    qml/Header.qml \
    qml/README.md \
    qml/create.qml \
    qml/data.json \
    qml/loader.qml \
    qml/login.qml \
    qml/main.qml \

HEADERS += \
    headers/article.h \
    headers/articlemodel.h \
    headers/filehandler.h \
    headers/user.h \
    headers/windowloader.h

ICON = icon/Blog.png
macos: ICON = icon/Blog.icns
win32: RC_FILE = icon/Blog.rc

