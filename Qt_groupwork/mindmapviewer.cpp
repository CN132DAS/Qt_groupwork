#include "mindmapviewer.h"

MindMapViewer::MindMapViewer(QWidget* parent_):QGraphicsView(parent_),scene(nullptr),
                                                m_panning(false), m_panStartX(0), m_panStartY(0){
    parent = parent_;
    scene = new QGraphicsScene(this);
    scene->setSceneRect(-1e6,-1e6,2e6,2e6);
    scene->addText("新建或打开文件以继续");
    this->setScene(scene);
    setDragMode(QGraphicsView::DragMode::NoDrag);
    setInteractive(false);
    setEnabled(false);
}

void MindMapViewer::init(SaveFile* save){
    save_SF = save;
    scene->clear();
    this->update();
    this->setEnabled(true);
}

void MindMapViewer::set_drag_mode(bool checked){
    if(checked)
        setDragMode(QGraphicsView::ScrollHandDrag);
    else
        setDragMode(QGraphicsView::DragMode::NoDrag);
    qDebug()<<"current drag mode:"<<dragMode();
}

void MindMapViewer::set_state(QString str){
    state = str;
}

void MindMapViewer::wheelEvent(QWheelEvent* event){
    setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    double scaleFactor = 1.15;
    if (event->angleDelta().y() > 0) {
        scale(scaleFactor, scaleFactor);
    } else {
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }
}

void MindMapViewer::mousePressEvent(QMouseEvent* event){
    if(!this->isEnabled())
        return;
    if(event->button() == Qt::LeftButton){
        if(state == "addText"){
            return;
        }
        else if (state == "addPic"){
            QString dir = QFileDialog::getOpenFileName(this,"选择图片",QString(), "Images (*.png *.xpm *.jpg)");
            if(dir!=""){
                QFileInfo tmp(dir);
                QString picName = "Pic_"+QString::number(save_SF->get_picNum()+1)+"."+tmp.suffix();
                QString targetPath = savePath+"/"+save_SF->get_saveName()+"/"+picName;
                QFile::copy(dir,targetPath);
                qDebug()<<"going to add pic "<<picName<<" in "<<targetPath;
                QPoint mousePos = event->position().toPoint();
                save_SF->add_pic(picName,mousePos);
                QPixmap pic_pixmap(targetPath);
                int w = pic_pixmap.width();
                int h = pic_pixmap.height();
                QGraphicsPixmapItem* pic= new QGraphicsPixmapItem(pic_pixmap);
                scene->addItem(pic);
                QPoint scene_pos = mapToScene(event->pos()).toPoint();
                QPoint delta(w/2,h/2);
                scene_pos -= delta;
                pic->setPos(scene_pos);
                scene->update();
            }
        }
        if(state == "addFile"){
            return;
        }
        else if(state =="drag"){
            return;
        }
    }
}

