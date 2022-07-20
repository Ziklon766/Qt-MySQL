#include "StaffInterface.h"
#include "ui_StaffInterface.h"
#include <QDebug>
#include <QtSql>
#include <QMessageBox>
#include <QTableView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Автосалон");
    if(!CreateConnection())     exit(-1);


    ui->changeButton->setEnabled(false);
    ui->delButton->setEnabled(false);
    //ui->viewButton->setEnabled(false);
    //------------------------------------загружаем все таблицы--------------------------------------------------------
    //таблица автомобилей
    mdl_prod = new QSqlRelationalTableModel(this,QSqlDatabase::database()); //Подключение модели к БД
    mdl_prod->setTable("products");                                //Выбор таблицы

    mdl_prod->setRelation(1,QSqlRelation("brends","brend_id","brend_name"));

    mdl_prod->select();                                          //Загрузка данных из таблицы в модель
    mdl_prod->setEditStrategy(QSqlTableModel::OnManualSubmit);   //Обновление БД только при вызове метода Submit
    mdl_prod->setHeaderData(0, Qt::Horizontal, tr("id"));        //Подписи к столбцам
    mdl_prod->setHeaderData(1, Qt::Horizontal, tr("Производитель"));
    mdl_prod->setHeaderData(2, Qt::Horizontal, tr("Модель"));
    mdl_prod->setHeaderData(3, Qt::Horizontal, tr("Объем двигателя"));
    mdl_prod->setHeaderData(4, Qt::Horizontal, tr("Используемое топливо"));
    mdl_prod->setHeaderData(5, Qt::Horizontal, tr("Коробка передач"));
    mdl_prod->setHeaderData(6, Qt::Horizontal, tr("Мощность(л.с.)"));
    mdl_prod->setHeaderData(7, Qt::Horizontal, tr("Год"));
    mdl_prod->setHeaderData(8, Qt::Horizontal, tr("Привод"));
    mdl_prod->setHeaderData(9, Qt::Horizontal, tr("Цвет"));
    mdl_prod->setHeaderData(10, Qt::Horizontal, tr("Цвет салона"));
    mdl_prod->setHeaderData(11, Qt::Horizontal, tr("Материал салона"));
    mdl_prod->setHeaderData(12, Qt::Horizontal, tr("Цена"));
    mdl_prod->setHeaderData(13, Qt::Horizontal, tr("Количество"));
    mdl_prod->setHeaderData(14, Qt::Horizontal, tr("Тип"));
    mdl_prod->sort(0,Qt::AscendingOrder);                        //Сортировать записи по возрастанию ключа, так как порядок записей часто меняется
    ui->tableView_prod->setModel(mdl_prod);                           //Подключение таблицы к представлению
    ui->tableView_prod->setEditTriggers(QAbstractItemView::NoEditTriggers); //Отключение возможности редактировать данные напрямую
    ui->tableView_prod->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_prod->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_prod->setColumnHidden(0, true);
    ui->tableView_prod->resizeColumnsToContents();

    //таблица брендов(производители)
    mdl_brend = new QSqlTableModel(this,QSqlDatabase::database()); //Подключение модели к БД
    mdl_brend->setTable("brends");                                //Выбор таблицы
    mdl_brend->select();                                          //Загрузка данных из таблицы в модель
    mdl_brend->setEditStrategy(QSqlTableModel::OnManualSubmit);   //Обновление БД только при вызове метода Submit
    mdl_brend->setHeaderData(0, Qt::Horizontal, tr("id"));        //Подписи к столбцам
    mdl_brend->setHeaderData(1, Qt::Horizontal, tr("Название"));
    mdl_brend->sort(0,Qt::AscendingOrder);                        //Сортировать записи по возрастанию ключа, так как порядок записей часто меняется
    ui->tableView_brend->setModel(mdl_brend);                           //Подключение таблицы к представлению
    ui->tableView_brend->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_brend->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_brend->setEditTriggers(QAbstractItemView::NoEditTriggers); //Отключение возможности редактировать данные напрямую
    ui->tableView_brend->setColumnHidden(0, true);
    ui->tableView_brend->resizeColumnsToContents();

    //таблица клиентов
    mdl_client = new QSqlTableModel(this,QSqlDatabase::database()); //Подключение модели к БД
    mdl_client->setTable("clients");                                //Выбор таблицы

    mdl_client->select();                                          //Загрузка данных из таблицы в модель
    mdl_client->setEditStrategy(QSqlTableModel::OnManualSubmit);   //Обновление БД только при вызове метода Submit
    mdl_client->setHeaderData(0, Qt::Horizontal, tr("id"));        //Подписи к столбцам
    mdl_client->setHeaderData(1, Qt::Horizontal, tr("Имя"));
    mdl_client->setHeaderData(2, Qt::Horizontal, tr("Фамилия"));
    mdl_client->setHeaderData(3, Qt::Horizontal, tr("Телефон"));
    mdl_client->setHeaderData(4, Qt::Horizontal, tr("Почта"));
    mdl_client->setHeaderData(5, Qt::Horizontal, tr("Пароль"));
    mdl_client->sort(0,Qt::AscendingOrder);                        //Сортировать записи по возрастанию ключа, так как порядок записей часто меняется
    ui->tableView_client->setModel(mdl_client);                           //Подключение таблицы к представлению
    ui->tableView_client->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_client->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_client->setEditTriggers(QAbstractItemView::NoEditTriggers); //Отключение возможности редактировать данные напрямую
    ui->tableView_client->setColumnHidden(0, true);
    ui->tableView_client->setColumnHidden(5, true);
    ui->tableView_client->resizeColumnsToContents();

    //таблица заказов
    mdl_ord = new QSqlRelationalTableModel(this,QSqlDatabase::database()); //Подключение модели к БД
    mdl_ord->setTable("orders");                                //Выбор таблицы

    mdl_ord->setRelation(1,QSqlRelation("clients","client_id","surname"));

    mdl_ord->select();                                          //Загрузка данных из таблицы в модель
    mdl_ord->setEditStrategy(QSqlTableModel::OnManualSubmit);   //Обновление БД только при вызове метода Submit
    mdl_ord->setHeaderData(0, Qt::Horizontal, tr("Номер чека"));        //Подписи к столбцам
    mdl_ord->setHeaderData(1, Qt::Horizontal, tr("Покупатель"));        //Подписи к столбцам
    mdl_ord->setHeaderData(2, Qt::Horizontal, tr("Дата"));
    mdl_ord->setHeaderData(3, Qt::Horizontal, tr("Сумма"));
    mdl_ord->setHeaderData(4, Qt::Horizontal, tr("Выполнен"));
    mdl_ord->sort(0,Qt::AscendingOrder);                        //Сортировать записи по возрастанию ключа, так как порядок записей часто меняется
    ui->tableView_ord->setModel(mdl_ord);                           //Подключение таблицы к представлению
    ui->tableView_ord->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_ord->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_ord->setEditTriggers(QAbstractItemView::NoEditTriggers); //Отключение возможности редактировать данные напрямую
    ui->tableView_ord->resizeColumnsToContents();

    //таблица партий
    mdl_cons = new QSqlRelationalTableModel(this,QSqlDatabase::database()); //Подключение модели к БД
    mdl_cons->setTable("consignment");                                //Выбор таблицы
    mdl_cons->select();                                          //Загрузка данных из таблицы в модель
    mdl_cons->setEditStrategy(QSqlTableModel::OnManualSubmit);   //Обновление БД только при вызове метода Submit
    mdl_cons->setHeaderData(0, Qt::Horizontal, tr("Номер договора"));        //Подписи к столбцам
    mdl_cons->setHeaderData(1, Qt::Horizontal, tr("Номер товара"));
    mdl_cons->setHeaderData(2, Qt::Horizontal, tr("Колличество товара"));
    mdl_cons->setHeaderData(3, Qt::Horizontal, tr("Номер заказа"));
    mdl_cons->sort(0,Qt::AscendingOrder);                        //Сортировать записи по возрастанию ключа, так как порядок записей часто меняется
    //ui->tableView_cons->setModel(mdl_cons);                           //Подключение таблицы к представлению
    //ui->tableView_cons->setSelectionMode(QAbstractItemView::SingleSelection);
    //ui->tableView_cons->setSelectionBehavior(QAbstractItemView::SelectRows);
    //ui->tableView_cons->setEditTriggers(QAbstractItemView::NoEditTriggers); //Отключение возможности редактировать данные напрямую
    //ui->tableView_treaty->resizeColumnsToContents();

    //таблица договоров
    mdl_treaty = new QSqlRelationalTableModel(this,QSqlDatabase::database()); //Подключение модели к БД
    mdl_treaty->setTable("treatys");                                //Выбор таблицы

    mdl_treaty->setRelation(1,QSqlRelation("companys","company_id","name"));

    mdl_treaty->select();                                          //Загрузка данных из таблицы в модель
    mdl_treaty->setEditStrategy(QSqlTableModel::OnManualSubmit);   //Обновление БД только при вызове метода Submit
    mdl_treaty->setHeaderData(0, Qt::Horizontal, tr("Номер договора"));        //Подписи к столбцам
    mdl_treaty->setHeaderData(1, Qt::Horizontal, tr("Поставщик"));
    mdl_treaty->setHeaderData(2, Qt::Horizontal, tr("Дата заключения"));
    mdl_treaty->setHeaderData(3, Qt::Horizontal, tr("Дата выполнения"));
    mdl_treaty->setHeaderData(4, Qt::Horizontal, tr("Сумма"));
    mdl_treaty->setHeaderData(5, Qt::Horizontal, tr("Выплаченная сумма"));
    mdl_treaty->setHeaderData(6, Qt::Horizontal, tr("PDF"));
    mdl_treaty->sort(0,Qt::AscendingOrder);                        //Сортировать записи по возрастанию ключа, так как порядок записей часто меняется
    ui->tableView_treaty->setModel(mdl_treaty);                           //Подключение таблицы к представлению
    ui->tableView_treaty->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_treaty->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_treaty->setEditTriggers(QAbstractItemView::NoEditTriggers); //Отключение возможности редактировать данные напрямую
    ui->tableView_treaty->resizeColumnsToContents();

    //таблица поставщиков
    mdl_comp = new QSqlTableModel(this,QSqlDatabase::database()); //Подключение модели к БД
    mdl_comp->setTable("companys");                                //Выбор таблицы
    mdl_comp->select();                                          //Загрузка данных из таблицы в модель
    mdl_comp->setEditStrategy(QSqlTableModel::OnManualSubmit);   //Обновление БД только при вызове метода Submit
    mdl_comp->setHeaderData(0, Qt::Horizontal, tr("id"));        //Подписи к столбцам
    mdl_comp->setHeaderData(1, Qt::Horizontal, tr("Название"));
    mdl_comp->setHeaderData(2, Qt::Horizontal, tr("Адресс"));
    mdl_comp->setHeaderData(3, Qt::Horizontal, tr("Телефон"));

    mdl_comp->sort(0,Qt::AscendingOrder);                        //Сортировать записи по возрастанию ключа, так как порядок записей часто меняется
    ui->tableView_comp->setModel(mdl_comp);                           //Подключение таблицы к представлению
    ui->tableView_comp->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_comp->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_comp->setEditTriggers(QAbstractItemView::NoEditTriggers); //Отключение возможности редактировать данные напрямую
    ui->tableView_comp->setColumnHidden(0, true);
    ui->tableView_comp->resizeColumnsToContents();

    ui->tabWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//соединение с сервером  +done+
