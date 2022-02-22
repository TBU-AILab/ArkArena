#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/core.hpp>
#include "dockimagesource.h"
#include "tools/ImageBuffer.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    DockIamgeSource *dockVideoSource;
    ImageBuffer<cv::Mat> *sourceBuffer;
};
#endif // MAINWINDOW_H
