#ifndef PIC_H
#define PIC_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

class Pic : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
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
