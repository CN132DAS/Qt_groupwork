#ifndef FILECONTENT_H
#define FILECONTENT_H

#include <QFontMetrics>
#include <QGraphicsObject>
#include <QIcon>
#include <QPainter>
#include <QSize>
#include <QString>
#include <QStyleOptionGraphicsItem>
#include <QTextStream>
#include <QWidget>




class FileContent : public QGraphicsObject
{
    Q_OBJECT
    int m_spacing,m_textWidth,m_totalWidth,m_totalHeight,m_margin;
    int ID;//从1开始
    QString name;
    QSize m_iconSize;
    static QIcon fileIcon;
public:
    FileContent(QString name_,int ID_);
    QPoint get_delta();
    int get_ID();
    void save(QTextStream& in);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget = nullptr) override;
signals:
    void position_changed();
};

#endif // FILECONTENT_H
