//
// Created by jondorito on 17/06/19.
//

#ifndef METADBSERVER_SERVER_H
#define METADBSERVER_SERVER_H


#include <stdio.h>
#include <string.h>   //strlen
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>   //close
#include <arpa/inet.h>    //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#include <iostream>
#include "NetPackage.h"
#include "../../Structure/GenericLinkedList.h"
#include "../Database/MetaController.h"

#define TRUE   1
#define FALSE  0
#define PORT 9999

enum cases{
    ROLLBACK = 0,
    getDatabase,
    setDatabase
};

class Server{
public:
    static int start();
    static bool hasSession(std::string user);
    static void closeSession(std::string user);
    static bool isUser(std::string user);
private:
    inline static GenericLinkedList<std::string>* currentUsers;
    inline static GenericLinkedList<std::string>* users;
    inline static MetaController* metaController;
};

#endif //METADBSERVER_SERVER_H
