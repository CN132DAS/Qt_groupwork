#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QIcon>
#include <QInputDialog>
#include <QKeySequence>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QRect>
#include <QResizeEvent>
#include <QToolBar>
#include "mindmapviewer.h"
#include "savefile.h"
#include "setting.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    SaveFile* save_SF;
    MindMapViewer* viewer;
    Setting s;

    QMenuBar* menuBar;
    QToolBar* toolBar;

    QMenu* fileOp;
    QAction* newFile_A;
    QAction* openFile_A;
    QAction* save_A;
    QAction* saveAs_A;
    QAction* close_A;

    QMenu* edit;
    QAction* undo_A;
    QAction* redo_A;
    QAction* addText_A;
    QAction* addFile_A;

    void resizeEvent(QResizeEvent* event);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void newFile_clicked();
signals:
    void create_save(QString saveName_);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
