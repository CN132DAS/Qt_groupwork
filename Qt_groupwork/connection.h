#ifndef CONNECTION_H
#define CONNECTION_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include "editabletext.h"
#include "filecontent.h"
#include "pic.h"


class Connection : public QGraphicsItem
{
private:
    int ID;
    QGraphicsItem *item1,*item2;
    QPen pen;
    QPainterPath path;
private:
    QPair<QPointF, QPointF> getConnectionPoints(QGraphicsItem* item1, QGraphicsItem* item2) const;
    void updatePath();
    QString gatSaveInfo(QGraphicsItem* item);
public:
    Connection(QGraphicsItem *item1_,QGraphicsItem *item2_,int ID_);
    void save(QTextStream& in);
    QPair<QGraphicsItem*,QGraphicsItem*> get_pair();
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    QRectF boundingRect() const override;
};

#endif // CONNECTION_H
