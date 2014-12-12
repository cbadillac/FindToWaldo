#ifndef MAT2QIMAGE_H
#define MAT2QIMAGE_H

class Mat2QImage
{
public:
    Mat2QImage();
    static QImage MatToQImage(const Mat& mat);
};

#endif // MAT2QIMAGE_H
