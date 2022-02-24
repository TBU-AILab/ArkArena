//
// Created by Peter Janků on 23.02.2022.
//

#ifndef ARKARENA_LIVEIMAGEPROVIDER_H
#define ARKARENA_LIVEIMAGEPROVIDER_H


#include <QImage>
#include <QQuickImageProvider>
#include <opencv2/opencv.hpp>

/**
 * This class will provide image source for QML part of the application. I takes cv::Mat image and tried to convert them and display on screen.
 */
class LiveImageProvider: public QQuickImageProvider {
    Q_OBJECT

public:
    LiveImageProvider(QObject *parent = nullptr);

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override ;

public slots:
    void updateImage(cv::Mat img);

signals:
    void imageChanged();

protected:
    QImage defaultImage;     /**< This image will be shown when no source image is available */
    QImage lastImage;        /**< Last stored image */
};


#endif //ARKARENA_LIVEIMAGEPROVIDER_H
