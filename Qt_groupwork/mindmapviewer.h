#ifndef MINDMAPVIEWER_H
#define MINDMAPVIEWER_H

#include <QGraphicsView>
#include <QWidget>
#include <QMouseEvent>
#include "savefile.h"

class MindMapViewer : public QGraphicsView
{
private:
    QString state;
    QWidget* parent;
    QGraphicsScene* scene;
    SaveFile* save_SF;
public:
    MindMapViewer(QWidget* parent= nullptr);
    void set_state(QString str);
    void mousePressEvent(QMouseEvent* event);
public slots:
    void init(SaveFile* save);
};


#endif // MINDMAPVIEWER_H
