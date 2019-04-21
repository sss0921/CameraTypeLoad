#include "cameraloader.h"
#include "ui_cameraloader.h"

#include <QDir>
#include <QFileDialog>
#include <QApplication>
#include <QLoggingCategory>

Q_LOGGING_CATEGORY(cameraLoader, "UAVGround.CameraLoader")

CameraLoader::CameraLoader(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CameraLoader)
    , m_dirty(false)
{
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this,
            &CameraLoader::onAcceptedButtonClicked);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &CameraLoader::reject);
}

CameraLoader::~CameraLoader()
{
    delete ui;
}

CameraLoader::CameraData CameraLoader::cameraData() const
{
    return m_cameraData;
}

void CameraLoader::setCameraData(const CameraData &data)
{
    if (m_cameraData != data) {
        m_cameraData = data;
        updateData();
    }
}

void CameraLoader::onAcceptedButtonClicked()
{
    setData();
    this->accept();
}

void CameraLoader::updateData()
{
    ui->cameraNameLineEdit->setText(m_cameraData.name);
    ui->sensorWidthDoubleSpinBox->setValue(m_cameraData.sensorWidth);
    ui->sensorHeightDoubleSpinBox->setValue(m_cameraData.sensorHeight);
    ui->imageWidthSpinBox->setValue(m_cameraData.imageWidth);
    ui->imageHeightSpinBox->setValue(m_cameraData.imageHeight);
    ui->focalLengthSpinBox->setValue(m_cameraData.focalLength);

    if (m_cameraData.fixedOrientation)
        ui->fixedOrientationComboBox->setCurrentIndex(1);
    else
        ui->fixedOrientationComboBox->setCurrentIndex(0);

    if (m_cameraData.landscape)
        ui->landscapeComboBox->setCurrentIndex(1);
    else
        ui->landscapeComboBox->setCurrentIndex(0);
}

void CameraLoader::setData()
{
    m_cameraData.name = ui->cameraNameLineEdit->text();
    m_cameraData.sensorWidth = ui->sensorWidthDoubleSpinBox->value();
    m_cameraData.sensorHeight = ui->sensorHeightDoubleSpinBox->value();
    m_cameraData.imageWidth = ui->imageWidthSpinBox->value();
    m_cameraData.imageHeight = ui->imageHeightSpinBox->value();
    m_cameraData.focalLength = ui->focalLengthSpinBox->value();
    m_cameraData.minTriggerInteral = ui->minTriggerTimeSpinBox->value();

    if (ui->landscapeComboBox->currentIndex() == 1)
        m_cameraData.landscape = true;
    else
        m_cameraData.landscape = false;

    if (ui->fixedOrientationComboBox->currentIndex() == 1)
        m_cameraData.fixedOrientation = true;
    else
        m_cameraData.fixedOrientation = false;
}
