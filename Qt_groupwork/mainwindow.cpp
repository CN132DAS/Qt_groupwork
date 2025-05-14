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

    QMenu* fileOp = new QMenu(QStringLiteral("文件(&F)"),this);
    QAction* newFile = new QAction(QStringLiteral("新建(&N)"),this);
    QAction* openFile = new QAction(QStringLiteral("打开(&O)"),this);
    QAction* save = new QAction(QStringLiteral("保存(&S)"),this);
    QAction* saveAs = new QAction(QStringLiteral("另存为(&A)"),this);

    menuBar_->addMenu(fileOp);
    fileOp->addAction(newFile);
    fileOp->addAction(openFile);
    fileOp->addSeparator();
    fileOp->addAction(save);
    fileOp->addAction(saveAs);

    QIcon newFile_QI (":/assets/new-file.svg");
    QIcon openFile_QI(":/assets/file.svg");
    QIcon save_QI(":/assets/save.svg");
    QIcon saveAs_QI(":/assets/save-as.svg");

    newFile->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_N));
    openFile->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_O));
    save->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_S));
    saveAs->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_A));

    newFile->setIcon(newFile_QI);
    openFile->setIcon(openFile_QI);
    save->setIcon(save_QI);
    saveAs->setIcon(saveAs_QI);

}

MainWindow::~MainWindow()
{
    delete ui;
}
