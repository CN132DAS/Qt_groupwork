#ifndef MINDMAPVIEWER_H
#define MINDMAPVIEWER_H

#include <QFile>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QMessageBox>
#include <QPixmap>
#include <QScrollBar>
#include <QWidget>
#include "savefile.h"

extern QString _state_;

class MindMapViewer : public QGraphicsView
{
private:
    QPoint m_last_pos;
    QGraphicsScene* scene;
    QWidget* parent;
    qreal view_x,view_y;
    SaveFile* save_SF;
    bool m_panning;
    QGraphicsItem* selectedItem;
public:
    MindMapViewer(QWidget* parent= nullptr,SaveFile* save = nullptr);
    void new_save();
    void close_save();
    void load(QString dir);
public slots:
    // void set_drag_mode(bool checked);
public:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
};


#endif // MINDMAPVIEWER_H
