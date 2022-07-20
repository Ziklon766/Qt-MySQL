#include "addorder.h"
#include "ui_addorder.h"

addorder::addorder(QWidget *parent, int cur) :
    QDialog(parent),
    ui(new Ui::addorder)
{
    ui->setupUi(this);
    num=cur;
    summa=0;
    int i=0;
    ui->amountSb->setMinimum(1);
    QSqlQuery query;
    QString  str = "SELECT client_id,name,surname,phone FROM clients ORDER BY name";       //Запрос на получение требуемых данных из таблицы species
    query.exec(str);

    //перенос списка клиентов
    while(query.next())         //Проход по строкам запроса
    {
        str = query.value(1).toString() + " " + query.value(2).toString() + ", " + query.value(3).toString();
        ui->clientCmb->addItem(str,query.value(0).toInt()); //поле с индексом 1 добавляется как значение в список, а с индексом 0 как UserData
    }
    //переносим список товаров
    while(i < qobject_cast<MainWindow*>(parent)->getRelModel(0)->rowCount()){
        record = qobject_cast<MainWindow*>(parent)->getRelModel(0)->record(i++);
        str = record.value("brend_name").toString() + ", " + record.value("model").toString() + ", " + record.value("V").toString()
                + ", " + record.value("fuel").toString() + ", " + record.value("transmis").toString() + ", " + record.value("power").toString()
                + ", " + record.value("year").toString() + ", " + record.value("unit").toString() + ", " + record.value("color_body").toString()
                + ", " + record.value("color_in").toString() + ", " + record.value("material").toString() + ", " + record.value("price").toString();
        ui->prodCmb->addItem(str, record.value("prod_id").toInt());
    }

    if(num>-1){//если это изменение записи
        record = qobject_cast<MainWindow*>(parent)->getRelModel(2)->record(num); //Получить запись из модели, необходимо явное преобразование типов
        query.prepare("SELECT * FROM orders WHERE order_num=:id");
        query.bindValue(":id", record.value("order_num").toInt());
        if(!query.exec())
            qDebug()<<"ERROR";
        query.next();

        ui->dateEdit->setDate(query.value(2).toDate());
        ui->clientCmb->setCurrentText(ui->clientCmb->itemText(ui->clientCmb->findData(query.value(1).toInt())));
        ui->sum->setText(query.value(3).toString());
        summa=query.value(3).toInt();
        ui->checkBox->setChecked(query.value(4).toBool());
        //запоминаем номер договора
        ord_num = record.value("order_num").toInt();

        //запрос партии
        query.prepare("SELECT product_id, amount FROM consignment WHERE ord_num=:num");
        query.bindValue(":num",record.value("order_num").toInt());
        if (!query.exec())  {                            //Выполнение запроса, в случае ошибки выдать предупреждение
           qDebug()  <<  "Unable to select!!";           //Так как в реальной ситуации запрос сработает всегда, вывод только в qDebug
        }
        //вывод списка товаров
        while(query.next())         //Проход по строкам запроса
        {
            ui->listWidget->addItem(ui->prodCmb->itemText(ui->prodCmb->findData(query.value(0).toInt())) + "; кол-во: " + query.value(1).toString());
        }
        setWindowTitle("Изменение данных о заказе");
    }
    else{
        setWindowTitle("Добавление заказа");
    }
    ui->sum->setText(QString::number(summa));

}

