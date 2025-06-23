#ifndef FUNCTION_H
#define FUNCTION_H

#include <QDir>
#include <QFile>
#include <QString>

extern QString _saveName_,_savePath_,_saveTempPath_,_saveFolderPath_;

QString get_filePath(const QString& fileName_);
QString get_fileTempPath(const QString& fileName_);
void set_saveName(const QString& saveName);
void move_file();
void delete_file();
void delete_tempFile();

#endif // FUNCTION_H
