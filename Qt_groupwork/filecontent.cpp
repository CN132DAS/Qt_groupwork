#include "filecontent.h"

QIcon FileContent::fileIcon(":/assets/file.svg");

FileContent::FileContent(QString name_,QPoint pos_,int ID_)
    :ID(ID_),name(name_),pos(pos_){
    m_spacing = 0;
    m_iconSize = QSize(32, 32);
    QFontMetrics fm(QFont("times",10));
    m_textWidth = fm.horizontalAdvance(name);
    m_totalWidth = m_textWidth + m_spacing + m_iconSize.width();
    m_totalHeight = qMax(fm.height(), m_iconSize.height());
    m_margin = 5;
    m_totalWidth += 2 * m_margin;
    m_totalHeight += 2 * m_margin;
}

QPoint FileContent::get_delta(){
    return QPoint(m_totalWidth/2,m_totalHeight/2);
}

void FileContent::save(QTextStream& in){
    in<<this->ID<<" "<<this->name<<" "<<this->pos.x()<<" "<<this->pos.y()<<" "<<Qt::endl;
}

QRectF FileContent::boundingRect() const {
    return QRectF(0, 0, m_totalWidth, m_totalHeight);
}

void FileContent::paint
    (QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(Qt::black);
    painter->setBrush(Qt::white);
    painter->drawRect(boundingRect());
    painter->drawText(QRectF(m_margin, m_margin,
                             m_textWidth, m_totalHeight - 2 * m_margin),
                      Qt::AlignLeft | Qt::AlignVCenter,
                      name);
    QRectF iconRect(m_totalWidth - m_margin - m_iconSize.width(),
                    (m_totalHeight - m_iconSize.height()) / 2,
                    m_iconSize.width(),
                    m_iconSize.height());
    fileIcon.paint(painter, iconRect.toRect());
}
