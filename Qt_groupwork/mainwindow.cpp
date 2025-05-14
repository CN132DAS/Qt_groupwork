#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(1100,700);
    setWindowTitle("MindMap");
    QIcon WindowIcon(":/assets/WindowIcon.png");
    setWindowIcon(WindowIcon);

    QMenuBar *menuBar_ = new QMenuBar(this);
    this->setMenuBar(menuBar_);

    QMenu* fileOp = new QMenu("文件",menuBar_);
    QMenu* newFile = new QMenu("新建",this);
    QMenu* openFile = new QMenu("打开",this);
    QMenu* save = new QMenu("保存",this);
    QMenu* saveAs = new QMenu("另存为",this);

    menuBar_->addMenu(fileOp);
    fileOp->addMenu(newFile);
    fileOp->addMenu(openFile);
    fileOp->addSeparator();
    fileOp->addMenu(save);
    fileOp->addMenu(saveAs);

    QIcon newFile_QI (":/assets/new-file.svg");
    QIcon openFile_QI(":/assets/file.svg");
    QIcon save_QI(":/assets/save.svg");
    QIcon saveAs_QI(":/assets/save-as.svg");

    newFile->setIcon(newFile_QI);
    openFile->setIcon(openFile_QI);
    save->setIcon(save_QI);
    saveAs->setIcon(saveAs_QI);

}

MainWindow::~MainWindow()
{
    delete ui;
}
