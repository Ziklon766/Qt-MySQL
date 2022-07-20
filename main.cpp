#include "StaffInterface.h"
#include "initwindow.h"

#include <QApplication>
#include <QObject>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //initwindow w;
    w.show();
    return a.exec();
}
