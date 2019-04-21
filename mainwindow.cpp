#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QFileDialog>
#include <QApplication>
#include <QMessageBox>
#include <QLoggingCategory>

Q_LOGGING_CATEGORY(mainwindow, "CameraTypeLoader.MainWindow")

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_cameraPath(QString())
    , m_filePath(QString())
{
    ui->setupUi(this);

    m_cameraData.clear();

    m_cameraArray = new CameraArray;
    m_cameraLoader = new CameraLoader(this);

    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::onOpenActionTriggered);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::onSaveActionTriggered);
    connect(ui->actionSaveAs, &QAction::triggered, this, &MainWindow::onSaveAsActionTriggered);
    connect(ui->actionCameraLoad, &QAction::triggered, this,
            &MainWindow::onCameraLoadActionTriggered);

    QString dirPath = qApp->applicationDirPath();
    m_cameraPath = dirPath + "/" + "Camera";

    QDir dir(m_cameraPath);
    if (!dir.exists())
        dir.mkpath(m_cameraPath);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_cameraArray;
}

void MainWindow::onOpenActionTriggered()
{
    QString filePath =
        QFileDialog::getOpenFileName(this, tr("Open Camera file"), m_cameraPath, tr("File *.data"));

    if (!filePath.isEmpty()) {
        doOpenFile(filePath);
        m_filePath = filePath;
    }
}

void MainWindow::onSaveActionTriggered()
{
    // judge the filePath
    if (m_filePath.isEmpty()) {
        if (QMessageBox::information(
                this, tr("Info"),
                "Don't open a file, need a file to save, Do you want to Open a file",
                QMessageBox::Yes, QMessageBox::No)
            == QMessageBox::Yes) {

            QString filePath = QFileDialog::getSaveFileName(this, tr("Open Camera file"),
                                                            m_cameraPath, tr("File *.data"));
            if (!filePath.isEmpty())
                m_filePath = filePath;
            else
                return;
        } else {
            return;
        }
    }
    doSaveFile(m_filePath);
}

void MainWindow::onSaveAsActionTriggered()
{
    QString filePath =
        QFileDialog::getSaveFileName(this, tr("Open Camera file"), m_cameraPath, tr("File *.data"));

    if (!filePath.isEmpty())
        doSaveFile(filePath);
}

void MainWindow::onCameraLoadActionTriggered()
{
    if (m_cameraLoader->exec() == QDialog::Accepted) {
        qCWarning(mainwindow) << "CameraLoader Accepted";
        appendCameraData(m_cameraLoader->cameraData());
    } else {
        qCWarning(mainwindow) << "CameraLoader Rejected";
    }
}

void MainWindow::doSaveFile(const QString &filePath)
{
    int i = 0;
    for (auto it = m_cameraData.begin(); it != m_cameraData.end(); it++) {
        auto value = it.value();
        CameraType type;
        type.setName(value.name);
        type.setSensorWidth(value.sensorWidth);
        type.setSensorHeight(value.sensorHeight);
        type.setImageWidth(value.imageWidth);
        type.setImageHeight(value.imageHeight);
        type.setFocalLength(value.focalLength);
        type.setLandScape(value.landscape);
        type.setMinTriggerInteral(value.minTriggerInteral);
        m_cameraArray->appendCamera(type, i++);
    }

    if (m_cameraArray->save(filePath)) {
        QMessageBox::information(this, tr("Info"), tr("Save camera file success!"));
    }
}

void MainWindow::doOpenFile(const QString &filePath)
{
    if (m_cameraArray->load(filePath)) {
        m_cameraData.clear();
        ui->treeWidget->clear();

        QMap<int, CameraType> cameras = m_cameraArray->cameraData();

        for (auto it = cameras.begin(); it != cameras.end(); it++) {
            auto value = it.value();
            CameraLoader::CameraData data;
            data.name = value.name();
            data.sensorWidth = value.sensorWidth();
            data.sensorHeight = value.sensorHeight();
            data.imageWidth = value.imageWidth();
            data.imageHeight = value.imageHeight();
            data.focalLength = value.focalLength();
            data.landscape = value.landscape();
            data.fixedOrientation = value.fixedOrientation();
            data.minTriggerInteral = value.minTriggerInteral();

            appendCameraData(data);
        }
    }
}

void MainWindow::appendCameraData(const CameraLoader::CameraData &data)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
    item->setText(0, "Camera Name:");
    item->setText(1, data.name);
    QTreeWidgetItem *sensorWidthItem = new QTreeWidgetItem(item);
    sensorWidthItem->setText(0, "SensorWidth:");
    sensorWidthItem->setText(1, QString::number(data.sensorWidth, 'f', 2));
    QTreeWidgetItem *sensorHeightItem = new QTreeWidgetItem(item);
    sensorHeightItem->setText(0, "SensorHeight:");
    sensorHeightItem->setText(1, QString::number(data.sensorHeight, 'f', 2));
    QTreeWidgetItem *imageWidthItem = new QTreeWidgetItem(item);
    imageWidthItem->setText(0, "ImageWidth:");
    imageWidthItem->setText(1, QString::number(data.imageWidth));
    QTreeWidgetItem *imageHeightItem = new QTreeWidgetItem(item);
    imageHeightItem->setText(0, "ImageHeight:");
    imageHeightItem->setText(1, QString::number(data.imageHeight));
    QTreeWidgetItem *focalLengthItem = new QTreeWidgetItem(item);
    focalLengthItem->setText(0, "FocalLength:");
    focalLengthItem->setText(1, QString::number(data.focalLength));
    QTreeWidgetItem *landscapeItem = new QTreeWidgetItem(item);
    QString landscapeString = data.landscape ? "true" : "false";
    landscapeItem->setText(0, "Landscape:");
    landscapeItem->setText(1, landscapeString);
    QTreeWidgetItem *fixedOrientationItem = new QTreeWidgetItem(item);
    QString fixedOrientationString = data.fixedOrientation ? "true" : "false";
    fixedOrientationItem->setText(0, "FixedOrientation:");
    fixedOrientationItem->setText(1, fixedOrientationString);
    QTreeWidgetItem *minTriggerInteralItem = new QTreeWidgetItem(item);
    minTriggerInteralItem->setText(0, "MinTriggerInteral:");
    minTriggerInteralItem->setText(1, QString::number(data.minTriggerInteral));

    ui->treeWidget->addTopLevelItem(item);

    m_cameraData[data.name] = data;
}
