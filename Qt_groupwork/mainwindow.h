#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QIcon>
#include <QAction>
#include <QKeySequence>
#include <QFile>
#include <QInputDialog>
#include <QDebug>
#include <QGridLayout>
#include "savefile.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QMenuBar* menuBar_;

    QMenu* fileOp;
    QAction* newFile_A;
    QAction* openFile_A;
    QAction* save_A;
    QAction* saveAs_A;
    QGridLayout* layout;


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void newFile_clicked();
signals:
    void save_created(QString saveName_,QWidget *parent);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
