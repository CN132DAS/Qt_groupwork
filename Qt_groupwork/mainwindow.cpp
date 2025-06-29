#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "function.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    AI = new AImodule();
    connect(AI,&AImodule::close,
            this,&MainWindow::untoggle_AI_PB);

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

        newSave_A = new QAction(QStringLiteral("新建"),this);
        openSave_A = new QAction(QStringLiteral("打开"),this);
        save_A = new QAction(QStringLiteral("保存"),this);
        saveAs_A = new QAction(QStringLiteral("另存为"),this);
        close_A = new QAction(QStringLiteral("关闭"),this);
        refresh_A = new QAction(QStringLiteral("刷新"),this);

        newSave_A->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_N));
        openSave_A->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_O));
        save_A->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_S));
        saveAs_A->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_A));
        close_A->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_W));
        refresh_A->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_R));

        QIcon newSave_QI(":/assets/new-file.svg");
        QIcon openSave_QI(":/assets/file.svg");
        QIcon save_QI(":/assets/save.svg");
        QIcon saveAs_QI(":/assets/save-as.svg");
        QIcon close_QI(":/assets/close.svg");
        QIcon refresh_QI(":/assets/refresh.svg");

        newSave_A->setIcon(newSave_QI);
        openSave_A->setIcon(openSave_QI);
        save_A->setIcon(save_QI);
        saveAs_A->setIcon(saveAs_QI);
        close_A->setIcon(close_QI);
        refresh_A->setIcon(refresh_QI);

        menuBar->addMenu(fileOp);
        fileOp->addAction(newSave_A);
        fileOp->addAction(openSave_A);
        fileOp->addSeparator();
        fileOp->addAction(save_A);
        fileOp->addAction(saveAs_A);
        fileOp->addSeparator();
        fileOp->addAction(close_A);
        fileOp->addAction(refresh_A);

        save_A->setEnabled(false);
        saveAs_A->setEnabled(false);
        close_A->setEnabled(false);
        refresh_A->setEnabled(false);

        connect(newSave_A,&QAction::triggered,
                this,&MainWindow::new_save);
        connect(openSave_A,&QAction::triggered,
                this,&MainWindow::load_save);
        connect(save_A,&QAction::triggered,
                this,&MainWindow::save);
        connect(close_A,&QAction::triggered,
                this,&MainWindow::close_save);
        connect(refresh_A,&QAction::triggered,
                this,&MainWindow::refresh);
    }

    {//QToolBar中按钮的初始化
        addText_PB = new QPushButton("插入文字",toolBar);
        addPic_PB = new QPushButton("插入图片",toolBar);
        addFile_PB = new QPushButton("插入文件",toolBar);
        addCon_PB = new QPushButton("新建连接",toolBar);
        edit_PB = new QPushButton("编辑",toolBar);
        drag_PB = new QPushButton("拖动",toolBar);
        AI_PB = new QPushButton("AI",toolBar);

        QIcon addText_QI(":/assets/add-text.svg");
        QIcon addPic_QI(":/assets/add-pic.svg");
        QIcon addFile_QI(":/assets/add-file.svg");
        QIcon addCon_QI(":/assets/add-con.svg");
        QIcon edit_QI(":/assets/edit.svg");
        QIcon drag_QI(":/assets/drag.svg");
        QIcon AI_QI(":/assets/AI.svg");

        addText_PB->setIcon(addText_QI);
        addPic_PB->setIcon(addPic_QI);
        addFile_PB->setIcon(addFile_QI);
        addCon_PB->setIcon(addCon_QI);
        edit_PB->setIcon(edit_QI);
        drag_PB->setIcon(drag_QI);
        AI_PB->setIcon(AI_QI);

        addText_PB->setIconSize(QSize(40,40));
        addPic_PB->setIconSize(QSize(40,40));
        addFile_PB->setIconSize(QSize(40,40));
        addCon_PB->setIconSize(QSize(40,40));
        edit_PB->setIconSize(QSize(40,40));
        drag_PB->setIconSize(QSize(40,40));
        AI_PB->setIconSize(QSize(40,40));

        addText_PB->setCheckable(true);
        addPic_PB->setCheckable(true);
        addFile_PB->setCheckable(true);
        addCon_PB->setCheckable(true);
        edit_PB->setCheckable(true);
        drag_PB->setCheckable(true);
        AI_PB->setCheckable(true);

        toolBar->addWidget(addText_PB);
        toolBar->addWidget(addPic_PB);
        toolBar->addWidget(addFile_PB);
        toolBar->addSeparator();
        toolBar->addWidget(addCon_PB);
        toolBar->addSeparator();
        toolBar->addWidget(edit_PB);
        toolBar->addWidget(drag_PB);
        toolBar->addSeparator();
        toolBar->addWidget(AI_PB);

        addText_PB->setEnabled(false);
        addPic_PB->setEnabled(false);
        addFile_PB->setEnabled(false);
        addCon_PB->setEnabled(false);
        edit_PB->setEnabled(false);
        drag_PB->setEnabled(false);

        connect(addText_PB,&QAbstractButton::toggled,
                this,&MainWindow::toggle_addText_PB);
        connect(addPic_PB,&QAbstractButton::toggled,
                this,&MainWindow::toggle_addPic_PB);
        connect(addFile_PB,&QAbstractButton::toggled,
                this,&MainWindow::toggle_addFile_PB);
        connect(addCon_PB,&QAbstractButton::toggled,
                this,&MainWindow::toggle_addCon_PB);
        connect(edit_PB,&QAbstractButton::toggled,
                this,&MainWindow::toggle_edit_PB);
        connect(drag_PB,&QAbstractButton::toggled,
                this,&MainWindow::toggle_drag_PB);
        connect(this,&MainWindow::state_changed,
                this,&MainWindow::only_toggle_one_button);
        connect(AI_PB,&QAbstractButton::toggled,
                this,&MainWindow::toggle_AI_PB);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::unfreeze(bool unfreeze){
    close_A->setEnabled(unfreeze);
    save_A->setEnabled(unfreeze);
    saveAs_A->setEnabled(unfreeze);
    refresh_A->setEnabled(unfreeze);
    addText_PB->setEnabled(unfreeze);
    addPic_PB->setEnabled(unfreeze);
    addFile_PB->setEnabled(unfreeze);
    addCon_PB->setEnabled(unfreeze);
    edit_PB->setEnabled(unfreeze);
    drag_PB->setEnabled(unfreeze);
}

//slot
void MainWindow::untoggle_AI_PB(){
    AI_PB->setChecked(false);
}

void MainWindow::toggle_addText_PB(bool checked){
    if(checked){
        _state_ = "addText";
        viewer->clear_selectedItem();
        save_SF->set_item_selectability(false);
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
        viewer->clear_selectedItem();
        save_SF->set_item_selectability(false);
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
        viewer->clear_selectedItem();
        save_SF->set_item_selectability(false);
        emit state_changed();
    }
    else if(_state_ == "addFile"){
        _state_ = "";
        emit state_changed();
    }
}

void MainWindow::toggle_addCon_PB(bool checked){
    if(checked){
        _state_ = "addCon";
        viewer->clear_selectedItem();
        save_SF->set_item_selectability(true);
        emit state_changed();
    }
    else if(_state_ == "addCon"){
        _state_ = "";
        save_SF->set_item_selectability(false);
        emit state_changed();
    }
}

void MainWindow::toggle_edit_PB(bool checked){
    if(checked){
        _state_ = "edit";
        viewer->clear_selectedItem();
        save_SF->set_item_selectability(true,true);
        emit state_changed();
    }
    else if(_state_ == "edit"){
        _state_ = "";
        save_SF->set_item_selectability(false);
        emit state_changed();
    }
}

void MainWindow::toggle_drag_PB(bool checked){
    if(checked){
        _state_ = "drag";
        viewer->clear_selectedItem();
        save_SF->set_item_selectability(true);
        emit state_changed();
    }
    else if(_state_ == "drag"){
        _state_ = "";
        save_SF->set_item_selectability(false);
        emit state_changed();
    }
}

void MainWindow::toggle_AI_PB(bool checked){
    if(checked)
        AI->show_ui();
    else
        AI->hide();
}

void MainWindow::only_toggle_one_button(){
    if(_state_!="addText")
        addText_PB->setChecked(false);
    if(_state_!="addPic")
        addPic_PB->setChecked(false);
    if(_state_!="addFile")
        addFile_PB->setChecked(false);
    if(_state_!="addCon")
        addCon_PB->setChecked(false);
    if(_state_!="drag")
        drag_PB->setChecked(false);
    if(_state_!="edit")
        edit_PB->setChecked(false);
}

void MainWindow::new_save(){
    if(_operation_){
        QMessageBox msgBox;
        msgBox.setWindowTitle("有未保存的操作");
        msgBox.setText("先保存吗");
        QPushButton *yesButton = msgBox.addButton("保存", QMessageBox::YesRole);
        QPushButton *noButton = msgBox.addButton("直接新建", QMessageBox::NoRole);
        QPushButton *cancelButton = msgBox.addButton("取消", QMessageBox::RejectRole);
        msgBox.setEscapeButton(nullptr);
        msgBox.exec();
        if(msgBox.clickedButton() == yesButton){
            this->save();
            this->close_save();
        }
        else if(msgBox.clickedButton() == noButton){
            _operation_ = false;
            this->close_save();
        }
        else if(msgBox.clickedButton() == cancelButton)
            return;
    }
    QString saveName;
    while(1){
        bool ok = false;
        saveName = QInputDialog::getText(this,"新建文件","存档名",QLineEdit::Normal,QString("新建存档"),&ok);
        if(!ok)
            return;
        else if(QFileInfo::exists(_saveFolderPath_+"/"+saveName+"/save.dat")){
            QMessageBox::warning(this,"存档已存在","存档已存在\n请更换存档名");
            ok = false;
        }
        if(ok&&!saveName.isEmpty()){
            set_saveName(saveName);
            QDir().mkpath(_saveTempPath_);
            break;
        }
    }
    _operation_ = false;
    viewer->new_save();
    QString title = _saveName_ + "   -MindMap";
    this->setWindowTitle(title);
    this->unfreeze(true);
}

void MainWindow::save(){
    save_SF->save();
    _operation_ = false;
}

void MainWindow::load_save(){
    if(_operation_){
        QMessageBox msgBox;
        msgBox.setWindowTitle("有未保存的操作");
        msgBox.setText("先保存吗");
        QPushButton *yesButton = msgBox.addButton("保存", QMessageBox::YesRole);
        QPushButton *noButton = msgBox.addButton("直接读取", QMessageBox::NoRole);
        QPushButton *cancelButton = msgBox.addButton("取消", QMessageBox::RejectRole);
        msgBox.setEscapeButton(nullptr);
        msgBox.exec();
        if(msgBox.clickedButton() == yesButton){
            this->save();
            this->close_save();
        }
        else if(msgBox.clickedButton() == noButton){
            _operation_ = false;
            this->close_save();
        }
        else if(msgBox.clickedButton() == cancelButton)
            return;
    }
    QString dir = QFileDialog::getOpenFileName(this,"选择存档",_saveFolderPath_,"文件 (*.dat)");
    if(dir!=""){
        if(_saveName_!="")
            this->close_save();
        viewer->load(dir);
        this->unfreeze(true);
        QString title = _saveName_ + "   -MindMap";
        this->setWindowTitle(title);
    }
}

void MainWindow::close_save(){
    if(_operation_){
        QMessageBox msgBox;
        msgBox.setWindowTitle("有未保存的操作");
        msgBox.setText("先保存吗");
        QPushButton *yesButton = msgBox.addButton("保存", QMessageBox::YesRole);
        QPushButton *noButton = msgBox.addButton("直接关闭", QMessageBox::NoRole);
        QPushButton *cancelButton = msgBox.addButton("取消", QMessageBox::RejectRole);
        msgBox.setEscapeButton(nullptr);
        msgBox.exec();
        if(msgBox.clickedButton() == yesButton)
            this->save();
        else if(msgBox.clickedButton() == cancelButton)
            return;
    }
    delete_tempFile();
    _saveName_ = "";
    _state_ = "";
    _operation_ = false;
    this->only_toggle_one_button();
    this->unfreeze(false);
    viewer->close_save();
    this->setWindowTitle("MindMap");
}

void MainWindow::refresh(){
    QString saveName = _saveName_;
    QString dir = get_filePath("save.dat");
    GraphicsViewState tempState = viewer->get_state();
    this->save();
    this->close_save();
    _saveName_ = saveName;
    viewer->load(dir);
    this->unfreeze(true);
    QString title = _saveName_ + "   -MindMap";
    this->setWindowTitle(title);
    viewer->restore_state(tempState);
}

//override

void MainWindow::resizeEvent(QResizeEvent *event){
    int h_ = event->size().height();
    int w_ = event->size().width();
    int menuBarH = menuBar->height();
    toolBar->resize(100,h_-menuBarH);
    viewer->resize(w_-100,h_-menuBarH);
}

void MainWindow::closeEvent(QCloseEvent *event){
    if(_operation_){
        QMessageBox msgBox;
        msgBox.setWindowTitle("有未保存的操作");
        msgBox.setText("先保存吗");
        QPushButton *yesButton = msgBox.addButton("保存", QMessageBox::YesRole);
        QPushButton *noButton = msgBox.addButton("直接退出", QMessageBox::NoRole);
        QPushButton *cancelButton = msgBox.addButton("取消", QMessageBox::RejectRole);
        msgBox.setEscapeButton(nullptr);
        msgBox.exec();
        if(msgBox.clickedButton() == yesButton){
            this->save();
            this->close_save();
            event->accept();
        }
        else if (msgBox.clickedButton() == noButton){
            _operation_ = false;
            this->close_save();
            event->accept();
        }
        else if (msgBox.clickedButton() == cancelButton)
            event->ignore();
    }
    else if(_saveName_ != "")
        this->close_save();
}
