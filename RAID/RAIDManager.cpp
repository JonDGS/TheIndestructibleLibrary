//
// Created by alvar on 02/06/19.
//

#include "RAIDManager.h"

RAIDManager::RAIDManager() {
    this->RAID5 = "/media/alvar/AVM/RAID5";

    this->disk_A = "/media/alvar/AVM/RAID5/Disk_A";
    this->disk_B = "/media/alvar/AVM/RAID5/Disk_B";
    this->disk_C = "/media/alvar/AVM/RAID5/Disk_C";
    this->disk_D = "/media/alvar/AVM/RAID5/Disk_D";
    this->disk_E = "/media/alvar/AVM/RAID5/Disk_E";

    this->n_Files = 0;

    this->parity_Allocator = 5;

    // CHECKS IF IT HAS TO REPAIR ANY DISK
    if (!this->disksOnline())
        this->repairDisk();

    // CHECKS FOR ANY ID ON THE BACKUP
    checkIDs();
}

/**
 * Take a string, slice it on three parts, based on this parts calculated a parity part using XOR and save the four
 * parts on the disks, in an alternating order in which the parity part is never stored on a single disk.
 * @param ID of the saved file
 * @param file to save
 */
void RAIDManager::saveFile(std::string ID, std::string file) {
    // CHECKS IF OT HAS TO REPAIR ANY DISK
    if (!this->disksOnline())
        this->repairDisk();

    // ADDS THE ID TO THE IDs LIST
    this->IDs.push_back(ID);

    // SPLITS THE FILE IN SUB PARTS
    std::string* parts = this->splitImg(file);

    // ADDS THE PARITY AS ONE OF THESE PARTS
    parts[4] = this->parityCalculator(parts);

    // CREATES THE SUB FILES BASED ON THE PARTS OF THE PASSED FILED, INCLUDING PARITY
    int x = 0;

    if (this->parity_Allocator == 1) {
        this->file_Manager.createFile(ID + "p",this->disk_A,parts[4]);
        this->parity_Allocator = 5;
    } else {
        this->file_Manager.createFile(ID + "a", this->disk_A, parts[x]);
        x++;
    }
    if (this->parity_Allocator == 2) {
        this->file_Manager.createFile(ID + "p",this->disk_B,parts[4]);
        this->parity_Allocator--;
    } else {
        this->file_Manager.createFile(ID + "b",this->disk_B,parts[x]);
        x++;
    }
    if (this->parity_Allocator == 3) {
        this->file_Manager.createFile(ID + "p",this->disk_C,parts[4]);
        this->parity_Allocator--;
    } else {
        this->file_Manager.createFile(ID + "c",this->disk_C,parts[x]);
        x++;
    }
    if (this->parity_Allocator == 4) {
        this->file_Manager.createFile(ID + "p",this->disk_D,parts[4]);
        this->parity_Allocator--;
    } else {
        this->file_Manager.createFile(ID + "d",this->disk_D,parts[x]);
        x++;
    }
    if (this->parity_Allocator == 5) {
        this->file_Manager.createFile(ID + "p",this->disk_E,parts[4]);
        this->parity_Allocator--;
    } else
        this->file_Manager.createFile(ID + "e", this->disk_E,parts[x]);

    // ADDS ONE TO THE FILES COUNTER
    this->n_Files++;

    // UPDATES THE BACKUP IDs
    saveIDs();
}

/**
 * Gives the full file string of the passed ID
 * @param ID to know which parts combine
 * @return The complete image string
 */
std::string RAIDManager::getFile(std::string ID) {
    // CHECKS IF OT HAS TO REPAIR ANY DISK
    if (!this->disksOnline())
        this->repairDisk();

    // DECLARES THE STRING TO RETURN
    std::string data;

    // TAKES ALL THE PARTS AND COMBINES THEM
    data += this->file_Manager.readRile(ID + "a",this->disk_A);
    data += this->file_Manager.readRile(ID + "b",this->disk_B);
    data += this->file_Manager.readRile(ID + "c",this->disk_C);
    data += this->file_Manager.readRile(ID + "d",this->disk_D);
    data += this->file_Manager.readRile(ID + "e",this->disk_D);

    return data;
}

