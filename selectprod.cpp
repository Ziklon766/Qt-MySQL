#include "selectprod.h"
#include "ui_selectprod.h"

selectProd::selectProd(QWidget *parent, int type) :
    QDialog(parent),
    ui(new Ui::selectProd)
{
    ui->setupUi(this);
    int i=0;
    flag = type;
    QString str;
    switch (flag) {
        case 0:
            setWindowTitle("Колличество продаваемого товара");
            //переносим список товаров
            while(i < qobject_cast<MainWindow*>(parent)->getRelModel(0)->rowCount()){
                record = qobject_cast<MainWindow*>(parent)->getRelModel(0)->record(i++);
                str = record.value("brend_name").toString() + ", " + record.value("model").toString() + ", " + record.value("V").toString()
                        + ", " + record.value("fuel").toString() + ", " + record.value("transmis").toString() + ", " + record.value("power").toString()
                        + ", " + record.value("year").toString() + ", " + record.value("unit").toString() + ", " + record.value("color_body").toString()
                        + ", " + record.value("color_in").toString() + ", " + record.value("material").toString() + ", " + record.value("price").toString();
                ui->prodCmb->addItem(str, record.value("prod_id").toString());
            }
        break;
        case 1:
            setWindowTitle("Заключенные договара на посавку товара");
            //переносим список товаров
            while(i < qobject_cast<MainWindow*>(parent)->getRelModel(0)->rowCount()){
                record = qobject_cast<MainWindow*>(parent)->getRelModel(0)->record(i++);
                str = record.value("brend_name").toString() + ", " + record.value("model").toString() + ", " + record.value("V").toString()
                        + ", " + record.value("fuel").toString() + ", " + record.value("transmis").toString() + ", " + record.value("power").toString()
                        + ", " + record.value("year").toString() + ", " + record.value("unit").toString() + ", " + record.value("color_body").toString()
                        + ", " + record.value("color_in").toString() + ", " + record.value("material").toString() + ", " + record.value("price").toString();
                ui->prodCmb->addItem(str, record.value("prod_id").toString());
            }
        break;
        case 2:
            setWindowTitle("Поставщики по типу товара");
            ui->label->setText("Выберите тип:");
            ui->prodCmb->addItem("Легковой");
            ui->prodCmb->addItem("Грузовой");
            ui->prodCmb->addItem("Мотоцикл");
            ui->prodCmb->addItem("Водный");
        break;

    }
}

selectProd::~selectProd()
{
    delete ui;
}

void selectProd::on_buttonBox_accepted()
{
    QMessageBox msgBox;
    QSqlQuery query ;

    switch (flag) {
        case 0:{
            query.prepare("SELECT * FROM consignment WHERE product_id=:id AND ord_num>0");
            query.bindValue(":id",ui->prodCmb->itemData(ui->prodCmb->currentIndex()).toInt());
            query.exec();
            msgBox.setText("Товар: "+ui->prodCmb->currentText()+" был продан "+QString::number(query.size())+" раз");
        break;}
        case 1:{
            query.prepare("SELECT * FROM treatys JOIN companys ON treatys.company_id=companys.company_id WHERE num_treaty IN (SELECT treaty_num FROM consignment WHERE product_id=:id AND treaty_num>0)");
            query.bindValue(":id",ui->prodCmb->itemData(ui->prodCmb->currentIndex()).toInt());
            query.exec();
            QString str = "Товар: "+ui->prodCmb->currentText()+" фигурирует в договорах:" + "\n";
            if(query.size()){
                while(query.next()){

                    str += "- номер "+query.value(0).toString() + " с компанией "+query.value(7).toString() + " от "+query.value(2).toString() +'\n';
                }
            }else {
                str = "Нет договоров на данный товар";
            }
            msgBox.setText(str);
        break;}
        case 2:{
            query.prepare("SELECT name FROM companys WHERE company_id IN"
                          "(SELECT company_id FROM treatys WHERE num_treaty IN"
                          "(SELECT treaty_num FROM consignment WHERE product_id IN"
                          "(SELECT prod_id FROM products WHERE type=:typ)))");
            query.bindValue(":typ",ui->prodCmb->currentText());
            query.exec();
            QString str = "Товары типа '"+ui->prodCmb->currentText()+"' поставляли следующие компании:" + "\n";
            if(query.size()){
                while(query.next()){

                    str += "- "+query.value(0).toString() +'\n';
                }
            }else {
                str = "Товаров данного типа нет в договорах";
            }
            msgBox.setText(str);
        break;}
    }

    msgBox.setWindowTitle("Результат");
    msgBox.exec();
}
