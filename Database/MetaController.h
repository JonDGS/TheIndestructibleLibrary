//
// Created by msegura on 11/06/19.
//

#ifndef THEINDESTRUCTIBLELIBRARY_METACONTROLLER_H
#define THEINDESTRUCTIBLELIBRARY_METACONTROLLER_H


#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

/**
 * Manages the storage of the metadata in json format
 */
class MetaController {
public:
    /**
     * Default constructor. Reads the values of currentDB and previousDB from their json files
     */
    MetaController();

    /**
     * Sets the new version of the database to be stored
     * @param database New database version
     */
    void commit(string database);

    /**
     * Restores the previous version of the database
     * @return Previous database version
     */
    string rollBack();

    string getCurrent();
private:
    /**
     * Writes currentDB and previousDB to their respective json file
     */
    void writeJSONS();
    string currentDB;
    string previousDB;
};


#endif //THEINDESTRUCTIBLELIBRARY_METACONTROLLER_H
