#ifndef SQLMANAGEMENTWINDOW_H
#define SQLMANAGEMENTWINDOW_H

#include <QMainWindow>
#include "genericlinkedlist.h"
#include <sstream>

#include "metadb.h"
#include "keyvalue.h"

namespace Ui {
class SQLManagementWindow;
}

class SQLManagementWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SQLManagementWindow(QWidget *parent = nullptr);
    void setUser(std::string user);
    ~SQLManagementWindow();

private slots:
    void on_runButton_clicked();

    void on_commitButton_clicked();

    void on_rollbackButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::SQLManagementWindow *ui;
    std::string user;
    MetaDB *db;


    GenericLinkedList<std::string> *convertStringToLL(std::string data, char limit);
    GenericLinkedList<std::string> runQueries(GenericLinkedList<std::string> *commands);
    KeyValue getCondition(std:: string);

    void displayList(GenericLinkedList<std::string> list);
};

#endif // SQLMANAGEMENTWINDOW_H
