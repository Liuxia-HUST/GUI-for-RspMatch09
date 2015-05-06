#include "run_rspmatch_dlg.h"
#include "ui_run_rspmatch_dlg.h"
#include <QFileDialog>
run_RspMatch_dlg::run_RspMatch_dlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::run_RspMatch_dlg)
{
    ui->setupUi(this);
}

run_RspMatch_dlg::~run_RspMatch_dlg()
{
    delete ui;
}



void run_RspMatch_dlg::on_pushButton_run_clicked()
{

    process = new QProcess(this);
//    process->setStandardOutputFile("output.txt");
    process->start("./rspm09.exe");
    ui->textBrowser->append("process started.");
    process->start("./rspm09.exe", QIODevice::ReadWrite);

    QString inpFileName = ui->lineEdit_inpFileName->text() + '\n';
    process->write(inpFileName.toLatin1());
//    process->write("Add.inp\n");

    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(start_read_output()));// !!!!!!!!!!!!!!!!!!!
    connect(process, SIGNAL(readyReadStandardError()), this, SLOT(start_read_err_output()));
}

void run_RspMatch_dlg::start_read_output()
{
    QByteArray data = process->readAllStandardOutput();
    ui->textBrowser->append(QString(data));
}

void run_RspMatch_dlg::start_read_err_output()
{
    QByteArray ba = process->readAllStandardError();
    ui->textBrowser->append("error: " + ba);
}

void run_RspMatch_dlg::on_pushButton_select_inpFile_clicked()
{
    QString inp_file_full, inp_file_name, inp_file_path;
    QFileInfo fi;
    inp_file_full = QFileDialog::getOpenFileName(this,tr("Open Inp File"), "/home/*.inp", tr("inp Files (*.inp)"));
    fi = QFileInfo(inp_file_full);
    inp_file_name = fi.fileName();
    inp_file_path = fi.absolutePath();
    ui->textBrowser->append(inp_file_full + '\n');
    ui->textBrowser->append(inp_file_name + '\n');
    ui->textBrowser->append(inp_file_path);
    ui->lineEdit_inpFileName->setText(inp_file_name);
}

void run_RspMatch_dlg::on_pushButton_kill_RspMatch_clicked()
{
    process->kill();
}
