#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/core.hpp>
#include "dockimagesource.h"
#include "tools/ImageBuffer.h"
#include "tools/LiveImageProvider.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected slots:
    void checkNewImg();
private:
    Ui::MainWindow *ui;
    DockIamgeSource *dockVideoSource;
    ImageBuffer<cv::Mat> *sourceBuffer;
    LiveImageProvider *imageProvider;

};
#endif // MAINWINDOW_H
