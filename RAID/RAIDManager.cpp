//
// Created by alvar on 02/06/19.
//

#include "RAIDManager.h"

RAIDManager::RAIDManager() {
    this->disk_A = "/media/alvar/AVM/MyRAID5/Disk_A";
    this->disk_B = "/media/alvar/AVM/MyRAID5/Disk_B";
    this->disk_C = "/media/alvar/AVM/MyRAID5/Disk_C";
    this->disk_D = "/media/alvar/AVM/MyRAID5/Disk_D";
    this->disk_BACK_UP = "/media/alvar/AVM/MyRAID5/Back_Up_Disk";

    this->parity_Allocator = 4;
}

void RAIDManager::saveImg(std::string file) {

}

std::string RAIDManager::getImg(std::string img_ID) {
    return std::__cxx11::string();
}

void RAIDManager::deleteImg(std::string img_ID) {

}

bool RAIDManager::disksOnline() {
    return false;
}

std::vector<std::string> RAIDManager::splitImg(std::string image) {
    int img_Length = image.length();

    std::vector<std::string> parts;

    for (int i = 0;i < img_Length;i++) {
        if (i < (img_Length/3))
            parts[0] += image[i];
        if (i > img_Length/3 && i < (img_Length/3) * 2)
            parts[1] += image[i];
        if (i > (img_Length/3) * 2)
            parts[2] += image[i];
    }
    return parts;
}

std::string RAIDManager::parityCalculator(std::vector<std::string> parts_Of_Image) {
    return std::__cxx11::string();
}
