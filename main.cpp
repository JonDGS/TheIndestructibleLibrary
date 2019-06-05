#include "MetaDB.h"
#include "RAID/FileManager.h"
#include "RAID/RAIDManager.h"

#include <thread>
#include <string>

using namespace std;

int main() {
    RAIDManager rm;
    FileManager fm;
    /*


    fm.createFile("test1","/media/alvar/AVM/MyRAID5/Disk_A","THIS IS A TEST");

    //cout<<fm.readRile("test1","/media/alvar/AVM/MyRAID5/Disk_A")<<endl;

    //std::this_thread::sleep_for(std::chrono::seconds(10));

    //fm.deleteFile("test1","/media/alvar/AVM/MyRAID5/Disk_A");

    std::cout << fm.checkLocation("/media/alvar/AVM/MyRAID5/Disk_");
    */

    /*
    rm.saveImg("123456789123456789123456789",1);
    rm.saveImg("123456789123456789123456789",2);
    rm.saveImg("123456789123456789123456789",3);
    rm.saveImg("123456789123456789123456789",4);
    rm.saveImg("123456789123456789123456789",5);
    rm.saveImg("Oh boi i just hope this works",6);
    rm.saveImg("Like pls work i wanna go to eat",7);
    rm.saveImg("pls pls work mah machine i believe in you",8);

    std::this_thread::sleep_for(std::chrono::seconds(4));
    rm.deleteImg(1);

    std::this_thread::sleep_for(std::chrono::seconds(2));
    rm.deleteImg(2);

    std::this_thread::sleep_for(std::chrono::seconds(2));
    rm.deleteImg(3);

    std::this_thread::sleep_for(std::chrono::seconds(2));
    rm.deleteImg(4);

    std::this_thread::sleep_for(std::chrono::seconds(2));
    rm.deleteImg(5);
    */

    //fm.createDirectory("TEST","/media/alvar/AVM/MyRAID5");

    rm.saveImg("Oh boi i just hope this works Like pls work i wanna go to sleep pls pls work mah machine i believe in you",1);

    std::this_thread::sleep_for(std::chrono::seconds(15));

    std::cout << rm.getImg(1);

    rm.deleteImg(1);

    return 0;
}