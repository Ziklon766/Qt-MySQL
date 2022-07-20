#include "addconsig.h"
#include "ui_addconsig.h"

addConsig::addConsig(QWidget *parent, int cur) :
    QDialog(parent),
    ui(new Ui::addConsig)
{
    ui->setupUi(this);
    num=cur;
    QSqlQuery query;
    QString  str = "SELECT num_treaty FROM treatys ORDER BY num_treaty";       //Запрос на получение требуемых данных из таблицы species
    query.exec(str);

    while(query.next())         //Проход по строкам запроса
    {
       ui->treatyCmb->addItem(query.value(0).toString()); //поле с индексом 1 добавляется как значение в список, а с индексом 0 как UserData
    }
    str = "SELECT prod_id,model FROM products ORDER BY model";       //Запрос на получение требуемых данных из таблицы species
    query.exec(str);

    while(query.next())         //Проход по строкам запроса
    {
       ui->prodCmb->addItem(query.value(1).toString(),query.value(0)); //поле с индексом 1 добавляется как значение в список, а с индексом 0 как UserData
    }
}

addConsig::~addConsig()
{
    delete ui;
}

addConsig::New addConsig::add(){
   New el;                           //Объявление структуры
   //el.name=ui->nameEdit->text();
  //el.address=ui->addressEdit->text();
  // el.phone=ui->phoneEdit->text();
   return el;          //Структура с данными возвращается в основную форму
}

void addConsig::on_buttonBox_accepted()
{
    if(num!=-1){
        QMessageBox msgBox; //Стоит спросить уверен ли пользователь
        QString str=QString("Уверены что хотите сохранить изменения о партии?");
        msgBox.setText(str);
        msgBox.setWindowTitle("Подтверждение");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setInformativeText("Данная операция необратима!");
        QPushButton* pButtonNo = msgBox.addButton("Нет", QMessageBox::NoRole); //Для корректного перевода, кнопки добавлены вручную
        QPushButton* pButtonYes = msgBox.addButton("Да", QMessageBox::YesRole);
        msgBox.setDefaultButton(pButtonYes);
        if(msgBox.exec()==QMessageBox::Accepted){
           //qobject_cast<MainWindow*>(parent())->getModel(6)->setData(qobject_cast<MainWindow*>(parent())->getModel(6)->index(num,1),ui->nameEdit->text());
           //qobject_cast<MainWindow*>(parent())->getModel(6)->setData(qobject_cast<MainWindow*>(parent())->getModel(6)->index(num,2),ui->addressEdit->text());
           //qobject_cast<MainWindow*>(parent())->getModel(6)->setData(qobject_cast<MainWindow*>(parent())->getModel(6)->index(num,3),ui->phoneEdit->text());
           //qobject_cast<MainWindow*>(parent())->getModel(6)->submitAll();
        }
    }
}
