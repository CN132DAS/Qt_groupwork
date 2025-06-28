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
#include "AImodule.h"
#include "mindmapviewer.h"
#include "savefile.h"

extern QString _saveName_,_saveFolderPath_,_saveTempPath_,_savePath_,_state_;
extern bool _operation_;

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
    AImodule* AI; 

    QMenuBar* menuBar;

    QMenu* fileOp;
    QAction* newSave_A;
    QAction* openSave_A;
    QAction* save_A;
    QAction* saveAs_A;
    QAction* close_A;
    QAction* refresh_A;

    QMenu* edit;
    QAction* undo_A;
    QAction* redo_A;

    QToolBar* toolBar;

    QPushButton* addText_PB;
    QPushButton* addPic_PB;
    QPushButton* addFile_PB;
    QPushButton* addCon_PB;
    QPushButton* edit_PB;
    QPushButton* drag_PB;
    QPushButton* AI_PB;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void unfreeze(bool unfreeze);
public slots:
    void untoggle_AI_PB();
    void toggle_addText_PB(bool checked);
    void toggle_addPic_PB(bool checked);
    void toggle_addFile_PB(bool checked);
    void toggle_addCon_PB(bool checked);
    void toggle_edit_PB(bool checked);
    void toggle_drag_PB(bool checked);
    void toggle_AI_PB(bool checked);
    void only_toggle_one_button();
    void new_save();
    void save();
    void load_save();
    void close_save();
    void refresh();
signals:
    void state_changed();
    void unfreeze_state_changed(bool unfreeze);
private:
    Ui::MainWindow *ui;
public:
    void resizeEvent(QResizeEvent* event) override;
    void closeEvent(QCloseEvent *event) override;
};
#endif // MAINWINDOW_H
