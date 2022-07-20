#ifndef ADDBREND_H
#define ADDBREND_H

#include <QDialog>
#include <QtSql>
#include <QFileDialog>
#include <QMessageBox>
#include "StaffInterface.h"

namespace Ui {
class addBrend;
}

class addBrend : public QDialog
{
    Q_OBJECT

public:
    explicit addBrend(QWidget *parent = nullptr, int cur=1);
    ~addBrend();
    //структура для хранения полей создаваемой записи
    struct NewBrend {
           QString SpName;
       };
    //Метод, который вернут созданные данные в основную программу
    NewBrend add();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::addBrend *ui;
    int num;
    QSqlRecord record;
};

#endif // ADDBREND_H
