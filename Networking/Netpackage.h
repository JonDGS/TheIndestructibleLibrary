//
// Created by jondorito on 05/06/19.
//

#ifndef THEINDESTRUCTIBLELIBRARY_NETPACKAGE_H
#define THEINDESTRUCTIBLELIBRARY_NETPACKAGE_H


#include <string>
#include "../libraries/rapidjson/document.h"
#include "../libraries/rapidjson/writer.h"
#include "../libraries/rapidjson/stringbuffer.h"

class NetPackage {
private:
    std::string from = "unassigned";
    std::string command = "NONE";
    std::string data =  "NONE";
    std::string type = "DEFAULT";
public:
    NetPackage();
    std::string getJSONPackage();
    std::string getFrom();
    std::string getData();
    std::string getcommand();
    std::string getType();
    void setFrom(std::string);
    void setData(std::string);
    void setCommand(std::string);
    void setType(std::string);
    static rapidjson::Document convertToRJ_Document(std::string);
};


#endif //THEINDESTRUCTIBLELIBRARY_NETPACKAGE_H
