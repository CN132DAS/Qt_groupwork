#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(1100,700);
    this->setStyleSheet("MainWindow{background-color:#F9F9F9;}");
    setWindowTitle("MindMap");
    QIcon WindowIcon(":/assets/WindowIcon.png");
    setWindowIcon(WindowIcon);
    QFile theme(":/assets/theme.qss");
    theme.open(QIODevice::ReadOnly);

    layout = new QGridLayout();


    menuBar_ = new QMenuBar(this);
    this->setMenuBar(menuBar_);
    menuBar_->setStyleSheet("QMenuBar{background-color:#CDDEEB;}");

    fileOp = new QMenu(QStringLiteral("文件(&F)"),this);

    newFile_A = new QAction(QStringLiteral("新建(&N)"),this);
    openFile_A = new QAction(QStringLiteral("打开(&O)"),this);
    save_A = new QAction(QStringLiteral("保存(&S)"),this);
    saveAs_A = new QAction(QStringLiteral("另存为(&A)"),this);

    menuBar_->addMenu(fileOp);
    fileOp->addAction(newFile_A);
    fileOp->addAction(openFile_A);
    fileOp->addSeparator();
    fileOp->addAction(save_A);
    fileOp->addAction(saveAs_A);

    QIcon newFile_QI (":/assets/new-file.svg");
    QIcon openFile_QI(":/assets/file.svg");
    QIcon save_QI(":/assets/save.svg");
    QIcon saveAs_QI(":/assets/save-as.svg");

    newFile_A->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_N));
    openFile_A->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_O));
    save_A->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_S));
    saveAs_A->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_A));

    newFile_A->setIcon(newFile_QI);
    openFile_A->setIcon(openFile_QI);
    save_A->setIcon(save_QI);
    saveAs_A->setIcon(saveAs_QI);

    connect(newFile_A,&QAction::triggered,
            this,&MainWindow::newFile_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newFile_clicked(){
    bool ok{};
    QString saveName;
    while(1){
        saveName = QInputDialog::getText(this,"新建文件","名称",QLineEdit::Normal,QString("新建文件"),&ok);
        if(ok&&!saveName.isEmpty())
            break;
    }
    extern SaveFile* save_S;
    save_S = new SaveFile;
    connect(this,&MainWindow::save_created,
            save_S,&SaveFile::create_save);
    emit save_created(saveName,this);
}
