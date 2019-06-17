//
// Created by jondorito on 15/06/19.
//

#include "BitConverter.h"


/**
     * Method convert a string of bits (previously made using an 8 bitset) to an image in the path specify by the user
     * of the method
     * @param string of bits of the image to be process
     * @param path of the destination, where the image is going to be stored in the system, example: ../Folder/image.jpg
     *  if a file with that name already exits is going to be rewritten, else a new file will be created
     */
void BitConverter::convertStringToImage(std::string bits, std::string destination) {
    char* buf;
    buf = (char*)malloc( bits.size() / 8 );
    for (int i = 0; i < bits.size() / 8; i++) // take 16 bits each time
    {
        std::string temp = bits.substr(i * 8, 8);
        std::bitset<8> temp2(temp);
        char temp3 = temp2.to_ulong();
        buf[i] = temp3;
    }
    //Open the destination file
    FILE* fp;
    fp = fopen(destination.c_str(), "wb" );
    if (!fp)
    {
        free( buf );
    }

    // Write the entire buffer to file
    if (!fwrite( buf, bits.size() / 8, 1, fp ))
    {
        free( buf );
        fclose( fp );
    }

    // All done -- return success
    fclose( fp );
    free( buf );
}

/**
     * Method converts an image store on the path given to a string of bits despite the type of data, images, text
     * documents, etc
     * @param path to the image in the system being used, example: ../Folder/image.jpg
     * @return the string with the representing bits using a bitset of 8
     */
std::string BitConverter::convertImageToStringBits(std::string path) {
    long  len;
    char* buf = NULL;
    FILE* fp  = NULL;

    // Open the source file
    fp = fopen( path.c_str(), "rb" );
    //if (!fp) return 0;

    // Get its length (in bytes)
    if (fseek( fp, 0, SEEK_END ) != 0)  // This should typically succeed
    {                                 // (beware the 2Gb limitation, though)
        fclose( fp );
        return nullptr;
    }

    len = ftell( fp );
    rewind( fp );

    // Get a buffer big enough to hold it entirely
    buf = (char*)malloc( len );
    if (!buf)
    {
        fclose( fp );
        return nullptr;
    }

    // Read the entire file into the buffer
    if (!fread( buf, len, 1, fp ))
    {
        free( buf );
        fclose( fp );
        return nullptr;
    }

    fclose( fp );

    std::cout << "The size is " << len << std::endl;

    std::string result;

    for(int i = 0; i < len; i++){
        std::bitset<8> current = std::bitset<8>(buf[i]);
        result += current.to_string();
    }

    return result;
}
