#include "waldogui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WaldoGUI w;
    w.show();

    return a.exec();
}
