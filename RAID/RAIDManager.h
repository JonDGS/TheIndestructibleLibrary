//
// Created by alvar on 02/06/19.
//

#pragma once

#include <iostream>
#include <vector>
#include <string>


class RAIDManager {
private:
    std::string disk_A;
    std::string disk_B;
    std::string disk_C;
    std::string disk_D;
    std::string disk_BACK_UP;
    int parity_Allocator;

public:
    RAIDManager();

    // MAIN METHODS (PUBLIC)

    /*
     * Take a string, slice it on three parts, based on this parts calculated a parity part using XOR and save the four
     * parts on the disks, in an alternating order in which the parity part is never stored on a single disk.
     */
    void saveImg(std::string file); // disksOnline() -> splitImg(Image) -> parityCalculator(parts of Image) -> Allocates all parts

    /*
     * With the given ID the program should search throughout the disks for the three parts tht make up the image and
     * combine the parts to create the full image and give it back to the caller.
     */
    std::string getImg(std::string img_ID);

    /*
     * With a given ID the program should search throughout the disks for each part conforming the image (including the
     * parity part) and delete them.
     */
    void deleteImg(std::string img_ID);

    // SUB METHODS (PRIVATE)

    /*
     * Checks if all disks are online, remakes a disk in the case it was lost using parity.
     */
    bool disksOnline();

    /*
     * Takes an image string and divides it into three mostly equals parts
     */
    std::vector<std::string> splitImg(std::string image);

    /*
     * Creates a parity part to be stored on the RAID
     */
    std::string parityCalculator(std::vector<std::string> parts_Of_Image);



};
