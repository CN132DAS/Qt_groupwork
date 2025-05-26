#include "savefile.h"
#include "qgraphicsitem.h"

Pic::Pic(QString name_,QPoint pos_){
    name = name_;
    pos = pos_;
}

SaveFile::SaveFile(QString saveName_,QObject *parent)
    : QObject{parent},saveName(saveName_),picNum(0){}

void SaveFile:: create_save(QString saveName_){
    saveName = saveName_;
    qDebug()<<"save created successfully!";
    emit save_created(this);
}

int SaveFile:: get_picNum(){
    return picNum;
}

void SaveFile::add_pic(QString picName,QPoint mousePos){
    pic.push_back(Pic(picName,mousePos));
    qDebug()<<"Pic added with name:"<<picName;
    qDebug()<<"and pos:"<<mousePos;
    picNum++;
}

QString SaveFile::get_saveName(){
    return saveName;
}

void SaveFile::save(){
    QFile saveFile(savePath+"/"+saveName+"/save.dat");
    qDebug()<<(savePath+"/"+saveName+"/save.dat");
    saveFile.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate);
    QTextStream in(&saveFile);
    in<<picNum<<Qt::endl;
    if(picNum!=0){
        for(auto it = pic.begin();it!=pic.end();it++){
            in<<it->pos.x()<<" "<<it->pos.y()<<" "<<it->name;
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
    qDebug()<<saveName;
    qDebug()<<savePath;
    for(int i = 0;i<picNum;i++){
        int x,y;
        out>>x>>y;
        QString name;
        out>>name;
        qDebug()<<x<<" "<<y<<" "<<name;
        qDebug()<<savePath+"/"+saveName+"/"+name;
        pic.push_back(Pic(name,QPoint(x,y)));
        QPixmap pic_pixmap(savePath+"/"+saveName+"/"+name);
        QGraphicsPixmapItem* pic= new QGraphicsPixmapItem(pic_pixmap);
        scene->addItem(pic);
        pic->setPos(QPoint(x,y));
    }
}

