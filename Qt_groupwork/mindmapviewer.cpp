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
}

void MindMapViewer::new_save(){
    scene->clear();
    save_SF->new_save();
    this->setEnabled(true);
}

void MindMapViewer::close_save(){
    centerOn(mapToScene(QPoint(0,0)));
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
            auto pair = save_SF->add_text(event->pos());
            QPoint delta = pair.first;
            EditableText* text = pair.second;
            scene->addItem(text);
            QPoint scene_pos = mapToScene(event->pos()).toPoint();
            scene_pos -= delta;
            text->setPos(scene_pos);
            scene->update();
        }
        else if (_state_ == "addPic"){
            QString dir = QFileDialog::getOpenFileName(this,"选择图片",QString(), "图像 (*.png *.xpm *.jpg)");
            if(dir!=""){
                auto pair = save_SF->add_pic(dir,event->pos());
                QPoint delta = pair.first;
                Pic* pic = pair.second;
                scene->addItem(pic);
                QPoint scene_pos = mapToScene(event->pos()).toPoint();
                scene_pos -= delta;
                pic->setPos(scene_pos);
                scene->update();
            }
        }
        if(_state_ == "addFile"){
            QString dir = QFileDialog::getOpenFileName(this,"选择文件",QString());
            if(dir!=""){
                auto pair = save_SF->add_file(dir,event->pos());
                QPoint delta = pair.first;
                FileContent* file = pair.second;
                if(file == nullptr)
                    return;
                scene->addItem(file);
                QPoint scene_pos = mapToScene(event->pos()).toPoint();
                scene_pos -= delta;
                file->setPos(scene_pos);
            }
        }
        else if(_state_ =="drag"){
            tmp_pos = event->pos();
            m_panning = true;
            setCursor(Qt::ClosedHandCursor);
        }
    }
    event->accept();
}

void MindMapViewer::mouseMoveEvent(QMouseEvent* event){
    if(_state_ =="drag"&&m_panning){
        QPointF delta = event->pos()- tmp_pos;
        int w = viewport()->rect().width();
        int h = viewport()->rect().height();
        QPoint newCenter(w / 2. - delta.x()+0.5,  h / 2. - delta.y()+0.5);
        centerOn(mapToScene(newCenter));
        tmp_pos = event->pos();
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
        setTransformationAnchor(QGraphicsView::AnchorViewCenter);
        int wheelValue = event->angleDelta().y();
        double ratio = (double)wheelValue / (double)1200 + 1;
        this->scale(ratio, ratio);
        event->accept();
    }
}
