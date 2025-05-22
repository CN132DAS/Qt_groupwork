#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <QDebug>
#include <QObject>
#include <QString>
#include <QVarLengthArray>
#include <QVector>
#include <QPoint>

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
    int get_picNum();
    QString get_saveName();
public slots:
    void create_save(QString saveName_);
signals:
    void init_done(SaveFile* save);
    friend class MainWindow;
};

#endif // SAVEFILE_H
