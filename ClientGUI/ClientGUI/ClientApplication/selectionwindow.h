#ifndef SELECTIONWINDOW_H
#define SELECTIONWINDOW_H

#include <QMainWindow>
#include "actionswindow.h"
#include "sqlmanagementwindow.h"

namespace Ui {
class SelectionWindow;
}

class SelectionWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SelectionWindow(QWidget *parent = nullptr);
    ~SelectionWindow();
    void setUsernameLabel(std::string);

private slots:

    void on_uploadPushButton_clicked();

    void on_managePushButton_clicked();

private:
    Ui::SelectionWindow *ui;
    ActionsWindow* actionsWindow;
    SQLManagementWindow* sqlManagementWindow;
    std::string user;
};

#endif // SELECTIONWINDOW_H
