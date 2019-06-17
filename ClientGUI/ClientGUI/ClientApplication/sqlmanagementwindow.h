#ifndef SQLMANAGEMENTWINDOW_H
#define SQLMANAGEMENTWINDOW_H

#include <QMainWindow>
#include "genericlinkedlist.h"
#include <sstream>

namespace Ui {
class SQLManagementWindow;
}

class SQLManagementWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SQLManagementWindow(QWidget *parent = nullptr);
    ~SQLManagementWindow();

private slots:
    void on_runButton_clicked();

private:
    Ui::SQLManagementWindow *ui;
    GenericLinkedList<std::string> *convertStringToLL(std::string data, char limit);
};

#endif // SQLMANAGEMENTWINDOW_H
