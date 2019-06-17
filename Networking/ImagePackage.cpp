//
// Created by jondorito on 05/06/19.
//

#include "ImagePackage.h"

void ImagePackage::setMetadata(std::string metadata) {
    this->metadata = metadata;
}

std::string ImagePackage::getMetadata() {
    return this->metadata;
}

ImagePackage::ImagePackage() : NetPackage(){
    this->metadata = "NONE";
}

std::string ImagePackage::getJSONPackage() {
    rapidjson::Document docu;

    docu.SetObject();

    rapidjson::Document::AllocatorType& allocator = docu.GetAllocator();

    rapidjson::Value object(rapidjson::kObjectType);
    object.AddMember("from", this->getFrom(), allocator);
    object.AddMember("data", this->getData(), allocator);
    object.AddMember("command", this->getcommand(), allocator);
    //object.AddMember("type", this->type, allocator);
    object.AddMember("metadata", this->getMetadata(), allocator);
    docu.AddMember("NetPackage", object, allocator);

    rapidjson::StringBuffer strbuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
    docu.Accept(writer);

    return strbuf.GetString();
}
