#ifndef IMAGEPACKAGE_H
#define IMAGEPACKAGE_H


#include "netpackage.h"

//Definition of Metadata
struct Metadata {
    std::string name;
    std::string author;
    std::string date;
    std::string size;
    std::string description;
};

//Definition of enums
enum attributes{
    name = 0,
    author,
    date,
    size,
    description,
};

class ImagePackage : public NetPackage{
private :
    Metadata* metadata;
public:
    ImagePackage();
    void setMetadata(std::string name, std::string author, std::string date, std::string size, std::string description);
    std::string getAttribute(enum attributes attribute);
    std::string getJSONPackage();
    std::string metaDataToJson();
};

#endif // IMAGEPACKAGE_H
