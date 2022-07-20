#ifndef PRODBREND_H
#define PRODBREND_H

#include <QDialog>
#include <QtSql>
#include <QFileDialog>
#include <QMessageBox>
#include "StaffInterface.h"

namespace Ui {
class prodBrend;
}

class prodBrend : public QDialog
{
    Q_OBJECT

public:
    explicit prodBrend(QWidget *parent = nullptr);
    ~prodBrend();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::prodBrend *ui;
    QSqlRecord record;
};

#endif // PRODBREND_H
