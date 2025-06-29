#ifndef CONNECTION_H
#define CONNECTION_H

#include <QGraphicsObject>
#include <QGraphicsScene>
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
    bool deleteOnce;
    Connection(MyGraphicsObject *item1_,MyGraphicsObject *item2_,int ID_);
    void save(QTextStream& out,int& i);
    QPair<MyGraphicsObject*,MyGraphicsObject*> get_pair();
    QString get_info() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    QRectF boundingRect() const override;
    int type() const override;
    void open() override;
public slots:
    void updatePath();
    void delete_();
signals:
    void to_delete(Connection* con);
};

#endif // CONNECTION_H
