#ifndef PLOT_ACC_DIALOG_H
#define PLOT_ACC_DIALOG_H

#include <QDialog>

namespace Ui {
class plot_Acc_Dialog;
}

class plot_Acc_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit plot_Acc_Dialog(QWidget *parent = 0);
    ~plot_Acc_Dialog();

private:
    Ui::plot_Acc_Dialog *ui;
};

#endif // PLOT_ACC_DIALOG_H
