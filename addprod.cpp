#include "addprod.h"
#include "ui_addprod.h"


addProd::addProd(QWidget *parent, int cur) :
    QDialog(parent),
    ui(new Ui::addProd)
{
    ui->setupUi(this);
    num=cur;

    QSqlQuery query;
    QString  str = "SELECT brend_id,brend_name FROM brends ORDER BY brend_name";       //Запрос на получение требуемых данных из таблицы species
    query.exec(str);

    while(query.next())         //Проход по строкам запроса
    {
       ui->brendCmb->addItem(query.value(1).toString(),query.value(0)); //поле с индексом 1 добавляется как значение в список, а с индексом 0 как UserData
    }

    ui->amountLb->setText("0");

    ui->VSb->setMinimum(1.2);
    ui->powerSb->setMinimum(50);
    ui->priceBox->setMinimum(1000);
    ui->yearSb->setMinimum(1900);

    ui->VSb->setMaximum(10);
    ui->powerSb->setMaximum(1000);
    ui->priceBox->setMaximum(100000000);
    ui->yearSb->setMaximum(2022);

    ui->fuelCmb->addItem("бензин");
    ui->fuelCmb->addItem("дизель");
    ui->fuelCmb->addItem("газ");
    ui->transCmb->addItem("MT");
    ui->transCmb->addItem("AT");
    ui->transCmb->addItem("RT");
    ui->unitCmb->addItem("передний");
    ui->unitCmb->addItem("задний");
    ui->unitCmb->addItem("полный");
    if(num>-1){//если это изменение записи
        record = qobject_cast<MainWindow*>(parent)->getRelModel(0)->record(num); //Получить запись из модели, необходимо явное преобразование типов
        ui->modelEdit->setText(record.value("model").toString());
        ui->colorEdit->setText(record.value("color_body").toString());
        ui->inColorEdit->setText(record.value("color_in").toString());
        ui->matEdit->setText(record.value("material").toString());

        ui->VSb->setValue(record.value("V").toDouble());
        ui->powerSb->setValue(record.value("power").toInt());
        ui->yearSb->setValue(record.value("year").toInt());
        ui->priceBox->setValue(record.value("price").toInt());
        ui->amountLb->setText(record.value("amount").toString());

        ui->brendCmb->setCurrentText(record.value("brend_name").toString());

        ui->unitCmb->setCurrentText(record.value("unit").toString());
        ui->fuelCmb->setCurrentText(record.value("fuel").toString());
        ui->transCmb->setCurrentText(record.value("transmis").toString());
        ui->typrCmb->setCurrentText(record.value("type").toString());

        setWindowTitle("Изменение данных о товаре");
    }
    else{
        setWindowTitle("Добавление товара");
    }
}

addProd::~addProd()
{
    delete ui;
}

addProd::New addProd::add(){
   New el;                           //Объявление структуры
   el.model=ui->modelEdit->text();
   el.color_body=ui->colorEdit->text();
   el.color_in=ui->inColorEdit->text();
   el.material=ui->matEdit->text();

   el.V=(float)ui->VSb->value();
   el.power=(float)ui->powerSb->value();
   el.year=ui->yearSb->value();
   el.price=ui->priceBox->value();
   el.amount=ui->amountLb->text().toInt();
   el.type=ui->typrCmb->currentText();

   el.unit=ui->unitCmb->currentText();
   el.fuel=ui->fuelCmb->currentText();
   el.transmis=ui->transCmb->currentText();
   el.transmis=ui->typrCmb->currentText();

   el.brend_id=ui->brendCmb->itemData(ui->brendCmb->currentIndex()).toInt();

   return el;          //Структура с данными возвращается в основную форму
}

void addProd::on_buttonBox_accepted()
{
    if(num!=-1){
        QMessageBox msgBox; //Стоит спросить уверен ли пользователь
        QString str=QString("Уверены что хотите сохранить изменения о товаре?");
        msgBox.setText(str);
        msgBox.setWindowTitle("Подтверждение");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setInformativeText("Данная операция необратима!");
        QPushButton* pButtonNo = msgBox.addButton("Нет", QMessageBox::NoRole); //Для корректного перевода, кнопки добавлены вручную
        QPushButton* pButtonYes = msgBox.addButton("Да", QMessageBox::YesRole);
        msgBox.setDefaultButton(pButtonYes);
        if(msgBox.exec()==QMessageBox::Accepted){
           qobject_cast<MainWindow*>(parent())->getRelModel(0)->setData(qobject_cast<MainWindow*>(parent())->getRelModel(0)->index(num,1),ui->brendCmb->itemData(ui->brendCmb->currentIndex()).toInt());
           qobject_cast<MainWindow*>(parent())->getRelModel(0)->setData(qobject_cast<MainWindow*>(parent())->getRelModel(0)->index(num,2),ui->modelEdit->text());
           qobject_cast<MainWindow*>(parent())->getRelModel(0)->setData(qobject_cast<MainWindow*>(parent())->getRelModel(0)->index(num,3),ui->VSb->value());
           qobject_cast<MainWindow*>(parent())->getRelModel(0)->setData(qobject_cast<MainWindow*>(parent())->getRelModel(0)->index(num,4),ui->fuelCmb->currentText());
           qobject_cast<MainWindow*>(parent())->getRelModel(0)->setData(qobject_cast<MainWindow*>(parent())->getRelModel(0)->index(num,5),ui->transCmb->currentText());
           qobject_cast<MainWindow*>(parent())->getRelModel(0)->setData(qobject_cast<MainWindow*>(parent())->getRelModel(0)->index(num,6),ui->powerSb->value());
           qobject_cast<MainWindow*>(parent())->getRelModel(0)->setData(qobject_cast<MainWindow*>(parent())->getRelModel(0)->index(num,7),ui->yearSb->value());
           qobject_cast<MainWindow*>(parent())->getRelModel(0)->setData(qobject_cast<MainWindow*>(parent())->getRelModel(0)->index(num,8),ui->unitCmb->currentText());
           qobject_cast<MainWindow*>(parent())->getRelModel(0)->setData(qobject_cast<MainWindow*>(parent())->getRelModel(0)->index(num,9),ui->colorEdit->text());
           qobject_cast<MainWindow*>(parent())->getRelModel(0)->setData(qobject_cast<MainWindow*>(parent())->getRelModel(0)->index(num,10),ui->inColorEdit->text());
           qobject_cast<MainWindow*>(parent())->getRelModel(0)->setData(qobject_cast<MainWindow*>(parent())->getRelModel(0)->index(num,11),ui->matEdit->text());
           qobject_cast<MainWindow*>(parent())->getRelModel(0)->setData(qobject_cast<MainWindow*>(parent())->getRelModel(0)->index(num,12),ui->priceBox->value());
           qobject_cast<MainWindow*>(parent())->getRelModel(0)->setData(qobject_cast<MainWindow*>(parent())->getRelModel(0)->index(num,13),ui->amountLb->text().toInt());
           qobject_cast<MainWindow*>(parent())->getRelModel(0)->setData(qobject_cast<MainWindow*>(parent())->getRelModel(0)->index(num,14),ui->typrCmb->currentText());
           qobject_cast<MainWindow*>(parent())->getRelModel(0)->submitAll();
        }
    }
}
