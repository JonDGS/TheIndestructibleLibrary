cmake_minimum_required(VERSION 3.13)
project(TheIndestructibleLibrary)

set(CMAKE_CXX_STANDARD 17)

Set(CMAKE_CXX_FLAGS  -pthread)



add_executable(TheIndestructibleLibrary main.cpp Structure/GenericLinkedList.h Structure/GenericNode.h "RAID Manager/FileManager.cpp" "RAID Manager/FileManager.h" "RAID Manager/RAIDManager.cpp" "RAID Manager/RAIDManager.h" Database/KeyValue.cpp Database/KeyValue.h Database/MetaController.h Database/MetaController.cpp)