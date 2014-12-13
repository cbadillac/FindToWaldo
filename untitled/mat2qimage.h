#ifndef MAT2QIMAGE_H
#define MAT2QIMAGE_H
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <QDebug>
#include <QImage>
class Mat2QImage
{
public:
    Mat2QImage();
    static QImage MatToQImage(const cv::Mat& mat);
};

#endif // MAT2QIMAGE_H
