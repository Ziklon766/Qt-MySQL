#ifndef ADDCONSIG_H
#define ADDCONSIG_H

#include <QDialog>
#include <QtSql>
#include <QFileDialog>
#include <QMessageBox>
#include "StaffInterface.h"

namespace Ui {
class addConsig;
}

class addConsig : public QDialog
{
    Q_OBJECT

public:
    explicit addConsig(QWidget *parent = nullptr, int cur=1);
    ~addConsig();
    struct New {
           int treaty, prod, amount;
       };
    //Метод, который вернут созданные данные в основную программу
    New add();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::addConsig *ui;
    int num;
    QSqlRecord record;
};

#endif // ADDCONSIG_H
