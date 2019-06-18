#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "selectionwindow.h"
#include "registrationscreen.h"
#include <QCloseEvent>
#include "connector.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    bool checkInfo(std::string user, std::string password);
    Ui::MainWindow *ui;
    SelectionWindow* selectionWindow;
    RegistrationScreen* registrationScreen;
};

#endif // MAINWINDOW_H
