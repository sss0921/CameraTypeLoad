#include "cameratype.h"

class CameraTypePrivate
{
public:
    CameraTypePrivate();
    ~CameraTypePrivate();

    QString name;
    double sensorWidth;
    double sensorHeight;
    int imageWidth;
    int imageHeight;
    int focalLength;
    bool landscape;
    bool fixedOrientation;
    int minTriggerInteral;
};

CameraTypePrivate::CameraTypePrivate()
    : name(QString())
    , sensorWidth(0.0)
    , sensorHeight(0.0)
    , imageWidth(0)
    , imageHeight(0)
    , focalLength(0)
    , landscape(false)
    , fixedOrientation(false)
    , minTriggerInteral(0)
{
}

CameraTypePrivate::~CameraTypePrivate()
{
}

CameraType::CameraType()
    : d(new CameraTypePrivate)
{
}

CameraType::CameraType(const CameraType &other)
    : d(other.d)
{
}

QString CameraType::Name() const
{
    return d->name;
}

void CameraType::setName(const QString &name)
{
    d->name = name;
}

double CameraType::sensorWidth() const
{
    return d->sensorWidth;
}

void CameraType::setSensorWidth(double width)
{
    d->sensorWidth = width;
}

double CameraType::sensorHeight() const
{
    return d->sensorHeight;
}

void CameraType::setSensorHeight(double height)
{
    d->sensorHeight = height;
}

int CameraType::imageWidth() const
{
    return d->imageWidth;
}

void CameraType::setImageWidth(int width)
{
    d->imageWidth = width;
}

int CameraType::imageHeight() const
{
    return d->imageWidth;
}

void CameraType::setImageHeight(int height)
{
    d->imageHeight = height;
}

int CameraType::focalLength() const
{
    return d->focalLength;
}

void CameraType::setFocalLength(int length)
{
    d->focalLength = length;
}

bool CameraType::landscape() const
{
    return d->landscape;
}

void CameraType::setLandScape(bool landscape)
{
    d->landscape = landscape;
}

bool CameraType::fixedOrientation() const
{
    return d->fixedOrientation;
}

void CameraType::setFixedOrientation(bool fixedOrientation)
{
    d->fixedOrientation = fixedOrientation;
}

int CameraType::minTriggerInteral() const
{
    return d->minTriggerInteral;
}

void CameraType::setMinTriggerInteral(int minTriggerInteral)
{
    d->minTriggerInteral = minTriggerInteral;
}
