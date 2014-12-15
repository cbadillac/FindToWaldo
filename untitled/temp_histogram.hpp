#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/features2d.hpp>

using namespace std;
using namespace cv;


void printHistogram(Mat image)
{
    /// Separate the image in 3 places ( B, G and R )
    vector<Mat> bgr_planes;
    split( image, bgr_planes );

    /// Establish the number of bins
    int histSize = 256;

    /// Set the ranges ( for B,G,R) )
    float range[] = { 0, 256 } ;
    const float* histRange = { range };

    bool uniform = true; bool accumulate = false;

    Mat b_hist, g_hist, r_hist;

    /// Compute the histograms:
    calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);

    // Draw the histograms for B, G and R
    int hist_w = 512; int hist_h = 400;
    int bin_w = cvRound( (double) hist_w/histSize );

    Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

    /// Normalize the result to [ 0, histImage.rows ]
    Mat b_hist_norm, g_hist_norm, r_hist_norm;
    normalize(b_hist, b_hist_norm, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    normalize(g_hist, g_hist_norm, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    normalize(r_hist, r_hist_norm, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

    /// Draw for each channel
    for( int i = 1; i < histSize; i++ )
    {
      line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist_norm.at<float>(i-1)) ) ,
                       Point( bin_w*(i), hist_h - cvRound(b_hist_norm.at<float>(i)) ),
                       Scalar( 255, 0, 0), 2, 8, 0  );
      line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist_norm.at<float>(i-1)) ) ,
                       Point( bin_w*(i), hist_h - cvRound(g_hist_norm.at<float>(i)) ),
                       Scalar( 0, 255, 0), 2, 8, 0  );
      line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist_norm.at<float>(i-1)) ) ,
                       Point( bin_w*(i), hist_h - cvRound(r_hist_norm.at<float>(i)) ),
                       Scalar( 0, 0, 255), 2, 8, 0  );
    }

    /// Display
    namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE );
    imshow("calcHist Demo", histImage );

    waitKey(0);
}

template< size_t N >
void matchWaldo(Mat& source, Mat templates[N], double results[N], Rect results_rect[N], int nscales=1)
{
    if(nscales<1){
        cout << "No se puede ingresar un valor de escalamiento menor a 1.\n";
        return;
    }

    /// Templates to HSV
    Mat hsv_source, hsv_temp[N];

    cvtColor( source, hsv_source, COLOR_BGR2HSV );
    for(int i=0;i<N;i++){
        cvtColor( templates[i], hsv_temp[i], COLOR_BGR2HSV );
    }

    /// Histogram parameters

    int h_bins = 50;
    int s_bins = 60;
    int histSize[] = { h_bins, s_bins };

    float h_ranges[] = { 0, 180 };
    float s_ranges[] = { 0, 256 };
    const float* ranges[] = { h_ranges, s_ranges };

    int channels[] = { 0, 1 };

    /// Templates's histograms calculation
    MatND hist_temp[N];

    for(int i=0; i<N;i++){
        calcHist( &hsv_temp[i], 1, channels, Mat(), hist_temp[i], 2, histSize, ranges, true, false );
        normalize( hist_temp[i], hist_temp[i], 0, 255, NORM_MINMAX, -1, Mat() );
    }

    ///Loop for matches in the source image
    Mat subArea;
    Mat hist_subArea;
    int temp_width;
    int temp_height;
    double actual_comparation;

    for(int ntemps=0; ntemps<N; ntemps++){
        temp_width  = 16;   // Harcorito
        temp_height = 22;   // Harcorito

        for(int it=1; it<=nscales; it++){
            for(int wi=0; wi<(hsv_source.cols-(temp_width-2*it)); wi += temp_width/3){
                for(int hi=0; hi<(hsv_source.rows-(temp_height-2*it)); hi += temp_height/3){

                    subArea = hsv_source(Rect(wi,hi,(temp_width-2*it), (temp_height-2*it)));
                    calcHist( &subArea, 1, channels, Mat(), hist_subArea, 2, histSize, ranges, true, false );
                    normalize( hist_subArea, hist_subArea, 0, 255, NORM_MINMAX, -1, Mat() );

                    actual_comparation = compareHist( hist_temp[ntemps], hist_subArea, CV_TM_CCORR_NORMED);

                    if(actual_comparation <= results[ntemps]){
                        results[ntemps] = actual_comparation;
                        results_rect[ntemps] = Rect(wi,hi,temp_width-2*it, temp_height-2*it);
                    }
                }
            }
        }
    }
}

