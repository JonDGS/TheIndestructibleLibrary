#include "selectionwindow.h"
#include "ui_selectionwindow.h"

SelectionWindow::SelectionWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SelectionWindow)
{
    ui->setupUi(this);
}

SelectionWindow::~SelectionWindow()
{
    delete ui;
}

void SelectionWindow::setUsernameLabel(std::string user){
    ui->usernamLabel->setText("Logged-in as: " + QString::fromStdString(user));
    this->user = user;
}

void SelectionWindow::on_uploadPushButton_clicked()
{
    this->actionsWindow = new ActionsWindow;
    this->actionsWindow->setUser(user);
    this->hide();
    this->actionsWindow->show();
}

void SelectionWindow::on_managePushButton_clicked()
{
    this->sqlManagementWindow = new SQLManagementWindow;
    this->hide();
    this->sqlManagementWindow->show();
}
