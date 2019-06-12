cmake_minimum_required(VERSION 3.13)
project(TheIndestructibleLibrary)

set(CMAKE_CXX_STANDARD 17)

Set(CMAKE_CXX_FLAGS  -pthread)

add_executable(TheIndestructibleLibrary main.cpp Structure/GenericLinkedList.h Structure/GenericNode.h RAID/FileManager.cpp RAID/FileManager.h RAID/RAIDManager.cpp RAID/RAIDManager.h Database/MetaController.cpp Database/MetaController.h)