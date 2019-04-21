#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cameraarray.h"
#include "cameraloader.h"

#include <QMap>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void onOpenActionTriggered();
    void onSaveActionTriggered();
    void onSaveAsActionTriggered();
    void onCameraLoadActionTriggered();
    void doSaveFile(const QString &filePath);
    void doOpenFile(const QString &filePath);
    void appendCameraData(const CameraLoader::CameraData &data);

    Ui::MainWindow *ui;
    QString m_cameraPath;
    QString m_filePath;
    CameraArray *m_cameraArray;
    CameraLoader *m_cameraLoader;
    QMap<QString, CameraLoader::CameraData> m_cameraData;
};

#endif // MAINWINDOW_H
