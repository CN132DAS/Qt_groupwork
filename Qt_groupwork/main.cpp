#include <QDir>
#include "mainwindow.h"
QString savePath_ = "";
QString saveName_ = "";
QIcon fileIcon(":/assets/file.svg");

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
    savePath_ = current.path()+"/save";
    qDebug()<<"save path is: "<<savePath_;
    qDebug()<<"is it right?";
    if(!QDir(savePath_).exists())
        QDir(savePath_).mkdir(savePath_);
}
