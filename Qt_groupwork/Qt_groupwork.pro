QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QT += network

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aimodule.cpp \
    connection.cpp \
    editabletext.cpp \
    filecontent.cpp \
    function.cpp \
    main.cpp \
    mainwindow.cpp \
    mygraphicsobject.cpp \
    picturecontent.cpp \
    mindmapviewer.cpp \
    savefile.cpp

HEADERS += \
    aimodule.h \
    connection.h \
    editabletext.h \
    filecontent.h \
    function.h \
    mainwindow.h \
    mygraphicsobject.h \
    picturecontent.h \
    mindmapviewer.h \
    savefile.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource.qrc
