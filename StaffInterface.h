#ifndef STAFFINTERFACE_H
#define STAFFINTERFACE_H

#include <QTextDocument>
#include <QTextCursor>
#include <QTextDocumentWriter>
#include <QPrinter>

#include <QMainWindow>
#include <QtSql>
#include <QObject>
#include "addbrend.h"
#include "addccient.h"
#include "addcomp.h"
#include "addconsig.h"
#include "addprod.h"
#include "addtreaty.h"
#include "addorder.h"
#include "inputdate.h"
#include "selectprod.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool CreateConnection();
    bool AddChangeRecord(int table, bool flag);
    QSqlTableModel * getModel(int num);
    QSqlRelationalTableModel * getRelModel(int num);

private slots:
    //запросы
    void request();
    void stok();
    void supplier_by_brend();
    void treatys_on_prod();
    void solds_in_range();
    void supplys_in_range();
    void payments();

    //сохранение таблицы в пдф
    void safe_table_in_pdf();

    void DisEnBtn();
    void on_addButton_clicked();

    void on_changeButton_clicked();

    void on_tableView_brend_clicked(const QModelIndex &index);

    void on_delButton_clicked();

    void on_pdfBtn_clicked();

private:
    Ui::MainWindow *ui;
    //РњРѕРґРµР»Рё РґР»СЏ СЂР°Р±РѕС‚С‹ СЃ С‚Р°Р±Р»РёС†Р°РјРё Р‘Р”
    QSqlTableModel *mdl_brend, *mdl_client, *mdl_comp;
    QSqlRelationalTableModel *mdl_ord, *mdl_prod, *mdl_treaty, *mdl_cons;
};
#endif // STAFFINTERFACE_H
