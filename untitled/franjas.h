#ifndef FRANJAS_H
#define FRANJAS_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <QWidget>

using namespace std;
using namespace cv;


namespace Ui {
class Franjas;
}

class Franjas : public QWidget
{
    Q_OBJECT

public:
    explicit Franjas(QWidget *parent = 0);
    ~Franjas();
    Mat redFilter(const Mat& src);
    Mat whiteFilter(const Mat& src);
    Mat morph(const Mat& src);
    Mat verticalBlur(const Mat& src);
    Mat combine_binary(Mat src,Mat bin1);
    Mat run(Mat&);


private:
    Ui::Franjas *ui;
};

#endif // FRANJAS_H
