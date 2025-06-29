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

void copy_file_to_temp(const QString& name){
    QString sourceFilePath = _savePath_ + "/" + name;
    QString destFilePath = _saveTempPath_ + "/" + name;
    QFile::copy(sourceFilePath, destFilePath);

}

void delete_file(){
    QStringList files = QDir(_savePath_).entryList(QDir::Files);
    foreach (const QString& file, files) {
        QString filePath = _savePath_ + "/" + file;
        QFile::remove(filePath);
    }
}

void delete_tempFile(){
    QStringList files = QDir(_saveTempPath_).entryList(QDir::Files);
    foreach (const QString& file, files) {
        QString filePath = _saveTempPath_ + "/" + file;
        QFile::remove(filePath);
    }
}
