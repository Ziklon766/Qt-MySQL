#include "addcomp.h"
#include "ui_addcomp.h"

addComp::addComp(QWidget *parent, int cur) :
    QDialog(parent),
    ui(new Ui::addComp)
{
    ui->setupUi(this);
    num=cur;
    qDebug()<<num;
    if(num>-1){//если это изменение записи
        record = qobject_cast<MainWindow*>(parent)->getModel(5)->record(num); //Получить запись из модели, необходимо явное преобразование типов
        ui->nameEdit->setText(record.value("name").toString());           //Присвоить необходимые значения виджетам формы
        ui->addressEdit->setText(record.value("address").toString());
        ui->phoneEdit->setText(record.value("phone").toString());
        setWindowTitle("Изменение данных о поставщике");
    }
    else{
        setWindowTitle("Добавление поставщика");
    }
}

addComp::~addComp()
{
    delete ui;
}

addComp::New addComp::add(){
   New el;                           //Объявление структуры
   el.name=ui->nameEdit->text();
   el.address=ui->addressEdit->text();
   el.phone=ui->phoneEdit->text();
   return el;          //Структура с данными возвращается в основную форму
}

void addComp::on_buttonBox_accepted()
{
    if(num!=-1){
        QMessageBox msgBox; //Стоит спросить уверен ли пользователь
        QString str=QString("Уверены что хотите сохранить изменения о поставщике?");//.arg(ui->anNameEdit->text());
        msgBox.setText(str);
        msgBox.setWindowTitle("Подтверждение");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setInformativeText("Данная операция необратима!");
        QPushButton* pButtonNo = msgBox.addButton("Нет", QMessageBox::NoRole); //Для корректного перевода, кнопки добавлены вручную
        QPushButton* pButtonYes = msgBox.addButton("Да", QMessageBox::YesRole);
        msgBox.setDefaultButton(pButtonYes);
        if(msgBox.exec()==QMessageBox::Accepted){
           qobject_cast<MainWindow*>(parent())->getModel(5)->setData(qobject_cast<MainWindow*>(parent())->getModel(5)->index(num,1),ui->nameEdit->text());
           qobject_cast<MainWindow*>(parent())->getModel(5)->setData(qobject_cast<MainWindow*>(parent())->getModel(5)->index(num,2),ui->addressEdit->text());
           qobject_cast<MainWindow*>(parent())->getModel(5)->setData(qobject_cast<MainWindow*>(parent())->getModel(5)->index(num,3),ui->phoneEdit->text());
           qobject_cast<MainWindow*>(parent())->getModel(5)->submitAll();
        }
    }
}
