#include "mindmapviewer.h"
#include "function.cpp"

MindMapViewer::MindMapViewer(QWidget* parent_,SaveFile* save):
    QGraphicsView(parent_),scene(nullptr),save_SF(save),m_panning(false),selectedItem(nullptr){
    parent = parent_;
    scene = new QGraphicsScene(this);
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
    selectedItem = nullptr;
    scene->clear();
    save_SF->clear();
    scene->addText("新建或打开文件以继续");
    this->setInteractive(false);
    this->setEnabled(false);
}

void MindMapViewer::load(QString dir){
    _operation_ = false;
    scene->clear();
    save_SF->load(dir,scene);
    this->setEnabled(true);
    this->update();
}

void MindMapViewer::clear_selectedItem(){
    if(selectedItem&& selectedItem->flags() & QGraphicsItem::ItemIsSelectable)
        selectedItem->setSelected(false);
    selectedItem = nullptr;
}

GraphicsViewState MindMapViewer::get_state(){
    QPoint viewportCenter = this->viewport()->rect().center();
    QPointF sceneCenter = this->mapToScene(viewportCenter);
    qreal zoom = this->transform().m11();
    return GraphicsViewState(sceneCenter, zoom);
}

void MindMapViewer::restore_state(GraphicsViewState state){
    this->setTransform(QTransform());
    this->scale(state.zoomLevel, state.zoomLevel);
    this->centerOn(state.sceneCenter);
}

//override

void MindMapViewer::mousePressEvent(QMouseEvent* event){
    if(!this->isEnabled())
        return;
    if(event->button() == Qt::LeftButton){
        if(_state_ == "addText"){
            // auto pair = save_SF->add_text();
            // QPoint delta = pair.first;
            // EditableText* text = pair.second;
            // scene->addItem(text);
            // QPointF scene_pos = mapToScene(event->pos());
            // scene_pos -= delta;
            // text->setPos(scene_pos);
        }
        else if (_state_ == "addPic"){
            QString dir = QFileDialog::getOpenFileName(this,"选择图片",QString(), "图像 (*.png *.xpm *.jpg)");
            if(dir!=""){
                _operation_ = true;
                PictureContent* pic = save_SF->add_pic(dir);
                scene->addItem(pic);
                QPointF scene_pos = mapToScene(event->pos());
                pic->setPos(scene_pos);
            }
        }
        else if(_state_ == "addFile"){
            QString dir = QFileDialog::getOpenFileName(this,"选择文件",QString());
            if(dir!=""){
                FileContent* file = save_SF->add_file(dir);
                if(file == nullptr)
                    return;
                _operation_ = true;
                scene->addItem(file);
                QPointF scene_pos = mapToScene(event->pos());
                file->setPos(scene_pos);
            }
        }
        else if(_state_ == "addCon"){
            QPointF scenePos = mapToScene(event->pos());
            QGraphicsItem *clickedItem = scene->itemAt(scenePos, QTransform());
            if (clickedItem->flags() & QGraphicsItem::ItemIsSelectable){
                MyGraphicsObject *newClickedItem = dynamic_cast<MyGraphicsObject*>(clickedItem);
                if(selectedItem == nullptr){
                    selectedItem = newClickedItem;
                    selectedItem->setSelected(true);
                }
                else if(selectedItem == newClickedItem){
                    selectedItem->setSelected(false);
                    selectedItem = nullptr;
                }
                else{
                    Connection* con = save_SF->add_connection(selectedItem,newClickedItem);
                    if(con!=nullptr){
                        scene->addItem(con);
                        _operation_ = true;
                    }
                    selectedItem->setSelected(false);
                    selectedItem = nullptr;
                }
            }
        }
        else if(_state_ == "edit"){
            QPointF scenePos = mapToScene(event->pos());
            QGraphicsItem *clickedItem = scene->itemAt(scenePos, QTransform());
            if (clickedItem->flags() & QGraphicsItem::ItemIsSelectable){
                MyGraphicsObject *newClickedItem = dynamic_cast<MyGraphicsObject*>(clickedItem);
                if(selectedItem == nullptr){
                    selectedItem = newClickedItem;
                    selectedItem->setSelected(true);
                }
                else{
                    selectedItem->setSelected(false);
                    selectedItem = newClickedItem;
                    selectedItem->setSelected(true);
                }
            }
            else if(selectedItem != nullptr){
                selectedItem->setSelected(false);
                selectedItem = nullptr;
            }
        }
        else if(_state_ == "drag"){
            setTransformationAnchor(QGraphicsView::NoAnchor);
            m_last_pos = event->pos();
            m_panning = true;
            setCursor(Qt::ClosedHandCursor);
            QGraphicsItem *clickedItem = scene->itemAt(mapToScene(event->pos()),QTransform());
            if(clickedItem && clickedItem->flags() & QGraphicsItem::ItemIsSelectable){
                selectedItem = (MyGraphicsObject*)clickedItem;
                selectedItem->setSelected(true);
            }
        }
    }
    else if(event->button() == Qt::RightButton){
        if(_state_ == "addCon"){
            if(selectedItem != nullptr){
                selectedItem->setSelected(false);
                selectedItem = nullptr;
            }
        }
    }
    event->accept();
}

void MindMapViewer::mouseMoveEvent(QMouseEvent* event){
    if(_state_ == "drag"&&m_panning){
        if(!selectedItem){
            QPointF mouseDelta = mapToScene(event->pos()) - mapToScene(m_last_pos);
            translate(mouseDelta.x(),mouseDelta.y());
        }
        else{
            QPointF mouseDelta = mapToScene(event->pos()) - mapToScene(m_last_pos);
            selectedItem->setPos(selectedItem->pos() + mouseDelta);
            _operation_ = true;
            emit selectedItem->position_changed();
        }
        m_last_pos = event->pos();
        scene->update();
    }
    event->accept();
}

void MindMapViewer::mouseReleaseEvent(QMouseEvent* event){
    if(_state_ == "drag"){
        setCursor(Qt::ArrowCursor);
        m_panning = false;
        if(selectedItem)
            selectedItem->setSelected(false);
        selectedItem = nullptr;
        scene->update();
    }
    event->accept();
}

void MindMapViewer::mouseDoubleClickEvent(QMouseEvent *event){
    if(!this->isEnabled())
        return;
    if(_state_ == "edit"){
        QPointF scenePos = mapToScene(event->pos());
        QGraphicsItem *clickedItem = scene->itemAt(scenePos, QTransform());
        if (clickedItem->flags() & QGraphicsItem::ItemIsSelectable){
            MyGraphicsObject* item = dynamic_cast<MyGraphicsObject*>(clickedItem);
            item->open();
        }
    }
}

void MindMapViewer::wheelEvent(QWheelEvent* event){
    if(this->isEnabled()){
        QPointF sceneCenter = mapToScene(viewport()->rect().center());
        double scaleFactor = (event->angleDelta().y() > 0) ? 1.1 : 0.9;
        scale(scaleFactor, scaleFactor);
        centerOn(sceneCenter);
        scene->update();
        event->accept();
    }
}

void MindMapViewer::keyPressEvent(QKeyEvent *event){
    if(_state_ == "edit"&&selectedItem != nullptr&& event->key()==Qt::Key_Backspace)

}
