#ifndef ADDORDER_H
#define ADDORDER_H

#include <QDialog>
#include <QtSql>
#include <QFileDialog>
#include <QMessageBox>
#include "StaffInterface.h"

namespace Ui {
class addorder;
}

class addorder : public QDialog
{
    Q_OBJECT

public:
    explicit addorder(QWidget *parent = nullptr, int cur=1);
    ~addorder();

    struct New {
           bool done;
           QDate date;
           int client, sum;
           QList<int> *prod_list, *amouts;            //для создания партии
       };
    //Метод, который вернут созданные данные в основную программу
    New add();

private slots:
    void on_buttonBox_accepted();

    void on_addClientBtn_clicked();

    void on_addProdBtn_clicked();

    void on_delProdBtn_clicked();

    void on_changeCountBtn_clicked();

private:
    Ui::addorder *ui;
    int num;
    QSqlRecord record;

    int summa, ord_num;
    QList<int> prod_list, amouts;
};

#endif // ADDORDER_H
