#include "inputdate.h"
#include "ui_inputdate.h"

inputDate::inputDate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::inputDate)
{
    ui->setupUi(this);
    setWindowTitle("Временной промежуток");
}

inputDate::~inputDate()
{
    delete ui;
}

inputDate::date_gap inputDate::input(){
   date_gap el;                           //Объявление структуры
   el.start=ui->startDate->date();
   el.fine=ui->fineDate->date();
   return el;          //Структура с данными возвращается в основную форму
}
