#ifndef CAMERALOADER_H
#define CAMERALOADER_H

#include <QDialog>

namespace Ui {
class CameraLoader;
}

class CameraLoader : public QDialog
{
    Q_OBJECT

public:
    struct CameraData
    {
        CameraData()
            : name(QString())
            , sensorWidth(0.00)
            , sensorHeight(0.00)
            , imageWidth(0)
            , imageHeight(0)
            , focalLength(0)
            , landscape(false)
            , fixedOrientation(false)
            , minTriggerInteral(0)
        {
        }
        CameraData(const QString &name, double sensorWidth, double sensorHeight, int imageWidth,
                   int imageHeight, int focalLength, bool landscape, bool fixedOrientation,
                   int minTriggerInteral)
            : name(name)
            , sensorWidth(sensorWidth)
            , sensorHeight(sensorHeight)
            , imageWidth(imageWidth)
            , imageHeight(imageHeight)
            , focalLength(focalLength)
            , landscape(landscape)
            , fixedOrientation(fixedOrientation)
            , minTriggerInteral(minTriggerInteral)
        {
        }

        bool operator==(const CameraData &other)
        {
            if ((name == other.name) && qFuzzyCompare(sensorWidth, other.sensorWidth)
                && qFuzzyCompare(sensorHeight, other.sensorHeight)
                && (imageWidth == other.imageWidth) && (imageHeight == other.imageHeight)
                && (focalLength == other.focalLength) && (landscape == other.landscape)
                && (fixedOrientation == other.fixedOrientation)
                && (minTriggerInteral == other.minTriggerInteral))
                return true;

            return false;
        }

        bool operator!=(const CameraData &other) { return !operator==(other); }
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
    explicit CameraLoader(QWidget *parent = nullptr);
    ~CameraLoader();

    CameraData cameraData() const;
    void setCameraData(const CameraData &data);

private:
    void onAcceptedButtonClicked();
    void updateData();
    void setData();

    Ui::CameraLoader *ui;
    bool m_dirty;
    CameraData m_cameraData;
    QString m_cameraConfigPath;
    QString m_cameraConfigFileName;
};

#endif // CAMERALOADER_H
