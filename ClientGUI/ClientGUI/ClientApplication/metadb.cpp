#include <algorithm>
#include "metadb.h"

MetaDB::MetaDB() {
    db = new GenericLinkedList<ImgTable>();
    toDelete = new GenericLinkedList<string>();
}

void MetaDB::print() {
    cout <<"-----------------------------" <<endl;
    for(int i=0;i<*db->getLength();i++) {
        ImgTable img = db->get(i)->getData();

        string name = img.getAttribute("name");
        string gallery = img.getAttribute("gallery");
        string author = img.getAttribute("author");
        string year = img.getAttribute("year");
        string size = img.getAttribute("size");
        string description = img.getAttribute("description");

        cout << gallery <<":"<<name<<endl;
        if(author!="") cout<<name<<".author = "<<author<<endl;
        if(year!="")cout<<name<<".year = "<<year<<endl;
        if(size!="")cout<<name<<".size = "<<size<<endl;
        if(description!="")cout<<name<<".description = "<<description<<endl<<endl;
    }
    cout <<"-----------------------------" <<endl<<endl;
}

GenericLinkedList<string> MetaDB::getPrintable()
{
    GenericLinkedList<string> list;
    list.add("");
    list.add("___Current database___");
    for(int i=0;i<*db->getLength();i++) {
        ImgTable img = db->get(i)->getData();

        string name = img.getAttribute("name");
        string gallery = img.getAttribute("gallery");
        string author = img.getAttribute("author");
        string year = img.getAttribute("year");
        string size = img.getAttribute("size");
        string description = img.getAttribute("description");

        list.add(gallery+":"+name);
        if(author!="") list.add(name+".author = "+author);
        if(year!="")list.add(name+".year = "+year);
        if(size!="")list.add(name+".size = "+size);
        if(description!="")list.add(name+".description = "+description);
        list.add("");
    }
    list.add("");

    return list;
}

void MetaDB::insert(ImgTable img) {
    this->db->add(img);
}

void MetaDB::setJSONDatabase(string str) {
    GenericLinkedList<ImgTable> *newDB = new GenericLinkedList<ImgTable>();
    this->toDelete= new GenericLinkedList<string>();

    str.erase(0,13);
    str.erase(str.size()-2,str.size());

    int n = std::count(str.begin(),str.end(),'{');

    for(int i=0;i<n;i++){
        ImgTable img = ImgTable();

        str.erase(0, str.find(":")+2);
        if(str.substr(0, str.find("\""))!="!")img.setName(str.substr(0, str.find("\"")));
        str.erase(0, str.find(":")+2);

        if(str.substr(0, str.find("\""))!="!")img.setGallery(str.substr(0, str.find("\"")));
        str.erase(0, str.find(":")+2);

        if(str.substr(0, str.find("\""))!="!")img.setAuthor(str.substr(0, str.find("\"")));
        str.erase(0, str.find(":")+2);

        if(str.substr(0, str.find("\""))!="!")img.setYear(str.substr(0, str.find("\"")));
        str.erase(0, str.find(":")+2);

        if(str.substr(0, str.find("\""))!="!")img.setSize(str.substr(0, str.find("\"")));
        str.erase(0, str.find(":")+2);

        if(str.substr(0, str.find("\""))!="!")img.setDescription(str.substr(0, str.find("\"")));

        newDB->add(img);
    }
    this->db=newDB;
}

bool MetaDB::meetsCondition(ImgTable img, KeyValue condition) {
    if(condition.getOperator()!=""){
        if(condition.getOperator()==">" || condition.getOperator()=="<"){
            if(condition.getOperator()==">" && stoi(img.getAttribute("year"))>stoi(condition.getValue())
               || condition.getOperator()=="<"&& stoi(img.getAttribute("year"))<stoi(condition.getValue())){
                return true;
            }else{
                return false;
            }
        }else{
            if(stoi(condition.getOperator()) < stoi(img.getAttribute("year")) && stoi(condition.getValue()) > stoi(img.getAttribute("year"))){
                return true;
            }else{
                return false;
            }
        }


    }else {
        if (img.getAttribute(condition.getKey()) == condition.getValue()) {
            return true;
        } else {
            return false;
        }
    }
}

GenericLinkedList<string> MetaDB::select(string gallery, GenericLinkedList<string> attributes) {
    GenericLinkedList<string> results;

    for(int i=0;i<*db->getLength();i++) {
        ImgTable img = db->get(i)->getData();

        if(gallery==img.getAttribute("gallery")) {
            for (int j=0;j<*attributes.getLength();j++){

                string attribute = attributes.get(j)->getData();
                if(attribute=="name")
                    results.add(img.inFormat("name"));
                if(img.getAttribute("author")!="" && attribute=="author")
                    results.add(img.inFormat("author"));
                if(img.getAttribute("year")!="" && attribute=="year")
                    results.add(img.inFormat("year"));
                if(img.getAttribute("size")!="" && attribute=="size")
                    results.add(img.inFormat("size"));
                if(img.getAttribute("description")!="" && attribute=="description")
                    results.add(img.inFormat("description"));
            }
            results.add("");
        }
    }

    return results;
}

