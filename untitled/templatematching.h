#ifndef TEMPLATEMATCHING_H
#define TEMPLATEMATCHING_H
#include <stdio.h>
#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <string>
#include "opencv2/imgproc/imgproc.hpp"
#include <QWidget>

using namespace std;
using namespace cv;

namespace Ui {
class TemplateMatching;
}

class TemplateMatching : public QWidget
{
    Q_OBJECT

public:
    explicit TemplateMatching(QWidget *parent = 0);
    ~TemplateMatching();
    Mat run(Mat&);

private:
    Ui::TemplateMatching *ui;
    Mat img;
    Mat templ[5][4];
    Mat result[10];
};



#endif // TEMPLATEMATCHING_H
