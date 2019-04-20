#ifndef CAMERAARRAY_H
#define CAMERAARRAY_H

#include "cameratype.h"

#include <QObject>
#include <QScopedPointer>

class CameraArrayPrivate;
class CameraArray : public QObject
{
    Q_OBJECT
public:
    enum FileFormat { BinaryFileFormat, TextFileFormat };
    explicit CameraArray(QObject *parent = nullptr);
    ~CameraArray();

    bool save(const QString &filePath, FileFormat format = BinaryFileFormat) const;
    bool load(const QString &filePath) const;

    bool cameraExists(int index);
    void appendCamera(const CameraType &type, int index = -1);
    bool removeCamera(int index);

private:
    QScopedPointer<CameraArrayPrivate> d;
};

#endif // CAMERAARRAY_H
