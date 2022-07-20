#include "add_classes.h"
#include "ui_add_classes.h"
#include "ui_addclient.h"

AddDlg::AddDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_classes)
{
    ui->setupUi(this);
}

AddDlg::~AddDlg()
{
    delete ui;
}

AddDlg::NewBrend AddDlg::addBrend()
{
   NewBrend el;                           //Объявление структуры
   el.SpName=ui->lineEdit->text();   //Имя берётся из Line Edit
   return el;          //Структура с данными возвращается в основную форму
}