bool MainWindow::CreateConnection()
{
   qDebug()<<QSqlDatabase::drivers();
   QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");   //Драйвер MySQL
   db.setHostName("localhost");                            //Адрес сервера
   db.setDatabaseName("autoroom");                              //Имя БД
   db.setUserName("root");                             //Имя пользователя
   db.setPassword("Z1klon766");                       //Пароль пользователя
   db.setPort(3306);                                       //Номер порта
   QMessageBox msgBox;
   if (!db.open()) {
       QString str=QString("Ошибка при открытии базы данных:");
       msgBox.setText(str);
       msgBox.setWindowTitle("Ошибка");
       msgBox.setIcon(QMessageBox::Critical);
       msgBox.setInformativeText(db.lastError().text());
       msgBox.exec();                                      //При ошибке отображение сообщения
       return false;
   }else
       return true;
}

//нажата кнопка "Добавить"
void MainWindow::on_addButton_clicked()
{
    switch (ui->tabWidget->currentIndex()) {
        case 0: AddChangeRecord(0, false); break;
        case 1: AddChangeRecord(1, false); break;
        case 2: AddChangeRecord(2, false); break;
        case 3: AddChangeRecord(3, false); break;
        case 4: AddChangeRecord(4, false); break;
        case 5: AddChangeRecord(5, false); break;
    }
}

//нажата кнопка "Редактировать"
void MainWindow::on_changeButton_clicked()
{
    switch (ui->tabWidget->currentIndex()) {
        case 0: AddChangeRecord(0, true); break;
        case 1: AddChangeRecord(1, true); break;
        case 2: AddChangeRecord(2, true); break;
        case 3: AddChangeRecord(3, true); break;
        case 4: AddChangeRecord(4, true); break;
        case 5: AddChangeRecord(5, true); break;
    }
}

//-------------------------------------удаление записи------------------------------------------------
void MainWindow::on_delButton_clicked()
{
    int tabNum = ui->tabWidget->currentIndex();     //Получение номера текущей таблицы
    int curRec;                                     //Получение номера текущей записи
    QSqlQuery query;
    bool flag = true;
    QMessageBox msgBox; //Стоит спросить пользователя уверен ли он
    QList<int> prod_list;  //на случай удаления договора
    QString str;
    switch (tabNum) {
        case 0://товар
            curRec=ui->tableView_prod->currentIndex().row();
            //запрашиваем связанные партии
            query.prepare("SELECT * FROM consignment WHERE prod_id=:id");//Запрос на получение связанных данных
            query.bindValue(":id",mdl_prod->record(ui->tableView_prod->currentIndex().row()).value("prod_id"));
            if (!query.exec())  {                            //Выполнение запроса, в случае ошибки выдать предупреждение
               qDebug()  <<  "Unable to select!!11";           //Так как в реальной ситуации запрос сработает всегда, вывод только в qDebug
            }
            if(query.size()>0){
                str = QString("Товар связан с партией");
                flag = false;
            }
            //запрашиваем связанные заказы
            query.prepare("SELECT * FROM orders WHERE prod_id=:id");//Запрос на получение связанных данных
            query.bindValue(":id",mdl_prod->record(ui->tableView_prod->currentIndex().row()).value("prod_id"));
            if (!query.exec())  {                            //Выполнение запроса, в случае ошибки выдать предупреждение
               qDebug()  <<  "Unable to select!!11";           //Так как в реальной ситуации запрос сработает всегда, вывод только в qDebug
            }
            if(query.size()>0){
                str = QString("Товар связан с заказом");
                flag = false;
            }
            if(flag)
                str=QString("Уверены что хотите удалить запись с кодом \"%1\"?").arg(mdl_prod->index(curRec,0).data().toString());
        break;
        case 1://бренд
            curRec=ui->tableView_brend->currentIndex().row();

            //запрашиваем связанные товары
            query.prepare("SELECT * FROM products WHERE brend_id=:id");//Запрос на получение связанных данных
            query.bindValue(":id",mdl_brend->record(ui->tableView_brend->currentIndex().row()).value("brend_id"));
            if (!query.exec())  {                            //Выполнение запроса, в случае ошибки выдать предупреждение
               qDebug()  <<  "Unable to select!!11";           //Так как в реальной ситуации запрос сработает всегда, вывод только в qDebug
            }
            if(query.size()>0){
                str = QString("Бренд связан с товаром");
                flag = false;
            }

            if(flag)
                str=QString("Уверены что хотите удалить запись с кодом \"%1\"?").arg(mdl_brend->index(curRec,0).data().toString());
        break;
        case 2://заказ
         {
            int i=0, ord;
            QSqlRecord record;
            curRec=ui->tableView_ord->currentIndex().row();

            //проверяем выполнение
            record = mdl_ord->record(curRec);
            if(mdl_ord->record(curRec).value("done") == 1){
                str = QString("Заказ уже выполнен");
                flag = false;
            }else{
                //получаем список товаров(номера в модели)
                ord = record.value("order_num").toInt();
                while(i < mdl_cons->rowCount()){
                    record = mdl_cons->record(i);
                    if(record.value("ord_num").toInt() == ord){
                        prod_list.append(i);
                    }
                    i++;
                }
            }

            if(flag)
                str=QString("Уверены что хотите удалить запись с кодом \"%1\"?").arg(mdl_ord->index(curRec,0).data().toString());
            break;
        }
        case 3://клиент
        {
            curRec=ui->tableView_client->currentIndex().row();

            //запрашиваем связанные заказы
            query.prepare("SELECT * FROM orders WHERE client_id=:id");//Запрос на получение связанных данных
            query.bindValue(":id",mdl_client->record(ui->tableView_client->currentIndex().row()).value("client_id"));
            if (!query.exec())  {                            //Выполнение запроса, в случае ошибки выдать предупреждение
               qDebug()  <<  "Unable to select!!11";           //Так как в реальной ситуации запрос сработает всегда, вывод только в qDebug
            }
            if(query.size()>0){
                str = QString("У клиента имеются заказы");
                flag = false;
            }

            if(flag)
                str=QString("Уверены что хотите удалить запись с кодом \"%1\"?").arg(mdl_client->index(curRec,0).data().toString());
        break;}
        case 4://договор
        {
            int i=0, tret;
            QSqlRecord record;
            curRec=ui->tableView_treaty->currentIndex().row();
            record = mdl_treaty->record(curRec);
            if(record.value("sum").toInt() == record.value("paid").toInt()){
                //msgBox.setText(record.value("sum").toString() +"=="+ record.value("paid").toString());
                str = QString("Договор выполнен!");
                flag = false;
            }
            else{
                //получаем список товаров(номера в модели)
                tret = record.value("num_treaty").toInt();
                while(i < mdl_cons->rowCount()){
                    record = mdl_cons->record(i);
                    if(record.value("treaty_num").toInt() == tret){
                        prod_list.append(i);
                    }
                    i++;
                }
            }

            if(flag)
                str=QString("Уверены что хотите удалить запись с кодом \"%1\"?").arg(mdl_treaty->index(curRec,0).data().toString());
        break;
        }
        case 5://поставщик
            curRec=ui->tableView_comp->currentIndex().row();

            //запрашиваем связанные договоры
            query.prepare("SELECT * FROM treatys WHERE company_id=:id");//Запрос на получение связанных данных
            query.bindValue(":id",mdl_comp->record(ui->tableView_comp->currentIndex().row()).value("company_id"));
            if (!query.exec())  {                            //Выполнение запроса, в случае ошибки выдать предупреждение
               qDebug()  <<  "Unable to select!!11";           //Так как в реальной ситуации запрос сработает всегда, вывод только в qDebug
            }
            if(query.size()>0){
                str = QString("С этой компанией имеются заключенные договора");
                flag = false;
            }

            if(flag)
                str=QString("Уверены что хотите удалить запись с кодом \"%1\"?").arg(mdl_comp->index(curRec,0).data().toString());
        break;
    }

    msgBox.setText(str);
    msgBox.setIcon(QMessageBox::Warning);
    QPushButton *pButtonYes, *pButtonNo;
    if(flag){
        pButtonNo = msgBox.addButton("Нет", QMessageBox::NoRole);
        pButtonYes = msgBox.addButton("Да", QMessageBox::YesRole);
        msgBox.setWindowTitle("Подтверждение");
        msgBox.setInformativeText("Данные будут удалены безвозвратно!");
        msgBox.setDefaultButton(pButtonNo);
    }
    else {
        msgBox.setWindowTitle("Ошибка");
        pButtonNo = msgBox.addButton("ОК", QMessageBox::NoRole);
        msgBox.setDefaultButton(pButtonNo);
    }


    msgBox.exec();
    if(msgBox.clickedButton()==pButtonYes)
    {
        switch (ui->tabWidget->currentIndex()) {
            case 0:
                mdl_prod->removeRows(curRec,1);
                mdl_prod->submitAll();
            break;
            case 1:
                mdl_brend->removeRows(curRec,1);
                mdl_brend->submitAll();
            break;
            case 2:
                //удаляем партию
                while(!prod_list.isEmpty()){
                    mdl_cons->removeRows(prod_list.last(),1);
                    prod_list.pop_back();
                }
                mdl_cons->submitAll();
                //а теперь и сам заказ
                mdl_ord->removeRows(curRec,1);
                mdl_ord->submitAll();
            break;
            case 3:
                mdl_client->removeRows(curRec,1);
                mdl_client->submitAll();
            break;
            case 4:{
                //удаляем партию
                while(!prod_list.isEmpty()){
                    mdl_cons->removeRows(prod_list.last(),1);
                    prod_list.pop_back();
                }
                mdl_cons->submitAll();
                //а теперь и сам договор
                mdl_treaty->removeRows(curRec,1);
                mdl_treaty->submitAll();
            break;
            }
            case 5:
                mdl_comp->removeRows(curRec,1);
                mdl_comp->submitAll();
            break;
        }
    }
    DisEnBtn();
}

