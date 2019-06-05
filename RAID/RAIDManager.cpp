//
// Created by alvar on 02/06/19.
//

#include "RAIDManager.h"

RAIDManager::RAIDManager() {
    this->disk_A = "/media/alvar/AVM/MyRAID5/Disk_A";
    this->disk_B = "/media/alvar/AVM/MyRAID5/Disk_B";
    this->disk_C = "/media/alvar/AVM/MyRAID5/Disk_C";
    this->disk_D = "/media/alvar/AVM/MyRAID5/Disk_D";

    this->parity_Allocator = 4;
}

void RAIDManager::saveImg(std::string file,int ID) {
    // CHECKS IF OT HAS TO REPAIR ANY DISK
    if (!this->disksOnline())
        this->repairDisk();

    // SPLITS THE FILE IN SUB PARTS
    std::vector<std::string> parts = this->splitImg(file);

    // ADDS THE PARITY AS ONE OF THESE PARTS
    parts[3] = this->parityCalculator(parts);

    /*
     * Here we should take the parts and create the respective files on the disks, using a useful ID for each file and
     * putting the parity where it belongs
     */
    int x = 0;

    if (this->parity_Allocator == 1) {
        this->file_Manager.createFile(std::to_string(ID) + "p",this->disk_A,parts[3]);
        this->parity_Allocator = 4;
    } else {
        this->file_Manager.createFile(std::to_string(ID) + "a", this->disk_A, parts[x]);
        x++;
    }

    if (this->parity_Allocator == 2) {
        this->file_Manager.createFile(std::to_string(ID) + "p",this->disk_B,parts[3]);
        this->parity_Allocator--;
    } else {
        this->file_Manager.createFile(std::to_string(ID) + "b",this->disk_B,parts[x]);
        x++;
    }

    if (this->parity_Allocator == 3) {
        this->file_Manager.createFile(std::to_string(ID) + "p",this->disk_C,parts[3]);
        this->parity_Allocator--;
    } else {
        this->file_Manager.createFile(std::to_string(ID) + "c",this->disk_C,parts[x]);
        x++;
    }

    if (this->parity_Allocator == 4) {
        this->file_Manager.createFile(std::to_string(ID) + "p",this->disk_D,parts[3]);
        this->parity_Allocator--;
    } else
        this->file_Manager.createFile(std::to_string(ID) + "d", this->disk_D,parts[x]);
}

std::string RAIDManager::getImg(std::string img_ID) {
    return std::__cxx11::string();
}

void RAIDManager::deleteImg(int img_ID) {

    if (this->file_Manager.checkLocation(this->disk_A + "/" + std::to_string(img_ID) + "a" + ".txt"))
        this->file_Manager.deleteFile(std::to_string(img_ID) + "a",this->disk_A);
    else
        this->file_Manager.deleteFile(std::to_string(img_ID) + "p",this->disk_A);

    if (this->file_Manager.checkLocation(this->disk_B + "/" + std::to_string(img_ID) + "b" + ".txt"))
        this->file_Manager.deleteFile(std::to_string(img_ID) + "b",this->disk_B);
    else
        this->file_Manager.deleteFile(std::to_string(img_ID) + "p",this->disk_B);

    if (this->file_Manager.checkLocation(this->disk_C + "/" + std::to_string(img_ID) + "c" + ".txt"))
        this->file_Manager.deleteFile(std::to_string(img_ID) + "c",this->disk_C);
    else
        this->file_Manager.deleteFile(std::to_string(img_ID) + "p",this->disk_C);

    if (this->file_Manager.checkLocation(this->disk_D + "/" + std::to_string(img_ID) + "d" + ".txt"))
        this->file_Manager.deleteFile(std::to_string(img_ID) + "d",this->disk_D);
    else
        this->file_Manager.deleteFile(std::to_string(img_ID) + "p",this->disk_D);
}

bool RAIDManager::disksOnline() {
    if (this->file_Manager.checkLocation(this->disk_A) && this->file_Manager.checkLocation(this->disk_B) &&
            this->file_Manager.checkLocation(this->disk_C) &&
            this->file_Manager.checkLocation(this->disk_D))
        return true;
    else
        return false;
}

void RAIDManager::repairDisk() {

}

std::vector<std::string> RAIDManager::splitImg(std::string image) {
    int img_Length = image.length();

    std::vector<std::string> parts(4);

    std::string part1, part2, part3;

    for (int i = 0;i < img_Length;i++) {
        if (i < img_Length / 3)
            part1 += image[i];
        if (i >= img_Length / 3 && i < (img_Length / 3) * 2)
            part2 += image[i];
        if (i >= (img_Length / 3) * 2)
            part3 += image[i];
    }

    parts[0] = part1;
    parts[1] = part2;
    parts[2] = part3;

    return parts;
}

std::string RAIDManager::parityCalculator(std::vector<std::string> parts_Of_Image) {
    return "PARITY CALCULATOR INCOMPLETED";
}

