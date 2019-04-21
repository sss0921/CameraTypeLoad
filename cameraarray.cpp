#include "cameraarray.h"

#include <QMap>
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QLoggingCategory>

Q_LOGGING_CATEGORY(cameraArray, "CameraTypeLoad.CameraArray")

class CameraArrayPrivate
{
public:
    CameraArrayPrivate();
    ~CameraArrayPrivate();

    bool loadFromJson(const QString &fileName);
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

bool CameraArrayPrivate::loadFromJson(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QFile::ReadOnly))
        return false;

    QByteArray fileContent = file.readAll();
    file.close();

    QJsonDocument json = QJsonDocument::fromBinaryData(fileContent);
    if (json.isNull())
        json = QJsonDocument::fromJson(fileContent);

    if (!json.isObject())
        return false;

    QJsonObject jsonObject = json.object();

    QJsonValue value = jsonObject["Camera"];

    if (!value.isArray())
        return false;

    QJsonArray array = value.toArray();

    if (!array.isEmpty())
        cameras.clear();

    for (int i = 0; i < array.size(); i++) {
        auto value = array[i];
        if (value.isObject()) {
            QJsonObject object = value.toObject();
            CameraType type;
            type.setName(object["name"].toString());
            type.setSensorWidth(object["sensorWidth"].toDouble());
            type.setSensorHeight(object["sensorHeight"].toDouble());
            type.setImageWidth(object["imageWidth"].toInt());
            type.setImageHeight(object["imageHeight"].toInt());
            type.setFocalLength(object["focalLength"].toInt());
            type.setLandScape(object["landscape"].toBool());
            type.setFixedOrientation(object["fixedOrientation"].toBool());
            type.setMinTriggerInteral(object["minTriggerInteral"].toInt());
            cameras[i] = type;
        }
    }

    return true;
}

bool CameraArrayPrivate::saveToJson(const QString &filePath, CameraArray::FileFormat format) const
{
    QFile file(filePath);
    if (!file.open(QFile::WriteOnly))
        return false;

    QByteArray fileContent;
    QJsonObject jsonObject;
    QJsonArray array;

    for (auto it = cameras.begin(); it != cameras.end(); it++) {
        QJsonObject cameraObject;
        CameraType cameraType = it.value();
        cameraObject["name"] = cameraType.name();
        cameraObject["sensorWidth"] = cameraType.sensorWidth();
        cameraObject["sensorHeight"] = cameraType.sensorHeight();
        cameraObject["imageWidth"] = cameraType.imageWidth();
        cameraObject["imageHeight"] = cameraType.imageHeight();
        cameraObject["focalLength"] = cameraType.focalLength();
        cameraObject["landscape"] = cameraType.landscape();
        cameraObject["fixedOrientation"] = cameraType.fixedOrientation();
        cameraObject["minTriggerInteral"] = cameraType.minTriggerInteral();
        array.append(cameraObject);
    }

    jsonObject["Camera"] = array;

    QJsonDocument json(jsonObject);
    if (format == CameraArray::BinaryFileFormat)
        fileContent = json.toBinaryData();
    else
        fileContent = json.toJson();
    file.write(fileContent);
    file.close();
    return !fileContent.isEmpty();
}

CameraArray::CameraArray(QObject *parent)
    : QObject(parent)
    , d(new CameraArrayPrivate)
{
}

CameraArray::~CameraArray()
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

QMap<int, CameraType> CameraArray::cameraData() const
{
    return d->cameras;
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