//-------------------------------------добавлние и изменение---------------------------------------------------
bool MainWindow::AddChangeRecord(int table, bool flag){
    int cur;
    QMessageBox msgBox;
    if(flag){//изменение записи
        switch (table) {
            case 0:{
                cur = ui->tableView_prod->currentIndex().row();
                addProd Dlg(this, cur);
                Dlg.setModal(true);
                Dlg.exec();
                break;
            }
            case 1:{
                cur = ui->tableView_brend->currentIndex().row();
                addBrend Dlg(this, cur);
                Dlg.setModal(true);
                Dlg.exec();
                break;
            }
            case 2:{
                cur = ui->tableView_ord->currentIndex().row();
                QSqlRecord record=mdl_ord->record(cur);//Взятие из таблицы нужной записи
                if(!record.value("done").toBool()){
                    addorder Dlg(this, cur);
                    Dlg.setModal(true);
                    Dlg.exec();
                } else{
                    msgBox.setText("Заказ выполнен!");
                    msgBox.setWindowTitle("Ошибка");
                    msgBox.exec();
                    record=mdl_ord->record(cur);
                    if(record.value("done").toBool()){
                        QSqlQuery query, query_update;
                        query.prepare("SELECT product_id, amount FROM consignment WHERE ord_num=:num");
                        query.bindValue(":num", record.value("order_num").toInt());
                        query.exec();
                        int new_count;
                        while(query.next()){
                            new_count =
                            query_update.prepare("UPDATE products SET amount = amount - :count WHERE prod_id =:id");
                            query_update.bindValue(":id", query.value(0).toInt());
                            query_update.bindValue(":count", query.value(1).toInt());
                            qDebug()<< query.value(0).toInt() << "  " <<query.value(1).toInt();
                            query_update.exec();
                        }
                        mdl_prod->submitAll();
                    }
                }
                break;
            }
            case 3:{
                cur = ui->tableView_client->currentIndex().row();
                addcCient Dlg(this, cur);
                Dlg.setModal(true);
                Dlg.exec();
                break;
            }
            case 4:{
                cur = ui->tableView_treaty->currentIndex().row();
                QSqlRecord record=mdl_treaty->record(cur);//Взятие из таблицы нужной записи
                if(record.value("sum").toInt() == record.value("paid").toInt()){
                    msgBox.setText("Договор выполнен!");
                    //msgBox.setText(record.value("sum").toString() + "-" + record.value("paid").toString());
                    msgBox.setWindowTitle("Ошибка");
                    msgBox.exec();
                } else{
                    addtreaty Dlg(this, cur);
                    Dlg.setModal(true);
                    Dlg.exec();
                    record=mdl_treaty->record(cur);
                    if(record.value("sum").toInt() == record.value("paid").toInt()){
                         QSqlQuery query, query_update;
                         query.prepare("SELECT product_id, amount FROM consignment WHERE treaty_num=:num");
                         query.bindValue(":num", record.value("num_treaty").toInt());
                         query.exec();
                         while(query.next()){
                             query_update.prepare("UPDATE products SET amount =:count WHERE prod_id =:id");
                             query_update.bindValue(":id", query.value(0).toInt());
                             query_update.bindValue(":count", query.value(1).toInt());
                             qDebug()<< query.value(0).toInt() << "  " <<query.value(1).toInt();
                             query_update.exec();
                         }
                         mdl_prod->submitAll();
                    }
                }
                break;
            }
            case 5:{
                cur = ui->tableView_comp->currentIndex().row();
                addComp Dlg(this, cur);
                Dlg.setModal(true);
                Dlg.exec();
                break;
            }
        }
    }
    else{ //добавление записи
        switch (table) {
            case 0://добавдление товара
            {
                addProd Dlg(this, -1);
                Dlg.setModal(true);
                if(Dlg.exec() == QDialog::Accepted)     //Если пользователь выбрал кнопку Ок
                {
                    addProd::New el = Dlg.add();   //Получение структуры со значениями полей записи
                    if(el.model!="")
                    {
                        mdl_prod->insertRows(mdl_prod->rowCount(),1);
                        mdl_prod->setData(mdl_prod->index(mdl_prod->rowCount()-1, 1), el.brend_id);
                        mdl_prod->setData(mdl_prod->index(mdl_prod->rowCount()-1, 2), el.model);
                        mdl_prod->setData(mdl_prod->index(mdl_prod->rowCount()-1, 3), el.V);
                        mdl_prod->setData(mdl_prod->index(mdl_prod->rowCount()-1, 4), el.fuel);
                        mdl_prod->setData(mdl_prod->index(mdl_prod->rowCount()-1, 5), el.transmis);
                        mdl_prod->setData(mdl_prod->index(mdl_prod->rowCount()-1, 6), el.power);
                        mdl_prod->setData(mdl_prod->index(mdl_prod->rowCount()-1, 7), el.year);
                        mdl_prod->setData(mdl_prod->index(mdl_prod->rowCount()-1, 8), el.unit);
                        mdl_prod->setData(mdl_prod->index(mdl_prod->rowCount()-1, 9), el.color_body);
                        mdl_prod->setData(mdl_prod->index(mdl_prod->rowCount()-1, 10), el.color_in);
                        mdl_prod->setData(mdl_prod->index(mdl_prod->rowCount()-1, 11), el.material);
                        mdl_prod->setData(mdl_prod->index(mdl_prod->rowCount()-1, 12), el.price);
                        mdl_prod->setData(mdl_prod->index(mdl_prod->rowCount()-1, 13), el.amount);
                        mdl_prod->setData(mdl_prod->index(mdl_prod->rowCount()-1, 14), el.type);
                        mdl_prod->submitAll();                       //Подтверждение добавления поля
                    }
                qDebug()<<mdl_prod->lastError().text();
                }
                break;
            }
            case 1://добавдление бренда
            {
                addBrend Dlg(this, -1);
                Dlg.setModal(true);
                if(Dlg.exec() == QDialog::Accepted)     //Если пользователь выбрал кнопку Ок
                {
                    addBrend::NewBrend el = Dlg.add();   //Получение структуры со значениями полей записи
                    if(el.SpName!="")
                    {
                        mdl_brend->insertRows(mdl_brend->rowCount(),1);
                        mdl_brend->setData(mdl_brend->index(mdl_brend->rowCount()-1, 1), el.SpName);
                        mdl_brend->submitAll();                       //Подтверждение добавления поля
                    }
                qDebug()<<mdl_brend->lastError().text();
                }
                break;
            }
            case 2://добавдление заказа
            {
                addorder Dlg(this, -1);
                Dlg.setModal(true);
                if(Dlg.exec() == QDialog::Accepted)     //Если пользователь выбрал кнопку Ок
                {
                    addorder::New el = Dlg.add();   //Получение структуры со значениями полей записи
                    mdl_ord->insertRows(mdl_ord->rowCount(),1);
                    mdl_ord->setData(mdl_ord->index(mdl_ord->rowCount()-1, 1), el.client);
                    mdl_ord->setData(mdl_ord->index(mdl_ord->rowCount()-1, 2), el.date);
                    mdl_ord->setData(mdl_ord->index(mdl_ord->rowCount()-1, 3), el.sum);
                    mdl_ord->setData(mdl_ord->index(mdl_ord->rowCount()-1, 4), el.done);
                    mdl_ord->submitAll();                       //Подтверждение добавления поля
                qDebug()<<mdl_ord->lastError().text();
                while(!el.prod_list->isEmpty() && !el.amouts->isEmpty()){
                    mdl_cons->insertRows(mdl_cons->rowCount(),1);
                    mdl_cons->setData(mdl_cons->index(mdl_cons->rowCount()-1, 3), mdl_ord->record(mdl_ord->rowCount()-1).value("order_num"));
                    mdl_cons->setData(mdl_cons->index(mdl_cons->rowCount()-1, 1), el.prod_list->last());
                    mdl_cons->setData(mdl_cons->index(mdl_cons->rowCount()-1, 2), el.amouts->last());
                    mdl_cons->submitAll();
                    el.prod_list->pop_back();
                    el.amouts->pop_back();
                }
                }
                break;
            }
            case 3://добавдление клиента
            {
                addcCient Dlg(this, -1);
                Dlg.setModal(true);
                if(Dlg.exec() == QDialog::Accepted)     //Если пользователь выбрал кнопку Ок
                {
                    addcCient::NewClient el = Dlg.addClient();   //Получение структуры со значениями полей записи
                    if(el.name!="" && el.surename!="" && el.phone!="")
                    {
                        mdl_client->insertRows(mdl_client->rowCount(),1);
                        mdl_client->setData(mdl_client->index(mdl_client->rowCount()-1, 1), el.name);  //Установка значений полей из структуры
                        mdl_client->setData(mdl_client->index(mdl_client->rowCount()-1, 2), el.surename);
                        mdl_client->setData(mdl_client->index(mdl_client->rowCount()-1, 3), el.phone);
                        mdl_client->setData(mdl_client->index(mdl_client->rowCount()-1, 4), el.mail);
                        mdl_client->setData(mdl_client->index(mdl_client->rowCount()-1, 5), el.psw);
                        mdl_client->submitAll();                       //Подтверждение добавления поля
                    }
                qDebug()<<mdl_client->lastError().text();
                }
                break;
            }
            case 4://добавдление договора и партии
            {
                addtreaty Dlg(this, -1);
                Dlg.setModal(true);
                if(Dlg.exec() == QDialog::Accepted)     //Если пользователь выбрал кнопку Ок
                {
                    addtreaty::New el = Dlg.add();   //Получение структуры со значениями полей записи

                    mdl_treaty->insertRows(mdl_treaty->rowCount(),1);
                    mdl_treaty->setData(mdl_treaty->index(mdl_treaty->rowCount()-1, 1), el.company);  //Установка значений полей из структуры
                    mdl_treaty->setData(mdl_treaty->index(mdl_treaty->rowCount()-1, 2), el.date);
                    mdl_treaty->setData(mdl_treaty->index(mdl_treaty->rowCount()-1, 3), el.date_comp);
                    mdl_treaty->setData(mdl_treaty->index(mdl_treaty->rowCount()-1, 4), el.sum);
                    mdl_treaty->setData(mdl_treaty->index(mdl_treaty->rowCount()-1, 5), el.paid);
                    mdl_treaty->submitAll();                       //Подтверждение добавления поля

                    qDebug()<<mdl_treaty->lastError().text();

                    while(!el.prod_list->isEmpty() && !el.amouts->isEmpty()){
                        mdl_cons->insertRows(mdl_cons->rowCount(),1);
                        mdl_cons->setData(mdl_cons->index(mdl_cons->rowCount()-1, 0), mdl_treaty->record(mdl_treaty->rowCount()-1).value("num_treaty"));
                        mdl_cons->setData(mdl_cons->index(mdl_cons->rowCount()-1, 1), el.prod_list->last());
                        mdl_cons->setData(mdl_cons->index(mdl_cons->rowCount()-1, 2), el.amouts->last());
                        mdl_cons->submitAll();
                        el.prod_list->pop_back();
                        el.amouts->pop_back();
                    }
                }
                break;
            }
            case 5://добавдление поставщика
            {
                addComp Dlg(this, -1);
                Dlg.setModal(true);
                if(Dlg.exec() == QDialog::Accepted)     //Если пользователь выбрал кнопку Ок
                {
                    addComp::New el = Dlg.add();   //Получение структуры со значениями полей записи
                    if(el.name!="" && el.address!="" && el.phone!="")
                    {
                        mdl_comp->insertRows(mdl_comp->rowCount(),1);
                        mdl_comp->setData(mdl_comp->index(mdl_comp->rowCount()-1, 1), el.name);  //Установка значений полей из структуры
                        mdl_comp->setData(mdl_comp->index(mdl_comp->rowCount()-1, 2), el.address);
                        mdl_comp->setData(mdl_comp->index(mdl_comp->rowCount()-1, 3), el.phone);
                        mdl_comp->setData(mdl_comp->index(mdl_comp->rowCount()-1, 4), el.type);
                        mdl_comp->submitAll();                       //Подтверждение добавления поля
                    }
                qDebug()<<mdl_comp->lastError().text();
                }
                break;
            }
        }
    }
    DisEnBtn();
}

