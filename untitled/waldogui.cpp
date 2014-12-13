#include "waldogui.h"
#include "ui_waldogui.h"
#include <string>
#include <QLabel>

WaldoGUI::WaldoGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WaldoGUI)
{
    ui->setupUi(this);
    QObject::connect(this, SIGNAL(imagen_lista()), this, SLOT(cargarImagenOriginal()));

}

void WaldoGUI::setFiltrosWindow(FiltrosGUI* win)
{
    filWind = win;
}

WaldoGUI::~WaldoGUI()
{
    delete ui;
}

void WaldoGUI::on_pushButton_clicked()
{
   QString fileName = QFileDialog::getOpenFileName(this, tr("Abrir Imagen"), "./",
        tr("Imagen (*.png *.jpg *.jpeg *.bmp *.ppm);; All files (*.*)"));
   if(fileName == "") return;
   emit texto_listo(fileName);
   Mat waldoImage = imread(fileName.toStdString());
   //cvtColor(waldoImage, waldoImage, CV_BGR2YCrCb);
   viewImage = MatToQImage(waldoImage);

         if(viewImage.isNull()) {
         QMessageBox::information(this, tr("Error de carga!!"), tr("No se puede cargar %1. ").arg(fileName));

         return;
         }
         emit imagen_lista();
}

void WaldoGUI::on_pushButton_2_clicked()
{
    CvCapture* cap = cvCaptureFromCAM(0);
    waldoImage = cvQueryFrame(cap);
    viewImage = MatToQImage(waldoImage);
    if(viewImage.isNull()) {
    QMessageBox::information(this, tr("Error de carga!!"), tr("No se puede cargar webcam"));

    return;
    }
    cvReleaseCapture(&cap);
    emit imagen_lista();
}

void WaldoGUI::on_actionVerFiltros_triggered()
{
    filWind->show();
}

void WaldoGUI::cargarImagenOriginal()
{
    QLabel* vistaImagenLista = new QLabel();
    vistaImagenLista->setPixmap(QPixmap::fromImage(viewImage, Qt::AutoColor));
    ui->scrollArea->setWidget(vistaImagenLista);
}

void WaldoGUI::cargarImagenProcesada()
{
    //TODO
    //QLabel* vistaImagenProcesada = new QLabel();
    //vistaImagenProcesada->setPixmap(QPixmap::fromImage());
}

QImage WaldoGUI::MatToQImage(const Mat& mat)
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
