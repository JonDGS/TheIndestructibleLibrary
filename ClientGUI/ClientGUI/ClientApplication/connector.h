#ifndef CONNECTOR_H
#define CONNECTOR_H


#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

#include "netpackage.h"
#include "genericlinkedlist.h"

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
    static bool checkLogInCredentials(std::string user, std::string password);
};
#endif // CONNECTOR_H
