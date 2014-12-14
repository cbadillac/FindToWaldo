#include <iostream>
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include <franjas.h>

using namespace std;
using namespace cv;
//using namespace franjas;

int main()
{
    //Mat ww = imread("C:/Users/Rene/Documents/GitHub/FindToWaldo/waldo/waldo.jpg");
    Mat ww = imread("C:/Users/Rene/Documents/GitHub/FindToWaldo/waldo/wheres-waldo.png");
    //Mat ww = imread("C:/Users/Rene/Desktop/color-test.png");
    imshow("original where's waldo",ww);

    //test_zone(ww,1);
    Mat red = get_redbinary(ww);
    Mat white = get_whitebinary(ww);
    Mat combine = combine_binary(ww,red,white);

    Mat filter = filter_image(combine);
    Mat group = group_pixels(filter);

    imshow("combine",combine);
    imshow( "sobel", filter);
    imshow( "close", group);

    waitKey(1000000);
    return 0;
}

void test_zone(Mat original,int color){//color=0 get white, color=1 get red
    Mat escribir;
    switch(color){
    case 0:
        escribir=get_whitebinary(original);
        break;
    case 1:
        escribir=get_redbinary(original);
        break;
    default:
        return;
    }

    int steps = original.step;
    int channels = original.channels();
    int steps2 = escribir.step;

    for(int i=0; i<original.rows; i++){
        for(int j=0; j<original.cols; j++){
            if(escribir.data[i*steps2+j]==255){
                original.data[i*steps+j*channels]=0;
                original.data[i*steps+j*channels+1]=0;
                original.data[i*steps+j*channels+2]=0;
            }
        }
    }
    imshow("test zone",original);

}

Mat get_stripezone(Mat src){
    Mat null;
    return null;
}

Mat get_whitebinary(Mat color){
    Mat channels[3];
    Mat white;
    split(color,channels);
    threshold(channels[0],channels[0],195,255,0);
    threshold(channels[1],channels[1],195,255,0);
    threshold(channels[2],channels[2],195,255,0);
    bitwise_and(channels[0],channels[2],white);
    bitwise_and(channels[1],white,white);
    imshow("white_thresh",white);
    return white;
}

Mat get_redbinary(Mat color){
    Mat channels[3];
    Mat red;
    split(color,channels);
    threshold(channels[0],channels[0],90,255,1);
    threshold(channels[1],channels[1],90,255,1);
    threshold(channels[2],channels[2],165,255,0);
    bitwise_and(channels[0],channels[2],red);
    bitwise_and(channels[1],red,red);
    imshow("red_thresh",red);
    return red;
}

Mat combine_binary(Mat src,Mat bin1, Mat bin2){
    Mat temp;
    Mat channels_src[3];
    Mat channels_dst[3];
    Mat dst;
    split(src,channels_src);
    bitwise_xor(bin1,bin2,temp);
    bitwise_and(channels_src[0],temp,channels_dst[0]);
    bitwise_and(channels_src[1],temp,channels_dst[1]);
    bitwise_and(channels_src[2],temp,channels_dst[2]);
    merge(channels_dst,3,dst);
    return dst;
}

Mat filter_image(Mat src){
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;
    Mat grad;
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;

    Sobel( src, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_x, abs_grad_x );
    Sobel( src, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_y, abs_grad_y );
    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );

    return grad;
}

Mat group_pixels(Mat src){
    Mat element = getStructuringElement(MORPH_RECT, Size(2, 2), Point(1,1) );
    Mat dst;
    morphologyEx(src, dst, CV_MOP_CLOSE, element);
    return dst;
}
