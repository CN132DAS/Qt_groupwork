#ifndef EDITABLETEXT_H
#define EDITABLETEXT_H

#include <QGraphicsTextItem>
#include <QString>
#include <QStyleOptionGraphicsItem>
#include <QPoint>
#include <QPainter>

class EditableText : public QGraphicsTextItem
{
    Q_OBJECT
private:
    QString name;
    int ID;
    void setTextInteraction(bool activate);
public:
    EditableText(QString name_,int ID_);
    QPoint get_delta();
    int get_ID();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // EDITABLETEXT_H
