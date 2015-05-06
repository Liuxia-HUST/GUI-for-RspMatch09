#ifndef INPUTFILE_DEFINE_DIALOG_H
#define INPUTFILE_DEFINE_DIALOG_H

#include <QDialog>

namespace Ui {
class InputFile_Define_Dialog;
}

class InputFile_Define_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit InputFile_Define_Dialog(QWidget *parent = 0);
    ~InputFile_Define_Dialog();

private slots:

    void on_pushButton_open_TgtResponse_clicked();

    void on_pushButton_open_InitialAccFile_clicked();

    void on_pushButton_Generate_inpFile_clicked();

private:
    Ui::InputFile_Define_Dialog *ui;
};

#endif // INPUTFILE_DEFINE_DIALOG_H
