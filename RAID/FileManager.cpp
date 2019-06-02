//
// Created by alvar on 01/06/19.
//

#include "FileManager.h"

void FileManager::createFile(std::string file_Name, std::string file_Location, std::string file_Data) {
    std::string type = "txt";

    std::ofstream file;

    file.open(file_Location + "/" + file_Name + "." + type,std::ios::out);

    file << file_Data;

    file.close();
}

std::string FileManager::readRile(std::string file_Name, std::string file_Location) {
    return std::__cxx11::string();
}
