#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ReadPEER.h"
#include "plot_acc_dialog.h"
#include "show_table_dlg.h"
#include "inputfile_define_dialog.h"
#include "run_rspmatch_dlg.h"
#include <QFileDialog>

QVector<double> alpha(200), freq(200), period(200);
QVector<double> InintialAcc,Times;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Gamma->setText("1");
    ui->MaxIter->setText("5");
    ui->Tol->setText("0.05");
    ui->iModel->addItem("1", 1);
    ui->iModel->addItem("6", 6);
    ui->iModel->addItem("7", 7);
    ui->lineEdit_Tg->setText("0.40");
    ui->lineEdit_alpha_max->setText("0.9");


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ShowSetting_clicked()
{

    ui->TextOutPut->setText("The inp File setting:\n");
    ui->TextOutPut->append(ui->MaxIter->text());
    ui->TextOutPut->append(ui->Tol->text());
    ui->TextOutPut->append(ui->Gamma->text());
    ui->TextOutPut->append(ui->iModel->currentText());

}

void MainWindow::on_pushButton_PlotRsp_clicked()
{
    // generate some data:
//    QVector<double> x(101), y(101), z(101); // initialize with entries 0..100
//    for (int i=0; i<101; ++i)
//    {
//      x[i] = i/50.0 - 1; // x goes from -1 to 1
//      y[i] = x[i]*x[i]; // let's plot a quadratic function
//      z[i] = x[i]*x[i]*x[i]*x[i];
//    }
//    ui->customplot_Rsp->legend->setVisible(true);
//    ui->customplot_Rsp->addGraph();
//    ui->customplot_Rsp->graph(0)->setPen(QPen(Qt::blue));
//    ui->customplot_Rsp->graph(0)->setData(x,y);
//    ui->customplot_Rsp->graph(0)->setName("x^2");

//    ui->customplot_Rsp->addGraph();
//    ui->customplot_Rsp->graph(1)->setPen(QPen(Qt::red));
//    ui->customplot_Rsp->graph(1)->setData(x,z);
//    ui->customplot_Rsp->graph(1)->setName("x^4");
//    ui->customplot_Rsp->xAxis->setRange(-1,1);
//    ui->customplot_Rsp->yAxis->setRange(0,1);
//    ui->customplot_Rsp->replot();
    MainWindow::on_pushButton_Calculate_sepc_clicked();
    //
    double alpha_max= 0.0;
    for (int i = 0; i < 200; i++)
    {
//        ui->TextOutPut->append(QString::number(i) + ' '+QString::number(freq[i]) + ' ' +QString::number(period[i]) + ' ' + QString::number(alpha[i])+ '\n');
        if (alpha_max < alpha[i])
            alpha_max = alpha[i];
    }
    //
    ui->customplot_Rsp->addGraph();
    // 频率坐标
//    ui->customplot_Rsp->graph(0)->addData(freq, alpha);
//    ui->customplot_Rsp->graph(0)->setPen(QPen(Qt::blue));
//    ui->customplot_Rsp->xAxis->setLabel("Freq(Hz)");
//    ui->customplot_Rsp->yAxis->setLabel("Sa(g)");
//    ui->customplot_Rsp->xAxis->setScaleType(QCPAxis::stLogarithmic);//设置x轴为对数比例
//    ui->customplot_Rsp->xAxis->setRange(0.1, 100);
//    ui->customplot_Rsp->yAxis->setRange(0, alpha_max*1.05);
//    ui->customplot_Rsp->replot();

    // 周期坐标
    ui->customplot_Rsp->graph(0)->addData(period, alpha);
    ui->customplot_Rsp->graph(0)->setPen(QPen(Qt::blue));
    ui->customplot_Rsp->xAxis->setLabel("T(s)");
    ui->customplot_Rsp->yAxis->setLabel("Sa(g)");
    ui->customplot_Rsp->xAxis->setRange(0, 6.0);
    ui->customplot_Rsp->yAxis->setRange(0, alpha_max*1.05);
    ui->customplot_Rsp->replot();
}


