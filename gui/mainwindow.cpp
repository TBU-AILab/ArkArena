#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "imageSource/ImageSource.h"
#include "imageSource/photo_source/PhotoImageSource.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dockVideoSource = new DockIamgeSource(sourceBuffer, this);
    addDockWidget(Qt::LeftDockWidgetArea,dockVideoSource);

}

MainWindow::~MainWindow()
{
    delete ui;
}

