#include "MetaDB.h"
#include "RAID/FileManager.h"

using namespace std;

int main() {

    FileManager fm;
    fm.createFile("test1","/media/alvar/AVM/MyRAID5/Disk_A","THIS IS A TEST");

    cout<<"all good"<<endl;


    return 0;
}