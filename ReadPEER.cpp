#include "ReadPEER.h"

void Read_PEER_From_File(QString file_name, QVector<double> &Acc, int *NPTS, double *DT)
{
    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox Msg;
        Msg.setText("Can't Open File!");
        return;
    }

    int HeadLines = HEAD_LINE;
    QString line;
    //跳过前HeadLines行
    for (int i =0;i<HeadLines - 1;i++)
    {
        line = file.readLine();
    }

    // NPTS ,DT
    line = "";
    line = file.readLine();
    QStringList myList;
    myList = line.simplified().split(" ");
    *NPTS = myList[0].toInt();
    *DT = myList[1].toDouble();
    //
    while (!file.atEnd()) {
        line = "";
        line = file.readLine();
        myList = line.simplified().split(" ");
        int N  =  myList.count();
        double acc_tmp=0.0;
        for (int i = 0; i<N; i++)
        {
            acc_tmp =  myList[i].toDouble();
            Acc.append(acc_tmp);
        }
    }
}

double get_PGA(QVector<double> &Acc)
{
    int N = Acc.size();
    double PGA = 0.0;
    for (int i = 0; i<N; i++)
    {
        if(PGA < fabs(Acc[i]))
            PGA = fabs(Acc[i]);
    }

    return PGA;
}
