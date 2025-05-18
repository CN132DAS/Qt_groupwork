#include "mygraphicsview.h"

MyGraphicsView::MyGraphicsView(QWidget* parent):QGraphicsView(parent) {}
void MyGraphicsView::showView(){
    qDebug()<<2;
    this->setScene(scene);
    this->show();
}
void MyGraphicsView:: resizeEvent(QResizeEvent* event){

}
