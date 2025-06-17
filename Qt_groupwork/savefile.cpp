#include "savefile.h"
#include "func_.h"

SaveFile::SaveFile(QString saveName_,QGraphicsScene* scene_,QObject *parent)
    : QObject{parent},saveName(saveName_),picNum(0),fileNum(0),textNum(0),scene(scene_){}

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
    pic.push_back(pic_);
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
    file.push_back(file_);
    QPoint delta = file_->get_delta();
    return qMakePair(delta,file_);
}

QPair<QPoint,EditableText*> SaveFile::add_text(){
    QString textName = "Text_"+QString::number(textNum+1);
    EditableText* text_ = new EditableText(textName);
    text.push_back(text_);
    QPoint delta = text_->get_delta();
    return qMakePair(delta,text_);
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
        pic.push_back(pic_);
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
        file.push_back(file_);
        scene->addItem(file_);
        file_->setPos(QPointF(x,y));
    }
}

//槽函数
