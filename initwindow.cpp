#include "initwindow.h"
#include "ui_initwindow.h"
#include <QtSql>
#include <QMessageBox>

#define pass "1"

initwindow::initwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::initwindow)
{
    ui->setupUi(this);

    ui->passEdit->setEchoMode(QLineEdit::Password);
    CreateConnection();
}

initwindow::~initwindow()
{
    delete ui;
}

void initwindow::on_checkBox_stateChanged(int arg1)
{
    if(arg1) ui->passEdit->setEchoMode(QLineEdit::Normal);
    else ui->passEdit->setEchoMode(QLineEdit::Password);
}

void initwindow::on_pushButton_clicked()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM clients WHERE email=:email");
    query.bindValue(":email",ui->loginEdit->text());
    if (!query.exec()) {
        qDebug()<<"Ошибка при выполнении запроса";
    }
     query.next();
    if(query.size()==0 && ui->loginEdit->text()!="admin"){
        ui->statusbar->showMessage("Неверный логин!");
        return;
    }
    if(query.record().value("password").toString() == ui->passEdit->text() ||
       (ui->passEdit->text()==pass && ui->loginEdit->text() == "admin")
       ){
        db.close();
        if(ui->loginEdit->text() == "admin"){
            staf_w = new MainWindow();
            staf_w->show();
            this->close();
        }else{
            //запуск пользователького интерфейса
        }
    }
    else ui->statusbar->showMessage("Неверный пароль!");
}

//соединение с сервером  +done+
bool initwindow::CreateConnection()
{
   qDebug()<<QSqlDatabase::drivers();
   db = QSqlDatabase::addDatabase("QMYSQL");   //Драйвер MySQL
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
