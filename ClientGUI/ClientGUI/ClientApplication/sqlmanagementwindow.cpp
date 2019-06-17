#include "sqlmanagementwindow.h"
#include "ui_sqlmanagementwindow.h"
#include "metadb.h"

SQLManagementWindow::SQLManagementWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SQLManagementWindow)
{
    ui->setupUi(this);
    MetaDB* database = new MetaDB();
}

SQLManagementWindow::~SQLManagementWindow()
{
    delete ui;
}

GenericLinkedList<std::string>* SQLManagementWindow::convertStringToLL(std::string data, char limit){
    std::stringstream ss(data);
    GenericLinkedList<std::string> *list = new GenericLinkedList<std::string>;

        while (ss.good()) {
            std::string substr;
            getline(ss, substr, limit);
            list->add(substr);
        }
        return list;
}

void SQLManagementWindow::on_runButton_clicked()
{
    std::cout << "current->get(j)->getData()" << std::endl;
    std::string code = this->ui->codePlainTextEdit->toPlainText().toUtf8().constData();
    GenericLinkedList<std::string>* lines = this->convertStringToLL(code, '\n');
    GenericLinkedList<GenericLinkedList<std::string>*>* words = new GenericLinkedList<GenericLinkedList<std::string>*>;
    for(int i = 0; i < *lines->getLength(); i++){
        std::string line = lines->get(i)->getData();
        std::cout << line << std::endl;
        GenericLinkedList<std::string>* wordLine = this->convertStringToLL(line, ' ');
        words->add(wordLine);
    }
    for(int i = 0; i < *words->getLength(); i++){
        GenericLinkedList<std::string>* current = words->get(i)->getData();
        for(int j = 0; j < *current->getLength(); j++){
            std::cout << current->get(j)->getData() << std::endl;
        }
    }
}
