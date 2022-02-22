//
// Created by Peter Janků on 18.02.2022.
//

#ifndef ARKARENA_PHOTOIMAGESOURCE_H
#define ARKARENA_PHOTOIMAGESOURCE_H
#include <opencv2/opencv.hpp>
#include <QTimer>
#include <QLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QCheckBox>
#include <QFileDialog>

#include "tools/ImageBuffer.h"
#include "imageSource/ImageSource.h"

/**
 * The photo source class. This class will load the set of images from specific folder and serve them as a image source for the ArkArena
 */
class PhotoImageSource: public  ImageSource{
public:
    explicit  PhotoImageSource(std::shared_ptr<ImageBuffer<cv::Mat>> buffer);
    virtual ~PhotoImageSource();

    void initSource() override;

    void start() override;

    void stop() override;

    QLayout* getUI() override;


protected slots:
    void loadNextImage(bool repeat = false);
    void selectNewPath();
    void changeFrameRate();

protected:
    void emitNewFrame() override;


    QStringList listOfFiles;
    QTimer timer;

    QLineEdit *pathLE;
    QSpinBox *frameRateSB;
    QCheckBox *repeatCH;

    void loadSetting();
};


#endif //ARKARENA_PHOTOIMAGESOURCE_H
