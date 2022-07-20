#ifndef INPUTDATE_H
#define INPUTDATE_H

#include <QDialog>
#include <QDate>

namespace Ui {
class inputDate;
}

class inputDate : public QDialog
{
    Q_OBJECT

public:
    explicit inputDate(QWidget *parent = nullptr);
    ~inputDate();
    struct date_gap{
        QDate start, fine;
    };
    date_gap input();

private:
    Ui::inputDate *ui;
};

#endif // INPUTDATE_H
