#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <QObject>
#include <QVarLengthArray>
#include <Qstring>
#include "connection.h"
#include "content.h"
#include "setting.h"

class SaveFile : public QObject   //存档文件结构
{
    Q_OBJECT;
    QVarLengthArray<Content> content; //文字、图像与文件/PDF，可能后续仍需细化
    QVarLengthArray<Connection> connection; //用于连接content的曲线
    Setting s; //储存一些设定，是否有存在必要仍需观察

public:
    explicit SaveFile(QObject *parent = nullptr);

signals:
};

#endif // SAVEFILE_H
