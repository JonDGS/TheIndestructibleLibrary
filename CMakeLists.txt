cmake_minimum_required(VERSION 3.13)
project(TheIndestructibleLibrary)

set(CMAKE_CXX_STANDARD 17)

Set(CMAKE_CXX_FLAGS  -pthread)

set(Boost_INCLUDE_DIR ${CMAKE_BINARY_DIR}/../libraries/boost_1_68_0)
find_package(Boost)
IF (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
    link_directories(${Boost_LIBRARY_DIRS})
endif()

add_executable(TheIndestructibleLibrary main.cpp GenericLinkedList.h GenericNode.h MetaDB.cpp MetaDB.h DBController.cpp DBController.h RAID/FileManager.cpp RAID/FileManager.h RAID/RAIDManager.cpp RAID/RAIDManager.h)