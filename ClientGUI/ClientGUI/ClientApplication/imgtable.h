#ifndef IMGTABLE_H
#define IMGTABLE_H


#include <string>
#include "keyvalue.h"

using namespace std;
/**
 * Table class used to manage information of an image
 */
class ImgTable {
public:
    /**
     * Default constructor
     */
    ImgTable();
    /**
     * Overloaded class constructor. Sets the name and gallery of the image
     * @param name
     * @param gallery
     */
    ImgTable(string name, string gallery);

    /**
     * Overloaded class constructor. Can be used to set all the info of an image
     * @param name Image's name
     * @param gallery Image's name
     * @param author Author's name
     * @param year Year's name
     * @param size Size's name
     * @param description Description's name
     */
    ImgTable(string name, string gallery, string author, string year, string size, string description);

    /**
     * Returns a specified attribute
     * @param attribute Required attribute
     * @return
     */
    string getAttribute(string attribute);

    /**
     * Sets a specified attribute
     * @param data KeyValue that contains the name of the attribute and it's value
     * @return If the attribute was set successfully
     */
    bool setAttribute(KeyValue data);

    /**
     * Returns a attribute in a given format thought for console printing.
     * @param attribute Required attribute
     * @return String formated attribute
     */
    string inFormat(string attribute);

    void setName(string name);
    void setGallery(string gallery);
    void setAuthor(string author);
    void setYear(string year);
    void setSize(string size);
    void setDescription(string description);
private:
    string name, gallery, author, year,size, description;
};

#endif // IMGTABLE_H
