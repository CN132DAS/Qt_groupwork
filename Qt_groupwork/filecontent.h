#ifndef FILECONTENT_H
#define FILECONTENT_H

#include <QFontMetrics>
#include <QGraphicsItem>
#include <QIcon>
#include <QPainter>
#include <QSize>
#include <QString>
#include <QTextStream>
#include <QWidget>
#include "func_.h"


extern QIcon fileIcon;

class FileContent : public QGraphicsItem
{
    QString name;
    QString path;
    QPoint pos;
    int m_spacing,m_textWidth,m_totalWidth,m_totalHeight,m_margin;
    QSize m_iconSize;
public:
    FileContent(QString name_,QPoint pos_);
    QPoint get_delta();
    void save(QTextStream& in);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget = nullptr) override;    
};

#endif // FILECONTENT_H
