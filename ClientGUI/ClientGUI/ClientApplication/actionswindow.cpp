#include "actionswindow.h"
#include "ui_actionswindow.h"

ActionsWindow::ActionsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ActionsWindow)
{
    ui->setupUi(this);
    metaDatabase = MetaDB();
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
    std::string currentDatabase = Connector::get(user, "sqlUpdate", "getDatabase");
    std::cout << currentDatabase << std::endl;
    metaDatabase.setJSONDatabase(currentDatabase);
    std::string attributes[6];
    bool allGood = true;
    if(ui->nameLineEdit->text().isEmpty()){
        allGood = false;
    }else{
        attributes[0] = ui->nameLineEdit->text().toStdString();
    }if(ui->authorLineEdit->text().isEmpty()){
        attributes[1] = "NONE";
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
    }if(ui->galleryLineEdit->text().isEmpty()){
        allGood = false;
    }else{
        attributes[5] = ui->galleryLineEdit->text().toStdString();
    }

    if(allGood){
        std::string format = this->currentPath.toStdString().substr(this->currentPath.toStdString().length()-4, 4);
        //std::string header;
        /*if(format.find("jpg") != std::string::npos){
            header = "00";
        }if(format.find("jpeg") != std::string::npos){
            header = "01";
        }if(format.find("png") != std::string::npos){
            header = "11";
        }*/
        attributes[3] = std::to_string(QFile(QString(this->currentPath)).size());
        ImgTable table = ImgTable(attributes[0], attributes[5], attributes[1], attributes[2], attributes[3], attributes[4]);
        metaDatabase.insert(table);
        BitConverter bitconverter;
        std::string bits = bitconverter.convertImageToStringBits(this->currentPath.toStdString());
        std::string bitsInfo = std::to_string(bits.length()) + ',' + attributes[0] + ',' + bits;
        std::string response = Connector::get(user, "uploadImage", bitsInfo);
        std::string database = metaDatabase.toJSON();
        std::string newResponse = Connector::get(user, "sqlUpdate", database);
        std::cout << response << std::endl;
        if(response == "SAVED"){
            ui->imageStatusLabel->setText("Image uploaded successfully");
        }else{
            ui->imageStatusLabel->setText("Something went wrong try again");
        }
    }


}

void ActionsWindow::on_pullPushButton_clicked()
{
    std::string name;
    if(!(name = ui->pullLineEdit->text().toStdString()).empty()){
        std::string bits = Connector::get(user, "requestImage", name);
        if(!bits.empty()){
        BitConverter* bitconverter;
        std::string header = bits.substr(0, 2);
        /*std::cout << header << std::endl;
        if(header.find("00") != std::string::npos){
            header = ".jpg";
        }if(header.find("01") != std::string::npos){
            header = ".jpeg";
        }if(header.find("11") != std::string::npos){
            header = ".png";
        }*/
        bitconverter->convertStringToImage(bits, "../ClientApplication/cache/" + name + ".jpg");
        ui->imageLabel->setPixmap("../ClientApplication/cache/" + QString::fromStdString(name) + ".jpg");
        ui->imageLabel->setScaledContents(true);
        ui->imageStatusLabel->setText("Image found");
        }else{
            ui->imageStatusLabel->setText("Image not found");
        }
    }
}
