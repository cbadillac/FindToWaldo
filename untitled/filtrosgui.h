#ifndef FILTROSGUI_H
#define FILTROSGUI_H

#include <QMainWindow>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <QMessageBox>
#include <QImage>
#include <QDebug>

namespace Ui {
class FiltrosGUI;
}

using namespace cv;
using namespace std;

class FiltrosGUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit FiltrosGUI(QWidget *parent = 0);
    ~FiltrosGUI();

private:
    Ui::FiltrosGUI *ui;
    QImage MatToQImage(const Mat& mat);
public slots:
    void mostrarFiltroUno(Mat&);
    void mostrarFiltroDos(Mat&);
    void mostrarFiltroTres(Mat&);

signals:
    void filtroUnoListo(Mat&);
    void filtroDosListo(Mat&);
    void filtroTresListo(Mat&);

};

#endif // FILTROSGUI_H
