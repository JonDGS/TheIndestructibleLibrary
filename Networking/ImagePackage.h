//
// Created by jondorito on 05/06/19.
//

#ifndef THEINDESTRUCTIBLELIBRARY_IMAGEPACKAGE_H
#define THEINDESTRUCTIBLELIBRARY_IMAGEPACKAGE_H


#include "Netpackage.h"

class ImagePackage : public NetPackage{
private :
    std::string metadata = "NONE";
public:
    ImagePackage();
    std::string getMetadata();
    void setMetadata(std::string metadata);
    std::string getJSONPackage();
};


#endif //THEINDESTRUCTIBLELIBRARY_IMAGEPACKAGE_H
