#ifndef DOCKVIDEOSOURCE_H
#define DOCKVIDEOSOURCE_H

#include <QDockWidget>
#include "imageSource/ImageSource.h"
#include "tools/ImageBuffer.h"

namespace Ui {
class DockImageSource;
}

class DockIamgeSource : public QDockWidget
{
    Q_OBJECT

public:
    explicit DockIamgeSource(ImageBuffer<cv::Mat> *buffer, QWidget *parent = nullptr);
    ~DockIamgeSource();

private slots:
    void on_imageSourceCB_currentTextChanged(const QString &arg1);

private:
    Ui::DockImageSource *ui;
    ImageSource *source = nullptr;
    ImageBuffer<cv::Mat> *buffer;

    void selectPhotoSource();
    void selectVideoSource();

    void reconnectSourceSignals() const;

};

#endif // DOCKVIDEOSOURCE_H
