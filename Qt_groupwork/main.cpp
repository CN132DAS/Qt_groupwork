#include <QDir>
#include "mainwindow.h"
#include "savefile.h"

QString savePath;

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
    savePath = current.path()+"/save";
    qDebug()<<"save path is: "<<savePath;
    qDebug()<<"is it right?";
    if(!QDir(savePath).exists())
        QDir(savePath).mkdir(savePath);
}
