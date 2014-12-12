#ifndef WALDOGUI_H
#define WALDOGUI_H

#include <QMainWindow>
#include <opencv/cv.h>
#include <opencv/highgui.h>

namespace Ui {
class WaldoGUI;
}

class WaldoGUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit WaldoGUI(QWidget *parent = 0);
    ~WaldoGUI();

private:
    Ui::WaldoGUI *ui;

public slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
signals:
    void imagen_lista();
    void imagen_lista_2();
};

#endif // WALDOGUI_H