Mat morph(const Mat& src){
    Mat dst;
    Mat element = getStructuringElement( MORPH_ELLIPSE, Size(7, 10), Point( -1,1) );
    morphologyEx(src,dst,CV_MOP_DILATE, element,Point(-1,1), 1);
    return dst;
}

template< size_t N >
void bestMatches(Mat& source, Mat templates[N], Mat results[N])
{
    /// Templates to HSV
    Mat hsv_source, hsv_temp[N];

    cvtColor( source, hsv_source, COLOR_BGR2HSV );
    for(int i=0;i<N;i++){
        cvtColor( templates[i], hsv_temp[i], COLOR_BGR2HSV );
    }

    /// Templates's histogram parameters

    int h_bins = 50;
    int s_bins = 60;
    int histSize[] = { h_bins, s_bins };

    float h_ranges[] = { 0, 180 };
    float s_ranges[] = { 0, 256 };
    const float* ranges[] = { h_ranges, s_ranges };

    int channels[] = { 0, 1};

    /// Templates's histograms calculation
    MatND hist_temp[N];

    for(int i=0; i<N;i++){
        calcHist( &hsv_temp[i], 1, channels, Mat(), hist_temp[i], 2, histSize, ranges, true, false );
        normalize( hist_temp[i], hist_temp[i], 0, 255, NORM_MINMAX, -1, Mat() );
    }

    for(int i=0;i<N;i++){
        calcBackProject(&hsv_source, 1, channels, hist_temp[i], results[i], ranges);
        threshold(results[i], results[i], 130, 255, THRESH_BINARY);
        results[i] = morph(results[i]);
    }

}

Mat combine_binary(Mat src,Mat bin1){
    Mat temp;
    Mat dst;
    Mat channels_src[3];
    Mat channels_dst[3];

    split(src,channels_src);

    temp=bin1;
    bitwise_and(channels_src[0],temp,channels_dst[0]);
    bitwise_and(channels_src[1],temp,channels_dst[1]);
    bitwise_and(channels_src[2],temp,channels_dst[2]);

    merge(channels_dst,3,dst);

    return dst;
}


void HistogramModule(Mat& sources, Rect )
{
    const int NTEMPS = 7;

    Mat templates[NTEMPS];
    Mat resultsMatch[NTEMPS];

    templates[0] = imread("temp8.jpeg", CV_LOAD_IMAGE_COLOR);
    templates[1] = imread("temp10.jpeg", CV_LOAD_IMAGE_COLOR);
    templates[2] = imread("temp11.jpeg", CV_LOAD_IMAGE_COLOR);
    templates[3] = imread("temp1.jpeg", CV_LOAD_IMAGE_COLOR);
    templates[4] = imread("temp9.jpeg", CV_LOAD_IMAGE_COLOR);
    templates[5] = imread("temp3.jpeg", CV_LOAD_IMAGE_COLOR);
    templates[6] = imread("temp6.jpeg", CV_LOAD_IMAGE_COLOR);

    /* Error handling */

    if(! sources.data )
    {
        cout <<  "Could not open or find the image where is waldo" << std::endl ;
        return;
    }

    for(int i=0; i<NTEMPS; i++)
    {
        if(! templates[i].data)
        {
            cout <<  "Could not open or find the image" << i << std::endl ;
            return;
        }
    }

    /* Back Projection */

    double results[NTEMPS] = {1,1,1,1,1,1,1};
    Rect result_rects[NTEMPS];

    //Mat buffer[NTEMPS];
    bestMatches<NTEMPS>(sources, templates, resultsMatch);
    for(int i=0;i<NTEMPS;i++){
        resultsMatch[i] = combine_binary(sources, resultsMatch[i]);
        //imshow( "Where is Waldo? Found!"+i, resultsMatch[i]);
    }
    //waitKey(0);

    /* Histogram correlation */

    for(int i=0; i<NTEMPS;i++)
        matchWaldo<NTEMPS>(resultsMatch[i], templates, results, result_rects, 1);

    for(int i=0; i<NTEMPS; i++){
        cout << " Correlation "<< ((i+1)*255/NTEMPS) << ": " <<  results[i] << "\n";
        //rectangle(sources, result_rects[i], (i+1)*255/NTEMPS, 2);
    }

    //imshow( "Where is Waldo? Found!", sources);
    //waitKey(0);

}

