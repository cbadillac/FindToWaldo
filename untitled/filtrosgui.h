#ifndef FILTROSGUI_H
#define FILTROSGUI_H

#include <QMainWindow>

namespace Ui {
class FiltrosGUI;
}

class FiltrosGUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit FiltrosGUI(QWidget *parent = 0);
    ~FiltrosGUI();

private:
    Ui::FiltrosGUI *ui;
};

#endif // FILTROSGUI_H
