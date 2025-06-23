#ifndef CONNECTION_H
#define CONNECTION_H

#include <QGraphicsObject>
#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include "mygraphicsobject.h"

class Connection : public MyGraphicsObject
{
private:
    int ID;
    MyGraphicsObject *item1,*item2;
    QPen pen;
    QPainterPath path;
private:
    QPair<QPointF, QPointF> get_ConnectionPoints(MyGraphicsObject* item1, MyGraphicsObject* item2) const;
    QString get_info(MyGraphicsObject* item);
public:
    Connection(MyGraphicsObject *item1_,MyGraphicsObject *item2_,int ID_);
    void save(QTextStream& out,int i);
    QPair<MyGraphicsObject*,MyGraphicsObject*> get_pair();
    QString get_info() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    QRectF boundingRect() const override;
    int type() const override;
public slots:
    void updatePath();
};

#endif // CONNECTION_H
