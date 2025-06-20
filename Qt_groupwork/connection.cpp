#include "connection.h"

Connection::Connection(QGraphicsItem *item1_,QGraphicsItem *item2_,int ID_)
    :ID(ID_),item1(item1_),item2(item2_){
    pen = QPen(Qt::blue, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    setZValue(-1);
    updatePath();
    // 监听两个矩形的位置变化
    if (item1) {
        item1->setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    }
    if (item2) {
        item2->setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    }
}

void Connection::save(QTextStream& in){
    in<<this->ID<<" "<<this->gatSaveInfo(item1)<<" "<<this->gatSaveInfo(item2)<<Qt::endl;
}

QPair<QGraphicsItem*,QGraphicsItem*> Connection::get_pair(){return qMakePair(item1,item2);}

//私有函数
QPair<QPointF, QPointF> Connection::getConnectionPoints(QGraphicsItem* item1, QGraphicsItem* item2) const
{
    QRectF rect1 = item1->mapRectToScene(item1->boundingRect());
    QRectF rect2 = item2->mapRectToScene(item2->boundingRect());

    QPointF center1 = rect1.center();
    QPointF center2 = rect2.center();

    QPointF top1(center1.x(), rect1.top());
    QPointF bottom1(center1.x(), rect1.bottom());
    QPointF left1(rect1.left(), center1.y());
    QPointF right1(rect1.right(), center1.y());

    QPointF top2(center2.x(), rect2.top());
    QPointF bottom2(center2.x(), rect2.bottom());
    QPointF left2(rect2.left(), center2.y());
    QPointF right2(rect2.right(), center2.y());

    bool item2IsRight = center2.x() > center1.x();
    bool item2IsBottom = center2.y() > center1.y();

    QVector<QPointF> candidates1, candidates2;

    if (item2IsRight) {
        candidates1 << right1;
    } else {
        candidates1 << left1;
    }
    if (item2IsBottom) {
        candidates1 << bottom1;
    } else {
        candidates1 << top1;
    }

    if (!item2IsRight) {
        candidates2 << right2;
    } else {
        candidates2 << left2;
    }
    if (!item2IsBottom) {
        candidates2 << bottom2;
    } else {
        candidates2 << top2;
    }

    QPair<QPointF, QPointF> bestPair;
    qreal bestAngleDiff = 360.0;

    foreach (const QPointF& p1, candidates1) {
        foreach (const QPointF& p2, candidates2) {
            QPointF vec = p2 - p1;
            qreal angle = qAtan2(qAbs(vec.y()), qAbs(vec.x())) * 180 / M_PI;
            qreal angleDiff = qMin(qAbs(angle - 45), qAbs(angle + 45));

            if (angleDiff < bestAngleDiff) {
                bestAngleDiff = angleDiff;
                bestPair = qMakePair(p1, p2);
            }
        }
    }

    return bestPair;
}

void Connection::updatePath()
{
    auto points = getConnectionPoints(item1, item2);
    QPointF startPoint = mapFromScene(points.first);
    QPointF endPoint = mapFromScene(points.second);

    path = QPainterPath();
    path.moveTo(startPoint);
    qreal dx = endPoint.x() - startPoint.x();
    qreal dy = endPoint.y() - startPoint.y();

    QPointF ctrl1, ctrl2;
    if (qAbs(dx) > qAbs(dy)) {
        ctrl1 = QPointF(startPoint.x() + dx * 0.3, startPoint.y());
        ctrl2 = QPointF(endPoint.x() - dx * 0.3, endPoint.y());
    } else {
        ctrl1 = QPointF(startPoint.x(), startPoint.y() + dy * 0.3);
        ctrl2 = QPointF(endPoint.x(), endPoint.y() - dy * 0.3);
    }
    path.cubicTo(ctrl1, ctrl2, endPoint);
    prepareGeometryChange();
}

QString Connection::gatSaveInfo(QGraphicsItem* item){
    if (auto* fileContent = dynamic_cast<FileContent*>(item)) {
        return "file " + QString::number(fileContent->get_ID());
    }
    else if (auto* editableText = dynamic_cast<EditableText*>(item)) {
        return "text " + QString::number(editableText->get_ID());
    }
    else if (auto* pic = dynamic_cast<Pic*>(item)) {
        return "pic " + QString::number(pic->get_ID());
    }
    return "";
}

//重载函数
QVariant Connection::itemChange(GraphicsItemChange change, const QVariant& value)
{
    if (change == ItemScenePositionHasChanged) {
        updatePath();
    }
    return QGraphicsItem::itemChange(change, value);
}

void Connection::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(pen);
    painter->drawPath(path);
}

QRectF Connection::boundingRect() const
{
    return path.boundingRect().adjusted(-pen.width(), -pen.width(),
                                          pen.width(), pen.width());
}
