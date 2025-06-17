#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QMessageBox>
#include <QObject>
#include <QPair>
#include <QPoint>
#include <QString>
#include <QTextStream>
#include <QVarLengthArray>
#include <QVector>
#include "editabletext.h"
#include "filecontent.h"
#include "pic.h"

extern QString _savePath_;
extern QString _saveName_;

class SaveFile : public QObject   //存档文件结构
{
    Q_OBJECT;
private:
    QString saveName;
    int picNum;
    QVarLengthArray<Pic*> pic;
    int fileNum;
    QVarLengthArray<FileContent*> file;
    int textNum;
    QVarLengthArray<EditableText*> text;
    QGraphicsScene* scene;
public:
    explicit SaveFile(QString saveName_="",QGraphicsScene* scene_ = nullptr,QObject *parent = nullptr);
    void add_text(EditableText* text_);
    void load(QString dir,QGraphicsScene* scene);
    void new_save();
    void clear();
    void set_scene(QGraphicsScene* scene_);
    QPair<QPoint,FileContent*> add_file(QString dir);
    QPair<QPoint,Pic*> add_pic(QString dir);
    QPair<QPoint,EditableText*>add_text();
    void save();
public slots:
signals:
    friend class MainWindow;
};

#endif // SAVEFILE_H
