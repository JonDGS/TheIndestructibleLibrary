//#include "MetaDB.h"
#include "RAID/FileManager.h"
#include "RAID/RAIDManager.h"

#include <thread>
#include <string>
#include <list>

using namespace std;

int main() {
    RAIDManager rm;
    FileManager fm;

    /*
    rm.saveFile("MOON", "100100101001100111011100101101011101101101100010");
    rm.saveFile("HERO", "110110101001100110000101101101010101101101100010");
    std::this_thread::sleep_for(std::chrono::seconds(30));
    std::cout << rm.getFile("MOON") << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(30));
    rm.deleteFile("MOON");
    rm.deleteFile("HERO");
    */

    fm.createFile("TEST","/media/alvar/AVM","A DAY IN THE LIFE");

    std::cout << "TXT:" << fm.readRile("TEST","/media/alvar/AVM") << std::endl;

    fm.emptyFile("TEST","/media/alvar/AVM");

    std::cout << "TXT:" << fm.readRile("TEST","/media/alvar/AVM") << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(30));

    fm.deleteFile("TEST","/media/alvar/AVM");

    return 0;
}