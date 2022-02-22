//
// Created by Peter Janků on 18.02.2022.
//

#include "SingleCameraImageSource.h"

#include <QVBoxLayout>
#include <QLabel>

void SingleCameraImageSource::initSource() {

}

void SingleCameraImageSource::start() {

}

void SingleCameraImageSource::stop() {

}

QLayout *SingleCameraImageSource::getUI() {
    QVBoxLayout *centralLayout = new QVBoxLayout;
    centralLayout->addWidget(new QLabel("Selected device:"));
    return centralLayout;
}

void SingleCameraImageSource::emitNewFrame() {
    ImageSource::emitNewFrame();
}

SingleCameraImageSource::SingleCameraImageSource(const std::shared_ptr<ImageBuffer<cv::Mat>> &buffer) : ImageSource(buffer) {}
