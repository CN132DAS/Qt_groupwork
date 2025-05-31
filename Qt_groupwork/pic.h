#ifndef PIC_H
#define PIC_H

#include <QGraphicsPixmapItem>

class Pic : public QGraphicsPixmapItem
{
    QString name;
    QPoint pos;
    int ID;//从1开始
public:
    Pic(QString name_,QPoint pos_,int ID_);
    void save(QTextStream& in);
};

#endif // PIC_H
