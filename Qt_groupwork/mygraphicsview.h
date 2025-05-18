#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>

class MyGraphicsView : public QGraphicsView
{
private:
    QGraphicsScene* scene;
protected:
    void resizeEvent(QResizeEvent* event) override;
public:
    MyGraphicsView(QWidget* parent = nullptr);
public slots:
    void showView();
};

#endif // MYGRAPHICSVIEW_H
