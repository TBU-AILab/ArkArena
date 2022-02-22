//
// Created by Peter Janků on 18.02.2022.
//

#ifndef ARKARENA_SINGLECAMERAIMAGESOURCE_H
#define ARKARENA_SINGLECAMERAIMAGESOURCE_H

#include <QLayout>
#include "imageSource/ImageSource.h"

class SingleCameraImageSource: public ImageSource{
public:

    SingleCameraImageSource(const std::shared_ptr<ImageBuffer<cv::Mat>> &buffer);

    void initSource() override;

    void start() override;

    void stop() override;

    QLayout *getUI() override;

protected:
    void emitNewFrame() override;
};


#endif //ARKARENA_SINGLECAMERAIMAGESOURCE_H