addorder::~addorder()
{
    delete ui;
}
//добавление
addorder::New addorder::add(){
   New el;                           //Объявление структуры
   el.client=ui->clientCmb->itemData(ui->clientCmb->currentIndex()).toInt();
   el.date=ui->dateEdit->date();
   el.done=ui->checkBox->isChecked();
   el.sum=ui->sum->text().toInt();

   el.prod_list = &prod_list;      //партия
   el.amouts = &amouts;            //колличества

   return el;          //Структура с данными возвращается в основную форму
}
//изменение
void addorder::on_buttonBox_accepted()
{
    if(num!=-1){
        QMessageBox msgBox; //Стоит спросить уверен ли пользователь
        QString str=QString("Уверены что хотите сохранить изменения о продаже?");//.arg(ui->anNameEdit->text());
        msgBox.setText(str);
        msgBox.setWindowTitle("Подтверждение");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setInformativeText("Данная операция необратима!");
        QPushButton* pButtonNo = msgBox.addButton("Нет", QMessageBox::NoRole); //Для корректного перевода, кнопки добавлены вручную
        QPushButton* pButtonYes = msgBox.addButton("Да", QMessageBox::YesRole);
        msgBox.setDefaultButton(pButtonYes);
        if(msgBox.exec()==QMessageBox::Accepted){
           qobject_cast<MainWindow*>(parent())->getRelModel(2)->setData(qobject_cast<MainWindow*>(parent())->getRelModel(2)->index(num,1),ui->clientCmb->itemData(ui->clientCmb->currentIndex()).toInt());
           qobject_cast<MainWindow*>(parent())->getRelModel(2)->setData(qobject_cast<MainWindow*>(parent())->getRelModel(2)->index(num,2),ui->dateEdit->date());
           qobject_cast<MainWindow*>(parent())->getRelModel(2)->setData(qobject_cast<MainWindow*>(parent())->getRelModel(2)->index(num,3),ui->sum->text().toInt());
           qobject_cast<MainWindow*>(parent())->getRelModel(2)->setData(qobject_cast<MainWindow*>(parent())->getRelModel(2)->index(num,4),ui->checkBox->isChecked());
           qobject_cast<MainWindow*>(parent())->getRelModel(2)->submitAll();

           //партии
           while(!prod_list.isEmpty()){
               qobject_cast<MainWindow*>(parent())->getRelModel(6)->insertRows(qobject_cast<MainWindow*>(parent())->getRelModel(6)->rowCount(),1);
               qobject_cast<MainWindow*>(parent())->getRelModel(6)->setData(qobject_cast<MainWindow*>(parent())->getRelModel(6)->index(qobject_cast<MainWindow*>(parent())->getRelModel(6)->rowCount()-1, 3), ord_num);
               qobject_cast<MainWindow*>(parent())->getRelModel(6)->setData(qobject_cast<MainWindow*>(parent())->getRelModel(6)->index(qobject_cast<MainWindow*>(parent())->getRelModel(6)->rowCount()-1, 1), prod_list.last());
               qobject_cast<MainWindow*>(parent())->getRelModel(6)->setData(qobject_cast<MainWindow*>(parent())->getRelModel(6)->index(qobject_cast<MainWindow*>(parent())->getRelModel(6)->rowCount()-1, 2), amouts.last());
               qobject_cast<MainWindow*>(parent())->getRelModel(6)->submitAll();
               prod_list.pop_back();
               amouts.pop_back();
           }

        }
    }
}

//добавление нового клинета
void addorder::on_addClientBtn_clicked()
{
    qobject_cast<MainWindow*>(parent())->AddChangeRecord(3, false);
    ui->clientCmb->clear();
    QSqlQuery query;
    QString  str = "SELECT client_id,name,surname,phone FROM clients ORDER BY name";       //Запрос на получение требуемых данных из таблицы species
    query.exec(str);

    while(query.next())         //Проход по строкам запроса
    {
       ui->clientCmb->addItem(query.value(1).toString() + " " + query.value(2).toString() + ", " + query.value(3).toString(),query.value(0)); //поле с индексом 1 добавляется как значение в список, а с индексом 0 как UserData
    }
}

//добавление товара в заказ
void addorder::on_addProdBtn_clicked()
{
    ui->listWidget->addItem(ui->prodCmb->currentText() + "; кол-во " + QString::number(ui->amountSb->value()));
    prod_list.append(ui->prodCmb->itemData(ui->prodCmb->currentIndex()).toInt());
    amouts.append(ui->amountSb->value());

    int i;
    while(i < qobject_cast<MainWindow*>(parent())->getRelModel(0)->rowCount()){
        record = qobject_cast<MainWindow*>(parent())->getRelModel(0)->record(i++);
        if(record.value("prod_id").toInt() == prod_list.last()){
            summa += record.value("price").toInt()*ui->amountSb->value();
            break;
        }
    }
    ui->sum->setText(QString::number(summa));
}

