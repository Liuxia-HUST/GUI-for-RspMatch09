#ifndef SHOW_TABLE_DLG_H
#define SHOW_TABLE_DLG_H

#include <QDialog>

namespace Ui {
class Show_Table_Dlg;
}

class Show_Table_Dlg : public QDialog
{
    Q_OBJECT

public:
    explicit Show_Table_Dlg(QWidget *parent = 0);
    ~Show_Table_Dlg();

private:
    Ui::Show_Table_Dlg *ui;
};

#endif // SHOW_TABLE_DLG_H
