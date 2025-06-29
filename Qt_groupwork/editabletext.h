#ifndef EDITABLETEXT_H
#define EDITABLETEXT_H

#include <QAbstractTextDocumentLayout>
#include <QGraphicsSceneMouseEvent>
#include <QInputDialog>
#include <QKeyEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QTextCursor>
#include <QTextDocument>
#include "mygraphicsobject.h"


class EditableText : public MyGraphicsObject
{
private:
    static QPen selectedPen;
    QTextDocument* document;
    int ID;
    QString name;
    QString content;
    bool isEditing = false;
    qreal width;
    qreal height;
    void updateSize();
public:
    EditableText(QString name_,int ID_,QString content_ = "请输入文字");
    void setText(const QString &text);
    void save(QTextStream& out,int& i);
    void update_size();
public:
    QString get_info() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    QRectF boundingRect() const override;
    int type() const override;
    void open() override;
};

#endif // EDITABLETEXT_H
