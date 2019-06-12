//
// Created by alvar on 02/06/19.
//

#pragma once

#include <iostream>
#include <list>
#include <vector>
#include <string>
#include "FileManager.h"


class RAIDManager {
private:
    FileManager file_Manager;

    std::string RAID5;
    std::string disk_A;
    std::string disk_B;
    std::string disk_C;
    std::string disk_D;
    std::string disk_E;

    int n_Files;

    std::vector<int> IDs;

    int parity_Allocator;

public:
    RAIDManager();

    // MAIN METHODS (PUBLIC)

    /*
     * Take a string, slice it on three parts, based on this parts calculated a parity part using XOR and save the four
     * parts on the disks, in an alternating order in which the parity part is never stored on a single disk.
     */
    void saveImg(std::string file, int ID);

    /**
     * With the given ID the program should search throughout the disks for the three parts tht make up the image and
     * combine the parts to create the full image and give it back to the caller.
     * @param img_ID used to make the system know which image is being requested
     * @return the complete requested image
     */
    std::string getImg(int img_ID);

    /**
     * With a given ID the program should search throughout the disks for each part conforming the image (including the
     * parity part) and delete them.
     * @param img_ID to find the image parts to delete
     */
    void deleteImg(int img_ID);

    // SUB METHODS (PRIVATE)

    /**
     * Checks if all disks are online, remakes a disk in the case it was lost using parity.
     * @return a boolean indicating the status of the disks
     */
    bool disksOnline();

    /*
     * Creates a disk that was destroyed, uses the parity files to recreated the missing parts contained in the lost
     * disk and recalculates the all the parities that were lost during the lost of the disk.
     */
    void repairDisk();


    /**
     * Takes an image string and divides it into three mostly equals parts
     * @param image string to be split
     * @return an array of substrings of the passed image string
     */
    std::string* splitImg(std::string image); // C

    /**
     * Creates a parity part to be stored on the RAID
     * @param parts_Of_Image need to calculate the parity
     * @return the parity based on the parts of the image
     */
    std::string parityCalculator(std::string* parts_Of_Image);
};