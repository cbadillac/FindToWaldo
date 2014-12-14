#include "filtrosgui.h"
#include "ui_filtrosgui.h"

FiltrosGUI::FiltrosGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FiltrosGUI)
{
    ui->setupUi(this);
    //TODO
    //QObject::connect(SENDER, SIGNAL(this->filtroUnoListo(Mat&)), this, SLOT(mostrarFiltroUno(Mat&)));
    //QObject::connect(SENDER, SIGNAL(this->filtroDosListo(Mat&)), this, SLOT(mostrarFiltroDos(Mat&)));
    //QObject::connect(SENDER, SIGNAL(this->filtroTresListo(Mat&)), this, SLOT(mostrarFiltroTres(Mat&)));
}

FiltrosGUI::~FiltrosGUI()
{
    delete ui;
}

void FiltrosGUI::mostrarFiltroUno(Mat& img)
{
    QImage imagenListaTransf = this-> MatToQImage(img);
    QLabel* vistaImagenProcesada = new QLabel();
    vistaImagenProcesada->setPixmap(QPixmap::fromImage(imagenListaTransf,
                                                       Qt::AutoColor));
    ui->scrollArea->setWidget(vistaImagenProcesada);
}

void FiltrosGUI::mostrarFiltroDos(Mat& img)
{
    QImage imagenListaTransf = this-> MatToQImage(img);
    QLabel* vistaImagenProcesada = new QLabel();
    vistaImagenProcesada->setPixmap(QPixmap::fromImage(imagenListaTransf,
                                                       Qt::AutoColor));
    ui->scrollArea_2->setWidget(vistaImagenProcesada);
}

void FiltrosGUI::mostrarFiltroTres(Mat& img)
{
    QImage imagenListaTransf = this-> MatToQImage(img);
    QLabel* vistaImagenProcesada = new QLabel();
    vistaImagenProcesada->setPixmap(QPixmap::fromImage(imagenListaTransf,
                                                       Qt::AutoColor));
    ui->scrollArea_3->setWidget(vistaImagenProcesada);
}

QImage FiltrosGUI::MatToQImage(const Mat& mat)
{
    // 8-bits unsigned, NO. OF CHANNELS=1
    if(mat.type()==CV_8UC1)
    {
        // Set the color table (used to translate colour indexes to qRgb values)
        QVector<QRgb> colorTable;
        for (int i=0; i<256; i++)
            colorTable.push_back(qRgb(i,i,i));
        // Copy input Mat
        const uchar *qImageBuffer = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);
        img.setColorTable(colorTable);
        return img;
    }
    // 8-bits unsigned, NO. OF CHANNELS=3
    if(mat.type()==CV_8UC3)
    {
        // Copy input Mat
        const uchar *qImageBuffer = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return img.rgbSwapped();
    }
    else
    {
        qDebug() << "ERROR: Mat could not be converted to QImage.";
        return QImage();
    }
}
