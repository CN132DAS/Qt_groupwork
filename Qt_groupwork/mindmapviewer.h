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
#include "editabletext.h"
#include "func_.h"
#include "savefile.h"

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
    MindMapViewer(QWidget* parent= nullptr,SaveFile* save = nullptr);
    void disable();
    void set_state(QString str);
    void load(QString dir);
    void clear();
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    bool is_panning();
public slots:
    void set_saveFile(SaveFile* save);
    void set_drag_mode(bool checked);
};


#endif // MINDMAPVIEWER_H
