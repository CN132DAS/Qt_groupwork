#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QIcon>
#include <QAction>
#include <QKeySequence>
#include <QFile>
#include <QResizeEvent>
#include <QInputDialog>
#include <QDebug>
#include <QToolBar>
#include <QGridLayout>
#include <QRect>
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
