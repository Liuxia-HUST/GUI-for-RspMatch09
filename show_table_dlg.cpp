#include "show_table_dlg.h"
#include "ui_show_table_dlg.h"
extern QVector<double> InintialAcc,Times;

Show_Table_Dlg::Show_Table_Dlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Show_Table_Dlg)
{
    ui->setupUi(this);
    ui->tableWidget_showAcc->setColumnCount(2);
    ui->tableWidget_showAcc->setRowCount(Times.count());
    QStringList colName;
    colName << "Time" << "Acc";
    ui->tableWidget_showAcc->setHorizontalHeaderLabels(colName);

    ui->tableWidget_showAcc->setColumnWidth(0, 100);
    ui->tableWidget_showAcc->setColumnWidth(1, 200);
    ui->tableWidget_showAcc->horizontalHeader()->setStretchLastSection(1);
    for (int i =0; i < Times.count(); i++)
    {
        ui->tableWidget_showAcc->setItem(i, 0, new QTableWidgetItem(QString::number(Times[i]) ));
        ui->tableWidget_showAcc->setItem(i, 1, new QTableWidgetItem(QString::number(InintialAcc[i]) ));
    }
    ui->tableWidget_showAcc->setEditTriggers(QAbstractItemView::NoEditTriggers);// 禁止编辑
}

Show_Table_Dlg::~Show_Table_Dlg()
{
    delete ui;
}
