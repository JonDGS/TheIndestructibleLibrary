//
// Created by jondorito on 17/06/19.
//

#ifndef THEINDESTRUCTIBLELIBRARY_CONNECTOR_H
#define THEINDESTRUCTIBLELIBRARY_CONNECTOR_H


#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

#include "Netpackage.h"
#include "../Structure/GenericLinkedList.h"

/**
 * @brief Communication interface for server interaction.
 *
 */
class Connector
{
public:
    /**
     * @brief Default constructor.
     *
     */
    Connector();
    /**
     * @brief Method for request a linked list from the server, used for commands and gladiator information.
     * @param std::string Specifies the linked list required.
     * @return GenericLinkedList<std::string> The linked list requested.
     */
    static std::string get(std::string user, std::string request, std::string data);
    /**
     * Function that checks whether or not the user is logged into the Server;
     * @param username
     * @param password (not implemented)
     * @return whether or not the user is logged
     */
    static bool checkLogInCredentials(std::string user, std::string password);
};


#endif //THEINDESTRUCTIBLELIBRARY_CONNECTOR_H
