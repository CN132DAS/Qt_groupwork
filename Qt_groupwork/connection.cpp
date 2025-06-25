#include "connection.h"
#include "function.h"

//public
Connection::Connection(MyGraphicsObject *item1_,MyGraphicsObject *item2_,int ID_)
    :ID(ID_),item1(item1_),item2(item2_){
    pen = QPen(Qt::blue, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    setZValue(-1);
    updatePath();
}

void Connection::save(QTextStream& out,int i){
    this->ID = i;
    out<<this->ID<<" "<<this->get_info(item1)<<" "<<this->get_info(item2)<<Qt::endl;
}

QPair<MyGraphicsObject*,MyGraphicsObject*> Connection::get_pair(){return qMakePair(item1,item2);}

//private
QPair<QPointF, QPointF> Connection::get_ConnectionPoints(MyGraphicsObject* item1, MyGraphicsObject* item2) const
{
    QPointF point[2];
    MyGraphicsObject* a[2];
    a[0] = item1;
    a[1] = item2;
    for(int i=0;i<=1;i++){
        int type = determineRegion(a[i],a[1-i]);
        point[i] = a[1-i]->get_middlePoint(type);
    }
    return qMakePair(point[0],point[1]);
}

void Connection::updatePath()
{
    auto points = get_ConnectionPoints(item1, item2);
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
    update();
}

QString Connection::get_info(MyGraphicsObject* item){
    return item->get_info();
}

//override
QString Connection::get_info()const{return "line "+QString::number(this->ID);}

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

int Connection::type() const{
    return UserType + 4;
}

void Connection::open(){}
