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
void MindMapViewer::show(){
    setEnabled(true);
}