//---------------------------преобразование заказа и договора в пдф----------------------
void MainWindow::on_pdfBtn_clicked()
{
    QSqlQuery query, query_2, query_3;
    QTextDocument doc;  //Формируемый документ
    QTextCursor cur(&doc);  //Указатель на текущее место в документе
    QSqlRecord record;
    QPrinter printer(QPrinter::HighResolution);  //Создание принтера
    QProcess proc;                              //процесс для открытия файла
    QTextTableFormat tableFormat;   //Настройки форматирования таблицы
    QBrush  borderBrush(Qt::SolidPattern);  //Кисть для рисования границ таблицы
    int num;

    //Задание формата отображения таблицы
    tableFormat.setHeaderRowCount(1);
    tableFormat.setBorderBrush(borderBrush);
    tableFormat.setCellPadding(0);
    tableFormat.setCellSpacing(0);
    tableFormat.setBorderCollapse(false);
    tableFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Solid);
    tableFormat.setWidth(QTextLength(QTextLength::PercentageLength,100));
    printer.setOutputFormat(QPrinter::PdfFormat);   //Формат документа

    switch (ui->tabWidget->currentIndex()) {
        case 2:{
            num = ui->tableView_ord->currentIndex().row();
            record=mdl_ord->record(num);//Взятие из таблицы нужной записи
            if(record.value("done").toBool()){
                printer.setOutputFileName("Чек"+record.value("order_num").toString() + ".pdf");      //Имя документа pdf

                //запрашиваем данные о клиенте
                query.prepare("SELECT * FROM clients WHERE surname=:id");
                query.bindValue(":id",record.value("surname").toString());
                if (!query.exec())  {                            //Выполнение запроса, в случае ошибки выдать предупреждение
                   qDebug()<<"Ошибка поиска клиента"<<query.lastError();
                }
                query.next();

                //Теперь, перемещая курсор по файлу начинается его заполнение данными
                cur.insertText("Чек №"+record.value("order_num").toString()+'\n');   //Добавление обычного текста
                cur.insertText("Покупатель: "+query.value(1).toString()+" "+query.value(2).toString()+'\n');

                //запрос партии
                query.prepare("SELECT * FROM consignment WHERE ord_num=:id");
                query.bindValue(":id",record.value("order_num"));
                if (!query.exec())  {                            //Выполнение запроса, в случае ошибки выдать предупреждение
                   qDebug()  <<  "Unable to select!!!";           //Так как в реальной ситуации запрос сработает всегда, вывод только в qDebug
                }
                //Добавление таблицы
                cur.insertTable(query.size()+1,mdl_prod->columnCount(),tableFormat); //Задаётся число строк, столбцов и формат
                //Формирование шапки таблицы
                cur.insertText("id");
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText("Производитель");
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText("Модель");
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText("Тип");
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText("Объем двигателя");
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText("Топливо");
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText("Коробка передач");
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText("Мощность");
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText("Год производста");
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText("Привод");
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText("Цвет кузова");
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText("Цвет салона");
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText("Материал салона");
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText("Цена");
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText("Количество");
                //запрос и запись данных о товаре
                while(query.next()){
                    query_2.prepare("SELECT * FROM products WHERE prod_id=:id");
                    query_2.bindValue(":id",query.value(1));
                    if (!query_2.exec())  {                            //Выполнение запроса, в случае ошибки выдать предупреждение
                       qDebug()  <<  "Unable to select!!!";           //Так как в реальной ситуации запрос сработает всегда, вывод только в qDebug
                    }
                    query_2.next();
                    query_3.prepare("SELECT brend_name FROM brends WHERE brend_id=:id");//Запрос на получение связанных данных
                    query_3.bindValue(":id",query_2.value(1).toInt());
                    if (!query_3.exec())  {                            //Выполнение запроса, в случае ошибки выдать предупреждение
                       qDebug()  <<  "Unable to select!!";           //Так как в реальной ситуации запрос сработает всегда, вывод только в qDebug
                    }
                    query_3.next();
                    //С текстом и числами всё просто - перевод в строки и запись в ячейку
                    cur.movePosition(QTextCursor::NextCell);
                    cur.insertText(query_2.value(0).toString());
                    cur.movePosition(QTextCursor::NextCell);
                    cur.insertText(query_3.value(0).toString());
                    cur.movePosition(QTextCursor::NextCell);
                    cur.insertText(query_2.value(2).toString());
                    cur.movePosition(QTextCursor::NextCell);
                    cur.insertText(query_2.value(14).toString());
                    cur.movePosition(QTextCursor::NextCell);
                    cur.insertText(query_2.value(3).toString());
                    cur.movePosition(QTextCursor::NextCell);
                    cur.insertText(query_2.value(4).toString());
                    cur.movePosition(QTextCursor::NextCell);
                    cur.insertText(query_2.value(5).toString());
                    cur.movePosition(QTextCursor::NextCell);
                    cur.insertText(query_2.value(6).toString());
                    cur.movePosition(QTextCursor::NextCell);
                    cur.insertText(query_2.value(7).toString());
                    cur.movePosition(QTextCursor::NextCell);
                    cur.insertText(query_2.value(8).toString());
                    cur.movePosition(QTextCursor::NextCell);
                    cur.insertText(query_2.value(9).toString());
                    cur.movePosition(QTextCursor::NextCell);
                    cur.insertText(query_2.value(10).toString());
                    cur.movePosition(QTextCursor::NextCell);
                    cur.insertText(query_2.value(11).toString());
                    cur.movePosition(QTextCursor::NextCell);
                    cur.insertText(query_2.value(12).toString());
                    cur.movePosition(QTextCursor::NextCell);
                    cur.insertText(query_2.value(13).toString());
                }
                cur.movePosition(QTextCursor::End);

                cur.insertText("Контакнтый телефон: "+query.value(3).toString()+'\n');
                cur.insertText("Контакнтая почта: "+query.value(4).toString()+'\n');
                cur.insertText("Сумма: "+record.value("sum").toString()+" рублей"+'\n');
                cur.insertText("Дата: "+record.value("date").toString()+'\n');
                cur.insertText("Подпись кассира                                   _______________________ ");

                doc.print(&printer);    //Печать документа на выбранном принтере
                proc.startDetached("explorer.exe",{"Чек"+record.value("order_num").toString() + ".pdf"});
            }
            else{
                QMessageBox msgBox;
                msgBox.setText("Заказ не выполнен!");
                msgBox.setWindowTitle("Ошибка");
                msgBox.exec();
            }
            break;
        }
        case 4:{
            num = ui->tableView_treaty->currentIndex().row();
            record=mdl_treaty->record(num);//Взятие из таблицы нужной записи
            printer.setOutputFileName("Договор"+record.value("num_treaty").toString() + ".pdf");      //Имя документа pdf

            //запрашиваем данные о поставщике
            query.prepare("SELECT * FROM companys WHERE name=:comp");
            query.bindValue(":comp",record.value("name"));
            if (!query.exec())  {                            //Выполнение запроса, в случае ошибки выдать предупреждение
               qDebug()  <<  "Unable to select!!!";           //Так как в реальной ситуации запрос сработает всегда, вывод только в qDebug
            }
            query.next();

            //Теперь, перемещая курсор по файлу начинается его заполнение данными
            cur.insertText("Договор №"+record.value("num_treaty").toString()+'\n');   //Добавление обычного текста
            cur.insertText("Поставщик: "+query.value(1).toString()+", "+query.value(2).toString()+", "+query.value(3).toString()+'\n'+'\n'+'\n');

            cur.insertText("Компания "+query.value(1).toString()+" обязуется поставить товары, приведенные в таблице 1 в срок до "
                            +record.value("date_comp").toString()+". Автосалон обязается выплатить указанную ниже сумму в срок до "+record.value("date_comp").toString()+'\n'+'\n');

            //Теперь, перемещая курсор по файлу начинается его заполнение данными
            cur.insertText("Таблица 1 - список поставляемых товаров:");   //Добавление обычного текста
            //запрос партии
            query.prepare("SELECT * FROM consignment WHERE treaty_num=:id");
            query.bindValue(":id",record.value("num_treaty"));
            if (!query.exec())  {                            //Выполнение запроса, в случае ошибки выдать предупреждение
               qDebug()  <<  "Unable to select!!!";           //Так как в реальной ситуации запрос сработает всегда, вывод только в qDebug
            }
            //Добавление таблицы
            cur.insertTable(query.size()+1,mdl_prod->columnCount(),tableFormat); //Задаётся число строк, столбцов и формат
            //Формирование шапки таблицы
            cur.insertText("Код товара");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Производитель");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Модель");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Тип");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Объем двигателя");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Топливо");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Коробка передач");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Мощность");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Год производста");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Привод");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Цвет кузова");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Цвет салона");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Материал салона");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Цена");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Количество");
            //запрос и запись данных о товаре
            while(query.next()){
                query_2.prepare("SELECT * FROM products WHERE prod_id=:id");
                query_2.bindValue(":id",query.value(1));
                if (!query_2.exec())  {                            //Выполнение запроса, в случае ошибки выдать предупреждение
                   qDebug()  <<  "Unable to select!!!";           //Так как в реальной ситуации запрос сработает всегда, вывод только в qDebug
                }
                query_2.next();
                query_3.prepare("SELECT brend_name FROM brends WHERE brend_id=:id");//Запрос на получение связанных данных
                query_3.bindValue(":id",query_2.value(1).toInt());
                if (!query_3.exec())  {                            //Выполнение запроса, в случае ошибки выдать предупреждение
                   qDebug()  <<  "Unable to select!!";           //Так как в реальной ситуации запрос сработает всегда, вывод только в qDebug
                }
                query_3.next();
                //С текстом и числами всё просто - перевод в строки и запись в ячейку
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText(query_2.value(0).toString());
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText(query_3.value(0).toString());
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText(query_2.value(2).toString());
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText(query_2.value(14).toString());
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText(query_2.value(3).toString());
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText(query_2.value(4).toString());
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText(query_2.value(5).toString());
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText(query_2.value(6).toString());
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText(query_2.value(7).toString());
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText(query_2.value(8).toString());
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText(query_2.value(9).toString());
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText(query_2.value(10).toString());
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText(query_2.value(11).toString());
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText(query_2.value(12).toString());
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText(query_2.value(13).toString());
            }
            cur.movePosition(QTextCursor::End);
            cur.insertText("Сумма: "+record.value("sum").toString()+'\n');
            cur.insertText("Дата оформления: "+record.value("date").toString()+'\n');
            cur.insertText("Подпись поставщика:        ______\n");
            cur.insertText("Подпись получателя:        ______\n");

            doc.print(&printer);    //Печать документа на выбранном принтере
            proc.startDetached("explorer.exe",{"Договор"+record.value("num_treaty").toString() + ".pdf"});
        break;
        }

    }
}