//удаление товара из списка(партии)
void addorder::on_delProdBtn_clicked()
{
    if(ui->listWidget->currentRow() != -1){
        QString prod_info = ui->listWidget->item(ui->listWidget->currentRow())->text();
        prod_info = prod_info.left(prod_info.indexOf(';'));
        int prod_id = ui->prodCmb->itemData(ui->prodCmb->findText(prod_info)).toInt();
        //количество записей в поставках
        int count = qobject_cast<MainWindow*>(parent())->getRelModel(6)->rowCount()-1;
        QMessageBox msgBox;
        while(count>-1){
            record = qobject_cast<MainWindow*>(parent())->getRelModel(4)->record(count);
            if(record.value("ord_num").toInt() == ord_num && record.value("product_id").toInt() == prod_id){
                msgBox.setText(record.value("ord_num").toString() + record.value("product_id").toString());
                msgBox.setIcon(QMessageBox::Warning);
                QPushButton *pButtonYes, *pButtonNo;
                pButtonNo = msgBox.addButton("Нет", QMessageBox::NoRole);
                pButtonYes = msgBox.addButton("Да", QMessageBox::YesRole);
                msgBox.setWindowTitle("Подтверждение");
                msgBox.setInformativeText("Данные будут удалены безвозвратно!");
                msgBox.setDefaultButton(pButtonNo);
                msgBox.exec();
                if(msgBox.clickedButton()==pButtonYes){
                    //лезем за стоимостью товара
                    int count2 = qobject_cast<MainWindow*>(parent())->getRelModel(0)->rowCount()-1;
                    int amount = record.value("amount").toInt();
                    while(count2>-1){
                        record = qobject_cast<MainWindow*>(parent())->getRelModel(0)->record(count2);
                        if(record.value("prod_id").toInt() == prod_id){
                            summa -= record.value("price").toInt()*amount;
                            break;
                        }
                        count2--;
                    }
                    qobject_cast<MainWindow*>(parent())->getRelModel(6)->removeRows(count,1);
                    qobject_cast<MainWindow*>(parent())->getRelModel(6)->submitAll();
                }
                ui->sum->setText(QString::number(summa));
                delete ui->listWidget->takeItem(ui->listWidget->currentRow());
                break;
            }
            count--;
        }
    } else {
        QMessageBox msgBox;
        msgBox.setText("Не выбран товар");
        msgBox.setWindowTitle("Предупреждение");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
    }
}

//измененеи кол-ва
void addorder::on_changeCountBtn_clicked()
{
    if(ui->listWidget->currentRow() != -1){
        QSqlQuery query;
        QString prod_info = ui->listWidget->item(ui->listWidget->currentRow())->text();
        prod_info = prod_info.left(prod_info.indexOf(';'));
        int prod_id = ui->prodCmb->itemData(ui->prodCmb->findText(prod_info)).toInt();

        //получаем стоимость товара
        query.prepare("SELECT price FROM products WHERE prod_id=:id");
        query.bindValue(":id",prod_id);
        if(!query.exec())
            qDebug()<<"Не найден товар";
        query.next();
        int price = query.value(0).toInt();
        query.prepare("SELECT amount FROM consignment WHERE product_id=:id");
        query.bindValue(":id",prod_id);
        if(query.exec())
            qDebug()<<"Количество";
        query.next();
        summa -= price*query.value(0).toInt();
        summa += price*ui->spinBox->value();
        query.prepare("UPDATE consignment SET amount=:count WHERE (ord_num=:num) AND (product_id=:id)");
        query.bindValue(":count",ui->spinBox->value());
        query.bindValue(":num",ord_num);
        query.bindValue(":id",prod_id);
        if(!query.exec())
            qDebug()<<"Ошибка";
        qobject_cast<MainWindow*>(parent())->getRelModel(6)->submitAll();
        prod_info = prod_info + "; кол-во: " + QString::number(ui->spinBox->value());
        ui->listWidget->item(ui->listWidget->currentRow())->setText(prod_info);
        ui->sum->setText(QString::number(summa));
    }else {
        QMessageBox msgBox;
        msgBox.setText("Не выбран товар");
        msgBox.setWindowTitle("Предупреждение");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
    }
}