/** Example *****************************************************************
int main()
{
    Mat sources[1] = {imread("whereiswaldo3.jpeg", CV_LOAD_IMAGE_COLOR)};
    //sources[0] = imread("temp8.jpeg", CV_LOAD_IMAGE_COLOR);

    HistogramModule<1>(sources);

    return 0;
}
******************************************************************************/


/*
template< std::size_t N >
void surfMatching(Mat source, Mat templates[N], int nscale=1)
{
    if(nscale<1){
        cout << "No se puede ingresar un valor de escalamiento menor a 1.\n";
        return;
    }

    ///Loop for matches in the source image
    Mat subArea;
    int temp_width;
    int temp_height;
    double actual_comparation;

    //vector of keypoints
    vector< cv::KeyPoint > keypointsO[N]; //keypoints for object
    vector< cv::KeyPoint > keypointsS; //keypoints for scene

    SurfFeatureDetector surf(1500);
    for(int i=0;i<N;i++)
        surf.detect(templates[i],keypointsO);

    //Descriptor matrices
    Mat descriptors_templ[N], descriptors_source;

    SurfDescriptorExtractor extractor;
    for(int i=0;i<N;i++)
        extractor.compute( templates[i], keypointsO, descriptors_templ[i] );

    //Declering flann based matcher
    FlannBasedMatcher matcher;
    vector< vector< DMatch > > matches;
    vector< DMatch > good_matches;

    for(int ntemps=0; ntemps<N; ntemps++){
        temp_width  = templates[ntemps].cols;
        temp_height = templates[ntemps].rows;

        for(int it=1;it<=nscale;it++){
            for(int wi=0; wi<(source.cols); wi++){
                for(int hi=0; hi<(source.rows); hi++){
                    subArea = source(Rect(wi, hi, temp_width/it, temp_height/it));

                    surf.detect(subArea,keypointsS);
                    extractor.compute( subArea, keypointsS, descriptors_source );

                    matcher.knnMatch( descriptors_templ[ntemps], descriptors_source, matches, 2 );

                    good_matches.reserve(matches.size());

                    for (size_t i = 0; i < matches.size(); ++i)
                    {
                        if (matches[i].size() < 2)
                                    continue;

                        const DMatch &m1 = matches[i][0];
                        const DMatch &m2 = matches[i][1];

                        if(m1.distance <= 1 * m2.distance) // nndrRatio
                            good_matches.push_back(m1);
                    }

                    std::vector< Point2f >  obj;
                    std::vector< Point2f >  scene;

                    for( unsigned int i = 0; i < good_matches.size(); i++ )
                    {
                        //-- Get the keypoints from the good matches
                        obj.push_back( keypointsO[ good_matches[i].queryIdx ].pt );
                        scene.push_back( keypointsS[ good_matches[i].trainIdx ].pt );
                    }

                    Mat H = findHomography( obj, scene, CV_RANSAC );

                    //-- Get the corners from the object to be "detected"
                    std::vector< Point2f > obj_corners[4];
                    obj_corners[0] = cvPoint(0,0);
                    obj_corners[1] = cvPoint( objectP.cols, 0 );
                    obj_corners[2] = cvPoint( objectP.cols, objectP.rows );
                    obj_corners[3] = cvPoint( 0, objectP.rows );
                    std::vector< Point2f > scene_corners(4);

                    perspectiveTransform( obj_corners, scene_corners, H);
                }
            }
        }
    }
}
*/
