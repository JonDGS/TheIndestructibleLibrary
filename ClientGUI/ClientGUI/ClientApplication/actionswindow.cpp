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

void ActionsWindow::setUser(std::string user){
    this->user = user;
}

void ActionsWindow::on_browsePushButton_clicked()
{
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg *.jpeg)"));
    dialog.setViewMode(QFileDialog::Detail);
    QString fileName = QFileDialog::getOpenFileName(this,
       tr("Open Images"), "/home", tr("Image Files (*.png *.jpg *.bmp *jpeg)"));
    if (!fileName.isEmpty())
    {
         QImage image(fileName);
         ui->imageLabel->setPixmap(QPixmap::fromImage(image));
         ui->imageLabel->setScaledContents(true);
         this->currentPath = fileName;
         this->isImageLoaded = true;
    }
}

void ActionsWindow::on_uploadPushButton_clicked()
{
    std::string attributes[5];
    bool allGood = true;
    if(ui->nameLineEdit->text().isEmpty()){
        allGood = false;
    }else{
        attributes[0] = ui->nameLineEdit->text().toStdString();
    }if(ui->authorLineEdit->text().isEmpty()){
        allGood = false;
    }else{
        attributes[1] = ui->authorLineEdit->text().toStdString();
    }if(ui->dateLineEdit->text().isEmpty()){
        attributes[2] = "NONE";
    }else{
        attributes[2] = ui->dateLineEdit->text().toStdString();
    }if(ui->descriptionTextEdit->toPlainText().isEmpty()){
        attributes[4] = "NONE";
    }else{
        attributes[4] = ui->descriptionTextEdit->toPlainText().toStdString();
    }

    if(allGood){
        attributes[3] = std::to_string(QFile(QString(this->currentPath)).size());
        BitConverter bitconverter;
        std::string bits = bitconverter.convertImageToStringBits(this->currentPath.toStdString());
        std::string bitsInfo = std::to_string(bits.length()) + ',' + attributes[0] + ',' + bits;
        std::string response = Connector::get(user, "uploadImage", bitsInfo);
    }


}
