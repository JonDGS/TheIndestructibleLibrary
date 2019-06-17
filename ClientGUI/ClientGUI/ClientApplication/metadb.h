#ifndef METADB_H
#define METADB_H


#include <iostream>
#include "genericlinkedlist.h"
#include "genericnode.h"
#include "imgtable.h"
#include <string>
#include "keyvalue.h"
using namespace std;

/**
 * Database structure to manage image metadata. Simulates SQL database functionality
 */
class MetaDB {
public:
    /**
     * Class default constructor
     */
    MetaDB();

    /**
     * Parses a database in string form and replaces the current database with it
     * @param strDB String database
     */
    void setJSONDatabase(string strDB);

    /**
     * Inserts a new image table to the database
     * @param img Image Table
     */
    void insert(ImgTable img);

    /**
     * Returns the requested attributes of all the images of a given gallery
     * @param gallery Image gallery to extract the info
     * @param attributes Attributes requested
     * @return A linked list that contains the requested info
     */
    GenericLinkedList<string> select(string gallery,GenericLinkedList<string> attributes);

    /**
     * Returns the requested attributes of all the images of a given gallery that satisfy the condition
     * @param gallery Image gallery to extract the info
     * @param attributes Attributes requested
     * @param condition Condition specified
     * @return A linked list that contains the requested info
     */
    GenericLinkedList<string> select(string gallery,GenericLinkedList<string> attributes, KeyValue condition);

    /**
     * Updates the information specified of a given gallery under a given condition in the database
     * @param gallery Gallery specified
     * @param values Information to update
     * @param condition Given condition
     */
    void update(string gallery, GenericLinkedList<KeyValue> values, KeyValue condition);

    /**
     * Deletes all the elements in the database that fulfill a given condition
     * @param gallery Gallery specified
     * @param condition Given condition
     */
    void delete_(string gallery, KeyValue condition);

    /**
     * Returns the database in form of a string in JSON format
     * @return JSON format database
     */
    string toJSON();

    /**
     * Prints the database info in console
     */
    void print();

    /**
     * Returns the names of the images whose metadata was deleted
     * @return
     */
    GenericLinkedList<string> getToDelete();

    /**
     * Returns the names of all the images inside a gallery
     * @param gallery Gallery specified
     * @return A linked list that contains the required names
     */
    GenericLinkedList<string> getNames(string gallery);

    /**
     * Checks if a gallery is registered
     * @param gallery Gallery to verify
     * @return boolean true if it exists
     */
    bool exists(string gallery);

private:
    /**
    * Verifies if an image table satisfies a condition
    * @param img Image to verify
    * @param condition Condition to verify
    * @return If the image satisfies the condition
    */
    bool meetsCondition(ImgTable img, KeyValue condition);
    GenericLinkedList<ImgTable> *db;
    GenericLinkedList<string> *toDelete;
};


#endif // METADB_H
