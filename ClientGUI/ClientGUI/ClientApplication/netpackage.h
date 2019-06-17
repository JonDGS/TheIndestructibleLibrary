#ifndef NETPACKAGE_H
#define NETPACKAGE_H


#include <string>
#include "libraries/rapidjson/document.h"
#include "libraries/rapidjson/writer.h"
#include "libraries/rapidjson/stringbuffer.h"

/**
 * @brief The NetPackage class Class used for formating server messages.
 */
class NetPackage {
private:
    std::string from = "unassigned";
    std::string command = "NONE";
    std::string data =  "NONE";
    std::string type = "DEFAULT";
public:
    /**
     * @brief NetPackage Default constructor.
     */
    NetPackage();

    /**
     * This function is in charge of constructing the json string
     * @return Json String of this NetPackage object
     */
    std::string getJSONPackage();

    /**
     * Gets the author of the package
     * @return The author of this package
     */
    std::string getFrom();

    /**
     * Gets the data of the Package
     * @return Data of the package
     */
    std::string getData();

    /**
     * Gets the command associated with the package
     * @return Command of this package
     */
    std::string getcommand();

    /**
     * Sets the author of the package
     * @param author
     */
    void setFrom(std::string);

    /**
     * Sets the data for the package
     * @param data ( as a string )
     */
    void setData(std::string);

    /**
     * Sets the command for the package
     * @param command
     */
    void setCommand(std::string);

    /**
     * @brief convertToRJ_Document Converts JString to a Rapid JSON Document.
     * @return A Rapid JSON version of the string.
     */
    static rapidjson::Document convertToRJ_Document(std::string);
};

#endif // NETPACKAGE_H
