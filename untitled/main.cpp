#include "waldogui.h"
#include "filtrosgui.h"
#include <QApplication>
#include <opencv/cv.h>
#include <opencv/highgui.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FiltrosGUI filterWindow;
    WaldoGUI w(&filterWindow);
    //filterWindow.show();
    w.show();

    return a.exec();
}
