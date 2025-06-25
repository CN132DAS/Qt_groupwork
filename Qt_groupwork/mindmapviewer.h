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
extern bool _operation_;

struct GraphicsViewState {
    QPointF sceneCenter;
    qreal zoomLevel;
    GraphicsViewState() : zoomLevel(1.0) {}
    GraphicsViewState(const QPointF& center, qreal zoom)
        : sceneCenter(center), zoomLevel(zoom) {}
};

class MindMapViewer : public QGraphicsView
{
private:
    QPoint m_last_pos;
    QGraphicsScene* scene;
    QWidget* parent;
    SaveFile* save_SF;
    bool m_panning;
    MyGraphicsObject* selectedItem;
public:
    MindMapViewer(QWidget* parent= nullptr,SaveFile* save = nullptr);
    void new_save();
    void close_save();
    void load(QString dir);
    void clear_selectedItem();
    GraphicsViewState get_state();
    void restore_state(GraphicsViewState state);
public:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent* event) override;
};


#endif // MINDMAPVIEWER_H