void MainWindow::on_tableView_brend_clicked(const QModelIndex &index)
{
    ui->changeButton->setEnabled(true);
    ui->delButton->setEnabled(true);
    if(ui->tabWidget->currentIndex() == 2 || ui->tabWidget->currentIndex() == 4)
        ui->pdfBtn->setEnabled(true);
}

void MainWindow::DisEnBtn(){
    ui->changeButton->setEnabled(false);
    ui->delButton->setEnabled(false);
    ui->pdfBtn->setEnabled(false);
}

QSqlTableModel* MainWindow::getModel(int num){
    switch (num) {
        case 1: return mdl_brend; break;
        case 3: return mdl_client; break;
        case 5: return mdl_comp; break;
    }
}

QSqlRelationalTableModel* MainWindow::getRelModel(int num){
    switch (num) {
        case 0: return mdl_prod;
        case 2: return mdl_ord;
        case 4: return mdl_treaty;
        case 6: return mdl_cons;
    }
}

//сохранение таблицы в pdf
void MainWindow::safe_table_in_pdf(){
    QTextDocument doc;  //Формируемый документ
    QTextCursor cur(&doc);  //Указатель на текущее место в документе
    QSqlRecord record;
    QPrinter printer(QPrinter::HighResolution);  //Создание принтера
    QProcess proc;                              //процесс для открытия файла
    QTextTableFormat tableFormat;   //Настройки форматирования таблицы

    QBrush  borderBrush(Qt::SolidPattern);  //Кисть для рисования границ таблицы

    //Задание формата отображения таблицы
    tableFormat.setHeaderRowCount(1);
    tableFormat.setBorderBrush(borderBrush);
    tableFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Ridge);
    tableFormat.setWidth(QTextLength(QTextLength::PercentageLength,100));

    switch (ui->tabWidget->currentIndex()) {
        case 0://товары
        {
            printer.setOutputFileName("Таблица товаров.pdf");      //Имя документа pdf
            //Теперь, перемещая курсор по файлу начинается его заполнение данными
            cur.insertText("Список товаров");   //Добавление обычного текста
            //Добавление таблицы
            cur.insertTable(mdl_prod->rowCount()+1,mdl_prod->columnCount()-1,tableFormat); //Задаётся число строк, столбцов и формат
            //Формирование шапки таблицы
            //cur.insertText("id");
           // cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Тип");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Производитель");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Модель");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Объем двигателя");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Топливо");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Коробка передач");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Мощность");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Год производста");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Привод");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Цвет кузова");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Цвет салона");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Материал салона");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Цена");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Количество");
            //Добавление данных в таблицу
            for(int i=0;i<mdl_prod->rowCount();i++)
            {
               record=mdl_prod->record(i);//Взятие из таблицы нужной записи
               //С текстом и числами всё просто - перевод в строки и запись в ячейку
               //cur.movePosition(QTextCursor::NextCell);
               //cur.insertText(record.value("prod_id").toString());
               cur.movePosition(QTextCursor::NextCell);
               cur.insertText(record.value("type").toString());
               cur.movePosition(QTextCursor::NextCell);
               cur.insertText(record.value("brend_name").toString());
               cur.movePosition(QTextCursor::NextCell);
               cur.insertText(record.value("model").toString());
               cur.movePosition(QTextCursor::NextCell);
               cur.insertText(record.value("V").toString());
               cur.movePosition(QTextCursor::NextCell);
               cur.insertText(record.value("fuel").toString());
               cur.movePosition(QTextCursor::NextCell);
               cur.insertText(record.value("transmis").toString());
               cur.movePosition(QTextCursor::NextCell);
               cur.insertText(record.value("power").toString());
               cur.movePosition(QTextCursor::NextCell);
               cur.insertText(record.value("year").toString());
               cur.movePosition(QTextCursor::NextCell);
               cur.insertText(record.value("unit").toString());
               cur.movePosition(QTextCursor::NextCell);
               cur.insertText(record.value("color_body").toString());
               cur.movePosition(QTextCursor::NextCell);
               cur.insertText(record.value("color_in").toString());
               cur.movePosition(QTextCursor::NextCell);
               cur.insertText(record.value("material").toString());
               cur.movePosition(QTextCursor::NextCell);
               cur.insertText(record.value("price").toString());
               cur.movePosition(QTextCursor::NextCell);
               cur.insertText(record.value("amount").toString());
            }
            break;
        }
        case 1://бренды
        {
            printer.setOutputFileName("Таблица брендов.pdf");      //Имя документа pdf
            //Теперь, перемещая курсор по файлу начинается его заполнение данными
            cur.insertText("Список брендов");   //Добавление обычного текста
            //Добавление таблицы
            cur.insertTable(mdl_brend->rowCount()+1,mdl_brend->columnCount(),tableFormat); //Задаётся число строк, столбцов и формат
            //Формирование шапки таблицы
            cur.insertText("Номер бренда");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Название");
            //Добавление данных в таблицу
            for(int i=0;i<mdl_brend->rowCount();i++)
            {
               record=mdl_brend->record(i);//Взятие из таблицы нужной записи
               //С текстом и числами всё просто - перевод в строки и запись в ячейку
               cur.movePosition(QTextCursor::NextCell);
               cur.insertText(record.value("brend_id").toString());
               cur.movePosition(QTextCursor::NextCell);
               cur.insertText(record.value("brend_name").toString());
               qDebug()<<record.value("brend_id").toString()<<" "<<record.value("brend_name").toString();
            }
            break;
        }
        case 2://продажи
        {
            printer.setOutputFileName("Таблица продаж.pdf");      //Имя документа pdf
            //Теперь, перемещая курсор по файлу начинается его заполнение данными
            cur.insertText("Список продаж");   //Добавление обычного текста
            //Добавление таблицы
            cur.insertTable(mdl_ord->rowCount()+1,mdl_ord->columnCount(),tableFormat); //Задаётся число строк, столбцов и формат
            //Формирование шапки таблицы
            cur.insertText("Номер продажи");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Клиент");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Дата");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Сумма");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Выполнен");
            //Добавление данных в таблицу
            for(int i=0;i<mdl_ord->rowCount();i++)
            {
               record=mdl_ord->record(i);//Взятие из таблицы нужной записи
               cur.movePosition(QTextCursor::NextCell);
               cur.insertText(record.value("order_num").toString());
               cur.movePosition(QTextCursor::NextCell);
               cur.insertText(record.value("surname").toString());
               cur.movePosition(QTextCursor::NextCell);
               cur.insertText(record.value("date").toString());
               cur.movePosition(QTextCursor::NextCell);
               cur.insertText(record.value("sum").toString());
               cur.movePosition(QTextCursor::NextCell);
               if(record.value("done").toBool())
                    cur.insertText("Да");
               else cur.insertText("Нет");
            }
            break;
        }
        case 3://клиенты
        {
            printer.setOutputFileName("Таблица клиентов.pdf");      //Имя документа pdf
            //Теперь, перемещая курсор по файлу начинается его заполнение данными
            cur.insertText("Список клиентов");   //Добавление обычного текста
            //Добавление таблицы
            cur.insertTable(mdl_client->rowCount()+1,mdl_client->columnCount()-2,tableFormat); //Задаётся число строк, столбцов и формат
            //Формирование шапки таблицы
            cur.insertText("Имя");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Фамилия");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Телефон");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Почта");
            //Добавление данных в таблицу
            for(int i=0;i<mdl_client->rowCount();i++)
            {
               record=mdl_client->record(i);//Взятие из таблицы нужной записи
               //С текстом и числами всё просто - перевод в строки и запись в ячейку
               cur.movePosition(QTextCursor::NextCell);
               cur.insertText(record.value("name").toString());
               cur.movePosition(QTextCursor::NextCell);
               cur.insertText(record.value("surname").toString());
               cur.movePosition(QTextCursor::NextCell);
               cur.insertText(record.value("phone").toString());
               cur.movePosition(QTextCursor::NextCell);
               cur.insertText(record.value("email").toString());
            }
            break;
        }
        case 4://поставки
        {
            printer.setOutputFileName("Таблица поставок.pdf");      //Имя документа pdf
            //Теперь, перемещая курсор по файлу начинается его заполнение данными
            cur.insertText("Список поставок");   //Добавление обычного текста
            //Добавление таблицы
            cur.insertTable(mdl_treaty->rowCount()+1,mdl_treaty->columnCount(),tableFormat); //Задаётся число строк, столбцов и формат
            //Формирование шапки таблицы
            cur.insertText("Номер договора");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Наименование");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Дата заключения");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Дата выполнения");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Сумма");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Выплаченная сумма");
            //Добавление данных в таблицу
            for(int i=0;i<mdl_treaty->rowCount();i++)
            {
               record=mdl_treaty->record(i);//Взятие из таблицы нужной записи
               //С текстом и числами всё просто - перевод в строки и запись в ячейку
               cur.movePosition(QTextCursor::NextCell);
               cur.insertText(record.value("num_treaty").toString());
               cur.movePosition(QTextCursor::NextCell);
               cur.insertText(record.value("name").toString());
               cur.movePosition(QTextCursor::NextCell);
               cur.insertText(record.value("date").toString());
               cur.movePosition(QTextCursor::NextCell);
               cur.insertText(record.value("date_comp").toString());
               cur.movePosition(QTextCursor::NextCell);
               cur.insertText(record.value("sum").toString());
               cur.movePosition(QTextCursor::NextCell);
               cur.insertText(record.value("paid").toString());
            }
            break;
        }
        case 5://поставщики
        {
            printer.setOutputFileName("Таблица поставщиков.pdf");      //Имя документа pdf
            //Теперь, перемещая курсор по файлу начинается его заполнение данными
            cur.insertText("Список поставщиков");   //Добавление обычного текста
            //Добавление таблицы
            cur.insertTable(mdl_comp->rowCount()+1,mdl_comp->columnCount(),tableFormat); //Задаётся число строк, столбцов и формат
            //Формирование шапки таблицы
            cur.insertText("Номер поставщика");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Название ");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Адресс");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Телефон");
            //Добавление данных в таблицу
            for(int i=0;i<mdl_comp->rowCount();i++)
            {
               record=mdl_comp->record(i);//Взятие из таблицы нужной записи
               //С текстом и числами всё просто - перевод в строки и запись в ячейку
               cur.movePosition(QTextCursor::NextCell);
               cur.insertText(record.value("company_id").toString());
               cur.movePosition(QTextCursor::NextCell);
               cur.insertText(record.value("name").toString());
               cur.movePosition(QTextCursor::NextCell);
               cur.insertText(record.value("address").toString());
               cur.movePosition(QTextCursor::NextCell);
               cur.insertText(record.value("phone").toString());
            }
            break;
        }
    }
    printer.setOutputFormat(QPrinter::PdfFormat);   //Формат документа
    doc.print(&printer);    //Печать документа на выбранном принтере
    switch (ui->tabWidget->currentIndex()){
        case 0: proc.startDetached("explorer.exe",{"Таблица товаров.pdf"}); break;
        case 1: proc.startDetached("explorer.exe",{"Таблица производителей.pdf"}); break;
        case 2: proc.startDetached("explorer.exe",{"Таблица продаж.pdf"}); break;
        case 3: proc.startDetached("explorer.exe",{"Таблица клиентов.pdf"}); break;
        case 4: proc.startDetached("explorer.exe",{"Таблица поставок.pdf"}); break;
        case 5: proc.startDetached("explorer.exe",{"Таблица поставщиков.pdf"}); break;
    }
}

