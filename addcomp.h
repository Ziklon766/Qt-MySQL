#ifndef ADDCOMP_H
#define ADDCOMP_H

#include <QDialog>
#include <QtSql>
#include <QFileDialog>
#include <QMessageBox>
#include "StaffInterface.h"

namespace Ui {
class addComp;
}

class addComp : public QDialog
{
    Q_OBJECT

public:
    explicit addComp(QWidget *parent = nullptr, int cur=1);
    ~addComp();
    struct New {
           QString name, address, phone, type;
       };
    //Метод, который вернут созданные данные в основную программу
    New add();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::addComp *ui;
    int num;
    QSqlRecord record;
};

#endif // ADDCOMP_H
