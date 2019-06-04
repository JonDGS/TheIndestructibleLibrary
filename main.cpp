#include "MetaDB.h"
#include "RAID/FileManager.h"

#include <thread>
#include <string>

using namespace std;

int main() {


    FileManager fm;

    fm.createFile("test1","/media/alvar/AVM/MyRAID5/Disk_A","THIS IS A TEST");

    //cout<<fm.readRile("test1","/media/alvar/AVM/MyRAID5/Disk_A")<<endl;

    //std::this_thread::sleep_for(std::chrono::seconds(10));

    //fm.deleteFile("test1","/media/alvar/AVM/MyRAID5/Disk_A");

    std::cout << fm.checkDir("/media/alvar/AVM/MyRAID5/Disk_");


    return 0;
}