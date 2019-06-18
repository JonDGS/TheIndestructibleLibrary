#include "sqlmanagementwindow.h"
#include "ui_sqlmanagementwindow.h"
#include "metadb.h"

SQLManagementWindow::SQLManagementWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SQLManagementWindow)
{
    ui->setupUi(this);
    setWindowTitle("IDE");

    this->db = new MetaDB();
        ImgTable img1 = ImgTable("Puddle","Dogs","Ruben","1688","87kb","A random dogo");
        db->insert(img1);
        ImgTable img2 = ImgTable("Chibba","Dogs");
        img2.setYear("2000");
        img2.setDescription("Chibbing being funny");
        db->insert(img2);
        ImgTable img3 = ImgTable("Grumpy","Dogs");
        img3.setYear("2000");
        img3.setAuthor("Sebastian");
        img3.setDescription("A grumpy foe");
        db->insert(img3);
        ImgTable img4 = ImgTable("Michi","Cats");
        img4.setYear("2002");
        img4.setAuthor("Sebastian");
        db->insert(img4);

    displayList(db->getPrintable());
}

void SQLManagementWindow::setUser(string user)
{
    this->user = user;
    ui->label_user->setText(QString::fromStdString(user));
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

GenericLinkedList<std::string> SQLManagementWindow::runQueries(GenericLinkedList<string> *commands)
{
    GenericLinkedList<std::string> result;

    std::cout<<"-------"<<std::endl;
    for(int n=0;n<*commands->getLength();n++){
        string cmd = commands->get(n)->getData();

        string query, gallery, condition,skip;

        query = cmd.substr(0, 6);
        cmd.erase(0,7);

        switch(query.at(0)){

            case 'I':
            {
                std::cout<<"INSERT"<<std::endl;

                cmd.erase(0,cmd.find("O")+2);

                gallery = cmd.substr(0, cmd.find("(")-1);
                if(!db->exists(gallery)){
                    result.add("Gallery doesn't exists");
                    break;
                }

                cmd.erase(0,cmd.find("'")+1);

                string name = cmd.substr(0, cmd.find("'"));
                cmd.erase(0,cmd.find("'")+1);
                cmd.erase(0,cmd.find("'")+1);

                string author = cmd.substr(0, cmd.find("'"));
                cmd.erase(0,cmd.find("'")+1);
                cmd.erase(0,cmd.find("'")+1);

                string year = cmd.substr(0, cmd.find("'"));
                cmd.erase(0,cmd.find("'")+1);
                cmd.erase(0,cmd.find("'")+1);

                string size = cmd.substr(0, cmd.find("'"));
                cmd.erase(0,cmd.find("'")+1);
                cmd.erase(0,cmd.find("'")+1);

                string description = cmd.substr(0, cmd.find("'"));
                cmd.erase(0,cmd.find("'")+1);
                cmd.erase(0,cmd.find("'")+1);

                ImgTable img = ImgTable(name,gallery, author, year,size,description);
                this->db->insert(img);


                break;
            }
            case 'S':
            {
                std::cout<<"SELECT"<<std::endl;

                string strAttributes = cmd.substr(0, cmd.find("FROM")-1);
                cmd.erase(0,cmd.find("FROM")+5);

                strAttributes.append(", ");
                int n=0;
                GenericLinkedList<std::string> attributes;
                for(char ch: strAttributes){
                    if(ch==',')n++;
                }

                string temp;
                for(int i=0;i<n;i++){
                    temp = strAttributes.substr(0, strAttributes.find(","));
                    strAttributes.erase(0,strAttributes.find(",")+2);
                    attributes.add(temp);
                }

                gallery = cmd.substr(0, cmd.find("WHERE")-1);
                if(!db->exists(gallery)){
                    result.add("Gallery doesn't exists");
                    break;
                }


                cmd.erase(0,cmd.find("WHERE")+6);
                ui->listWidget->addItem("___SELECT QUERY___");
                if(cmd.empty()){
                    result = db->select(gallery, attributes);
                }else{
                    KeyValue cond = getCondition(cmd);
                    result = db->select(gallery, attributes,cond);
                }

            }
                break;
            case 'U':
            {
                std::cout<<"UPDATE"<<std::endl;

                std::stringstream ss(cmd);
                getline(ss, gallery,' ');

                if(!db->exists(gallery)){
                    result.add("Gallery doesn't exists");
                    break;
                }

                getline(ss, skip,' ');
                cmd.erase(0,cmd.find("SET")+4);
                string strAtributes;

                strAtributes = cmd.substr(0, cmd.find("WHERE")-1);
                cmd.erase(0,cmd.find("WHERE")+6);
                KeyValue kv = getCondition(cmd);

                GenericLinkedList<KeyValue> attributes;
                strAtributes.append(",");
                string key, value;

                int n=0;
                for(char ch: strAtributes){
                    if(ch=='=')n++;
                }

                for(int i=0;i<n;i++){
                    key = strAtributes.substr(0, strAtributes.find("="));
                    strAtributes.erase(0,strAtributes.find("=")+1);
                    value = strAtributes.substr(0, strAtributes.find(","));
                    strAtributes.erase(0,strAtributes.find(",")+2);
                    attributes.add(KeyValue(key,value));
                }
                this->db->update(gallery, attributes, kv);
                break;
            }
            case 'D':
            {
                std::cout<<"DELETE"<<std::endl;
                cmd.erase(0,cmd.find("M")+2);
                std::stringstream ss(cmd);
                getline(ss, gallery,' ');

                if(!db->exists(gallery)){
                    result.add("Gallery doesn't exists");
                    break;
                }

                cmd.erase(0,cmd.find("WHERE")+6);
                KeyValue kv = getCondition(cmd);
                this->db->delete_(gallery,kv);
                break;
            }
            default:
                break;
        }
    }

    return result;
}

KeyValue SQLManagementWindow::getCondition(string condition)
{
    std::string option = "BETWEEN";

    for(char ch:condition){
        if(ch=='>' || ch=='<') option="higher/lower";
    }

    if (condition.find("IS")!=string::npos) option="IS";


    std::stringstream ss(condition);
    KeyValue kv;
    string s1,s2,s3,skip;

    if(option=="BETWEEN"){
        getline(ss, s1,' ');
        getline(ss, skip,' ');
        getline(ss, s2,' ');
        getline(ss, skip,' ');
        getline(ss, s3,' ');
        kv = KeyValue(s1,s2,s3);
    }else if(option=="higher/lower"){
        getline(ss, s1,' ');
        getline(ss, s2,' ');
        getline(ss, s3,' ');
        kv = KeyValue(s1,s2,s3);
    }else{
        getline(ss, s1,' ');
        getline(ss, skip,' ');
        getline(ss, s2,' ');
        kv = KeyValue(s1,s2);
    }

    //std::cout<<kv.getKey()+" , "+kv.getOperator()+" , "+kv.getValue()<<std::endl;
    return kv;
}

void SQLManagementWindow::displayList(GenericLinkedList<string> list)
{
    for(int n=0;n<*list.getLength();n++){
        std::string s = list.get(n)->getData();
        std::cout<<s<<std::endl;
        ui->listWidget->addItem(QString::fromStdString(s));
    }
}

void SQLManagementWindow::on_runButton_clicked()
{
    //std::cout << "Input line by line" << std::endl;
    std::string code = this->ui->codePlainTextEdit->toPlainText().toUtf8().constData();

    GenericLinkedList<std::string>* lines = this->convertStringToLL(code, '\n');
    string first = lines->get(0)->getData();

    if(first=="PRINT"){
        displayList(db->getPrintable());
    }else if(first == "SAMPLES"){
        GenericLinkedList<string> sample;
        sample.add("INSERT INTO Landscapes (name, gallery, author, year, size, description) VALUES ('Tree', 'Boznack', '1750', '90kb', 'A simple computer image')");

    }else{
        displayList(runQueries(lines));
    }
}

void SQLManagementWindow::on_commitButton_clicked()
{

}

void SQLManagementWindow::on_rollbackButton_clicked()
{

}

void SQLManagementWindow::on_pushButton_3_clicked()
{
    ui->codePlainTextEdit->clear();
}
