#ifndef ADDPROD_H
#define ADDPROD_H

#include <QDialog>
#include <QtSql>
#include <QFileDialog>
#include <QMessageBox>
#include "StaffInterface.h"

namespace Ui {
class addProd;
}

class addProd : public QDialog
{
    Q_OBJECT

public:
    explicit addProd(QWidget *parent = nullptr, int cur=1);
    ~addProd();
    struct New {
           QString model, fuel, transmis, unit,
                    color_body, color_in, material, type;
           float V;
           int brend_id, power, year, price, amount;
       };
    //Метод, который вернут созданные данные в основную программу
    New add();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::addProd *ui;
    int num;
    QSqlRecord record;
};

#endif // ADDPROD_H
