//
// Created by jondorito on 05/06/19.
//

#include "ImagePackage.h"

void ImagePackage::setMetadata(std::string name, std::string author, std::string date, std::string size, std::string description) {
    this->metadata->name = name;
    this->metadata->author = author;
    this->metadata->date = date;
    this->metadata->size = size;
    this->metadata->description = description;
}

ImagePackage::ImagePackage() : NetPackage(){

}

std::string ImagePackage::getJSONPackage() {
    rapidjson::Document docu;

    docu.SetObject();

    rapidjson::Document::AllocatorType& allocator = docu.GetAllocator();

    rapidjson::Value object(rapidjson::kObjectType);
    object.AddMember("from", this->getFrom(), allocator);
    object.AddMember("data", this->getData(), allocator);
    object.AddMember("command", this->getcommand(), allocator);
    object.AddMember("metadata", this->metaDataToJson(), allocator);
    docu.AddMember("NetPackage", object, allocator);

    rapidjson::StringBuffer strbuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
    docu.Accept(writer);

    return strbuf.GetString();
}

std::string ImagePackage::getAttribute(enum attributes attribute) {
    switch(attribute){
        case name:
            return this->metadata->name;
        case author:
            return this->metadata->author;
        case date:
            return this->metadata->date;
        case size:
            return this->metadata->size;
        case description:
            return this->metadata->description;
        default:
            return nullptr;
    }
}

std::string ImagePackage::metaDataToJson() {
    rapidjson::Document docu;

    docu.SetObject();

    rapidjson::Document::AllocatorType& allocator = docu.GetAllocator();

    rapidjson::Value object(rapidjson::kObjectType);
    object.AddMember("name", this->metadata->name, allocator);
    object.AddMember("author", this->metadata->author, allocator);
    object.AddMember("date", this->metadata->date, allocator);
    object.AddMember("size", this->metadata->size, allocator);
    object.AddMember("description", this->metadata->description, allocator);
    docu.AddMember("MetaData", object, allocator);

    rapidjson::StringBuffer strbuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
    docu.Accept(writer);

    return strbuf.GetString();
}
