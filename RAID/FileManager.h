//
// Created by alvar on 01/06/19.
//

#pragma once

#include <iostream>
#include <fstream>
#include <string>


class FileManager {
public:
    FileManager() = default;
    void createFile(std::string file_Name,std::string file_Location,std::string file_Data);
    std::string readRile(std::string file_Name,std::string file_Location);
};