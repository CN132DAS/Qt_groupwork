#ifndef FILECONTENT_H
#define FILECONTENT_H

#include <QFile>
#include <QFontMetrics>
#include <QIcon>
#include <QPainter>
#include <QSize>
#include <QString>
#include <QStyleOptionGraphicsItem>
#include <QTextStream>
#include "mygraphicsobject.h"

class FileContent : public MyGraphicsObject
{
    int textWidth,totalWidth,totalHeight,margin;
    int ID;
    QString name;
    QSize iconSize;
    static QIcon fileIcon;
public:
    FileContent(QString name_,int ID_,bool loadMode = false);
    void save(QTextStream& out,int& i);
    QString get_info() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
    int type() const override;
    void open() override;
};

#endif // FILECONTENT_H
