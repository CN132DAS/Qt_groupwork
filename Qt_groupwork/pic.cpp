#include "pic.h"
#include "func_.h"

Pic::Pic(QString name_,int ID_):QGraphicsPixmapItem(QPixmap(get_filePath(name_))),name(name_),ID(ID_){}

void Pic::save(QTextStream& in){
    QPointF pos = this->scenePos();
    in<<this->ID<<" "<<this->name<<" "<<pos.x()<<" "<<pos.y()<<Qt::endl;
}
