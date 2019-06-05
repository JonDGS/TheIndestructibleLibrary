//
// Created by alvar on 01/06/19.
//

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <sys/stat.h>


class FileManager {
private:
    std::string type = ".txt";

public:
    FileManager() = default;

    void createFile(std::string file_Name,std::string file_Location,std::string file_Data);

    std::string readRile(std::string file_Name,std::string file_Location);

    void deleteFile(std::string file_Name,std::string file_Location);

    void createDirectory(std::string dir_Name,std::string dir_Location);

    bool checkLocation(std::string path);
};