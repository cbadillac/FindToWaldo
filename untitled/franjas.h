#ifndef FRANJAS_H
#define FRANJAS_H

#include <iostream>
#include "opencv/cv.h"
#include "opencv/highgui.h"

using namespace std;
using namespace cv;


Mat get_whitebinary(Mat);
Mat get_redbinary(Mat);
Mat combine_binary(Mat,Mat,Mat);
Mat filter_image(Mat);
Mat group_pixels(Mat);
void test_zone(Mat,int);
Mat get_stripezone(Mat);

/*class Franjas
{
private:
    Mat get_whitebinary(Mat);
    Mat get_redbinary(Mat);
    Mat combine_binary(Mat,Mat);
    Mat filter_image(Mat);
    Mat group_pixels(Mat);
    void test_zone(Mat,int);
public:
    Mat get_stripezone(Mat);
signals:
    void combinacion_lista();
    void patron_listo();
};*/




#endif // FRANJAS_H