/**
 * Deletes all the associated parts of an image by using its ID
 * @param ID to know which parts to delete
 */
void RAIDManager::deleteFile(std::string ID) {
    // CHECKS IF OT HAS TO REPAIR ANY DISK
    if (!this->disksOnline())
        this->repairDisk();

    // DELETES ALL THE PARTS ASSOCIATED TO THE PASSED ID
    if (this->file_Manager.checkLocation(this->disk_A + "/" + ID + "a" + ".txt"))
        this->file_Manager.deleteFile(ID + "a",this->disk_A);
    else
        this->file_Manager.deleteFile(ID + "p",this->disk_A);

    if (this->file_Manager.checkLocation(this->disk_B + "/" + ID + "b" + ".txt"))
        this->file_Manager.deleteFile(ID + "b",this->disk_B);
    else
        this->file_Manager.deleteFile(ID + "p",this->disk_B);

    if (this->file_Manager.checkLocation(this->disk_C + "/" + ID + "c" + ".txt"))
        this->file_Manager.deleteFile(ID + "c",this->disk_C);
    else
        this->file_Manager.deleteFile(ID + "p",this->disk_C);

    if (this->file_Manager.checkLocation(this->disk_D + "/" + ID + "d" + ".txt"))
        this->file_Manager.deleteFile(ID + "d",this->disk_D);
    else
        this->file_Manager.deleteFile(ID + "p",this->disk_D);

    if (this->file_Manager.checkLocation(this->disk_E + "/" + ID + "e" + ".txt"))
        this->file_Manager.deleteFile(ID + "e",this->disk_E);
    else
        this->file_Manager.deleteFile(ID + "p",this->disk_E);

    // DECREASE THE FILE COUNTER
    this->n_Files--;

    // DELETES THE ID FROM THE IDs LIST
    for(int i = 0;i < this->IDs.size();i++) {
        if (this->IDs[i] == ID)
            this->IDs.erase(this->IDs.begin() + i);
    }

    // UPDATES THE BACKUP IDs
    saveIDs();
}

/**
 * Checks if the disks are avalible
 * @return state the disks
 */
bool RAIDManager::disksOnline() {
    return this->file_Manager.checkLocation(this->disk_A) && this->file_Manager.checkLocation(this->disk_B) &&
           this->file_Manager.checkLocation(this->disk_C) && this->file_Manager.checkLocation(this->disk_D) &&
           this->file_Manager.checkLocation(this->disk_E);
}

/**
 * Creates a disk that was destroyed, uses the parity files to recreated the missing parts contained in the lost
 * disk and recalculates the all the parities that were lost during the lost of the disk.
 */
