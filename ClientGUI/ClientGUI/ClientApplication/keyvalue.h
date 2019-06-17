#ifndef KEYVALUE_H
#define KEYVALUE_H


#include <iostream>
using namespace std;

/**
 * Data class used for key-value pair
 */
class KeyValue {
public:
    /**
     * Default constructor
     */
    KeyValue();

    /**
     * Overloaded constructor. Recieves the key value pair
     * @param key Key to be stored
     * @param value Value to be stored
     */
    KeyValue(string key, string value);

    /**
     * Overloaded constructor. Recieves a key, a value and a operator
     * @param key Key to be stored
     * @param operator_ Operator to be stored
     * @param value Value to be stored
     */
    KeyValue(string key, string operator_, string value);

    string getKey();
    string getValue();
    string getOperator();

private:
    string key;
    string value;
    string operator_;
};


#endif // KEYVALUE_H
