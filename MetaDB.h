//
// Created by msegura on 01/06/19.
//

#ifndef THEINDESTRUCTIBLELIBRARY_METADB_H
#define THEINDESTRUCTIBLELIBRARY_METADB_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using boost::property_tree::ptree;
using boost::property_tree::basic_ptree;
using namespace std;

/**
 * Database used for metadata information management and storage.
 */
class MetaDB {
    MetaDB();
    void create(string id,string data);

    void writeFile(string id, string data);

    void deleteFile(string id);

    string getMeta(string id);
    string getMeta(string id, string key);

    string getStr(ptree data);
    ptree getPtree(string json);
    string getPath(string id);
    bool registered(string id);
};


#endif //THEINDESTRUCTIBLELIBRARY_METADB_H
