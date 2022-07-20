#ifndef ADD_CLASSES_H
#define ADD_CLASSES_H

#include <QDialog>

namespace Ui {
class add_classes;
}

class AddDlg : public QDialog
{
    Q_OBJECT

public:
    explicit AddDlg(QWidget *parent = nullptr);
    ~AddDlg();
    //структура для хранения полей создаваемой записи
    struct NewBrend {
           QString SpName;
       };
    //Метод, который вернут созданные данные в основную программу
    NewBrend addBrend();
private:
    Ui::add_classes *ui;
};

#endif // ADD_CLASSES_H
