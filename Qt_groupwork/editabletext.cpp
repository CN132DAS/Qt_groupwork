#include "editabletext.h"

EditableText::EditableText(QString name_,int ID_)
    :QGraphicsTextItem("填入文字...",nullptr),name(name_),ID(ID_){
    QGraphicsTextItem::setFlags(QGraphicsItem::ItemIsSelectable |
             QGraphicsItem::ItemIsFocusable |
             QGraphicsItem::ItemSendsGeometryChanges);
    QGraphicsTextItem::setTextInteractionFlags(Qt::TextEditorInteraction);
}

QPoint EditableText::get_delta(){
    QRectF rect = this->boundingRect();
    QPointF deltaF(rect.width() / 2, rect.height() / 2);
    return deltaF.toPoint();
}

int EditableText::get_ID(){return this->ID;}

void EditableText::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawRect(QGraphicsTextItem::boundingRect());
    QGraphicsTextItem::paint(painter, option, widget);
    if(option->state & QStyle::State_Selected){
        painter->setPen(QPen(Qt::red, 3, Qt::DashLine));
        painter->drawRect(boundingRect().adjusted(-2, -2, 2, 2));
    }
}
