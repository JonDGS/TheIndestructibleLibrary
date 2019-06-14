#include "actionswindow.h"
#include "ui_actionswindow.h"

ActionsWindow::ActionsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ActionsWindow)
{
    ui->setupUi(this);
}

ActionsWindow::~ActionsWindow()
{
    delete ui;
}
