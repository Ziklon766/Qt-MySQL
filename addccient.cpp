#include "addccient.h"
#include "ui_addccient.h"

addcCient::addcCient(QWidget *parent, int cur) :
    QDialog(parent),
    ui(new Ui::addcCient)
{
    ui->setupUi(this);
    num=cur;
    if(num>-1){//если это изменение записи
        record = qobject_cast<MainWindow*>(parent)->getModel(3)->record(num); //Получить запись из модели, необходимо явное преобразование типов
        ui->nameEdit->setText(record.value("name").toString());           //Присвоить необходимые значения виджетам формы
        ui->surenameEdit->setText(record.value("surname").toString());
        ui->phoneEdit->setText(record.value("phone").toString());
        ui->mailEdit->setText(record.value("e-mail").toString());
        ui->pswEdit->setText(record.value("psw").toString());
        setWindowTitle("Изменение данных о клиенте");
    }
    else{
        setWindowTitle("Добавление клиента");
    }
}

addcCient::~addcCient()
{
    delete ui;
}

addcCient::NewClient addcCient::addClient()
{
   NewClient el;                           //Объявление структуры
   el.name=ui->nameEdit->text();
   el.surename=ui->surenameEdit->text();
   el.phone=ui->phoneEdit->text();
   el.mail=ui->mailEdit->text();
   el.psw=ui->pswEdit->text();
   return el;          //Структура с данными возвращается в основную форму
}

void addcCient::on_buttonBox_accepted()
{
    if(num!=-1){
        QMessageBox msgBox; //Стоит спросить уверен ли пользователь
        QString str=QString("Уверены что хотите сохранить изменения о клиенте?");//.arg(ui->anNameEdit->text());
        msgBox.setText(str);
        msgBox.setWindowTitle("Подтверждение");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setInformativeText("Данная операция необратима!");
        QPushButton* pButtonNo = msgBox.addButton("Нет", QMessageBox::NoRole); //Для корректного перевода, кнопки добавлены вручную
        QPushButton* pButtonYes = msgBox.addButton("Да", QMessageBox::YesRole);
        msgBox.setDefaultButton(pButtonYes);
        if(msgBox.exec()==QMessageBox::Accepted){
           qobject_cast<MainWindow*>(parent())->getModel(3)->setData(qobject_cast<MainWindow*>(parent())->getModel(3)->index(num,1),ui->nameEdit->text());
           qobject_cast<MainWindow*>(parent())->getModel(3)->setData(qobject_cast<MainWindow*>(parent())->getModel(3)->index(num,2),ui->surenameEdit->text());
           qobject_cast<MainWindow*>(parent())->getModel(3)->setData(qobject_cast<MainWindow*>(parent())->getModel(3)->index(num,3),ui->phoneEdit->text());
           qobject_cast<MainWindow*>(parent())->getModel(3)->setData(qobject_cast<MainWindow*>(parent())->getModel(3)->index(num,4),ui->mailEdit->text());
           qobject_cast<MainWindow*>(parent())->getModel(3)->setData(qobject_cast<MainWindow*>(parent())->getModel(3)->index(num,5),ui->pswEdit->text());
           qobject_cast<MainWindow*>(parent())->getModel(3)->submitAll();
        }
    }
}
