#include "savefile.h"

SaveFile::SaveFile(QString saveName_,QObject *parent)
    : QObject{parent},saveName(saveName_)
{}
