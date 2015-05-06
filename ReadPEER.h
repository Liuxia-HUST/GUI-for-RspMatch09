#ifndef READPEER_H
#define READPEER_H
#include <QString>
#include <QVector>
#include <QFileDialog>
#include <math.h>
#include <QMessageBox>
#define HEAD_LINE 4

void Read_PEER_From_File(QString file_name, QVector<double> &Acc, int *NPTS, double *DT);
double get_PGA(QVector<double> &Acc);
#endif // READPEER_H
