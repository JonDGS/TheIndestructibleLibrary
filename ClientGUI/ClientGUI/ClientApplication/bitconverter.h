#ifndef BITCONVERTER_H
#define BITCONVERTER_H


#include <string>
#include <iostream>
#include <bitset>


class BitConverter {
public:
    /**
     * Method converts an image store on the path given to a string of bits despite the type of data, images, text
     * documents, etc
     * @param path to the image in the system being used, example: ../Folder/image.jpg
     * @return the string with the representing bits using a bitset of 8
     */
    std::string convertImageToStringBits(std::string path);
    /**
     * Method convert a string of bits (previously made using an 8 bitset) to an image in the path specify by the user
     * of the method
     * @param string of bits of the image to be process
     * @param path of the destination, where the image is going to be stored in the system, example: ../Folder/image.jpg
     *  if a file with that name already exits is going to be rewritten, else a new file will be created
     */
    void convertStringToImage(std::string bits, std::string destination);
};

#endif // BITCONVERTER_H
