#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <QObject>
#include <QVarLengthArray>
#include <Qstring>
#include "connection.h"
#include "content.h"
#include "qgraphicsview.h"


class SaveFile : public QObject   //存档文件结构
{
    Q_OBJECT;
private:
    QString saveName;
    QVarLengthArray<Content> content; //文字、图像与文件/PDF，可能后续仍需细化
    QVarLengthArray<Connection> connection; //用于连接content的曲线
private:
    void resize();
public:
    explicit SaveFile(QString saveName_="",QObject *parent = nullptr);
public slots:
    void create_save(QString saveName_);
signals:
    void init_done();
};

#endif // SAVEFILE_H
