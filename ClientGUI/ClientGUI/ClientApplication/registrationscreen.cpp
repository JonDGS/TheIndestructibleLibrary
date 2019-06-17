#include "registrationscreen.h"
#include "ui_registrationscreen.h"

RegistrationScreen::RegistrationScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegistrationScreen)
{
    ui->setupUi(this);
    ui->statusLabel->hide();
}

RegistrationScreen::~RegistrationScreen()
{
    delete ui;
}

void RegistrationScreen::on_acceptButton_clicked()
{
    std::string user = ui->usernameLineEdit->text().toUtf8().constData();
    bool isCorrect = Connector::checkLogInCredentials(user, "test");
    ui->statusLabel->show();
    if(isCorrect){
        ui->statusLabel->setText("Accepted");
        //usleep(3);
        this->hide();
        this->selectionWindow = new SelectionWindow;
        this->selectionWindow->setUsernameLabel(user);
        this->selectionWindow->show();
    }else{
        ui->statusLabel->setText("Duplicate, try again");
    }
}
