#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <QObject>
#include <QVarLengthArray>
#include <Qstring>
#include "connection.h"
#include "content.h"

class SaveFile : public QObject
{
    Q_OBJECT;
    QVarLengthArray<Content> content;
    QVarLengthArray<Connection> connection;

public:
    explicit SaveFile(QObject *parent = nullptr);

signals:
};

#endif // SAVEFILE_H
