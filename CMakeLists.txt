cmake_minimum_required(VERSION 3.13)
project(TheIndestructibleLibrary)

set(CMAKE_CXX_STANDARD 17)

Set(CMAKE_CXX_FLAGS  -pthread)



add_executable(TheIndestructibleLibrary main.cpp Structure/GenericLinkedList.h Structure/GenericNode.h RAID/FileManager.cpp RAID/FileManager.h RAID/RAIDManager.cpp RAID/RAIDManager.h Networking/ImagePackage.h Networking/ImagePackage.cpp Networking/Server.cpp Networking/Server.h Networking/Netpackage.h Networking/Netpackage.cpp Converters/BitConverter.h Converters/BitConverter.cpp)