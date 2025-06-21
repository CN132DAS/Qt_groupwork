#include "savefile.h"
#include "func_.h"

SaveFile::SaveFile(QString saveName_,QGraphicsScene* scene_,QObject *parent)
    : QObject{parent},saveName(saveName_),picNum(0),fileNum(0),textNum(0),conNum(0),scene(scene_){}

//

void SaveFile::new_save(){
    saveName = _saveName_;
    this->clear();
}

void SaveFile::clear(){
    this->pic.clear();
    this->file.clear();
    this->text.clear();
    this->picNum = 0;
    this->fileNum = 0;
    this->textNum = 0;
}

void SaveFile::set_scene(QGraphicsScene* scene_){
    scene = scene_;
}

QPair<QPoint,Pic*> SaveFile::add_pic(QString dir){
    picNum++;
    QFileInfo tmp(dir);
    QString picName = "Pic_"+QString::number(picNum)+"."+tmp.suffix();
    QString targetPath = get_filePath(picName);
    QFile::copy(dir,targetPath);
    Pic* pic_ = new Pic(picName,picNum);
    pic.insert(picNum,pic_);
    QPixmap pic_pixmap(targetPath);
    int w = pic_pixmap.width();
    int h = pic_pixmap.height();
    QPoint delta(w/2,h/2);
    return qMakePair(delta,pic_);
}

QPair<QPoint,FileContent*> SaveFile::add_file(QString dir){
    QFileInfo tmp(dir);
    QString fileName = tmp.fileName();
    QString targetPath = get_filePath(fileName);
    if(QDir(targetPath).exists(targetPath)){
        QMessageBox::warning(nullptr,"文件名重复","已有同名文件，请修改文件名！");
        return qMakePair(QPoint(),nullptr);
    }
    QFile::copy(dir,targetPath);
    fileNum++;
    FileContent* file_ = new FileContent(fileName,fileNum);
    file.insert(fileNum,file_);
    QPoint delta = file_->get_delta();
    return qMakePair(delta,file_);
}

QPair<QPoint,EditableText*> SaveFile::add_text(){
    textNum++;
    QString textName = "Text_"+QString::number(textNum);
    EditableText* text_ = new EditableText(textName,textNum);
    text.insert(textNum,text_);
    QPoint delta = text_->get_delta();
    return qMakePair(delta,text_);
}

Connection* SaveFile::add_connection(QGraphicsItem* item1,QGraphicsItem* item2){
    for(auto item = connection.begin();item!=connection.end();item++){
        auto pair = (*item)->get_pair();
        if(qMakePair(item1,item2)==pair ||qMakePair(item2,item1)==pair)
            return nullptr;
    }
    conNum++;
    Connection *con = new Connection(item1,item2,conNum);
    connection.insert(conNum,con);
    if (auto item = dynamic_cast<Pic*>(item1)) {
        connect(item, &Pic::position_changed, con, &Connection::updatePath);
    }
    else if (auto item = dynamic_cast<FileContent*>(item1)) {
        connect(item, &FileContent::position_changed, con, &Connection::updatePath);
    }
    else if (auto item = dynamic_cast<EditableText*>(item1)) {
        connect(item, &EditableText::position_changed, con, &Connection::updatePath);
    }
    if (auto item = dynamic_cast<Pic*>(item2)) {
        connect(item, &Pic::position_changed, con, &Connection::updatePath);
    }
    else if (auto item = dynamic_cast<FileContent*>(item2)) {
        connect(item, &FileContent::position_changed, con, &Connection::updatePath);
    }
    else if (auto item = dynamic_cast<EditableText*>(item2)) {
        connect(item, &EditableText::position_changed, con, &Connection::updatePath);
    }
    return con;
}

