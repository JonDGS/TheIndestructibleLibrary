//
// Created by jondorito on 17/06/19.
//

#include "FileManager.h"

/**
 * Creates a file with a specified name and on a specified location
 * @param file_Name of the file that will be created
 * @param file_Location of where it will be created
 * @param file_Data data that will be saved on the new file
 */
void FileManager::createFile(std::string file_Name, std::string file_Location, std::string file_Data) {
    std::ofstream file;

    file.open(file_Location + "/" + file_Name + this->type,std::ios::out);

    if (file.fail())
        std::cout << "FILE: " + file_Name + " , COULD NOT BE CREATED" << std::endl;

    file << file_Data;

    file.close();
}

/**
 * Adds data to an already existing file
 * @param file_Name to which add data
 * @param file_Location where the file is located
 * @param file_Data to add to the file
 */
void FileManager::addData(std::string file_Name, std::string file_Location, std::string file_Data) {
    std::ofstream file;

    file.open(file_Location + "/" + file_Name + this->type,std::ios::app);

    if (file.fail())
        std::cout << "FILE: " + file_Name + " , COULD NOT ADDED DATA" << std::endl;

    file << file_Data;

    file.close();
}

/**
 * Gives back the info stored on the file
 * @param file_Name name of the file to get the data from
 * @param file_Location where the file is located
 * @return data of the file
 */
std::string FileManager::readRile(std::string file_Name, std::string file_Location) {
    std::ifstream file;
    std::string file_Data;

    file.open(file_Location + "/" + file_Name + this->type,std::ios::in);

    if (file.fail()) {
        std::cout << "FILE: " + file_Name + " , COULD NOT BE READ" << std::endl;
        return "";
    }

    while (!file.eof())
        getline(file,file_Data);

    return file_Data;
}

/**
 * Deletes a specified file in a specified location
 * @param file_Name file name to delete
 * @param file_Location location of the file
 */
void FileManager::deleteFile(std::string file_Name, std::string file_Location) {
    std::string file = file_Location + "/" + file_Name + this->type;

    if( std::remove(file.c_str()) != 0 )
        std::cout << "FILE: " + file + " , COULD NOT BE DELETED" << std::endl;
}

/**
 * Empties a given file on a given location
 * @param file_Name to empty
 * @param file_Location where the file is
 */
void FileManager::emptyFile(std::string file_Name,std::string file_Location) {
    std::ofstream file;

    file.open(file_Location + "/" + file_Name + this->type,std::ofstream::out | std::ofstream::trunc);

    file.close();
}

/**
 * Creates a directory with a specified name and a specified location
 * @param dir_Name name of the new directory
 * @param dir_Location location to create the new directory
 */
void FileManager::createDirectory(std::string dir_Name, std::string dir_Location) {
    mkdir((dir_Location + "/" + dir_Name).c_str(),S_IRUSR | S_IWUSR | S_IXUSR);
}

/**
 * Checks if a file of directory exists
 * @param path of the file to check
 * @return the status of the file or directory
 */
bool FileManager::checkLocation(std::string path) {
    std::ifstream file;
    std::string file_Data;

    bool status = true;

    file.open(path,std::ios::in);

    if (file.fail()) {
        status = false;
        std::cout << "Dir: " + path + " , COULD NOT BE OPENED" << std::endl;
    }

    return status;
}

std::string FileManager::getType() {
    return this->type;
}
