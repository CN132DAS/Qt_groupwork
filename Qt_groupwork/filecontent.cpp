#include "filecontent.h"
#include "function.h"

QIcon FileContent::fileIcon(":/assets/file.svg");

//public
FileContent::FileContent(QString name_,int ID_)
    :ID(ID_),name(name_){
    iconSize = QSize(32, 32);
    QFontMetrics fm(QFont("times",10));
    textWidth = fm.horizontalAdvance(name);
    margin = 5;
    totalWidth = textWidth + iconSize.width() + 3 * margin;
    totalHeight = qMax(fm.height(), iconSize.height()) + 2 * margin;
}

void FileContent::save(QTextStream& out,int i){
    QPointF pos = this->scenePos();
    out<<i<<" "<<this->name<<" "<<pos.x()<<" "<<pos.y()<<" "<<Qt::endl;
    QFile::copy(get_fileTempPath(this->name),get_filePath(this->name));
    this->ID = i;
}

//override
QString FileContent::get_info() const{return "file "+QString::number(this->ID);}

void FileContent::paint
    (QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (option->state & QStyle::State_Selected) {
        painter->save();
        painter->setPen(QPen(Qt::red, 3, Qt::DashLine));
        painter->drawRect(boundingRect().adjusted(-2, -2, 2, 2));
        painter->restore();
    }
    painter->setPen(Qt::black);
    painter->setBrush(Qt::white);
    painter->drawRect(boundingRect());
    QRectF textRect(-totalWidth / 2 + margin,-totalHeight / 2 + margin,
                    textWidth,totalHeight - 2 * margin);
    painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, name);
    QRectF iconRect(totalWidth / 2 - margin - iconSize.width(),-iconSize.height() / 2,
                    iconSize.width(),iconSize.height());
    fileIcon.paint(painter, iconRect.toRect());
}

QRectF FileContent::boundingRect() const {
    return QRectF(-totalWidth / 2, -totalHeight / 2, totalWidth, totalHeight);
}

int FileContent::type() const{
    return UserType + 2;
}



// QRectF FileContent::boundingRect() const {
//     return QRectF(0, 0, totalWidth, totalHeight);
// }

// void FileContent::paint
//     (QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget) {
//     Q_UNUSED(option);
//     Q_UNUSED(widget);
//     painter->setPen(Qt::black);
//     painter->setBrush(Qt::white);
//     painter->drawRect(boundingRect());
//     painter->drawText(QRectF(margin, margin,
//                              textWidth, totalHeight - 2 * margin),
//                       Qt::AlignLeft | Qt::AlignVCenter,
//                       name);
//     QRectF iconRect(totalWidth - margin - iconSize.width(),
//                     (totalHeight - iconSize.height()) / 2,
//                     iconSize.width(),
//                     iconSize.height());
//     fileIcon.paint(painter, iconRect.toRect());
//     if(option->state & QStyle::State_Selected){
//         painter->setPen(QPen(Qt::red, 3, Qt::DashLine));
//         painter->drawRect(boundingRect().adjusted(-2, -2, 2, 2));
//     }
// }
