#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "imageSource/ImageSource.h"
#include "imageSource/photo_source/PhotoImageSource.h"
#include <QMetaObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sourceBuffer = new ImageBuffer<cv::Mat>();
    dockVideoSource = new DockIamgeSource(sourceBuffer, this);
    addDockWidget(Qt::LeftDockWidgetArea,dockVideoSource);

    imageProvider = new LiveImageProvider();
    ui->quickWidget->engine()->addImageProvider("live",imageProvider);
    ui->quickWidget->setSource(QUrl::fromLocalFile(":/mainPainter.qml"));
    ui->quickWidget->show();

    checkNewImg();
   /* connect(sourceBuffer, &ImageBuffer<cv::Mat>::newImg,[this](){
        imageProvider->updateImage(sourceBuffer->fetchLast());
    } );*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::checkNewImg() {

    if (sourceBuffer->getCurrentIndex() != -1){
        cv::Mat img;
        sourceBuffer->fetchLast().copyTo(img);
        imageProvider->updateImage(img);
    }
    QMetaObject::invokeMethod(this, "checkNewImg", Qt::QueuedConnection);
}

