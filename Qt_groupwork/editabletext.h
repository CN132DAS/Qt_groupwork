#ifndef EDITABLETEXT_H
#define EDITABLETEXT_H

#include <QGraphicsTextItem>
#include <QString>
#include <QPoint>
#include <QPainter>

class EditableText : public QGraphicsTextItem
{
    Q_OBJECT
private:
    QString name;
    void setTextInteraction(bool activate);
public:
    EditableText(QString name_);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QPoint get_delta();
};

#endif // EDITABLETEXT_H
