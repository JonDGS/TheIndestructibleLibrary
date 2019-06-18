cmake_minimum_required(VERSION 3.13)
project(MetaDBServer)

set(CMAKE_CXX_STANDARD 17)

add_executable(MetaDBServer main.cpp Database/KeyValue.cpp Database/KeyValue.h Database/MetaController.cpp Database/MetaController.h Networking/NetPackage.h Networking/NetPackage.cpp Networking/Server.h Networking/Server.cpp)