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
#include <QMouseEvent>
#include <QPushButton>
#include <QRect>
#include <QResizeEvent>
#include <QToolBar>
#include "mindmapviewer.h"
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
    SaveFile* save_SF;
    MindMapViewer* viewer;

    QMenuBar* menuBar;

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
    QAction* addPic_A;
    QAction* addFile_A;

    QToolBar* toolBar;

    QPushButton* addText_PB;
    QPushButton* addPic_PB;
    QPushButton* addFile_PB;
    QPushButton* drag_PB;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    void close_file();
    void unfreeze(bool unfreeze);
public slots:
    void get_newFile_name();
    void only_toggle_addText_PB(bool checked);
    void only_toggle_addPic_PB(bool checked);
    void only_toggle_addFile_PB(bool checked);
    void only_toggle_drag_PB(bool checked);
    void set_text_checked();
    void set_pic_checked();
    void set_file_checked();
    void load();
signals:
    void unfreeze_state_changed(bool unfreeze);
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
