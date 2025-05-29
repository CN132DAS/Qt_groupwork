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
#include "editabletext.h"
#include "filecontent.h"
#include "func_.h"

extern QString savePath_;
extern QString saveName_;


struct Pic{
    QString name;
    QString path;
    QPoint pos;
    Pic(QString name_,QString path_,QPoint pos_);
};

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
public:
    explicit SaveFile(QString saveName_="",QObject *parent = nullptr);
    void add_pic(Pic* pic_);
    void add_file(FileContent* file_);
    void add_text(EditableText* text_);
    void load(QString dir,QGraphicsScene* scene);
    int get_picNum();
    int get_textNum();
public slots:
    void create_save(QString saveName_);
    void save();
signals:
    void save_created(SaveFile* save);
    friend class MainWindow;
};

#endif // SAVEFILE_H