//+++количество продаваемого товара
void MainWindow::request(){
    selectProd Dlg(this, 0);
    Dlg.setModal(true);
    Dlg.exec();
}

//+++товар на складе
void MainWindow::stok(){
    QTextDocument doc;  //Формируемый документ
    QTextCursor cur(&doc);  //Указатель на текущее место в документе
    QSqlRecord record;
    QSqlQuery query;
    QPrinter printer(QPrinter::HighResolution);  //Создание принтера
    QProcess proc;                              //процесс для открытия файла
    QTextTableFormat tableFormat;   //Настройки форматирования таблицы
    int sum=0;

    QBrush  borderBrush(Qt::SolidPattern);  //Кисть для рисования границ таблицы

    //Задание формата отображения таблицы
    tableFormat.setHeaderRowCount(1);
    tableFormat.setBorderBrush(borderBrush);
    tableFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Ridge);
    tableFormat.setWidth(QTextLength(QTextLength::PercentageLength,100));

    //запрашиваем товары, где кол-во больше 0
    query.prepare("SELECT * FROM products WHERE amount>0");
    if (!query.exec())  {                            //Выполнение запроса, в случае ошибки выдать предупреждение
       qDebug()<<"Ошибка"<<query.lastError();
    }

    printer.setOutputFileName("Товар на складе.pdf");      //Имя документа pdf
    //Теперь, перемещая курсор по файлу начинается его заполнение данными
    cur.insertText("Список товаров на складе");   //Добавление обычного текста
    //Добавление таблицы
    cur.insertTable(query.size()+1,mdl_prod->columnCount(),tableFormat); //Задаётся число строк, столбцов и формат
    //Формирование шапки таблицы
    cur.insertText("Код товара");
    cur.movePosition(QTextCursor::NextCell);
    cur.insertText("Производитель");
    cur.movePosition(QTextCursor::NextCell);
    cur.insertText("Модель");
    cur.movePosition(QTextCursor::NextCell);
    cur.insertText("Тип");
    cur.movePosition(QTextCursor::NextCell);
    cur.insertText("Объем двигателя");
    cur.movePosition(QTextCursor::NextCell);
    cur.insertText("Топливо");
    cur.movePosition(QTextCursor::NextCell);
    cur.insertText("Коробка передач");
    cur.movePosition(QTextCursor::NextCell);
    cur.insertText("Мощность");
    cur.movePosition(QTextCursor::NextCell);
    cur.insertText("Год производста");
    cur.movePosition(QTextCursor::NextCell);
    cur.insertText("Привод");
    cur.movePosition(QTextCursor::NextCell);
    cur.insertText("Цвет кузова");
    cur.movePosition(QTextCursor::NextCell);
    cur.insertText("Цвет салона");
    cur.movePosition(QTextCursor::NextCell);
    cur.insertText("Материал салона");
    cur.movePosition(QTextCursor::NextCell);
    cur.insertText("Цена");
    cur.movePosition(QTextCursor::NextCell);
    cur.insertText("Количество");
    //Добавление данных в таблицу
    for(int i=0;i<mdl_prod->rowCount();i++)
    {
       record=mdl_prod->record(i);//Взятие из таблицы нужной записи
       if(record.value("amount").toInt() > 0){
           cur.movePosition(QTextCursor::NextCell);
           cur.insertText(record.value("prod_id").toString());
           cur.movePosition(QTextCursor::NextCell);
           cur.insertText(record.value("brend_name").toString());
           cur.movePosition(QTextCursor::NextCell);
           cur.insertText(record.value("model").toString());
           cur.movePosition(QTextCursor::NextCell);
           cur.insertText(record.value("type").toString());
           cur.movePosition(QTextCursor::NextCell);
           cur.insertText(record.value("V").toString());
           cur.movePosition(QTextCursor::NextCell);
           cur.insertText(record.value("fuel").toString());
           cur.movePosition(QTextCursor::NextCell);
           cur.insertText(record.value("transmis").toString());
           cur.movePosition(QTextCursor::NextCell);
           cur.insertText(record.value("power").toString());
           cur.movePosition(QTextCursor::NextCell);
           cur.insertText(record.value("year").toString());
           cur.movePosition(QTextCursor::NextCell);
           cur.insertText(record.value("unit").toString());
           cur.movePosition(QTextCursor::NextCell);
           cur.insertText(record.value("color_body").toString());
           cur.movePosition(QTextCursor::NextCell);
           cur.insertText(record.value("color_in").toString());
           cur.movePosition(QTextCursor::NextCell);
           cur.insertText(record.value("material").toString());
           cur.movePosition(QTextCursor::NextCell);
           cur.insertText(record.value("price").toString());
           cur.movePosition(QTextCursor::NextCell);
           cur.insertText(record.value("amount").toString());

           sum += record.value("price").toInt();
       }
    }
    cur.movePosition(QTextCursor::End);

    cur.insertText("Общая стоимость товара: "+QString::number(sum)+'\n');
    printer.setOutputFormat(QPrinter::PdfFormat);   //Формат документа
    doc.print(&printer);
    proc.startDetached("explorer.exe",{"Товар на складе.pdf"});
}

