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
#include <queue>
#include <unordered_map>
#include <algorithm>
#include "KeyValue.h"
#include "../Structure/GenericLinkedList.h"
using namespace std;

/**
 * Node basic structure used for Huffman Algorithm
 */
struct Node{
    char ch;
    int freq;
    Node *left, *right;
};

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
     * Applies Huffman algorithm and returns the compressed json and his tree values
     * @param json JSON to compress
     * @return
     */
    string getCompressed(string text);

    /**
     * Uncompresses a string with Huffman algorithm
     * @param text JSON formatted compressed string and his Huffman codes
     * @return Uncompressed string
     */
    string getUncompressed(string text);

    /**
     * Writes currentDB and previousDB to their respective json file
     */
    void writeJSONS();

    /**
    * Creates and returns a node
    * @param ch Characters hold
    * @param freq Frequency linked to the character
    * @param left Reference to a left node
    * @param right Reference to a right node
    * @return
    */
    Node* getNode(char ch, int freq, Node* left, Node* right);

    /**
     * Traverses a tree out of a root node and fills a map with the characters Huffman codes
     * @param root Tree huffman node
     * @param str Initial Huffman code value
     * @param map Map to be filled
     */
    void fillHuffmanCodes(Node* root, string str, GenericLinkedList<KeyValue> &map);

    string currentDB;
    string previousDB;
};


#endif //THEINDESTRUCTIBLELIBRARY_METACONTROLLER_H
