//
// Created by jondorito on 17/06/19.
//

#ifndef RAIDSERVER_RAIDMANAGER_H
#define RAIDSERVER_RAIDMANAGER_H


#pragma once

#include <iostream>
#include <list>
#include <vector>
#include <string>
#include "FileManager.h"

/**
 * Manages the RAID 5, uses three methods as the interface, save, delete and get file
 */
class RAIDManager {
private:
    /**
     * Instance of the file manager class used for managing files
     */
    FileManager file_Manager;

    /**
     * Path to the RAID 5 folder
     */
    std::string RAID5;

    /**
     * Path to the disk A
     */
    std::string disk_A;

    /**
     * Path to the disk B
     */
    std::string disk_B;

    /**
     * Path to the disk C
     */
    std::string disk_C;

    /**
     * Path to the disk D
     */
    std::string disk_D;

    /**
     * Path to the disk E
     */
    std::string disk_E;

    /**
     * Counter for the umber of files in the
     */
    int n_Files;

    /**
     * A vector for storing the IDs of the stored files
     */
    std::vector<std::string> IDs;

    /**
     * A variable used for the distribution of parity files
     */
    int parity_Allocator;

    /**
     * Checks if all disks are online, remakes a disk in the case it was lost using parity.
     * @return a boolean indicating the status of the disks
     */
    bool disksOnline();

    /**
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

    /**
     * This method should take the Ids stored on the IDs vector and save them to a file in disk
     */
    void saveIDs();

    /**
     * This method should check the backup file of the IDs and complete the vector in the case the vector is lacking any
     * of the IDs stored on the backup file
     */
    void checkIDs();

public:
    /**
     * Main constructor or the class, assign and initializes al the needed members of the class
     */
    RAIDManager();

    /**
     * Take a string, slice it on three parts, based on this parts calculated a parity part using XOR and save the four
     * parts on the disks, in an alternating order in which the parity part is never stored on a single disk.
     * @param ID of the saved file
     * @param file to save
     */
    void saveFile(std::string ID, std::string file);

    /**
     * With the given ID the program should search throughout the disks for the three parts tht make up the image and
     * combine the parts to create the full image and give it back to the caller.
     * @param ID used to make the system know which image is being requested
     * @return the complete requested image
     */
    std::string getFile(std::string ID);

    /**
     * With a given ID the program should search throughout the disks for each part conforming the image (including the
     * parity part) and delete them.
     * @param ID to find the image parts to delete
     */
    void deleteFile(std::string ID);
};


#endif //RAIDSERVER_RAIDMANAGER_H
