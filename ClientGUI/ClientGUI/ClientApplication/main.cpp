#include "mainwindow.h"
#include <QApplication>

#include "sqlmanagementwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*MainWindow w;
    w.setWindowTitle("The Indestructible Library");
    w.show();*/

    SQLManagementWindow ide;
    ide.setWindowTitle("IDE");
    ide.show();



    return a.exec();
}
