#include "MetaDB.h"
#include "RAID/FileManager.h"
#include "RAID/RAIDManager.h"

#include <thread>
#include <string>

using namespace std;

int main() {

    /*
    FileManager fm;

    fm.createFile("test1","/media/alvar/AVM/MyRAID5/Disk_A","THIS IS A TEST");

    //cout<<fm.readRile("test1","/media/alvar/AVM/MyRAID5/Disk_A")<<endl;

    //std::this_thread::sleep_for(std::chrono::seconds(10));

    //fm.deleteFile("test1","/media/alvar/AVM/MyRAID5/Disk_A");

    std::cout << fm.checkDir("/media/alvar/AVM/MyRAID5/Disk_");
    */

    RAIDManager rm;
    rm.saveImg("123456789123456789123456789",1);
    rm.saveImg("123456789123456789123456789",2);
    rm.saveImg("123456789123456789123456789",3);
    rm.saveImg("123456789123456789123456789",4);
    rm.saveImg("123456789123456789123456789",5);


    return 0;
}