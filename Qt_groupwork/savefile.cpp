#include "savefile.h"

SaveFile::SaveFile(QString saveName_,QObject *parent)
    : QObject{parent},saveName(saveName_)
{}
void SaveFile::resize(){

}
void SaveFile:: create_save(QString saveName_){
    saveName = saveName_;
    qDebug()<<1;
    emit init_done();
}
