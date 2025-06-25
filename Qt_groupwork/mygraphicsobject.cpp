#include "mygraphicsobject.h"

MyGraphicsObject::MyGraphicsObject() {}

QPointF MyGraphicsObject::get_middlePoint(int type){
    QRectF rect = this->mapRectToScene(this->boundingRect());
    QPointF center = rect.center();
    if(type == 1)//top-middle
        return QPointF(center.x(),rect.top());
    else if(type == 4)//left-middle
        return QPointF(rect.left(),center.y());
    else if(type == 3)//bottom-middle
        return QPointF(center.x(),rect.bottom());
    else if(type == 2)//right-middle
        return QPointF(rect.right(),center.y());
    return QPointF(0,0);
}

int determineRegion(MyGraphicsObject* item1,MyGraphicsObject* item2){
    QRectF rect2 = item2->mapRectToScene(item2->boundingRect());
    QPointF center1 = item1->mapRectToScene(item1->boundingRect()).center();
    QPointF topLeft = rect2.topLeft();
    QPointF topRight = rect2.topRight();
    QPointF bottomLeft = rect2.bottomLeft();
    QPointF bottomRight = rect2.bottomRight();
    bool aboveTopLeftLine = (center1.y() - topLeft.y()) <  (center1.x() - topLeft.x());
    bool aboveTopRightLine = (center1.y() - topRight.y()) <  -(center1.x() - topRight.x());
    bool aboveBottomLeftLine = (center1.y() - bottomLeft.y()) <  -(center1.x() - bottomLeft.x());
    bool aboveBottomRightLine = (center1.y() - bottomRight.y()) <  (center1.x() - bottomRight.x());
    if (aboveTopLeftLine && aboveTopRightLine) {
        return 1; // 上方区域
    } else if (!aboveTopRightLine && aboveBottomRightLine) {
        return 2; // 右侧区域
    } else if (!aboveBottomLeftLine && !aboveBottomRightLine) {
        return 3; // 下方区域
    } else if (!aboveTopLeftLine && aboveBottomLeftLine) {
        return 4; // 左侧区域
    }
    return 1;
}