//договора на товар
void MainWindow::supplier_by_brend(){
    selectProd Dlg(this, 2);
    Dlg.setModal(true);
    Dlg.exec();
}


//поставщики товара по типу товара
void MainWindow::treatys_on_prod(){
    selectProd Dlg(this, 1);
    Dlg.setModal(true);
    Dlg.exec();
}

//+++продажи за период
void MainWindow::solds_in_range(){
    int sum=0;
    QMessageBox msgBox;
    QSqlQuery query, query_2, query_3;
    inputDate Dlg(this);
    QTextTableFormat tableFormat;   //Настройки форматирования таблицы
    QBrush  borderBrush(Qt::SolidPattern);  //Кисть для рисования границ таблицы
    QTextDocument doc;  //Формируемый документ
    QTextCursor cur(&doc);  //Указатель на текущее место в документе
    QProcess proc;
    //Задание формата отображения таблицы
    tableFormat.setHeaderRowCount(1);
    tableFormat.setBorderBrush(borderBrush);
    tableFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Ridge);
    tableFormat.setWidth(QTextLength(QTextLength::PercentageLength,100));
    QPrinter printer(QPrinter::HighResolution);  //Создание принтера
    printer.setOutputFormat(QPrinter::PdfFormat);   //Формат документа

    Dlg.setModal(true);
    if(Dlg.exec() == QDialog::Accepted)     //Если пользователь выбрал кнопку Ок
    {
        inputDate::date_gap el = Dlg.input();   //Получение структуры со значениями полей записи
        while(el.start > el.fine){
            msgBox.setWindowTitle("Ошибка");
            msgBox.setText("Дата 'от' должна быть меньше или равна дате 'до'!");
            msgBox.exec();
            Dlg.exec();
            el = Dlg.input();
        }
        query.prepare("SELECT * FROM orders WHERE date>=:start AND date<=:fine");
        query.bindValue(":start",el.start);
        query.bindValue(":fine",el.fine);
        if (!query.exec())  {                            //Выполнение запроса, в случае ошибки выдать предупреждение
           qDebug()  <<  "Unable to select!!11";           //Так как в реальной ситуации запрос сработает всегда, вывод только в qDebug
        }
        if(query.size()==0){
            msgBox.setWindowTitle("Ошибка");
            msgBox.setText("Нет продаж за указанный период!");
            msgBox.exec();
        } else{
            printer.setOutputFileName("Продажи с "+el.start.toString()+" по "+el.fine.toString()+ ".pdf");
            cur.insertText("Продажи с"+el.start.toString()+" по "+el.fine.toString()+'\n');
            cur.insertTable(query.size()+1,6,tableFormat); //Задаётся число строк, столбцов и формат
            //Формирование шапки таблицы
            cur.insertText("Номер заказа");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Покупатель");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Дата");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Сумма");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Номер телефона");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Почта");
            while(query.next()){
                //заполняем таблицу
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText(query.value(0).toString());
                cur.movePosition(QTextCursor::NextCell);
                //запрашиваем данные о покупателе
                query_2.prepare("SELECT * FROM clients WHERE client_id=:id");
                query_2.bindValue(":id",query.value(1).toInt());
                qDebug()<<"Сука"<<query.value(1).toInt();
                query_2.exec();
                query_2.next();

                cur.insertText(query_2.value(1).toString()+query_2.value(2).toString());
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText(query.value(2).toString());
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText(query.value(3).toString());
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText(query_2.value(3).toString());
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText(query_2.value(4).toString());
                sum += query.value(3).toInt();
            }
            cur.movePosition(QTextCursor::End);
            cur.insertText("Общаяя сумма продаж: "+QString::number(sum));
            doc.print(&printer);    //Печать документа на выбранном принтере
            proc.startDetached("explorer.exe",{"Продажи с "+el.start.toString()+" по "+el.fine.toString()+ ".pdf"});
        }
    }
}

