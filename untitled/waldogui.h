#ifndef WALDOGUI_H
#define WALDOGUI_H

#include <QMainWindow>
#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QImage>
#include <QDebug>
#include "filtrosgui.h"


namespace Ui {
class WaldoGUI;
}

using namespace cv;
using namespace std;

class WaldoGUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit WaldoGUI(QWidget *parent = 0);
    ~WaldoGUI();
    cv::Mat getWaldoImage();
    void setFiltrosWindow(FiltrosGUI* win);

private:
    Ui::WaldoGUI *ui;
    Mat waldoImage;
    QImage viewImage;
    FiltrosGUI* filWind;
    QImage MatToQImage(const Mat& mat);




public slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_actionVerFiltros_triggered();
    void cargarImagenOriginal();
    void cargarImagenProcesada();

signals:
    void texto_listo(QString);
    void imagen_lista();
    void imagen_lista_2();
    void charge_Filters();


};

#endif // WALDOGUI_H