void RAIDManager::repairDisk() {
    std::string lost_Disk_Location;
    std::string lost_Disk_Name;
    char lost_File_Char;

    // CHECK WHICH DISK FAILED
    if (!this->file_Manager.checkLocation(this->disk_A)) {
        lost_Disk_Location = this->disk_A;
        lost_Disk_Name = "Disk_A";
        lost_File_Char = 'a';
    }
    if (!this->file_Manager.checkLocation(this->disk_B)) {
        lost_Disk_Location = this->disk_B;
        lost_Disk_Name = "Disk_B";
        lost_File_Char = 'b';
    }
    if (!this->file_Manager.checkLocation(this->disk_C)) {
        lost_Disk_Location = this->disk_C;
        lost_Disk_Name = "Disk_C";
        lost_File_Char = 'c';
    }
    if (!this->file_Manager.checkLocation(this->disk_D)) {
        lost_Disk_Location = this->disk_D;
        lost_Disk_Name = "Disk_D";
        lost_File_Char = 'd';
    }
    if (!this->file_Manager.checkLocation(this->disk_E)) {
        lost_Disk_Location = this->disk_E;
        lost_Disk_Name = "Disk_E";
        lost_File_Char = 'e';
    }

    // CREATE THE LOST DISK
    this->file_Manager.createDirectory(lost_Disk_Name, this->RAID5);

    // CHECK IF FILES WERE LOST
    if (n_Files == 0)
        return;

    // CHECK THE IDS OF THE LOST FILES
    // BASED ON THE IDS TAKE ALL REMAINING PARTS OF THAT IMAGE AN CALCULATE THE LOST FILE
    // CREATE THIS NEW FILE THAT WILL REPLACE THE LOST ONE WITH THE CORRECT NAME

    for (int i = 0; i < this->IDs.size(); i++) {

        // NAME TO CREATE THE NEW FILE
        std::string lost_File_Name = this->IDs[i];

        std::string parts[4];

        std::string lost_File_Data;

        // WE CHECK IF THE PARITY IS OUTSIDE OF THE LOST DISK, TO KNOW WHICH FULL NAME THE LOST FILE HAD
        if (this->file_Manager.checkLocation(this->disk_A + "/" + this->IDs[i] + "p" + ".txt") ||
            this->file_Manager.checkLocation(this->disk_B + "/" + this->IDs[i] + "p" + ".txt") ||
            this->file_Manager.checkLocation(this->disk_C + "/" + this->IDs[i] + "p" + ".txt") ||
            this->file_Manager.checkLocation(this->disk_D + "/" + this->IDs[i] + "p" + ".txt") ||
            this->file_Manager.checkLocation(this->disk_E + "/" + this->IDs[i] + "p" + ".txt"))
            lost_File_Name += lost_File_Char;
        else
            lost_File_Name += 'p';

        if (lost_Disk_Name == "Disk_A") { // CASE WERE DISK_A WAS LOST
            if (this->file_Manager.checkLocation(this->disk_B + "/" + IDs[i] + 'b' + ".txt"))
                parts[0] = this->file_Manager.readRile(IDs[i] + 'b', this->disk_B);
            else
                parts[0] = this->file_Manager.readRile(IDs[i] + 'p', this->disk_B);
            if (this->file_Manager.checkLocation(this->disk_C + "/" + IDs[i] + 'c' + ".txt"))
                parts[1] = this->file_Manager.readRile(IDs[i] + 'c', this->disk_C);
            else
                parts[1] = this->file_Manager.readRile(IDs[i] + 'p', this->disk_C);
            if (this->file_Manager.checkLocation(this->disk_D + "/" + IDs[i] + 'd' + ".txt"))
                parts[2] = this->file_Manager.readRile(IDs[i] + 'd', this->disk_D);
            else
                parts[2] = this->file_Manager.readRile(IDs[i] + 'p', this->disk_D);
            if (this->file_Manager.checkLocation(this->disk_E + "/" + IDs[i] + 'e' + ".txt"))
                parts[3] = this->file_Manager.readRile(IDs[i] + 'e', this->disk_E);
            else
                parts[3] = this->file_Manager.readRile(IDs[i] + 'p', this->disk_E);
        }

        if (lost_Disk_Name == "Disk_B") { // CASE WERE DISK_A WAS LOST
            if (this->file_Manager.checkLocation(this->disk_A + "/" + IDs[i] + 'a' + ".txt"))
                parts[0] = this->file_Manager.readRile(IDs[i] + 'a', this->disk_A);
            else
                parts[0] = this->file_Manager.readRile(IDs[i] + 'p', this->disk_A);
            if (this->file_Manager.checkLocation(this->disk_C + "/" + IDs[i] + 'c' + ".txt"))
                parts[1] = this->file_Manager.readRile(IDs[i] + 'c', this->disk_C);
            else
                parts[1] = this->file_Manager.readRile(IDs[i] + 'p', this->disk_C);
            if (this->file_Manager.checkLocation(this->disk_D + "/" + IDs[i] + 'd' + ".txt"))
                parts[2] = this->file_Manager.readRile(IDs[i] + 'd', this->disk_D);
            else
                parts[2] = this->file_Manager.readRile(IDs[i] + 'p', this->disk_D);
            if (this->file_Manager.checkLocation(this->disk_E + "/" + IDs[i] + 'e' + ".txt"))
                parts[3] = this->file_Manager.readRile(IDs[i] + 'e', this->disk_E);
            else
                parts[3] = this->file_Manager.readRile(IDs[i] + 'p', this->disk_E);
        }

        if (lost_Disk_Name == "Disk_C") { // CASE WERE DISK_A WAS LOST
            if (this->file_Manager.checkLocation(this->disk_A + "/" + IDs[i] + 'a' + ".txt"))
                parts[0] = this->file_Manager.readRile(IDs[i] + 'a', this->disk_A);
            else
                parts[0] = this->file_Manager.readRile(IDs[i] + 'p', this->disk_A);
            if (this->file_Manager.checkLocation(this->disk_B + "/" + IDs[i] + 'b' + ".txt"))
                parts[1] = this->file_Manager.readRile(IDs[i] + 'b', this->disk_B);
            else
                parts[1] = this->file_Manager.readRile(IDs[i] + 'p', this->disk_B);
            if (this->file_Manager.checkLocation(this->disk_D + "/" + IDs[i] + 'd' + ".txt"))
                parts[2] = this->file_Manager.readRile(IDs[i] + 'd', this->disk_D);
            else
                parts[2] = this->file_Manager.readRile(IDs[i] + 'p', this->disk_D);
            if (this->file_Manager.checkLocation(this->disk_E + "/" + IDs[i] + 'e' + ".txt"))
                parts[3] = this->file_Manager.readRile(IDs[i] + 'e', this->disk_E);
            else
                parts[3] = this->file_Manager.readRile(IDs[i] + 'p', this->disk_E);
        }

        if (lost_Disk_Name == "Disk_D") { // CASE WERE DISK_A WAS LOST
            if (this->file_Manager.checkLocation(this->disk_A + "/" + IDs[i] + 'a' + ".txt"))
                parts[0] = this->file_Manager.readRile(IDs[i] + 'a', this->disk_A);
            else
                parts[0] = this->file_Manager.readRile(IDs[i] + 'p', this->disk_A);
            if (this->file_Manager.checkLocation(this->disk_B + "/" + IDs[i] + 'b' + ".txt"))
                parts[1] = this->file_Manager.readRile(IDs[i] + 'b', this->disk_B);
            else
                parts[1] = this->file_Manager.readRile(IDs[i] + 'p', this->disk_B);
            if (this->file_Manager.checkLocation(this->disk_C + "/" + IDs[i] + 'c' + ".txt"))
                parts[2] = this->file_Manager.readRile(IDs[i] + 'c', this->disk_C);
            else
                parts[2] = this->file_Manager.readRile(IDs[i] + 'p', this->disk_C);
            if (this->file_Manager.checkLocation(this->disk_E + "/" + IDs[i] + 'e' + ".txt"))
                parts[3] = this->file_Manager.readRile(IDs[i] + 'e', this->disk_E);
            else
                parts[3] = this->file_Manager.readRile(IDs[i] + 'p', this->disk_E);
        }

        if (lost_Disk_Name == "Disk_E") { // CASE WERE DISK_A WAS LOST
            if (this->file_Manager.checkLocation(this->disk_E + "/" + IDs[i] + 'a' + ".txt"))
                parts[0] = this->file_Manager.readRile(IDs[i] + 'a', this->disk_A);
            else
                parts[0] = this->file_Manager.readRile(IDs[i] + 'p', this->disk_A);
            if (this->file_Manager.checkLocation(this->disk_B + "/" + IDs[i] + 'b' + ".txt"))
                parts[1] = this->file_Manager.readRile(IDs[i] + 'b', this->disk_B);
            else
                parts[1] = this->file_Manager.readRile(IDs[i] + 'p', this->disk_B);
            if (this->file_Manager.checkLocation(this->disk_C + "/" + IDs[i] + 'c' + ".txt"))
                parts[2] = this->file_Manager.readRile(IDs[i] + 'c', this->disk_C);
            else
                parts[2] = this->file_Manager.readRile(IDs[i] + 'p', this->disk_C);
            if (this->file_Manager.checkLocation(this->disk_D + "/" + IDs[i] + 'd' + ".txt"))
                parts[3] = this->file_Manager.readRile(IDs[i] + 'd', this->disk_D);
            else
                parts[3] = this->file_Manager.readRile(IDs[i] + 'p', this->disk_D);

        }

        lost_File_Data = parityCalculator(parts);

        this->file_Manager.createFile(lost_File_Name,lost_Disk_Location,lost_File_Data);
    }
}

