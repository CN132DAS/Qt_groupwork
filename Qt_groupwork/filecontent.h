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




class FileContent : public QGraphicsItem
{
    int m_spacing,m_textWidth,m_totalWidth,m_totalHeight,m_margin;
    int ID;//从1开始
    QString name;
    QPoint pos;
    QSize m_iconSize;
    static QIcon fileIcon;
public:
    FileContent(QString name_,QPoint pos_,int ID_);
    QPoint get_delta();
    void save(QTextStream& in);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget = nullptr) override;    
};

#endif // FILECONTENT_H
