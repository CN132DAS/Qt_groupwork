#ifndef PICTURECONTENT_H
#define PICTURECONTENT_H

#include <QFile>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QTextStream>
#include "mygraphicsobject.h"


class PictureContent : public MyGraphicsObject
{
private:
    int ID;
    QString suffix;
    QPixmap picture;
    int width,height;
    static QPen selectedPen;
public:
    PictureContent(QString name_,int ID_,QString suffix_,bool loadMode = false);
    void save(QTextStream& out,int& new_ID);
    QString get_info() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    int type() const override;
    void open() override;
};

#endif // PICTURECONTENT_H
