#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_ShowSetting_clicked();

    void on_pushButton_PlotRsp_clicked();

    void on_pushButton_Calculate_sepc_clicked();

    void on_pushButton_save_spec_clicked();

    void on_actionOpenFile_triggered();

    void on_pushButton_Show_AccDlg_clicked();

    void on_pushButton_clicked();

    void on_pushButton_DefineInpDlg_open_clicked();

    void on_pushButton_run_RspMatch_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
