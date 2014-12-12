#ifndef WALDOGUI_H
#define WALDOGUI_H

#include <QMainWindow>

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
};

#endif // WALDOGUI_H
