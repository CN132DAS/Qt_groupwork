#ifndef CONNECTION_H
#define CONNECTION_H

#include <QGraphicsObject>
#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include "editabletext.h"
#include "filecontent.h"
#include "pic.h"


class Connection : public QGraphicsObject
{
private:
    int ID;
    QGraphicsItem *item1,*item2;
    QPen pen;
    QPainterPath path;
private:
    QPair<QPointF, QPointF> getConnectionPoints(QGraphicsItem* item1, QGraphicsItem* item2) const;
    QString gatSaveInfo(QGraphicsItem* item);
public:
    Connection(QGraphicsItem *item1_,QGraphicsItem *item2_,int ID_);
    void save(QTextStream& in);
    QPair<QGraphicsItem*,QGraphicsItem*> get_pair();
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    QRectF boundingRect() const override;
signals:
    void deleteConnection(int ID,QString type = "Connection");
public slots:
    void updatePath();
};

#endif // CONNECTION_H