GenericLinkedList<string> MetaDB::select(string gallery, GenericLinkedList<string> attributes, KeyValue condition) {
    GenericLinkedList<string> results;

    for (int i = 0; i < *db->getLength(); i++) {
        ImgTable img = db->get(i)->getData();
        if (gallery == img.getAttribute("gallery") && meetsCondition(img, condition)) {
            for (int j = 0; j < *attributes.getLength(); j++) {
                string attribute = attributes.get(j)->getData();
                if(attribute=="name")
                    results.add(img.inFormat("name"));
                if (img.getAttribute("author") != "" && attribute == "author")
                    results.add(img.inFormat("author"));
                if (img.getAttribute("year") != "" && attribute == "year")
                    results.add(img.inFormat("year"));
                if (img.getAttribute("size") != "" && attribute == "size")
                    results.add(img.inFormat("size"));
                if (img.getAttribute("description") != "" && attribute == "description")
                    results.add(img.inFormat("description"));
            }
            results.add("");
        }
    }
    return results;
}

void MetaDB::delete_(string gallery, KeyValue condition) {

    GenericLinkedList<int> indexDelete;

    for (int i = 0; i < *db->getLength(); i++) {
        ImgTable img = db->get(i)->getData();
        if (gallery == img.getAttribute("gallery") && meetsCondition(img, condition)) {
            indexDelete.add(i);

            bool registered= false;
            for(int j =0;j<*toDelete->getLength();j++){
                string name = toDelete->get(j)->getData();
                if(name==img.getAttribute("name"))
                    registered=true;
            }
            if(!registered)
                toDelete->add(img.getAttribute("name"));
        }
    }
    for(int i=*indexDelete.getLength()-1;i>-1;i--){
        int n = indexDelete.get(i)->getData();
        db->remove(n);
    }
}

void MetaDB::update(string gallery, GenericLinkedList<KeyValue> values, KeyValue condition) {
    for(int i=0;i<*db->getLength();i++) {
        ImgTable *img = db->get(i)->getDataPtr();

        if(gallery==img->getAttribute("gallery") && meetsCondition(*img, condition)) {
            for (int j=0;j<*values.getLength();j++){
                KeyValue setData = values.get(j)->getData();
                img->setAttribute(setData);

            }
        }
    }
}

string MetaDB::toJSON() {
    string str;
    str.append("{\"database\":[");

    int size = *db->getLength();
    for(int i=0;i<size;i++) {
        ImgTable img = db->get(i)->getData();

        str.append("{\"name\":");
        if(img.getAttribute("name")==""){
            str.append("\"!\",");
        }else{
            str.append("\""+img.getAttribute("name")+"\",");
        }

        str.append("\"gallery\":");
        if(img.getAttribute("gallery")==""){
            str.append("\"!\",");
        }else{
            str.append("\""+img.getAttribute("gallery")+"\",");
        }

        str.append("\"author\":");
        if(img.getAttribute("author")==""){
            str.append("\"!\",");
        }else{
            str.append("\""+img.getAttribute("author")+"\",");
        }

        str.append("\"year\":");
        if(img.getAttribute("year")==""){
            str.append("\"!\",");
        }else{
            str.append("\""+img.getAttribute("year")+"\",");
        }

        str.append("\"size\":");
        if(img.getAttribute("size")==""){
            str.append("\"!\",");
        }else{
            str.append("\""+img.getAttribute("size")+"\",");
        }

        str.append("\"description\":");
        if(img.getAttribute("description")==""){
            str.append("\"!\"}");
        }else{
            str.append("\""+img.getAttribute("description")+"\"}");
        }

        if(i!=size-1)
            str.append(",");

    }
    str.append("]}");
    return str;
}

GenericLinkedList<string> MetaDB::getNames(string gallery) {
    GenericLinkedList<string> names;
    for(int i=0;i<*db->getLength();i++) {
        if(db->get(i)->getData().getAttribute("gallery")==gallery)
            names.add(db->get(i)->getData().getAttribute("name"));
    }
    return names;
}

GenericLinkedList<string> MetaDB::getToDelete() {
    GenericLinkedList<string> list = *toDelete;
    toDelete=new GenericLinkedList<string>();
    return list;
}

bool MetaDB::exists(string gallery) {
    for(int i=0;i<*db->getLength();i++) {
        if(db->get(i)->getData().getAttribute("gallery")==gallery)
            return true;
    }
    return false;
}
