#ifndef MINDMAPVIEWER_H
#define MINDMAPVIEWER_H

#include <QFile>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QPixmap>
#include <QScrollBar>
#include <QWidget>
#include "savefile.h"

extern QString savePath;

class MindMapViewer : public QGraphicsView
{
private:
    QPointF tmp_pos;
    QPointF centerAnchor;
    QGraphicsScene* scene;
    QWidget* parent;
    QString state;
    SaveFile* save_SF;
    bool m_panning;
public:
    MindMapViewer(QWidget* parent= nullptr);
    void set_state(QString str);
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    bool is_panning();
public slots:
    void init(SaveFile* save);
    void set_drag_mode(bool checked);
};


#endif // MINDMAPVIEWER_H
