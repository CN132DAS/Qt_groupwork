#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QObject>
#include <QPoint>
#include <QString>
#include <QTextStream>
#include <QVarLengthArray>
#include <QVector>

extern QString savePath;

struct Pic{
    QString name;
    QPoint pos;
    Pic(QString name_,QPoint pos_);
};

class SaveFile : public QObject   //存档文件结构
{
    Q_OBJECT;
private:
    QString saveName;
    int picNum;
    QVarLengthArray<Pic> pic;

private:
    void resize();
public:
    explicit SaveFile(QString saveName_="",QObject *parent = nullptr);
    void add_pic(QString picName,QPoint mousePos);
    void load(QString dir,QGraphicsScene* scene);
    int get_picNum();
    QString get_saveName();
public slots:
    void create_save(QString saveName_);
    void save();
signals:
    void save_created(SaveFile* save);
    friend class MainWindow;
};

#endif // SAVEFILE_H
