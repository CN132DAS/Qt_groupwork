#include "editabletext.h"

QPen EditableText::selectedPen = QPen(Qt::red, 3, Qt::DashLine);

EditableText::EditableText(QString name_,int ID_,QString content_)
    :name(name_),ID(ID_),document(new QTextDocument(this)),content(content_) {
    document->setDocumentMargin(2);
    document->setDefaultFont(QFont("Arial", 10));
    document->setTextWidth(200);
    document->setPlainText(content);
    this->update_size();
}

void EditableText::save(QTextStream& out, int& i)
{
    if(!deleted) {
        QPointF pos = this->scenePos();
        out << i << " " << "Text_" << QString::number(i) << " " << pos.x() << " " << pos.y() << " " << content << Qt::endl;
        ID = i;
        i++;
    }
}

int EditableText::type() const{
    return UserType + 3;
}

void EditableText::open()
{
    // 使用输入对话框编辑文本
    bool ok;
    QString newText = QInputDialog::getMultiLineText(nullptr, tr("编辑文本"),
                                                     tr("内容:"), content, &ok);
    if (ok) {
        setText(newText);
    }
}

void EditableText::update_size()
{
    width = document->idealWidth() + 10;
    height = document->size().height() + 10;
    prepareGeometryChange();
}

void EditableText::setText(const QString& text)
{
    content = text;
    document->setPlainText(content);
    update_size();
    update();
}

//override

QString EditableText::get_info() const
{
    return "text " + QString::number(ID);
}

void EditableText::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    if (option->state & QStyle::State_Selected) {
        painter->save();
        painter->setPen(selectedPen);
        painter->drawRect(boundingRect());
        painter->restore();
    }
    painter->setBrush(Qt::white);
    painter->setPen(Qt::black);
    painter->drawRect(boundingRect());
    painter->save();
    QAbstractTextDocumentLayout::PaintContext ctx;
    painter->translate(-width/2 + document->documentMargin(),
                       -height/2 + document->documentMargin());
    document->documentLayout()->draw(painter, ctx);
    painter->restore();
}

QRectF EditableText::boundingRect() const
{
    return QRectF(-width/2, -height/2, width, height);
}
