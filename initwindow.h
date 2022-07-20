#ifndef INITWINDOW_H
#define INITWINDOW_H

#include <QMainWindow>
#include "StaffInterface.h"

namespace Ui {
class initwindow;
}

class initwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit initwindow(QWidget *parent = nullptr);
    ~initwindow();

private slots:
    void on_checkBox_stateChanged(int arg1);

    void on_pushButton_clicked();

private:
    Ui::initwindow *ui;
    bool CreateConnection();
    MainWindow *staf_w;
    QSqlDatabase db;
};

#endif // INITWINDOW_H
