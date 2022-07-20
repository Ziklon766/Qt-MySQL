#ifndef SELECTPROD_H
#define SELECTPROD_H

#include <QDialog>
#include <QtSql>
#include <QFileDialog>
#include <QMessageBox>
#include "StaffInterface.h"

namespace Ui {
class selectProd;
}

class selectProd : public QDialog
{
    Q_OBJECT

public:
    explicit selectProd(QWidget *parent = nullptr, int type = 0);
    ~selectProd();
    int flag;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::selectProd *ui;
    QSqlRecord record;
};

#endif // SELECTPROD_H
