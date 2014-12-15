#include <stdio.h>
#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <string>
#include "opencv2/imgproc/imgproc.hpp"


using namespace std;
using namespace cv;

Mat img; Mat templ[5][4]; Mat result[10];


int main()
{
    //leer imagen
    img = imread("imagen.jpg");  // CAMBIAR , se debiese pasar el parametro Mat?



    // Source image to display
    Mat img_display;
    img.copyTo( img_display );

    int result_cols; int result_rows;

    // Para minmaxLoc
    double minVal; double maxVal; Point minLoc; Point maxLoc;
    //guardar maximo global
    double MAX = 0; Point MAXLoc; int num;

    //cargar templates
    templ[0][0] = imread("template/template11.jpg");
    templ[0][1] = imread("template/template12.jpg");
    templ[0][2] = imread("template/template13.jpg");
    templ[0][3] = imread("template/template14.jpg");
    templ[1][0] = imread("template/template21.jpg");
    templ[1][1] = imread("template/template22.jpg");
    templ[1][2] = imread("template/template23.jpg");
    templ[1][3] = imread("template/template24.jpg");
    templ[2][0] = imread("template/template31.jpg");
    templ[2][1] = imread("template/template32.jpg");
    templ[2][2] = imread("template/template33.jpg");
    templ[2][3] = imread("template/template34.jpg");
    templ[3][0] = imread("template/template41.jpg");
    templ[3][1] = imread("template/template42.jpg");
    templ[3][2] = imread("template/template43.jpg");
    templ[3][3] = imread("template/template44.jpg");
    templ[4][0] = imread("template/template51.jpg");
    templ[4][1] = imread("template/template52.jpg");
    templ[4][2] = imread("template/template53.jpg");
    templ[4][3] = imread("template/template54.jpg");



    //FOR tamaños templates
    for (int i=0;i<5;i++)
    {

        // Matriz de resultados
        result_cols =  img.cols - templ[i][0].cols + 1;
        result_rows = img.rows - templ[i][0].rows + 1;

        result[i].create( result_cols, result_rows, CV_32FC1 );

        //FOR rotacion
        for (int j=0;j<4;j++)
        {

            // Matching y normalizacion
            matchTemplate( img, templ[i][j], result[i], CV_TM_CCOEFF_NORMED);

            //guardar maximo para esta rotacion de template
            minMaxLoc( result[i], &minVal, &maxVal, &minLoc, &maxLoc, Mat() );

            //comparar con maximo global para este tamaño
            if (maxVal>MAX)
            {
                MAX = maxVal;
                num = j;
                MAXLoc = maxLoc;
            }
            normalize( result[i], result[i], 0, 1, NORM_MINMAX, -1, Mat() );
            //buscar maximo
            minMaxLoc( result[i], &minVal, &maxVal, &minLoc, &maxLoc, Mat() );

        }
        //termina FOR rotacion

        //buscar nuevamente aquella rotacion que arrojo mejor resultado
        matchTemplate( img, templ[i][num], result[i], CV_TM_CCOEFF_NORMED);
        minMaxLoc( result[i], &minVal, &maxVal, &minLoc, &maxLoc, Mat() );

        // mostrar resultados
        rectangle( img_display, Point( maxLoc.x-10,maxLoc.y-10), Point( maxLoc.x+10 + templ[i][num].cols , maxLoc.y + templ[i][num].rows+10 ), Scalar::all(0), 2, 8, 0 );
        rectangle( result[i], maxLoc, Point( maxLoc.x + templ[i][num].cols , maxLoc.y + templ[i][num].rows ), Scalar::all(0), 2, 8, 0 );

        //termina FOR tamaños

    }
   // imshow( "result_window", result[4] );
    //Mostrar mejor resultado de cada template
    imshow( "resultado MatchTemplate", img_display ); //comentar

 


    waitKey(0);
    return 0;       //DEBIESE DEVOLVER EL RESULTADO? ( result[0] hasta [result[4] )




}

