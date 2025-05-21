#include "savefile.h"

SaveFile::SaveFile(QString saveName_,QObject *parent)
    : QObject{parent},saveName(saveName_)
{}
void SaveFile::resize(){

}
void SaveFile:: create_save(QString saveName_){
    saveName = saveName_;
    qDebug()<<"save created successfully!";
    emit init_done(this);
}
