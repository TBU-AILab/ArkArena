//
// Created by Peter Janků on 18.02.2022.
//

#include "PhotoImageSource.h"
#include <QDir>
#include <QObject>
#include <QPushButton>
#include <QLabel>
#include <QSettings>
#include <QMessageBox>

PhotoImageSource::PhotoImageSource(ImageBuffer<cv::Mat> *buffer) :ImageSource(buffer){
    connect(&timer,&QTimer::timeout, this, [this](){
        loadNextImage(false);
    });
}

void PhotoImageSource::initSource() {
    QDir dir(pathLE->text());
    listOfFiles.clear();

    for(QFileInfo fi:dir.entryInfoList(QDir::Files)){
        if (fi.exists()){
            if (fi.fileName().toLower().contains(".jpg")){
                listOfFiles.append(fi.absoluteFilePath());
            }
        }
    }
    if (!listOfFiles.isEmpty()){
        status = ImageSourceStatus::Initialized;
        QMessageBox::information(nullptr, "Photo source", QString("Loaded %1 images").arg(listOfFiles.size()));
    }else{
        status = ImageSourceStatus::Error;
        QMessageBox::critical(nullptr,"Image source", "No images were found!");
    }
}
//TODO: OPRAVIT OKAMŽITĚ - NELZE POKAŽDÉ VYTVÁŘET NOVÝ WOKER
void PhotoImageSource::start() {
    worker = new PhotoLoader(buffer,listOfFiles);
    worker->moveToThread(&workerThread);
    workerThread.start();
}

void PhotoImageSource::stop() {
    timer.stop();
    status = ImageSourceStatus::Initialized;
}

void PhotoImageSource::loadNextImage(bool repeat) {

    this->status = ImageSourceStatus::Running;
    qDebug() << "New frame";
   emitNewFrame();
}
/**
 * This function generates the necessary UI and initialize it to a saved values.
 * @return QLayout with corresponding content.
 */
QLayout *PhotoImageSource::getUI() {
    QVBoxLayout *vLayout = new QVBoxLayout;
    QHBoxLayout *hLayout = new QHBoxLayout;
    pathLE = new QLineEdit("");
    pathLE->setReadOnly(true);
    hLayout->addWidget(pathLE);
    QPushButton *btn = new QPushButton("...");
    hLayout->addWidget(btn);
    vLayout->addWidget(new QLabel("Source path:"));
    vLayout->addLayout(hLayout);
    vLayout->addWidget(new QLabel("Frame rate:"));
    frameRateSB = new QSpinBox();
    vLayout->addWidget(frameRateSB);
    repeatCH = new QCheckBox("repeat");
    vLayout->addWidget(repeatCH);

    loadSetting();


    connect(btn, &QPushButton::clicked, this,&PhotoImageSource::selectNewPath);
    return vLayout;
}
/**
 * This function will load previously stored setting or use a predefined values.
 */
void PhotoImageSource::loadSetting() {
    QSettings set;
    set.beginGroup("photoImageSource");

    pathLE->setText(set.value("lastPath", "").toString());
    frameRateSB->setValue(set.value("lastFrameRate", 25).toInt());
    repeatCH->setChecked(set.value("repeate", true).toBool());

    set.endGroup();
}

void PhotoImageSource::emitNewFrame() {
    //ImageSource::emitNewFrame();
    emit ImageSource::newFrame();
}


/**
 * Slot for the button in configuration section - select a new source path.
 */
void PhotoImageSource::selectNewPath() {
    QString newPath = QFileDialog::getExistingDirectory(nullptr,"Select the folder with source files");
    if (!newPath.isEmpty()){
        QSettings set;
        pathLE->setText(newPath);
        set.beginGroup("photoImageSource");
        set.setValue("lastPath", newPath);
        set.endGroup();
        initSource();
    }
}


/**
 * Slot for a spin box in configuration section - select a new frame rate
 */
void PhotoImageSource::changeFrameRate() {

}

PhotoImageSource::~PhotoImageSource() {
    workerThread.quit();
    workerThread.wait();
    qDebug() << "Photo source is deleted";
}
