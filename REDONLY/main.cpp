#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;


Mat redFilter(const Mat& src)
{
    assert(src.type() == CV_8UC3);

    Mat redOnly;
    inRange(src, Scalar(0, 0, 165), Scalar(90, 90, 255), redOnly);

    return redOnly;
}

Mat whiteFilter(const Mat& src)
{
    assert(src.type() == CV_8UC3);

    Mat whiteOnly;
    inRange(src, Scalar(190, 190, 190), Scalar(255, 255, 255), whiteOnly);

    return whiteOnly;
}

Mat morph(const Mat& src){

    Mat test  =src;


    Mat element = getStructuringElement( MORPH_ELLIPSE, Size(15, 15), Point( -1,1) );

    Mat opening;
//        morphologyEx(binary,opening, MORPH_OPEN, element);
    morphologyEx(test,opening,CV_MOP_DILATE, element,Point(-1,1), 1);

//    erode(test,opening,element,Point(-1,1),1);

//    cv::blur(opening,test,Size(11,1));


//    return test;
    return opening;
}

Mat verticalBlur(const Mat& src){

//    assert(src.type() == CV_8UC3);

    Mat blur;


    cv::blur(src, blur, Size(1,11));

    return blur;
}

Mat combine_binary(Mat src,Mat bin1){
    Mat temp;
    Mat channels_src[3];
    Mat channels_dst[3];
    Mat dst;
    split(src,channels_src);
    temp=bin1;
    bitwise_and(channels_src[0],temp,channels_dst[0]);
    bitwise_and(channels_src[1],temp,channels_dst[1]);
    bitwise_and(channels_src[2],temp,channels_dst[2]);
    merge(channels_dst,3,dst);
    return dst;
}

int main(int argc, char** argv)
{
    Mat input = imread("C:/Users/Rene/Documents/GitHub/FindToWaldo/waldo/wheres-waldo.png");



    Mat redOnly = redFilter(input);
//    redOnly  =  morph(redOnly);

    Mat redBlur = verticalBlur(redOnly);

    Mat whiteOnly = whiteFilter(input);
    Mat whiteBlur = verticalBlur(whiteOnly);

    Mat final;


    cv::multiply(whiteBlur, redBlur, final);
    final = morph(final);

    Mat final2 = combine_binary(input,final);
  //  Mat final3 = morph(final2);

    imshow("input", input);
    imshow("redOnly", redOnly);
    imshow("redBlur", redBlur);
    imshow("whiteOnly", whiteOnly);
    imshow("whiteBlur", whiteBlur);
    imshow("final",final);
    imshow("final2",final2);
 //   imshow("final3",final3);

    waitKey();

    return 0;
}
