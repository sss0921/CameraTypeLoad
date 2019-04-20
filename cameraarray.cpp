#include "cameraarray.h"

#include <QMap>
#include <QLoggingCategory>

Q_LOGGING_CATEGORY(cameraArray, "CameraTypeLoad.CameraArray")

class CameraArrayPrivate
{
public:
    CameraArrayPrivate();
    ~CameraArrayPrivate();

    bool loadFromJson(const QString &fileName) const;
    bool saveToJson(const QString &fileName, CameraArray::FileFormat format) const;

    QMap<int, CameraType> cameras;
};

CameraArrayPrivate::CameraArrayPrivate()
{
    cameras.clear();
}

CameraArrayPrivate::~CameraArrayPrivate()
{
}

bool CameraArrayPrivate::loadFromJson(const QString &filePath) const
{
    return false;
}

bool CameraArrayPrivate::saveToJson(const QString &filePath, CameraArray::FileFormat format) const
{
    return false;
}

CameraArray::CameraArray(QObject *parent)
    : QObject(parent)
    , d(new CameraArrayPrivate)
{
}

bool CameraArray::save(const QString &filePath, FileFormat format) const
{
    return d->saveToJson(filePath, format);
}

bool CameraArray::load(const QString &filePath) const
{
    return d->loadFromJson(filePath);
}

bool CameraArray::cameraExists(int index)
{
    return d->cameras.contains(index);
}

void CameraArray::appendCamera(const CameraType &type, int index)
{
    int i = index != -1 ? index : d->cameras.size();

    if (i == -1) {
        if (d->cameras.isEmpty())
            i = 0;
        else
            i = d->cameras.size();
    }

    d->cameras[i] = type;
}

bool CameraArray::removeCamera(int index)
{
    if (!cameraExists(index))
        return false;

    d->cameras.remove(index);
    return true;
}
