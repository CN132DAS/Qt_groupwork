#include <QApplication>
#include <QDir>
#include "mainwindow.h"
QString _saveFolderPath_ = "";
QString _savePath_ = "";
QString _saveTempPath_ = "";
QString _saveName_ = "";
QString _state_ = "";
bool _operation_ = false;

void init()
{
    QDir current = QDir::current();
    _saveFolderPath_ = current.path()+"/save";
    if(!QDir(_saveFolderPath_).exists())
        QDir().mkdir(_saveFolderPath_);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    init();
    MainWindow w;
    w.show();
    return a.exec();
}
