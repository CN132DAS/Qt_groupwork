#ifndef MINDMAPVIEWER_H
#define MINDMAPVIEWER_H

#include <QGraphicsView>
#include <QWidget>

class MindMapViewer : public QGraphicsView
{
private:
    QWidget* parent;
    QGraphicsScene* scene;
public:
    MindMapViewer(QWidget* parent= nullptr);
    void show();
};

#endif // MINDMAPVIEWER_H
