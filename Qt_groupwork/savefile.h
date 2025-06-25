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
#include <QMap>
#include <QVarLengthArray>
#include "connection.h"
#include "editabletext.h"
#include "filecontent.h"
#include "picturecontent.h"

extern QString _savePath_,_saveName_;

class SaveFile : public QObject   //存档文件结构
{
    Q_OBJECT;
private:
    QString saveName;
    int picNum;
    QMap<int,PictureContent*> pic;
    int fileNum;
    QMap<int,FileContent*> file;
    int textNum;
    QMap<int,EditableText*> text;
    int conNum;
    QMap<int,Connection*> connection;
public:
    explicit SaveFile(QString saveName_="",QObject *parent = nullptr);
    void add_text(EditableText* text_);
    void load(QString dir,QGraphicsScene* scene);
    void new_save();
    void clear();
    FileContent* add_file(QString dir);
    PictureContent* add_pic(QString dir);
    // QPair<QPoint,EditableText*>add_text();
    Connection* add_connection(MyGraphicsObject* item1,MyGraphicsObject* item2);
    void save();
    void set_item_selectability(bool selectable, bool connectionIncluded = false);
    friend class MainWindow;
};

#endif // SAVEFILE_H
