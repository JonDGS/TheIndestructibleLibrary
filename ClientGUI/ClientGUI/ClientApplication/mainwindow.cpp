#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "selectionwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    std::string user = ui->usernamelineEdit->text().toUtf8().constData();
    if((Connector::get(user, "CHECK", "NONE") == "CHECKED")){
        Connector::get(user, "LogIn", "NONE");
        this->selectionWindow = new SelectionWindow();
        this->selectionWindow->setUsernameLabel(user);
        this->selectionWindow->setWindowTitle("Selection Screen");
        this->hide();
        this->close();
        this->selectionWindow->show();
    }else{
        this->ui->usernamelineEdit->clear();
    }
}

bool MainWindow::checkInfo(std::string user, std::string password){
    bool isCorrect = Connector::checkLogInCredentials(user, password);
    return isCorrect;
}

void MainWindow::on_pushButton_2_clicked()
{
    this->registrationScreen = new RegistrationScreen;
    this->registrationScreen->setWindowTitle("Register");
    this->hide();
    this->registrationScreen->show();
}
