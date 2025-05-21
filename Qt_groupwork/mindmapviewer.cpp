#include "mindmapviewer.h"

MindMapViewer::MindMapViewer(QWidget* parent_):QGraphicsView(parent_),scene(nullptr) {
    parent = parent_;
    scene = new QGraphicsScene(this);
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

void MindMapViewer::set_state(QString str){
    state = str;
}

void MindMapViewer::mousePressEvent(QMouseEvent* event){
    if(!this->isEnabled())
        return;
    qDebug()<<"MindMapViewer::mousePressEvent detected!";
    int x = event->pos().x();
    int y = event->pos().y();
    if(state == "addText"){

    }
    else if (state == "addPic"){

    }
    else if(state == "addFile"){

    }
}
