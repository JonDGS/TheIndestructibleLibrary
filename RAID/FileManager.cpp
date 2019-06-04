//
// Created by alvar on 01/06/19.
//

#include "FileManager.h"

void FileManager::createFile(std::string file_Name, std::string file_Location, std::string file_Data) {
    std::ofstream file;

    file.open(file_Location + "/" + file_Name + this->type,std::ios::out);

    if (file.fail())
        std::cout << "FILE: " + file_Name + " , COULD NOT BE CREATED" << std::endl;

    file << file_Data;

    file.close();
}

std::string FileManager::readRile(std::string file_Name, std::string file_Location) {
    std::ifstream file;
    std::string file_Data;

    file.open(file_Location + "/" + file_Name + this->type,std::ios::in);

    if (file.fail())
        std::cout << "FILE: " + file_Name + " , COULD NOT BE OPENED" << std::endl;

    while (!file.eof())
        getline(file,file_Data);

    return file_Data;
}

void FileManager::deleteFile(std::string file_Name, std::string file_Location) {
    std::string file = file_Location + "/" + file_Name + this->type;

    if( std::remove(file.c_str()) != 0 )
        std::cout << "FILE: " + file_Name + " , COULD NOT BE DELETED";
}

bool FileManager::checkDir(std::string path) {
    std::ifstream file;
    std::string file_Data;

    bool status = true;

    file.open(path,std::ios::in);

    if (file.fail()) {
        status = false;
        std::cout << "Dir: " + path + " , DOES NOT EXIST" << std::endl;
    }

    return status;
}