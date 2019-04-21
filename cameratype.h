#ifndef CAMERATYPE_H
#define CAMERATYPE_H

#include <QSharedDataPointer>

class CameraTypePrivate;
class CameraType
{
public:
    explicit CameraType();

    QString name() const;
    void setName(const QString &name);

    double sensorWidth() const;
    void setSensorWidth(double width);

    double sensorHeight() const;
    void setSensorHeight(double height);

    int imageWidth() const;
    void setImageWidth(int width);

    int imageHeight() const;
    void setImageHeight(int height);

    int focalLength() const;
    void setFocalLength(int length);

    bool landscape() const;
    void setLandScape(bool landscape);

    bool fixedOrientation() const;
    void setFixedOrientation(bool fixedOrientation);

    int minTriggerInteral() const;
    void setMinTriggerInteral(int minTriggerInteral);

private:
    CameraTypePrivate *d;
};

#endif // CAMERATYPE_H
