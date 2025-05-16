#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <QObject>
#include <QVarLengthArray>
#include <Qstring>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "connection.h"
#include "content.h"
#include "setting.h"


class SaveFile : public QObject   //存档文件结构
{
    Q_OBJECT;
private:
    QString saveName;
    QVarLengthArray<Content> content; //文字、图像与文件/PDF，可能后续仍需细化
    QVarLengthArray<Connection> connection; //用于连接content的曲线
    Setting s; //储存一些设定，是否有存在必要仍需观察
    QGraphicsScene* scene=nullptr;
    QGraphicsView* view=nullptr;
private:
    void resize();
public:
    explicit SaveFile(QString saveName_="",QObject *parent = nullptr);
public slots:
    void create_save(QString saveName_,QWidget* parent);
signals:
    void view_toAnchor(QGraphicsView* view);
};

#endif // SAVEFILE_H
