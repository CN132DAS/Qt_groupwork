#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFile theme(":/assets/theme.qss");
    theme.open(QFile::ReadOnly);
    this->setStyleSheet(theme.readAll());
    theme.close();
    this->resize(1100,700);
    int h = this->height();
    int w = this->width();

    setWindowTitle("MindMap");
    QIcon WindowIcon(":/assets/WindowIcon.png");
    setWindowIcon(WindowIcon);

    menuBar = new QMenuBar(this);
    this->setMenuBar(menuBar);
    int menuBarH = menuBar->height();

    toolBar = new QToolBar(this);
    toolBar->setMovable(false);
    toolBar->setFloatable(false);
    toolBar->move(0,menuBarH);
    toolBar->resize(100,h-menuBarH);

    viewer = new MindMapViewer(this);
    viewer->move(100,menuBarH);
    viewer->resize(w-100,h-menuBarH);

    save_SF = new SaveFile("",this);

    {//第一个Qmenu及相关按钮的初始化
        fileOp = new QMenu(QStringLiteral("文件(&F)"),this);

        newFile_A = new QAction(QStringLiteral("新建"),this);
        openFile_A = new QAction(QStringLiteral("打开"),this);
        save_A = new QAction(QStringLiteral("保存"),this);
        saveAs_A = new QAction(QStringLiteral("另存为"),this);
        close_A = new QAction(QStringLiteral("关闭"),this);

        newFile_A->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_N));
        openFile_A->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_O));
        save_A->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_S));
        saveAs_A->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_A));
        close_A->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_W));

        QIcon newFile_QI (":/assets/new-file.svg");
        QIcon openFile_QI(":/assets/file.svg");
        QIcon save_QI(":/assets/save.svg");
        QIcon saveAs_QI(":/assets/save-as.svg");
        QIcon close_QI(":/assets/close.svg");

        newFile_A->setIcon(newFile_QI);
        openFile_A->setIcon(openFile_QI);
        save_A->setIcon(save_QI);
        saveAs_A->setIcon(saveAs_QI);
        close_A->setIcon(close_QI);

        menuBar->addMenu(fileOp);
        fileOp->addAction(newFile_A);
        fileOp->addAction(openFile_A);
        fileOp->addSeparator();
        fileOp->addAction(save_A);
        fileOp->addAction(saveAs_A);
        fileOp->addSeparator();
        fileOp->addAction(close_A);

        connect(newFile_A,&QAction::triggered,
                this,&MainWindow::newFile_clicked);
        connect(this,&MainWindow::create_save,
                save_SF,&SaveFile::create_save);
    }

    {//第二个Qmenu及相关按钮的初始化
        edit = new QMenu(QStringLiteral("编辑(&E)"),this);

        undo_A = new QAction(QStringLiteral("撤销"),this);
        redo_A = new QAction(QStringLiteral("重做"),this);
        addText_A = new QAction(QStringLiteral("添加语段"),this);
        addFile_A = new QAction(QStringLiteral("添加文件"),this);

        undo_A->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_Z));
        redo_A->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_Y));
        addText_A->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_T));
        addFile_A->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_F));

        QIcon undo_QI(":/assets/undo.svg");
        QIcon redo_QI(":/assets/redo.svg");
        QIcon addText_QI(":/assets/add-text.svg");
        QIcon addFile_QI(":/assets/add-file.svg");

        undo_A->setIcon(undo_QI);
        redo_A->setIcon(redo_QI);
        addText_A->setIcon(addText_QI);
        addFile_A->setIcon(addFile_QI);

        menuBar->addMenu(edit);
        edit->addAction(undo_A);
        edit->addAction(redo_A);
        edit->addSeparator();
        edit->addAction(addText_A);
        edit->addAction(addFile_A);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newFile_clicked(){
    bool ok{};
    QString saveName;
    while(1){
        saveName = QInputDialog::getText(this,"新建文件","存档名",QLineEdit::Normal,QString("新建存档"),&ok);
        extern QString savePath;
        if(!ok)
            return;
        if(QDir(savePath+"/"+saveName).exists()){
            QMessageBox::warning(this,"存档已存在","存档已存在\n请更换存档名");
            ok = false;
        }
        if(ok&&!saveName.isEmpty()){
            QDir(savePath+"/"+saveName).mkdir(savePath+"/"+saveName);
            break;
        }
    }
    viewer->init();
    save_SF = new SaveFile;
    emit create_save(saveName);
}

void MainWindow::resizeEvent(QResizeEvent *event){
    int h_ = event->size().height();
    int w_ = event->size().width();
    int menuBarH = menuBar->height();
    toolBar->resize(100,h_-menuBarH);
    viewer->resize(w_-100,h_-menuBarH);
}
