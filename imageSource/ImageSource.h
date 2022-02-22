//
// Created by Peter Janků on 18.02.2022.
//

#ifndef ARKARENA_IMAGESOURCE_H
#define ARKARENA_IMAGESOURCE_H

#include <QObject>
#include <QThread>
#include "tools/ImageBuffer.h"
#include <opencv2/opencv.hpp>


enum class ImageSourceStatus{
    Uninitialized,   /**< Original state - the device is not initialized at all */
    Initialized,     /**< Device is initialized, ready to serve images */
    Running,         /**< The device acquiring the images */
    Error            /**< The device provides some errors */
};


/**
 * This class provide and interface for each image source used in the KilobotArena. All virtual functions need to be correctly implemented including all signals and slots.
 * The implementation as a worker thread is chosen in order to have ability of future parallelization (in case of multiple camera source)
 */
class ImageSource : public QObject {
public:

    explicit ImageSource(std::shared_ptr<ImageBuffer<cv::Mat>> buffer) : buffer(buffer), status(ImageSourceStatus::Uninitialized) {};

    /**
     * Returns current status of the image source.
     * @return
     */
    ImageSourceStatus getStatus() const;

public slots:

    /**
     * This function tries to initialize the source of the images. It should be called before the first frame is aquired.
     */
    virtual void initSource() = 0;

    /**
     * This slot will start the image acquisition.
     */
    virtual void start() = 0;


    /**
     * This slot will stop the image acquisition in next possible time.
     */
    virtual void stop()  = 0;

    /**
     * Construct and return the pointer to initial panel with configuration GUI. The GUI could be SMALL set of controls in column  layout or configuration button, which shows another dialogs.
     * @return The pointer to a QWidget representing the GUI.
     */
    virtual QLayout* getUI() = 0;


signals:
    void newFrame();


protected:

    virtual void emitNewFrame() {;} //emit newFrame(); }

    std::weak_ptr<ImageBuffer<cv::Mat>> buffer;         /**< Pointer to a image buffer */
    ImageSourceStatus status;                           /**< Status of the ImageSource device */
};

#endif //ARKARENA_IMAGESOURCE_H
