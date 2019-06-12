//
// Created by msegura on 11/06/19.
//

#include "MetaController.h"


MetaController::MetaController() {

    ifstream curr;
    curr.open("../Database/metadata/current.json");
    string temp;
    while(getline(curr,temp)){
        currentDB.append(temp);
    }
    curr.close();

    ifstream pre;
    pre.open("../Database/metadata/previous.json");
    while(getline(pre,temp)){
        previousDB.append(temp);
    }
    pre.close();
}

void MetaController::commit(string database) {
    previousDB=currentDB;
    currentDB=database;

    writeJSONS();
}

string MetaController::rollBack() {
    string temp = previousDB;
    currentDB=previousDB;
    previousDB=temp;

    writeJSONS();

    return currentDB;
}

void MetaController::writeJSONS() {
    ofstream currStream;
    currStream.open("../Database/metadata/current.json", ofstream::trunc);
    currStream << currentDB;
    currStream.close();

    ofstream preStream;
    preStream.open("../Database/metadata/previous.json", ofstream::trunc);
    preStream << previousDB;
    preStream.close();
}

string MetaController::getCurrent() {
    return currentDB;
}