//
// Created by alvar on 01/06/19.
//

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <sys/stat.h>

/**
 * Manages all the file and directory related methods
 */
class FileManager {
private:
    /**
     * Type of file to create
     */
    std::string type = ".txt";

public:
    /**
     * Default constructor for the class
     */
    FileManager() = default;

    /**
     * Creates a file with a specified name and on a specified location
     * @param file_Name of the file that will be created
     * @param file_Location of where it will be created
     * @param file_Data data that will be saved on the new file
     */
    void createFile(std::string file_Name,std::string file_Location,std::string file_Data);

    /**
     * Gives back the info stored on the file
     * @param file_Name name of the file to get the data from
     * @param file_Location where the file is located
     * @return data of the file
     */
    std::string readRile(std::string file_Name,std::string file_Location);

    /**
     * Deletes a specified file in a specified location
     * @param file_Name file name to delete
     * @param file_Location location of the file
     */
    void deleteFile(std::string file_Name,std::string file_Location);

    /**
     * Empties a given file on a given location
     * @param file_Name to empty
     * @param file_Location where the file is
     */
    void emptyFile(std::string file_Name,std::string file_Location);

    /**
     * Creates a directory with a specified name and a specified location
     * @param dir_Name name of the new directory
     * @param dir_Location location to create the new directory
     */
    void createDirectory(std::string dir_Name,std::string dir_Location);

    /**
     * Checks if a file of directory exists
     * @param path of the file to check
     * @return the status of the file or directory
     */
    bool checkLocation(std::string path);
};