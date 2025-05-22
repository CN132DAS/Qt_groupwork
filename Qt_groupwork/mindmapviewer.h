#ifndef MINDMAPVIEWER_H
#define MINDMAPVIEWER_H

#include <QFile>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QPixmap>
#include <QWidget>
#include "savefile.h"

extern QString savePath;

class MindMapViewer : public QGraphicsView
{
private:
    QString state;
    QWidget* parent;
    QGraphicsScene* scene;
    SaveFile* save_SF;
    bool m_panning;
    int m_panStartX;
    int m_panStartY;
public:
    MindMapViewer(QWidget* parent= nullptr);
    void set_state(QString str);
    void mousePressEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
public slots:
    void init(SaveFile* save);
    void set_drag_mode(bool checked);
};


#endif // MINDMAPVIEWER_H