//+++договоры за период
void MainWindow::supplys_in_range(){
    int sum=0, paid=0;
    QMessageBox msgBox;
    QSqlQuery query, query_2, query_3;
    inputDate Dlg(this);
    QTextTableFormat tableFormat;   //Настройки форматирования таблицы
    QBrush  borderBrush(Qt::SolidPattern);  //Кисть для рисования границ таблицы
    QTextDocument doc;  //Формируемый документ
    QTextCursor cur(&doc);  //Указатель на текущее место в документе
    QProcess proc;
    //Задание формата отображения таблицы
    tableFormat.setHeaderRowCount(1);
    tableFormat.setBorderBrush(borderBrush);
    tableFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Ridge);
    tableFormat.setWidth(QTextLength(QTextLength::PercentageLength,100));
    QPrinter printer(QPrinter::HighResolution);  //Создание принтера
    printer.setOutputFormat(QPrinter::PdfFormat);   //Формат документа

    Dlg.setModal(true);
    if(Dlg.exec() == QDialog::Accepted)     //Если пользователь выбрал кнопку Ок
    {
        inputDate::date_gap el = Dlg.input();   //Получение структуры со значениями полей записи
        while(el.start > el.fine){
            msgBox.setWindowTitle("Ошибка");
            msgBox.setText("Дата 'от' должна быть меньше или равна дате 'до'!");
            msgBox.exec();
            Dlg.exec();
            el = Dlg.input();
        }
        query.prepare("SELECT * FROM treatys WHERE date>=:start AND date<=:fine");
        query.bindValue(":start",el.start);
        query.bindValue(":fine",el.fine);
        if (!query.exec())  {                            //Выполнение запроса, в случае ошибки выдать предупреждение
           qDebug()  <<  "Unable to select!!11";           //Так как в реальной ситуации запрос сработает всегда, вывод только в qDebug
        }
        if(query.size()==0){
            msgBox.setWindowTitle("Ошибка");
            msgBox.setText("Нет договоров за указанный период!");
            msgBox.exec();
        } else{
            printer.setOutputFileName("Договоры с "+el.start.toString()+" по "+el.fine.toString()+ ".pdf");
            cur.insertText("Договоры с"+el.start.toString()+" по "+el.fine.toString()+'\n');
            cur.insertTable(query.size()+1,8,tableFormat); //Задаётся число строк, столбцов и формат
            //Формирование шапки таблицы
            cur.insertText("Номер договора");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Компания");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Адресс");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Телефон");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Дата заключения");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Предполагаемая дата завершения");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Сумма");
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText("Выплачено");
            while(query.next()){
                //запрашиваем данные о компании
                query_2.prepare("SELECT * FROM companys WHERE company_id=:id");
                query_2.bindValue(":id",query.value(1));
                query_2.exec();
                query_2.next();
                sum += query.value(4).toInt();
                paid += query.value(5).toInt();
                //заполняем таблицу
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText(query.value(0).toString());
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText(query_2.value(1).toString());
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText(query_2.value(2).toString());
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText(query_2.value(3).toString());
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText(query.value(2).toString());
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText(query.value(3).toString());
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText(query.value(4).toString());
                cur.movePosition(QTextCursor::NextCell);
                cur.insertText(query.value(5).toString());
            }
            cur.movePosition(QTextCursor::End);
            cur.insertText("Общаяя сумма договоров: "+QString::number(sum) + '\n');
            cur.insertText("Общаяя выплаченная сумма: "+QString::number(paid));
            doc.print(&printer);    //Печать документа на выбранном принтере
            proc.startDetached("explorer.exe",{"Договоры с "+el.start.toString()+" по "+el.fine.toString()+ ".pdf"});
        }
    }
}

//+++неоплаченные договоры
void MainWindow::payments(){
    int sum=0, paid=0;
    QMessageBox msgBox;
    QSqlQuery query, query_2, query_3;
    QTextTableFormat tableFormat;   //Настройки форматирования таблицы
    QBrush  borderBrush(Qt::SolidPattern);  //Кисть для рисования границ таблицы
    QTextDocument doc;  //Формируемый документ
    QTextCursor cur(&doc);  //Указатель на текущее место в документе
    QProcess proc;
    //Задание формата отображения таблицы
    tableFormat.setHeaderRowCount(1);
    tableFormat.setBorderBrush(borderBrush);
    tableFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Ridge);
    tableFormat.setWidth(QTextLength(QTextLength::PercentageLength,100));
    QPrinter printer(QPrinter::HighResolution);  //Создание принтера
    printer.setOutputFormat(QPrinter::PdfFormat);   //Формат документа

    query.prepare("SELECT * FROM treatys WHERE sum>paid");
    if (!query.exec())  {                            //Выполнение запроса, в случае ошибки выдать предупреждение
       qDebug()  <<  "Unable to select!!11";           //Так как в реальной ситуации запрос сработает всегда, вывод только в qDebug
    }
    if(query.size()==0){
        msgBox.setWindowTitle("Ошибка");
        msgBox.setText("Нет не оплаченных договоров!");
        msgBox.exec();
    } else{
        printer.setOutputFileName("Не оплаченные договоры.pdf");
        cur.insertText("Не оплаченные договоры");
        cur.movePosition(QTextCursor::End);
        cur.insertTable(query.size()+1,8,tableFormat); //Задаётся число строк, столбцов и формат
        //Формирование шапки таблицы
        cur.insertText("Номер договора");
        cur.movePosition(QTextCursor::NextCell);
        cur.insertText("Компания");
        cur.movePosition(QTextCursor::NextCell);
        cur.insertText("Адресс");
        cur.movePosition(QTextCursor::NextCell);
        cur.insertText("Телефон");
        cur.movePosition(QTextCursor::NextCell);
        cur.insertText("Дата заключения");
        cur.movePosition(QTextCursor::NextCell);
        cur.insertText("Предполагаемая дата завершения");
        cur.movePosition(QTextCursor::NextCell);
        cur.insertText("Сумма");
        cur.movePosition(QTextCursor::NextCell);
        cur.insertText("Выплачено");
        while(query.next()){
            //запрашиваем данные о компании
            query_2.prepare("SELECT * FROM companys WHERE company_id=:id");
            query_2.bindValue(":id",query.value(1));
            query_2.exec();
            query_2.next();
            sum += query.value(4).toInt();
            paid += query.value(5).toInt();
            //заполняем таблицу
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText(query.value(0).toString());
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText(query_2.value(1).toString());
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText(query_2.value(2).toString());
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText(query_2.value(3).toString());
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText(query.value(2).toString());
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText(query.value(3).toString());
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText(query.value(4).toString());
            cur.movePosition(QTextCursor::NextCell);
            cur.insertText(query.value(5).toString());
        }
        cur.movePosition(QTextCursor::End);
        cur.insertText("Общаяя сумма договоров: "+QString::number(sum)+" рублей"+'\n');
        cur.insertText("Общаяя выплаченная сумма: "+QString::number(paid)+" рублей"+'\n');
        cur.insertText("Необходимо выплатить: "+QString::number(sum-paid)+" рублей");
        doc.print(&printer);    //Печать документа на выбранном принтере
        proc.startDetached("explorer.exe",{"Не оплаченные договоры.pdf"});
    }
}
