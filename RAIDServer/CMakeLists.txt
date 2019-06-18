cmake_minimum_required(VERSION 3.13)
project(RAIDServer)

set(CMAKE_CXX_STANDARD 14)

add_executable(RAIDServer main.cpp Networking/Server.h Networking/Server.cpp Networking/NetPackage.h Networking/NetPackage.cpp RAIDManager/FileManager.h RAIDManager/FileManager.cpp RAIDManager/RAIDManager.h RAIDManager/RAIDManager.cpp)