#include <QDir>
#include "mainwindow.h"
QString _savePath_ = "";
QString _saveName_ = "";
QString _state_ = "";

#include <QApplication>

// QString appDirPath;

void init();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    init();
    MainWindow w;
    w.show();
    return a.exec();
}

void init()
{
    QDir current = QDir::current();
    current.cd("..");
    current.cd("..");
    _savePath_ = current.path()+"/save";
    qDebug()<<"save path is: "<<_savePath_;
    qDebug()<<"is it right?";
    if(!QDir(_savePath_).exists())
        QDir(_savePath_).mkdir(_savePath_);
}
