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

void ActionsWindow::on_loadImageButton_clicked()
{
    QString imagePath = ui->imagePathLineEdit->text();
    try {
        QPixmap pix(imagePath);
        ui->imageLabel->setPixmap(pix);
        ui->imageLabel->setScaledContents(true);
    } catch (int e) {
        ui->imageStatusLabel->setText("Image not found");
        ui->imagePathLineEdit->clear();
    }
}
