#include "inputfile_define_dialog.h"
#include "ui_inputfile_define_dialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
InputFile_Define_Dialog::InputFile_Define_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputFile_Define_Dialog)
{
    ui->setupUi(this);
    // 设置iModel
    ui->comboBox_iModel->addItem("1", 1);
    ui->comboBox_iModel->addItem("6", 6);
    ui->comboBox_iModel->addItem("7", 7);
    ui->comboBox_iModel->setCurrentIndex(2);//默认显式为7
    //
    ui->lineEdit_MaxIter->setText("30");;
    //
    ui->lineEdit_Tol->setText("0.05");
    //
    ui->lineEdit_Gamma->setText("1.0");
    //
    ui->lineEdit_a1->setText("1.25");
    ui->lineEdit_a2->setText("0.25");
    ui->lineEdit_f1->setText("1.0");
    ui->lineEdit_f2->setText("4.0");
    //
    ui->comboBox_Scale->addItem("0", 0);
    ui->comboBox_Scale->addItem("1", 1);
    ui->comboBox_Scale->addItem("2", 2);
    ui->comboBox_Scale->setCurrentIndex(2);
    ui->lineEdit_Period->setText("0.0");
    //
    ui->lineEdit_dtFlag->setText("1");
    //
    ui->lineEdit_evmin->setText("1.0e-4");
    //
    ui->lineEdit_Groupsize->setText("30");
    //
    ui->lineEdit_MaxFreq->setText("35.0");
    //
    ui->lineEdit_fBand_1->setText("0.0");
    ui->lineEdit_fBand_2->setText("0.0");
    ui->lineEdit_nPole->setText("4");
    //
    ui->comboBox_iModPGA->addItem("0", 0);
    ui->comboBox_iModPGA->addItem("1", 1);
    ui->comboBox_iModPGA->setCurrentIndex(0);
    //
    ui->lineEdit_iSeed->setText("0");
    //
    ui->lineEdit_RanFactor->setText("0.0");
    //
    ui->lineEdit_freqMatch1->setText("0.1");
    ui->lineEdit_freqMatch2->setText("35.0");
    //
    ui->comboBox_BaselineCorFlag->addItem("0", 0);
    ui->comboBox_BaselineCorFlag->addItem("1", 1);
    ui->comboBox_BaselineCorFlag->setCurrentIndex(0);
    //
    ui->lineEdit_ScaleFactor->setText("1.0");




}

InputFile_Define_Dialog::~InputFile_Define_Dialog()
{
    delete ui;
}


void InputFile_Define_Dialog::on_pushButton_open_TgtResponse_clicked()
{

    QString tgt_file_full, tgt_file_name, tgt_file_path;
    QFileInfo fi;
    tgt_file_full = QFileDialog::getOpenFileName(this,tr("Open Target Response Spectrum"), "/home/*.tgt", tr("tgt Files (*.tgt)"));
    fi = QFileInfo(tgt_file_full);
    tgt_file_name = fi.fileName();
    tgt_file_path = fi.absolutePath();
    ui->textBrowser->append(tgt_file_full + '\n');
    ui->textBrowser->append(tgt_file_name + '\n');
    ui->textBrowser->append(tgt_file_path);
    ui->lineEdit_tgt_filename->setText(tgt_file_name);

}


void InputFile_Define_Dialog::on_pushButton_open_InitialAccFile_clicked()
{

    QString acc_file_full, acc_file_name, acc_file_path;
    QFileInfo fi;
    acc_file_full = QFileDialog::getOpenFileName(this,tr("Open Initial Acc File"), "/home/*.acc", tr("acc Files (*.acc)"));
    fi = QFileInfo(acc_file_full);
    acc_file_name = fi.fileName();
    acc_file_path = fi.absolutePath();
    ui->textBrowser->append(acc_file_full + '\n');
    ui->textBrowser->append(acc_file_name + '\n');
    ui->textBrowser->append(acc_file_path);
    ui->lineEdit_InintialAccFile->setText(acc_file_name);
}

void InputFile_Define_Dialog::on_pushButton_Generate_inpFile_clicked()
{
    QString FileName;
    FileName = "./current.inp";
    QFile file(FileName);
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QMessageBox msgBox;
        msgBox.setText("Can't open file.");
        msgBox.exec();
        return;
    }

    QTextStream out(&file);//新建流对象，指向选定文件

    out << ui->lineEdit_MaxIter->text() <<endl;
    out << ui->lineEdit_Tol->text()<<endl;
    out << ui->lineEdit_Gamma->text() << endl;
    out << ui->comboBox_iModel->currentText() << endl;
    out << ui->lineEdit_a1->text() << '\t' << ui->lineEdit_a2->text()<<'\t' << ui->lineEdit_f1->text()<< '\t' << ui->lineEdit_f2->text() << endl;
    out << ui->comboBox_Scale->currentText()<< '\t'<< ui->lineEdit_Period->text() << endl;
    out << ui->lineEdit_dtFlag->text() << endl;
    out << ui->lineEdit_evmin->text() << endl;
    out << ui->lineEdit_Groupsize->text() << endl;
    out << ui->lineEdit_MaxFreq->text() << endl;
    out << ui->lineEdit_fBand_1->text() << '\t' << ui->lineEdit_fBand_2->text() << '\t' << ui->lineEdit_nPole->text() << endl;
    out << ui->comboBox_iModPGA->currentText() << endl;
    out << ui->lineEdit_iSeed->text() << '\t' << ui->lineEdit_RanFactor->text() << endl;
    out << ui->lineEdit_freqMatch1->text() << '\t' << ui->lineEdit_freqMatch2->text() << endl;
    out << ui->comboBox_BaselineCorFlag->currentText() << endl;
    out << ui->lineEdit_ScaleFactor->text() << endl;

    //
    out << "Input Files\\" << ui->lineEdit_tgt_filename->text() << endl;
    out << "Input Files\\" << ui->lineEdit_InintialAccFile->text() << endl;
    out << "Output Files\\" << ui->lineEdit_InintialAccFile->text() << endl;
    out << "Output Files\\" << ui->lineEdit_InintialAccFile->text().replace(".acc", ".rsp") << endl;
    out << "Output Files\\" << ui->lineEdit_InintialAccFile->text().replace(".acc", ".unm") << endl;
    //
    file.close();
    //
    QMessageBox msgBox;
    msgBox.setText("inp File Saved!");
    msgBox.exec();
}
