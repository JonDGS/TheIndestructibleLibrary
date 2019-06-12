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

    //fm.createDirectory("TEST","/media/alvar/AVM/MyRAID5");
    rm.saveImg("100100101001100111011100101101011101101101100010",1);
    rm.saveImg("110110101001100110000101101101010101101101100010",2);
    //std::this_thread::sleep_for(std::chrono::seconds(30));
    std::cout << rm.getImg(1) << std::endl;
    //std::this_thread::sleep_for(std::chrono::seconds(30));
    rm.deleteImg(1);
    rm.deleteImg(2);

    return 0;
}