//
// Created by Peter Janků on 22.02.2022.
//

#ifndef ARKARENA_PHOTOLOADER_H
#define ARKARENA_PHOTOLOADER_H
#include <QTimer>
#include <QObject>
#include <tools/ImageBuffer.h>
#include <opencv2/core.hpp>

/**
 * Loader class. Will be executed as a worker in separate class. The delay represents time between grabbed images.
 */
class PhotoLoader: public  QTimer {
Q_OBJECT
public:
    explicit PhotoLoader(ImageBuffer<cv::Mat> *buffer,const QStringList &files, int delay = 1000/25, bool repeat = true, QObject *parent = nullptr);

signals:
    void imageLoaded();
    void aquirisionStopped();

protected:

    void timerEvent(QTimerEvent *event) override;

    ImageBuffer<cv::Mat> *buffer;
    const QStringList &files;
    int index = 0;
    bool repeat;

};


#endif //ARKARENA_PHOTOLOADER_H
