#include "filtrosgui.h"
#include "ui_filtrosgui.h"

FiltrosGUI::FiltrosGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FiltrosGUI)
{
    ui->setupUi(this);
}

FiltrosGUI::~FiltrosGUI()
{
    delete ui;
}
