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

    save_SF = new SaveFile("",nullptr,this);

    toolBar = new QToolBar(this);
    toolBar->setOrientation(Qt::Orientation::Vertical);
    toolBar->setMovable(false);
    toolBar->setFloatable(false);
    toolBar->move(0,menuBarH);
    toolBar->resize(100,h-menuBarH);

    viewer = new MindMapViewer(this,save_SF);
    viewer->move(100,menuBarH);
    viewer->resize(w-100,h-menuBarH);
    viewer->setEnabled(false);

    {//第一个Qmenu及相关按钮的初始化
        fileOp = new QMenu(QStringLiteral("文件(&F)"),this);

        newSave_A = new QAction(QStringLiteral("新建"),this);
        openSave_A = new QAction(QStringLiteral("打开"),this);
        save_A = new QAction(QStringLiteral("保存"),this);
        saveAs_A = new QAction(QStringLiteral("另存为"),this);
        close_A = new QAction(QStringLiteral("关闭"),this);

        newSave_A->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_N));
        openSave_A->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_O));
        save_A->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_S));
        saveAs_A->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_A));
        close_A->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_W));

        QIcon newSave_QI(":/assets/new-file.svg");
        QIcon openSave_QI(":/assets/file.svg");
        QIcon save_QI(":/assets/save.svg");
        QIcon saveAs_QI(":/assets/save-as.svg");
        QIcon close_QI(":/assets/close.svg");

        newSave_A->setIcon(newSave_QI);
        openSave_A->setIcon(openSave_QI);
        save_A->setIcon(save_QI);
        saveAs_A->setIcon(saveAs_QI);
        close_A->setIcon(close_QI);

        menuBar->addMenu(fileOp);
        fileOp->addAction(newSave_A);
        fileOp->addAction(openSave_A);
        fileOp->addSeparator();
        fileOp->addAction(save_A);
        fileOp->addAction(saveAs_A);
        fileOp->addSeparator();
        fileOp->addAction(close_A);

        save_A->setEnabled(false);
        saveAs_A->setEnabled(false);
        close_A->setEnabled(false);

        connect(newSave_A,&QAction::triggered,
                this,&MainWindow::new_save);
        connect(openSave_A,&QAction::triggered,
                this,&MainWindow::load_save);
        connect(save_A,&QAction::triggered,
                this,&MainWindow::save);
        connect(close_A,&QAction::triggered,
                this,&MainWindow::close_save);

    }

    {//第二个Qmenu及相关按钮的初始化
        edit = new QMenu(QStringLiteral("编辑(&E)"),this);

        undo_A = new QAction(QStringLiteral("撤销"),this);
        redo_A = new QAction(QStringLiteral("重做"),this);

        undo_A->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_Z));
        redo_A->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_Y));

        QIcon undo_QI(":/assets/undo.svg");
        QIcon redo_QI(":/assets/redo.svg");

        undo_A->setIcon(undo_QI);
        redo_A->setIcon(redo_QI);

        menuBar->addMenu(edit);
        edit->addAction(undo_A);
        edit->addAction(redo_A);
        undo_A->setEnabled(false);
        redo_A->setEnabled(false);
    }

    {//QToolBar中按钮的初始化
        addText_PB = new QPushButton("插入文字",toolBar);
        addPic_PB = new QPushButton("插入图片",toolBar);
        addFile_PB = new QPushButton("插入文件",toolBar);
        drag_PB = new QPushButton("拖动画布",toolBar);

        QIcon addText_Q(":/assets/add-text.svg");
        QIcon addPic_Q(":/assets/add-pic.svg");
        QIcon addFile_Q(":/assets/add-file.svg");
        QIcon drag_Q(":/assets/drag.svg");

        addText_PB->setIcon(addText_Q);
        addPic_PB->setIcon(addPic_Q);
        addFile_PB->setIcon(addFile_Q);
        drag_PB->setIcon(drag_Q);

        addText_PB->setIconSize(QSize(40,40));
        addPic_PB->setIconSize(QSize(40,40));
        addFile_PB->setIconSize(QSize(40,40));
        drag_PB->setIconSize(QSize(40,40));

        addText_PB->setCheckable(true);
        addPic_PB->setCheckable(true);
        addFile_PB->setCheckable(true);
        drag_PB->setCheckable(true);

        toolBar->addWidget(addText_PB);
        toolBar->addWidget(addPic_PB);
        toolBar->addWidget(addFile_PB);
        toolBar->addWidget(drag_PB);

        addText_PB->setEnabled(false);
        addPic_PB->setEnabled(false);
        addFile_PB->setEnabled(false);
        drag_PB->setEnabled(false);

        connect(addText_PB,&QAbstractButton::toggled,
                this,&MainWindow::toggle_addText_PB);
        connect(addPic_PB,&QAbstractButton::toggled,
                this,&MainWindow::toggle_addPic_PB);
        connect(addFile_PB,&QAbstractButton::toggled,
                this,&MainWindow::toggle_addFile_PB);
        connect(drag_PB,&QAbstractButton::toggled,
                this,&MainWindow::toggle_drag_PB);
        connect(this,&MainWindow::state_changed,
                this,&MainWindow::only_toggle_one_button);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::unfreeze(bool unfreeze){
    close_A->setEnabled(unfreeze);
    undo_A->setEnabled(unfreeze);
    redo_A->setEnabled(unfreeze);
    save_A->setEnabled(unfreeze);
    saveAs_A->setEnabled(unfreeze);
    addText_PB->setEnabled(unfreeze);
    addPic_PB->setEnabled(unfreeze);
    addFile_PB->setEnabled(unfreeze);
    drag_PB->setEnabled(unfreeze);
}

//槽函数

void MainWindow::toggle_addText_PB(bool checked){
    if(checked){
        _state_ = "addText";
        emit state_changed();
    }
    else if(_state_ == "addText"){
        _state_ = "";
        emit state_changed();
    }
}

void MainWindow::toggle_addPic_PB(bool checked){
    if(checked){
        _state_ = "addPic";
        emit state_changed();
    }
    else if(_state_ == "addPic"){
        _state_ = "";
        emit state_changed();
    }
}

void MainWindow::toggle_addFile_PB(bool checked){
    if(checked){
        _state_ = "addFile";
        emit state_changed();
    }
    else if(_state_ == "addFile"){
        _state_ = "";
        emit state_changed();
    }
}

void MainWindow::toggle_drag_PB(bool checked){
    if(checked){
        _state_ = "drag";
        emit state_changed();
    }
    else if(_state_ == "drag"){
        _state_ = "";
        emit state_changed();
    }
}

void MainWindow::only_toggle_one_button(){
    if(_state_!="addText")
        addText_PB->setChecked(false);
    if(_state_!="addPic")
        addPic_PB->setChecked(false);
    if(_state_!="addFile")
        addFile_PB->setChecked(false);
    if(_state_!="drag")
        drag_PB->setChecked(false);
}

void MainWindow::new_save(){
    bool ok{};
    QString saveName;
    while(1){
        saveName = QInputDialog::getText(this,"新建文件","存档名",QLineEdit::Normal,QString("新建存档"),&ok);
        if(!ok)
            return;
        if(QDir(_savePath_+"/"+saveName).exists()){
            QMessageBox::warning(this,"存档已存在","存档已存在\n请更换存档名");
            ok = false;
        }
        if(ok&&!saveName.isEmpty()){
            QDir(_savePath_+"/"+saveName).mkdir(_savePath_+"/"+saveName);
            _saveName_ = saveName;
            break;
        }
    }
    viewer->new_save();
    QString title = _saveName_ + "   -MindMap";
    this->setWindowTitle(title);
    this->unfreeze(true);
}

void MainWindow::close_save(){
    _saveName_ = "";
    this->unfreeze(false);
    _state_ = "";
    this->only_toggle_one_button();
    viewer->close_save();
    this->setWindowTitle("MindMap");
}

void MainWindow::save(){
    save_SF->save();
}

void MainWindow::load_save(){
    QString dir = QFileDialog::getOpenFileName(this,"选择存档",QString(),"文件 (*.dat)");
    if(dir!=""){
        viewer->load(dir);
        this->unfreeze(true);
        QString title = _saveName_ + "   -MindMap";
        this->setWindowTitle(title);
    }
}

//重写函数

void MainWindow::resizeEvent(QResizeEvent *event){
    int h_ = event->size().height();
    int w_ = event->size().width();
    int menuBarH = menuBar->height();
    toolBar->resize(100,h_-menuBarH);
    viewer->resize(w_-100,h_-menuBarH);
}
