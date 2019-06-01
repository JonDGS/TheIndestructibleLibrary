//
// Created by msegura on 01/06/19.
//

#include "MetaDB.h"

MetaDB::MetaDB() {
}

string MetaDB::getStr(ptree data) {
    ostringstream buffer;
    write_json(buffer, data, false);
    buffer << std::endl;
    return buffer.str();
}

ptree MetaDB::getPtree(string json) {
    ptree data;
    stringstream ss;
    ss << json;
    read_json(ss,data);
    return data;
}

void MetaDB::create(string id, string data) {
    string dirCur = "../metabase/currents/"+id+".json";
    writeFile(dirCur,data);
    ofstream file1;
    file1.open(dirCur);
    file1 << data;
    file1.close();
    cout<<"Metadata of image \""+id+"\" successfully registered"<<endl;
}

void MetaDB::writeFile(string path, string data){
    ofstream outputStream;
    outputStream.open(path, ofstream::trunc);
    outputStream << data;
    outputStream.close();
    cout<<"Metadata writen in file directory: "+path<<endl;
}

void MetaDB::deleteFile(string id) {
    const char *path = getPath(id).c_str();
    remove(path);
    cout<<"Metadata of \""+id+"\" deleted"<<endl;
}

string MetaDB::getPath(string id) {
    string path = "../metabase/currents/"+id+".json";
    return path;
}

bool MetaDB::registered(string id) {
    fstream dir(getPath(id));
    bool exists = false;
    if(dir) exists = true;
    return exists;
}

string MetaDB::getMeta(string id) {

    return std::__cxx11::string();
}
