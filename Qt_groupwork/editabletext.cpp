#include "editabletext.h"

EditableText::EditableText(QString name_)
    :QGraphicsTextItem("填入文字...",nullptr),name(name_){
    QGraphicsTextItem::setFlags(QGraphicsItem::ItemIsSelectable |
             QGraphicsItem::ItemIsFocusable |
             QGraphicsItem::ItemSendsGeometryChanges);
    QGraphicsTextItem::setTextInteractionFlags(Qt::TextEditorInteraction);
}

void EditableText::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawRect(QGraphicsTextItem::boundingRect());
    QGraphicsTextItem::paint(painter, option, widget);
}

QPoint EditableText::get_delta(){
    QRectF rect = this->boundingRect();
    QPointF deltaF(rect.width() / 2, rect.height() / 2);
    return deltaF.toPoint();
}
