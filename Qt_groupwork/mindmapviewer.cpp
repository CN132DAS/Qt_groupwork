#include "mindmapviewer.h"
#include "func_.h"

// void MindMapViewer::clear(){
//     scene->clear();
//     this->update();
// }

// void MindMapViewer::disable(){
//     scene->clear();
//     scene->addText("新建或打开文件以继续");
//     this->setInteractive(false);
//     this->setEnabled(false);
//     this->update();
// }

// void MindMapViewer::set_drag_mode(bool checked){
//     if(checked)
//         this->setDragMode(QGraphicsView::ScrollHandDrag);
//     else
//         this->setDragMode(QGraphicsView::DragMode::NoDrag);
// }
//

MindMapViewer::MindMapViewer(QWidget* parent_,SaveFile* save):
    QGraphicsView(parent_),scene(nullptr),save_SF(save),m_panning(false){
    parent = parent_;
    scene = new QGraphicsScene(this);
    save->set_scene(scene);
    scene->setSceneRect(-1e6,-1e6,2e6,2e6);
    scene->addText("新建或打开文件以继续");
    this->setScene(scene);
    this->setDragMode(QGraphicsView::DragMode::NoDrag);
    this->setInteractive(false);
    this->setEnabled(false);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void MindMapViewer::new_save(){
    scene->clear();
    save_SF->new_save();
    this->setEnabled(true);
}

void MindMapViewer::close_save(){
    this->setTransform(QTransform());
    this->centerOn(QPointF(0,0));
    scene->clear();
    save_SF->clear();
    scene->addText("新建或打开文件以继续");
    this->setInteractive(false);
    this->setEnabled(false);
}

void MindMapViewer::load(QString dir){
    save_SF->load(dir,scene);
    this->setEnabled(true);
    this->update();
}

bool MindMapViewer::is_panning(){
    return m_panning;
}

//槽函数


//重载函数

void MindMapViewer::mousePressEvent(QMouseEvent* event){
    if(!this->isEnabled())
        return;
    if(event->button() == Qt::LeftButton){
        if(_state_ == "addText"){
            auto pair = save_SF->add_text();
            QPoint delta = pair.first;
            EditableText* text = pair.second;
            scene->addItem(text);
            QPointF scene_pos = mapToScene(event->pos());
            scene_pos -= delta;
            text->setPos(scene_pos);
        }
        else if (_state_ == "addPic"){
            QString dir = QFileDialog::getOpenFileName(this,"选择图片",QString(), "图像 (*.png *.xpm *.jpg)");
            if(dir!=""){
                auto pair = save_SF->add_pic(dir);
                QPoint delta = pair.first;
                Pic* pic = pair.second;
                scene->addItem(pic);
                QPointF scene_pos = mapToScene(event->pos());
                scene_pos -= delta;
                pic->setPos(scene_pos);
            }
        }
        if(_state_ == "addFile"){
            QString dir = QFileDialog::getOpenFileName(this,"选择文件",QString());
            if(dir!=""){
                auto pair = save_SF->add_file(dir);
                QPoint delta = pair.first;
                FileContent* file = pair.second;
                if(file == nullptr)
                    return;
                scene->addItem(file);
                QPointF scene_pos = mapToScene(event->pos());
                scene_pos -= delta;
                file->setPos(scene_pos);
            }
        }
        else if(_state_ =="drag"){
            setTransformationAnchor(QGraphicsView::NoAnchor);
            m_last_pos = event->pos();
            m_panning = true;
            setCursor(Qt::ClosedHandCursor);
            // setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        }
    }
    event->accept();
}

void MindMapViewer::mouseMoveEvent(QMouseEvent* event){
    if(_state_ =="drag"&&m_panning){
        QPointF mouseDelta = mapToScene(event->pos()) - mapToScene(m_last_pos);
        m_last_pos = event->pos();
        translate(mouseDelta.x(),mouseDelta.y());
        // QPoint delta = event->pos()- tmp_pos;
        // qDebug()<<"delta:"<<delta.x()<<delta.y();
        // qDebug()<<"Rect size:"<<view_x<<view_y;
        // QPoint oldCenter = viewport()->rect().center();
        // qDebug()<<"old center:"<<mapToScene(oldCenter).x()<<oldCenter.y();
        // QPointF newCenter = mapToScene(oldCenter - delta);
        // centerOn(newCenter);
        // qDebug()<<"new center:"<<newCenter.x()<<newCenter.y();
        // tmp_pos = event->pos();
    }
    event->accept();
}

void MindMapViewer::mouseReleaseEvent(QMouseEvent* event){
    if(_state_ =="drag"){
        setCursor(Qt::ArrowCursor);
        m_panning = false;
    }
    event->accept();
}

void MindMapViewer::wheelEvent(QWheelEvent* event){
    if(this->isEnabled()){
        // setTransformationAnchor(QGraphicsView::AnchorViewCenter);
        // int wheelValue = event->angleDelta().y();
        // double ratio = (double)wheelValue / (double)1200 + 1;
        // this->scale(ratio, ratio);
        QPointF sceneCenter = mapToScene(viewport()->rect().center());
        double scaleFactor = (event->angleDelta().y() > 0) ? 1.1 : 0.9;
        scale(scaleFactor, scaleFactor);
        centerOn(sceneCenter);
        event->accept();
    }
}
