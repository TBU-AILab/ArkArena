#include <QAbstractButton>
#include "dockimagesource.h"
#include "ui_dockimagesource.h"
#include "imageSource/photo_source/PhotoImageSource.h"
#include "imageSource/single_camera_source/SingleCameraImageSource.h"

//TODO:: finalize the documentation


DockIamgeSource::DockIamgeSource(ImageBuffer<cv::Mat> *buffer, QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::DockImageSource),buffer(buffer)
{
    ui->setupUi(this);
    ui->imageSourceCB->addItem("photo");
    ui->imageSourceCB->addItem("video");
}

DockIamgeSource::~DockIamgeSource()
{
    delete ui;
}

//TODO: Check if the object deletion work correctly
//TODO: Reprogramm the source selectiong methods

void DockIamgeSource::on_imageSourceCB_currentTextChanged(const QString &arg1)
{
    if (source) {
        source->stop();
        delete source;
        qDeleteAll(ui->sourceControlsW->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));
        delete ui->sourceControlsW->layout();
    }
    if (arg1 == "photo"){
        selectPhotoSource();
    }
    if (arg1 == "video"){
        selectVideoSource();
    }
}


/**
 * Create a new photo source object, append the GUI elements into the correct section and connect all necessary signals.
 */
void DockIamgeSource::selectPhotoSource() {

    source = new PhotoImageSource(buffer);
    ui->sourceControlsW->setLayout(source->getUI());
    reconnectSourceSignals();

}
/**
 * Create new connection to a standard dock buttons (Run and Stop). It should be called after each source change.
 */
void DockIamgeSource::reconnectSourceSignals() const {
    connect(ui->startPB, &QPushButton::clicked, source, &ImageSource::start);
    connect(ui->stopPB, &QPushButton::clicked, source, &ImageSource::stop);
}

void DockIamgeSource::selectVideoSource() {
    source = new SingleCameraImageSource(buffer);
    ui->sourceControlsW->setLayout(source->getUI());
    reconnectSourceSignals();
}

