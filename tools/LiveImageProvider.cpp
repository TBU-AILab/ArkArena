//
// Created by Peter Janků on 23.02.2022.
//

#include "LiveImageProvider.h"



LiveImageProvider::LiveImageProvider(QObject *parent) : QQuickImageProvider(QQuickImageProvider::Image) {
    this->defaultImage = QImage(":/img/faiLogo.jpeg");
}


QImage LiveImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    QImage result = this->lastImage;

    if(result.isNull()) {
        result = this->defaultImage;
    }

    if(size) {
        *size = result.size();
    }

    if(requestedSize.width() > 0 && requestedSize.height() > 0) {
        result = result.scaled(requestedSize.width(), requestedSize.height(), Qt::KeepAspectRatio);
    }

    return result;
}

void LiveImageProvider::updateImage(cv::Mat img) {

    if (!img.empty()){
        lastImage = QImage((uchar*)img.data, img.cols, img.rows, img.step1(), QImage::Format_RGB888).copy();
        emit imageChanged();
    }
}