void MainWindow::on_pushButton_Calculate_sepc_clicked()
{


    double eta_2 = 1.0;
    double eta_1 = 0.02;
    double T_0 = 0.1;
    double gama = 0.9;
    double T_g ;
    double alpha_max;

    QString str = ui->lineEdit_Tg->text();
    T_g = str.toDouble();
    str = ui->lineEdit_alpha_max->text();
    alpha_max = str.toDouble();

    period[0] = 0.01;
    freq[0] = 100;
    for (int i=1; i<200; ++i)
    {
        period[i] = 1.035322*period[i-1];
        freq[i] = (1.0/period[i]);
    }
    for(int i=0; i< 200; i++)
    {
        if (period[i] < T_0)
                alpha[i] = (0.45*alpha_max + period[i] * (eta_2*alpha_max - 0.45*alpha_max)/T_0);
        else if (period[i] < T_g)
                alpha[i] = (eta_2 *alpha_max);
        else if (period[i] < 5*T_g)
                alpha[i] = (pow(T_g/period[i], gama) * eta_2 *alpha_max);
        else
                alpha[i] = ((eta_2*pow(0.2,gama)-eta_1*(period[i] - 5*T_g)) * alpha_max);
    }
//    QMessageBox msgBox;
//    msgBox.setText("Design Spec Calculated!");
//    msgBox.exec();
}

void MainWindow::on_pushButton_save_spec_clicked()
{
    QString FileName;
    FileName = "./Code.tgt";
    QFile file(FileName);
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QMessageBox msgBox;
        msgBox.setText("Can't open file.");
        msgBox.exec();
        return;
    }

    QTextStream out(&file);//新建流对象，指向选定文件

    out << "GB50011" <<endl;
    out << "200	1" << endl;
    out << "0.05" << endl;
    out.setFieldWidth(6);
    out.setRealNumberPrecision(4);
    out.setRealNumberNotation(QTextStream:: FixedNotation);
    for(int i=0; i<200; ++i)
    {
        out << freq[199 - i] <<" 0.0000 1000.0000 " <<alpha[199 - i] <<endl;
    }
    //
    file.close();
    //
    QMessageBox msgBox;
    msgBox.setText("Design Spec Saved!");
    msgBox.exec();
}

void MainWindow::on_actionOpenFile_triggered()
{
    // 清除之前保存的数据
    Times.clear();
    InintialAcc.clear();
    //
    QString file_name = QFileDialog::getOpenFileName(this,tr("Open NGA AT2 File"), "/home/*.AT2", tr("tgt Files (*.AT2)"));
       // 获取输入
    //int HeadLines = 4;
    double DT = 0.01;
    int NPTS;
    ui->TextOutPut->append(file_name +'\n' + QString::number(DT)+'\n' );
//    NPTS = InintialAcc.count();
    Read_PEER_From_File(file_name, InintialAcc, &NPTS, &DT);
    double PGA=0.0;
    PGA = get_PGA(InintialAcc);
    for(int i = 0;i < NPTS; i++)
    {
        Times.append((i+1) *DT);
//        ui->TextOutPut->append(QString::number(Times[i]) + '\t' + QString::number(InintialAcc[i]) +'\t');
    }
    ui->customplot_Acc->addGraph();
    ui->customplot_Acc->graph(0)->clearData();// 清除之前的绘图
    ui->customplot_Acc->graph(0)->addData(Times, InintialAcc);
    ui->customplot_Acc->xAxis->setLabel("Time(s)");
    ui->customplot_Acc->xAxis->setRange(0,Times[Times.count()-1]);
    ui->customplot_Acc->yAxis->setRange(-1.05*PGA, 1.05*PGA);
    ui->customplot_Acc->replot();
    ui->TextOutPut->append(QString::number(Times.count()) + '\t' + QString::number(InintialAcc.count())  + '\n');
}

void MainWindow::on_pushButton_Show_AccDlg_clicked()
{
    plot_Acc_Dialog *AccDlg = new plot_Acc_Dialog(this);
    AccDlg->show();
}

void MainWindow::on_pushButton_clicked()
{
    Show_Table_Dlg *TableDlg = new Show_Table_Dlg(this);
    TableDlg->show();
}

void MainWindow::on_pushButton_DefineInpDlg_open_clicked()
{
    InputFile_Define_Dialog *DefineInpDlg = new InputFile_Define_Dialog(this);
    DefineInpDlg->show();
}

void MainWindow::on_pushButton_run_RspMatch_clicked()
{
    run_RspMatch_dlg *runRspMatchDlg = new run_RspMatch_dlg(this);
    runRspMatchDlg->show();
}
