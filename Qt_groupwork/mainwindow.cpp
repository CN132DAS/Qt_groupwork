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

    save_SF = new SaveFile("",this);

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

        QIcon newFile_QI(":/assets/new-file.svg");
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

        save_A->setEnabled(false);
        saveAs_A->setEnabled(false);
        close_A->setEnabled(false);

        connect(newFile_A,&QAction::triggered,
                this,&MainWindow::get_newFile_name);
        connect(save_SF,&SaveFile::save_created,
                viewer,&MindMapViewer::set_saveFile);
        connect(openFile_A,&QAction::triggered,
                this,&MainWindow::load);
        connect(save_A,&QAction::triggered,
                save_SF,&SaveFile::save);
        connect(close_A,&QAction::triggered,
                this,&MainWindow::close_file);

    }

    {//第二个Qmenu及相关按钮的初始化
        edit = new QMenu(QStringLiteral("编辑(&E)"),this);

        undo_A = new QAction(QStringLiteral("撤销"),this);
        redo_A = new QAction(QStringLiteral("重做"),this);
        addText_A = new QAction(QStringLiteral("插入文字"),this);
        addPic_A = new QAction(QStringLiteral("插入图片"),this);
        addFile_A = new QAction(QStringLiteral("插入文件"),this);

        undo_A->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_Z));
        redo_A->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_Y));
        addText_A->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_T));
        addPic_A->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_P));
        addFile_A->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_F));

        QIcon undo_QI(":/assets/undo.svg");
        QIcon redo_QI(":/assets/redo.svg");
        QIcon addText_QI(":/assets/add-text.svg");
        QIcon addPic_QI(":/assets/add-pic.svg");
        QIcon addFile_QI(":/assets/add-file.svg");

        undo_A->setIcon(undo_QI);
        redo_A->setIcon(redo_QI);
        addText_A->setIcon(addText_QI);
        addPic_A->setIcon(addPic_QI);
        addFile_A->setIcon(addFile_QI);

        menuBar->addMenu(edit);
        edit->addAction(undo_A);
        edit->addAction(redo_A);
        edit->addSeparator();
        edit->addAction(addText_A);
        edit->addAction(addPic_A);
        edit->addAction(addFile_A);

        undo_A->setEnabled(false);
        redo_A->setEnabled(false);
        addText_A->setEnabled(false);
        addPic_A->setEnabled(false);
        addFile_A->setEnabled(false);

        connect(addText_A,&QAction::triggered,
                this,&MainWindow::set_text_checked);
        connect(addPic_A,&QAction::triggered,
                this,&MainWindow::set_pic_checked);
        connect(addFile_A,&QAction::triggered,
                this,&MainWindow::set_file_checked);
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
                this,&MainWindow::only_toggle_addText_PB);
        connect(addPic_PB,&QAbstractButton::toggled,
                this,&MainWindow::only_toggle_addPic_PB);
        connect(addFile_PB,&QAbstractButton::toggled,
                this,&MainWindow::only_toggle_addFile_PB);
        connect(drag_PB,&QAbstractButton::toggled,
                this,&MainWindow::only_toggle_drag_PB);
        connect(drag_PB,&QAbstractButton::toggled,
                             viewer,&MindMapViewer::set_drag_mode);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::get_newFile_name(){
    bool ok{};
    QString saveName;
    while(1){
        saveName = QInputDialog::getText(this,"新建文件","存档名",QLineEdit::Normal,QString("新建存档"),&ok);
        if(!ok)
            return;
        if(QDir(savePath_+"/"+saveName).exists()){
            QMessageBox::warning(this,"存档已存在","存档已存在\n请更换存档名");
            ok = false;
        }
        if(ok&&!saveName.isEmpty()){
            QDir(savePath_+"/"+saveName).mkdir(savePath_+"/"+saveName);
            saveName_ = saveName;
            break;
        }
    }
    viewer->clear();
    save_SF->create_save(saveName_);
    this->unfreeze(true);
}

void MainWindow::load(){
    QString dir = QFileDialog::getOpenFileName(this,"选择存档",QString(),"文件 (*.dat)");
    if(dir!=""){
        viewer->load(dir);
        unfreeze(true);
    }
}

void MainWindow::unfreeze(bool unfreeze){
    close_A->setEnabled(unfreeze);
    undo_A->setEnabled(unfreeze);
    redo_A->setEnabled(unfreeze);
    save_A->setEnabled(unfreeze);
    saveAs_A->setEnabled(unfreeze);
    addText_A->setEnabled(unfreeze);
    addPic_A->setEnabled(unfreeze);
    addFile_A->setEnabled(unfreeze);
    addText_PB->setEnabled(unfreeze);
    addPic_PB->setEnabled(unfreeze);
    addFile_PB->setEnabled(unfreeze);
    drag_PB->setEnabled(unfreeze);
}

void MainWindow::resizeEvent(QResizeEvent *event){
    int h_ = event->size().height();
    int w_ = event->size().width();
    int menuBarH = menuBar->height();
    toolBar->resize(100,h_-menuBarH);
    viewer->resize(w_-100,h_-menuBarH);
}

void MainWindow::only_toggle_addText_PB(bool checked){
    if(checked){
        addFile_PB->setChecked(false);
        addPic_PB->setChecked(false);
        drag_PB->setChecked(false);
        viewer->set_state("addText");
    }
    else
        viewer->set_state("");
}

void MainWindow::only_toggle_addFile_PB(bool checked){
    if(checked){
        addText_PB->setChecked(false);
        addPic_PB->setChecked(false);
        drag_PB->setChecked(false);
        viewer->set_state("addFile");
    }
    else
        viewer->set_state("");
}

void MainWindow::only_toggle_addPic_PB(bool checked){
    if(checked){
        addText_PB->setChecked(false);
        addFile_PB->setChecked(false);
        drag_PB->setChecked(false);
        viewer->set_state("addPic");
    }
    else
        viewer->set_state("");
}

void MainWindow::only_toggle_drag_PB(bool checked){
    if(checked){
        addText_PB->setChecked(false);
        addFile_PB->setChecked(false);
        addPic_PB->setChecked(false);
        viewer->set_state("drag");
    }
    else
        viewer->set_state("");
}

void MainWindow::set_text_checked(){
    addText_PB->setChecked(true);
}

void MainWindow::set_pic_checked(){
    addPic_PB->setChecked(true);
}

void MainWindow::set_file_checked(){
    addFile_PB->setChecked(true);
}

void MainWindow::close_file(){
    delete save_SF;
    saveName_ = "";
    save_SF = new SaveFile("",this);
    unfreeze(false);
    viewer->disable();
}

void MainWindow::mousePressEvent(QMouseEvent* event){
    QPoint tmp = event->pos();
    if(tmp.y()>30&&tmp.x()>100)
        viewer->mousePressEvent(event);
    event->accept();
}

void MainWindow::mouseMoveEvent(QMouseEvent* event){
    QPoint tmp = event->pos();
    if((tmp.y()>30&&tmp.x()>100)||viewer->is_panning())
        viewer->mouseMoveEvent(event);
    event->accept();
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event){
    QPoint tmp = event->pos();
    if((tmp.y()>30&&tmp.x()>100)||viewer->is_panning())
        viewer->mouseReleaseEvent(event);
    event->accept();
}

void MainWindow::wheelEvent(QWheelEvent* event){
    QPointF tmp = event->position();
    if(tmp.y()>30&&tmp.x()>100)
        viewer->wheelEvent(event);
    event->accept();
}

