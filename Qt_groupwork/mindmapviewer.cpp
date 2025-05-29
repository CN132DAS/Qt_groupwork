#include "mindmapviewer.h"

MindMapViewer::MindMapViewer(QWidget* parent_,SaveFile* save):
    QGraphicsView(parent_),scene(nullptr),save_SF(save),m_panning(false){
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

bool MindMapViewer::is_panning(){
    return m_panning;
}

void MindMapViewer::clear(){
    scene->clear();
    this->update();
}

void MindMapViewer::set_saveFile(SaveFile* save){
    save_SF = save;
    this->setEnabled(true);
}

void MindMapViewer::disable(){
    scene->clear();
    scene->addText("新建或打开文件以继续");
    this->setInteractive(false);
    this->setEnabled(false);
    this->update();
}

void MindMapViewer::set_drag_mode(bool checked){
    if(checked)
        this->setDragMode(QGraphicsView::ScrollHandDrag);
    else
        this->setDragMode(QGraphicsView::DragMode::NoDrag);
}

void MindMapViewer::set_state(QString str){
    state = str;
}

void MindMapViewer::load(QString dir){
    save_SF->load(dir,scene);
    this->setEnabled(true);
    this->update();
}

void MindMapViewer::mousePressEvent(QMouseEvent* event){
    if(!this->isEnabled())
        return;
    if(event->button() == Qt::LeftButton){
        if(state == "addText"){
            QString textName = "Text_"+QString::number((save_SF->get_textNum()+1));
            EditableText* text = new EditableText(textName,event->pos());
            save_SF->add_text(text);
            scene->addItem(text);
            QPoint scene_pos = mapToScene(event->pos()).toPoint();
            QPoint delta = text->get_delta();
            scene_pos -= delta;
            text->setPos(scene_pos);
            scene->update();
        }
        else if (state == "addPic"){
            QString dir = QFileDialog::getOpenFileName(this,"选择图片",QString(), "图像 (*.png *.xpm *.jpg)");
            if(dir!=""){
                QFileInfo tmp(dir);
                QString picName = "Pic_"+QString::number(save_SF->get_picNum()+1)+"."+tmp.suffix();
                QString targetPath = get_filePath(picName);
                QFile::copy(dir,targetPath);
                qDebug()<<"going to add pic "<<picName;
                qDebug()<<" in "<<targetPath;
                QPoint mousePos = event->position().toPoint();
                Pic* pic_ = new Pic(picName,get_filePath(picName),mousePos);
                save_SF->add_pic(pic_);
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
            QString dir = QFileDialog::getOpenFileName(this,"选择文件",QString());
            if(dir!=""){
                QFileInfo tmp(dir);
                QString fileName = tmp.fileName();
                QString targetPath = get_filePath(fileName);
                if(QDir(targetPath).exists(targetPath)){
                    QMessageBox::warning(this,"文件名重复","已有同名文件，请修改文件名！");
                    return;
                }
                QFile::copy(dir,targetPath);
                qDebug()<<"going to add file "<<fileName;
                qDebug()<<" in "<<targetPath;
                QPoint mousePos = event->position().toPoint();
                FileContent* file = new FileContent(fileName,mousePos);
                save_SF->add_file(file);
                scene->addItem(file);
                QPoint scene_pos = mapToScene(event->pos()).toPoint();
                QPoint delta = file->get_delta();
                scene_pos -= delta;
                file->setPos(scene_pos);
                scene->update();
            }
        }
        else if(state =="drag"){
            tmp_pos = event->pos();
            m_panning = true;
            setCursor(Qt::ClosedHandCursor);
        }
    }
    event->accept();
}

void MindMapViewer::mouseMoveEvent(QMouseEvent* event){
    if(state =="drag"&&m_panning){
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
    if(state =="drag"){
        setCursor(Qt::ArrowCursor);
        m_panning = false;
    }
    event->accept();
}

void MindMapViewer::wheelEvent(QWheelEvent* event){
    setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    int wheelValue = event->angleDelta().y();
    double ratio = (double)wheelValue / (double)1200 + 1;
    this->scale(ratio, ratio);
    event->accept();
}