/**
 * Splits the image string into four parts
 * @param image string to divide
 * @return string array with the image string sub parts
 */
std::string* RAIDManager::splitImg(std::string image) {
    int img_Length = image.length();

    std::string* parts = new std::string[5];

    std::string part_1, part_2, part_3, part_4;

    for (int i = 0;i < img_Length;i++) {
        if ((i + 1) > (img_Length / 4) * 3) {
            part_4 += image[i];
            continue;
        }
        if ((i + 1) > (img_Length / 2)) {
            part_3 += image[i];
            continue;
        }
        if ((i + 1) > (img_Length / 4)) {
            part_2 += image[i];
            continue;
        }
        else
            part_1 += image[i];
    }

    parts[0] = part_1;
    parts[1] = part_2;
    parts[2] = part_3;
    parts[3] = part_4;

    return parts;
}

/**
 * Based on a set of binary strings calculate the parity of those parts
 * @param parts_Of_Image to use to calculate parity
 * @return parity of the parts
 */
std::string RAIDManager::parityCalculator(std::string* parts_Of_Image) {
    std::string parity;

    std::string* part_A = &parts_Of_Image[0];
    std::string* part_B = &parts_Of_Image[1];
    std::string* part_C = &parts_Of_Image[2];
    std::string* part_D = &parts_Of_Image[3];

    for (int i = 0;i < parts_Of_Image[0].length();i++) {

        char first = (*part_A)[i];
        char second = (*part_B)[i];
        char third = (*part_C)[i];
        char fourth = (*part_D)[i];

        bool a = first == '1';
        bool b = second == '1';
        bool c = third == '1';
        bool d = fourth == '1';

        parity += std::to_string(((a ^ b) ^ c) ^ d);
    }
    return parity;
}

void RAIDManager::saveIDs() {
    // EMPTIES THE BACKUP FILE
    this->file_Manager.emptyFile("IDs",this->RAID5);

    // IF THERE ARE NO IDs TO STORE STOPS
    if (this->IDs.empty())
        return;

    std::string backup_IDs;

    for (int i = 0;i < this->IDs.size();i++)
        backup_IDs += this->IDs[i] + "/";

    this->file_Manager.addData("IDs",this->RAID5,backup_IDs);
}

void RAIDManager::checkIDs() {
    if (this->file_Manager.readRile("IDs",this->RAID5).length() == 0)
        return;

    std::string backup = this->file_Manager.readRile("IDs",this->RAID5);

    std::string ID;

    bool word_Zone;

    for (int i = 0;i < backup.length();i++) {
        word_Zone = backup[i] != '/';

        if (word_Zone)
            ID += backup[i];

        else {
            this->IDs.push_back(ID);
            ID.clear();
        }
    }
}

