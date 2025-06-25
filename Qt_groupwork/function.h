#ifndef FUNCTION_H
#define FUNCTION_H

#include <QDir>
#include <QFile>
#include <QtMath>
#include <QPointF>
#include <QString>

extern QString _saveName_,_savePath_,_saveTempPath_,_saveFolderPath_;

QString get_filePath(const QString& fileName_);
QString get_fileTempPath(const QString& fileName_);
void set_saveName(const QString& saveName);
void copy_file_to_temp(const QString& name);
void delete_file();
void delete_tempFile();

#endif // FUNCTION_H
