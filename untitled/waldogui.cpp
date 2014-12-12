#include "waldogui.h"
#include "ui_waldogui.h"

WaldoGUI::WaldoGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WaldoGUI)
{
    ui->setupUi(this);
}

WaldoGUI::~WaldoGUI()
{
    delete ui;
}
