#include "pic.h"
#include "func_.h"

Pic::Pic(QString name_,int ID_):QGraphicsPixmapItem(QPixmap(get_filePath(name_))),name(name_),ID(ID_){}

int Pic::get_ID(){return this->ID;}

void Pic::save(QTextStream& in){
    QPointF pos = this->scenePos();
    in<<this->ID<<" "<<this->name<<" "<<pos.x()<<" "<<pos.y()<<Qt::endl;
}
void Pic::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QGraphicsPixmapItem::paint(painter,option,widget);
    if(option->state & QStyle::State_Selected){
        painter->setPen(QPen(Qt::red, 3, Qt::DashLine));
        painter->drawRect(QGraphicsPixmapItem::boundingRect().adjusted(-2, -2, 2, 2));
    }
}
