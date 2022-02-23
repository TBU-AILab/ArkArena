//
// Created by Peter Janků on 22.02.2022.
//

#include "PhotoLoader.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>


PhotoLoader::PhotoLoader(ImageBuffer<cv::Mat> *buffer, const QStringList &files, int delay, bool repeat, QObject *parent):
    files(files),
    buffer(buffer),
    repeat(repeat),
    QTimer(parent){

    setInterval(delay);
    start();

}

void PhotoLoader::timerEvent(QTimerEvent *event) {
    if (index == files.size() && repeat){
        index = 0;
    }
    if (index < files.size()){
           cv::Mat sourceImage = cv::imread(files[index].toStdString());
           if (!sourceImage.empty()){
               buffer->pushOverride(sourceImage);
               index++;
               emit imageLoaded();
           }
    }else{
        stop();
        emit aquirisionStopped();
    }
}

