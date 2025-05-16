#include "savefile.h"

SaveFile::SaveFile(QString saveName_,QObject *parent)
    : QObject{parent},saveName(saveName_)
{
    // connect()
}
void SaveFile::resize(){

}
void SaveFile:: create_save(QString saveName_,QWidget* parent){
    saveName = saveName_;
    if(scene!=nullptr&&view!=nullptr){
        delete scene;
        delete view;
    }
    scene = new QGraphicsScene;
    view = new QGraphicsView;
    scene->addText("Hello World!");
    view->setParent(parent);
    view->setScene(scene);
    view->show();

}
