#ifndef MYGRAPHICSOBJECT_H
#define MYGRAPHICSOBJECT_H

#include <QDesktopServices>
#include <QGraphicsObject>
#include <QGraphicsSceneMouseEvent>
#include <QUrl>

class MyGraphicsObject : public QGraphicsObject
{
    Q_OBJECT
public:
    MyGraphicsObject();
    QPointF get_middlePoint(int type);
    virtual QString get_info() const = 0;
    virtual void open() = 0;
signals:
    void position_changed();
};

int determineRegion(MyGraphicsObject* item1,MyGraphicsObject* item2);

#endif // MYGRAPHICSOBJECT_H
