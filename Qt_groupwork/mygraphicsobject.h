#ifndef MYGRAPHICSOBJECT_H
#define MYGRAPHICSOBJECT_H

#include <QGraphicsObject>

class MyGraphicsObject : public QGraphicsObject
{
    Q_OBJECT
public:
    MyGraphicsObject();
    virtual QString get_info() const = 0;
signals:
    void position_changed();
};

#endif // MYGRAPHICSOBJECT_H
