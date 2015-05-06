#ifndef RUN_RSPMATCH_DLG_H
#define RUN_RSPMATCH_DLG_H

#include <QDialog>
#include <QProcess>

namespace Ui {
class run_RspMatch_dlg;
}

class run_RspMatch_dlg : public QDialog
{
    Q_OBJECT

public:
    explicit run_RspMatch_dlg(QWidget *parent = 0);
    ~run_RspMatch_dlg();
    QProcess* process;// !!!!!!!!!!!!!!!!!!!

private slots:
    void on_pushButton_run_clicked();
    void start_read_output();// !!!!!!!!!!!!!!!!!!!
    void start_read_err_output();

    void on_pushButton_select_inpFile_clicked();

    void on_pushButton_kill_RspMatch_clicked();

private:
    Ui::run_RspMatch_dlg *ui;
};

#endif // RUN_RSPMATCH_DLG_H
