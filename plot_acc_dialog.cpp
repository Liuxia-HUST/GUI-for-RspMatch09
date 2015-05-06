#include "plot_acc_dialog.h"
#include "ui_plot_acc_dialog.h"
#include "ReadPEER.h"
extern QVector<double> InintialAcc,Times;

plot_Acc_Dialog::plot_Acc_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::plot_Acc_Dialog)
{
    ui->setupUi(this);
    ui->customPlot_acc->addGraph();
    ui->customPlot_acc->graph(0)->clearData();
    ui->customPlot_acc->graph(0)->setData(Times,InintialAcc);
    ui->customPlot_acc->xAxis->setLabel("Time(s)");
    ui->customPlot_acc->xAxis->setRange(0,Times[Times.count()-1]);
    double PGA = get_PGA(InintialAcc);
    ui->customPlot_acc->yAxis->setRange(-1.05*PGA, 1.05*PGA);
    ui->customPlot_acc->replot();
//
}

plot_Acc_Dialog::~plot_Acc_Dialog()
{
    delete ui;
}

