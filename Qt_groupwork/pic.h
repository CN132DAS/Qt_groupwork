#ifndef PIC_H
#define PIC_H

#include <QGraphicsPixmapItem>
#include <QStyleOptionGraphicsItem>
#include <QPainter>

class Pic : public QGraphicsPixmapItem
{
    QString name;
    int ID;//从1开始
public:
    Pic(QString name_,int ID_);
    int get_ID();
    void save(QTextStream& in);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
signals:
    void position_changed();
};

#endif // PIC_H