void SaveFile::save(){
    QFile saveFile(get_filePath("save.dat"));
    saveFile.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate);
    QTextStream in(&saveFile);
    in<<picNum<<Qt::endl;
    if(picNum!=0){
        for(auto it = pic.begin();it!=pic.end();it++){
            (*it)->save(in);
        }
    }
    in<<fileNum<<Qt::endl;
    if(fileNum!=0){
        for(auto it = file.begin();it!=file.end();it++){
            (*it)->save(in);
        }
    }
    in<<textNum<<Qt::endl;
    // if(textNum!=0){
    //     for(auto it = text.begin();it!=text.end();it++){
    //         (*it)->save(in);
    //     }
    // }
    in<<conNum<<Qt::endl;
    if(conNum!=0){
        for(auto it = connection.begin();it!=connection.end();it++){
            (*it)->save(in);
        }
    }
    saveFile.close();
}

void SaveFile::load(QString dir,QGraphicsScene* scene){
    scene->clear();
    QFile saveFile(dir);
    saveFile.open(QIODevice::ReadWrite|QIODevice::Text);
    QTextStream out(&saveFile);
    out>>picNum;
    QDir dir_(dir);
    dir_.cdUp();
    saveName = dir_.dirName();
    _saveName_ = saveName;
    for(int i = 0;i<picNum;i++){
        int ID;
        out>>ID;
        QString name;
        out>>name;
        qreal x,y;
        out>>x>>y;
        Pic* pic_ = new Pic(name,ID);
        pic.insert(ID,pic_);
        scene->addItem(pic_);
        pic_->setPos(QPointF(x,y));
    }
    out>>fileNum;
    for(int i = 0;i<fileNum;i++){
        int ID;
        out>>ID;
        QString name;
        out>>name;
        qreal x,y;
        out>>x>>y;
        FileContent* file_ = new FileContent(name,ID);
        file.insert(ID,file_);
        scene->addItem(file_);
        file_->setPos(QPointF(x,y));
    }
    out>>textNum;
    // for(int i = 0;i<textNum;i++){

    // }
    out>>conNum;
    for(int i = 0;i<conNum;i++){
        int ID,ID_[2];
        QString type_[2];
        out>>ID>>type_[0]>>ID_[0]>>type_[1]>>ID_[1];
        QGraphicsItem* item_[2];
        for(int j = 0;j<=1;j++){
            if(type_[j]=="pic")
                item_[j] = pic[ID_[j]];
            else if(type_[j]=="text")
                item_[j] = text[ID_[j]];
            else if(type_[j]=="file")
                item_[j] = file[ID_[j]];
        }
        Connection *con = new Connection(item_[0],item_[1],ID);
        connection.insert(conNum,con);
        if (auto item = dynamic_cast<Pic*>(item_[0])) {
            connect(item, &Pic::position_changed, con, &Connection::updatePath);
        }
        else if (auto item = dynamic_cast<FileContent*>(item_[0])) {
            connect(item, &FileContent::position_changed, con, &Connection::updatePath);
        }
        else if (auto item = dynamic_cast<EditableText*>(item_[0])) {
            connect(item, &EditableText::position_changed, con, &Connection::updatePath);
        }
        if (auto item = dynamic_cast<Pic*>(item_[1])) {
            connect(item, &Pic::position_changed, con, &Connection::updatePath);
        }
        else if (auto item = dynamic_cast<FileContent*>(item_[1])) {
            connect(item, &FileContent::position_changed, con, &Connection::updatePath);
        }
        else if (auto item = dynamic_cast<EditableText*>(item_[1])) {
            connect(item, &EditableText::position_changed, con, &Connection::updatePath);
        }
        scene->addItem(con);
    }
}

void SaveFile::set_item_selectability(bool selectable){
    for(auto item = pic.begin();item!=pic.end();item++)
        item.value()->setFlag(QGraphicsItem::ItemIsSelectable, selectable);
    for(auto item = file.begin();item!=file.end();item++)
        item.value()->setFlag(QGraphicsItem::ItemIsSelectable, selectable);
    for(auto item = text.begin();item!=text.end();item++)
        item.value()->setFlag(QGraphicsItem::ItemIsSelectable, selectable);
}

//槽函数
