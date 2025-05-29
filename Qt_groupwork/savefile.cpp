#include "savefile.h"
#include "qgraphicsitem.h"

Pic::Pic(QString name_,QString path_,QPoint pos_)
    :name(name_),path(path_),pos(pos_){}

SaveFile::SaveFile(QString saveName_,QObject *parent)
    : QObject{parent},saveName(saveName_),picNum(0){}

void SaveFile:: create_save(QString saveName__){
    saveName = saveName__;
    saveName_ = saveName;
    qDebug()<<"save created successfully!";
    emit save_created(this);
}

int SaveFile:: get_picNum(){
    return picNum;
}

int SaveFile:: get_textNum(){
    return textNum;
}

void SaveFile::add_pic(Pic* pic_){
    pic.push_back(pic_);
    picNum++;
}

void SaveFile::add_file(FileContent* file_){
    file.push_back(file_);
    fileNum++;
}

void SaveFile::add_text(EditableText* text_){
    text.push_back(text_);
    textNum++;
}

void SaveFile::save(){
    QFile saveFile(get_filePath("save.dat"));
    saveFile.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate);
    QTextStream in(&saveFile);
    in<<picNum<<Qt::endl;
    if(picNum!=0){
        for(auto it = pic.begin();it!=pic.end();it++){
            in<<(*it)->pos.x()<<" "<<(*it)->pos.y()<<" "<<(*it)->name<<Qt::endl;
        }
    }
    in<<fileNum<<Qt::endl;
    if(fileNum!=0){
        for(auto it = file.begin();it!=file.end();it++){
            (*it)->save(in);
        }
    }
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
    saveName_ = saveName;
    for(int i = 0;i<picNum;i++){
        int x,y;
        out>>x>>y;
        QString name;
        out>>name;
        pic.push_back(new Pic(name,get_filePath(name),QPoint(x,y)));
        QPixmap pic_pixmap(get_filePath(name));
        QGraphicsPixmapItem* pic= new QGraphicsPixmapItem(pic_pixmap);
        scene->addItem(pic);
        pic->setPos(QPoint(x,y));
    }
    out>>fileNum;
    for(int i = 0;i<fileNum;i++){
        int x,y;
        out>>x>>y;
        QString name;
        out>>name;
        FileContent* file_ = new FileContent(name,QPoint(x,y));
        file.push_back(file_);
        scene->addItem(file_);
        file_->setPos(QPoint(x,y));
    }
}

