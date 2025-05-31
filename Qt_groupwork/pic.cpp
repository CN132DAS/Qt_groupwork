#include "pic.h"
#include "func_.h"

Pic::Pic(QString name_,QPoint pos_,int ID_):QGraphicsPixmapItem(QPixmap(get_filePath(name_))),name(name_),pos(pos_),ID(ID_){}

void Pic::save(QTextStream& in){
    in<<this->ID<<" "<<this->name<<" "<<this->pos.x()<<" "<<this->pos.y()<<Qt::endl;
}
