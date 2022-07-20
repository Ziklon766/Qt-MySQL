#ifndef ADDTREATY_H
#define ADDTREATY_H

#include <QDialog>
#include <QtSql>
#include <QFileDialog>
#include <QMessageBox>
#include "StaffInterface.h"
#include "addprod.h"

typedef struct newprod{
    QString model, fuel, transmis, unit,
             color_body, color_in, material;
    float V;
    int brend_id, power, year, price, amount;
};

namespace Ui {
class addtreaty;
}

class addtreaty : public QDialog
{
    Q_OBJECT

public:
    explicit addtreaty(QWidget *parent = nullptr, int cur=1);
    ~addtreaty();

    struct New {
           QDate date, date_comp;
           int company, sum, paid;
           QList<int> *prod_list, *amouts;            //для создания партии
       };
    //Метод, который вернут созданные данные в основную программу
    New add();

private slots:
    void on_buttonBox_accepted();

    void on_newComp_clicked();

    void on_addProd_clicked();

    void on_addNewProdButton_clicked();

    void on_delProdButton_clicked();

    void on_changeCountBtn_clicked();

private:
    Ui::addtreaty *ui;
    int num;
    QSqlRecord record;

    int summa, treaty_num;
    QList<int> prod_list, amouts;
};

#endif // ADDTREATY_H
