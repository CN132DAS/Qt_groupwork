#include "function.h"

QString get_filePath(const QString& fileName_){
    return _savePath_+"/"+fileName_;
}

QString get_fileTempPath(const QString& fileName_){
    return _saveTempPath_+"/"+fileName_;
}

void set_saveName(const QString& saveName){
    _saveName_ = saveName;
    _savePath_ = _saveFolderPath_+"/"+_saveName_;
    _saveTempPath_ = _savePath_+"/temp";
}

void move_file(){
    QStringList files = QDir(_savePath_).entryList(QDir::Files);
    foreach (QString file, files) {
        if (file=="save.dat")
            continue;
        QString sourceFilePath = _savePath_ + "/" + file;
        QString destFilePath = _saveTempPath_ + "/" + file;
        QFile::rename(sourceFilePath, destFilePath);
    }
}

void delete_file(){
    QStringList files = QDir(_savePath_).entryList(QDir::Files);
    foreach (QString file, files) {
        QString filePath = _savePath_ + "/" + file;
        QFile::remove(filePath);
    }
}

void delete_tempFile(){
    QStringList files = QDir(_saveTempPath_).entryList(QDir::Files);
    foreach (QString file, files) {
        QString filePath = _saveTempPath_ + "/" + file;
        QFile::remove(filePath);
    }
}
