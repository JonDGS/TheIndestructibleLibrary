#include "imgtable.h"

ImgTable::ImgTable() {
    name,gallery,author,year,size,description="!";
}

ImgTable::ImgTable(string name, string gallery) {
    this->name=name;
    this->gallery=gallery;
}

void ImgTable::setName(string name) {
    this->name=name;
}

void ImgTable::setAuthor(string author) {
    this->author=author;
}

void ImgTable::setYear(string year) {
    this->year=year;
}

void ImgTable::setSize(string size) {
    this->size=size;
}

void ImgTable::setDescription(string description) {
    this->description=description;
}

void ImgTable::setGallery(string gallery) {
    this->gallery=gallery;
}

ImgTable::ImgTable(string name, string gallery, string author, string year, string size,
                   string description) {
    this->name=name;
    this->gallery=gallery;
    this->author=author;
    this->year=year;
    this->size=size;
    this->description=description;
}

string ImgTable::inFormat(string attribute) {
    if(attribute=="name") return gallery+":"+name;

    string str=name+"."+attribute+" = ";
    if(attribute=="author"){
        str = str+author;
    }else if(attribute=="year"){
        str = str+year;
    }else if(attribute=="size"){
        str = str+size;
    }else{
        str = str+description;
    }


    return str;
}

string ImgTable::getAttribute(string attribute) {
    if(attribute=="name"){
        return this->name;
    }else if(attribute=="gallery"){
        return this->gallery;
    }else if(attribute=="author"){
        return this->author;
    }else if(attribute=="year"){
        return this->year;
    }else if(attribute=="size"){
        return this->size;
    }else if (attribute=="description"){
        return this->description;
    }else{
        return "!";
    }
}

bool ImgTable::setAttribute(KeyValue data) {
    if(data.getKey()=="name"){
        name=data.getValue();
        return true;
    }else if(data.getKey()=="gallery"){
        gallery=data.getValue();
        return true;
    }else if(data.getKey()=="author"){
        author=data.getValue();
        return true;
    }else if(data.getKey()=="year"){
        this->year=data.getValue();
        return true;
    }else if(data.getKey()=="size"){
        this->size=data.getValue();
        return true;
    }else if (data.getKey()=="description"){
        description=data.getValue();
        return true;
    }else{
        return false;
    }
}
