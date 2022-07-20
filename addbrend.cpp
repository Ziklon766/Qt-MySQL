#include "addbrend.h"
#include "ui_addbrend.h"

addBrend::addBrend(QWidget *parent, int cur) :
    QDialog(parent),
    ui(new Ui::addBrend)
{
    ui->setupUi(this);
    num=cur;
    if(num>-1){//если это изменение записи
        record = qobject_cast<MainWindow*>(parent)->getModel(1)->record(num); //Получить запись из модели, необходимо явное преобразование типов
        ui->lineEdit->setText(record.value("brend_name").toString());           //Присвоить необходимые значения виджетам формы
        setWindowTitle("Изменение данных о производителе");
    }
    else{
        setWindowTitle("Добавление производителя");
    }
}

addBrend::~addBrend()
{
    delete ui;
}

addBrend::NewBrend addBrend::add(){
   NewBrend el;                           //Объявление структуры
   el.SpName=ui->lineEdit->text();   //Имя берётся из Line Edit
   return el;          //Структура с данными возвращается в основную форму
}

void addBrend::on_buttonBox_accepted()
{
    if(num!=-1){
        QMessageBox msgBox; //Стоит спросить уверен ли пользователь
        QString str=QString("Уверены что хотите сохранить изменения о производителе?");//.arg(ui->anNameEdit->text());
        msgBox.setText(str);
        msgBox.setWindowTitle("Подтверждение");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setInformativeText("Данная операция необратима!");
        QPushButton* pButtonNo = msgBox.addButton("Нет", QMessageBox::NoRole); //Для корректного перевода, кнопки добавлены вручную
        QPushButton* pButtonYes = msgBox.addButton("Да", QMessageBox::YesRole);
        msgBox.setDefaultButton(pButtonYes);
        if(msgBox.exec()==QMessageBox::Accepted){
           qobject_cast<MainWindow*>(parent())->getModel(1)->setData(qobject_cast<MainWindow*>(parent())->getModel(1)->index(num,1),ui->lineEdit->text());
           qobject_cast<MainWindow*>(parent())->getModel(1)->submitAll();
        }
    }
}
