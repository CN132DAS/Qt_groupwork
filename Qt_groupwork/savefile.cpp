#include "savefile.h"

Pic::Pic(QString name_,QPoint pos_){
    name = name_;
    pos = pos_;
}

SaveFile::SaveFile(QString saveName_,QObject *parent)
    : QObject{parent},saveName(saveName_),picNum(0)
{}
void SaveFile::resize(){

}
void SaveFile:: create_save(QString saveName_){
    saveName = saveName_;
    qDebug()<<"save created successfully!";
    emit init_done(this);
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

