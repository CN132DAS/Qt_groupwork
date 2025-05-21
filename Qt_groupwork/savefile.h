#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <QObject>
#include <QVarLengthArray>
#include <Qstring>
#include <QDebug>


class SaveFile : public QObject   //存档文件结构
{
    Q_OBJECT;
private:
    QString saveName;
private:
    void resize();
public:
    explicit SaveFile(QString saveName_="",QObject *parent = nullptr);
public slots:
    void create_save(QString saveName_);
signals:
    void init_done(SaveFile* save);
    friend class MainWindow;
};

#endif // SAVEFILE_H
