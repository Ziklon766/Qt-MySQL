#ifndef ADDCCIENT_H
#define ADDCCIENT_H

#include <QDialog>
#include <QtSql>
#include <QFileDialog>
#include <QMessageBox>
#include "StaffInterface.h"

namespace Ui {
class addcCient;
}

class addcCient : public QDialog
{
    Q_OBJECT

public:
    explicit addcCient(QWidget *parent = nullptr, int cur=1);
    ~addcCient();
    //структура для хранения полей создаваемой записи
    struct NewClient {
           QString name, surename, phone, mail, psw;
       };
    NewClient addClient();//Метод, который вернут созданные данные в основную программу

private slots:
    void on_buttonBox_accepted();

private:
    Ui::addcCient *ui;
    int num;
    QSqlRecord record;
};

#endif // ADDCCIENT_H
