#include "prodbrend.h"
#include "ui_prodbrend.h"

prodBrend::prodBrend(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::prodBrend)
{
    ui->setupUi(this);
    int i=0;
    QString str;
    //переносим список товаров
    while(i < qobject_cast<MainWindow*>(parent)->getModel(1)->rowCount()){
        record = qobject_cast<MainWindow*>(parent)->getModel(1)->record(i++);
        str = record.value("brend_name").toString();
        ui->brendCmb->addItem(str, record.value("prod_id").toString());
    }
    setWindowTitle("Все товары бренда");
}

prodBrend::~prodBrend()
{
    delete ui;
}

void prodBrend::on_buttonBox_accepted()
{
    QMessageBox msgBox;
    QSqlQuery query;

    query.prepare("SELECT * FROM products WHERE brend_id=:id");
    query.bindValue(":id",ui->brendCmb->itemData(ui->brendCmb->currentIndex()).toInt());
    query.exec();
    msgBox.setWindowTitle("Результат");
    msgBox.setText("Товар: "+ui->brendCmb->currentText()+" был продан "+QString::number(query.size())+" раз");
    msgBox.exec();
}
