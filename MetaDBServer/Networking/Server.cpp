//
// Created by jondorito on 17/06/19.
//

#include <sstream>
#include <fcntl.h>
#include "Server.h"

#define bufferMultiplier 1

#include "Server.h"
#include "../../Structure/GenericLinkedList.h"

GenericLinkedList<std::string> *convertStringToLL(std::string data, char limit) {
    std::stringstream ss(data);
    GenericLinkedList<std::string> *list = new GenericLinkedList<std::string>;

    while (ss.good()) {
        std::string substr;
        getline(ss, substr, limit);
        list->add(substr);
    }
    return list;
}

std::string convertStringToSubstr(std::string data, char limit) {
    std::stringstream ss(data);
    std::string list = "";

    while (ss.good()) {
        std::string substr;
        getline(ss, substr, limit);
        list += substr;
    }
    return list;
}

int convertCommandToInter(std::string data) {
    if (data == "ROLLBACK") {
        return ROLLBACK;
    }if (data == "getDatabase") {
        return getDatabase;
    }if (data == "setDatabase") {
        return setDatabase;
    }
    return -1;
}

void Server::closeSession(std::string user) {
    for(int i = 0; i < *currentUsers->getLength(); i++){
        std::string current = currentUsers->get(i)->getData();
        if(user == current) currentUsers->remove(i);
    }
}

bool Server::hasSession(std::string user) {
    for(int i = 0; i < *currentUsers->getLength(); i++){
        std::string current = currentUsers->get(i)->getData();
        if(user == current) return true;
    }
    return false;
}


int Server::start() {

    Server::currentUsers = new GenericLinkedList<std::string>;
    Server::users = new GenericLinkedList<std::string>;
    Server::metaController = new MetaController;


    int opt = TRUE;
    int master_socket, addrlen, new_socket, client_socket[30],
            max_clients = 30, activity, i, valread, sd;
    int max_sd;
    struct sockaddr_in address;

    char buffer[1025*bufferMultiplier];  //data buffer of 1K

    //set of socket descriptors
    fd_set readfds;

    //initialise all client_socket[] to 0 so not checked
    for (i = 0; i < max_clients; i++) {
        client_socket[i] = 0;
    }

    //create a master socket
    if ((master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    //set master socket to allow multiple connections ,
    //this is just a good habit, it will work without this
    if (setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *) &opt,
                   sizeof(opt)) < 0) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    //type of socket created
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    //bind the socket to localhost port 8888
    if (bind(master_socket, (struct sockaddr *) &address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Listener on port %d \n", PORT);

    //try to specify maximum of 3 pending connections for the master socket
    if (listen(master_socket, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    //accept the incoming connection
    addrlen = sizeof(address);
    puts("Waiting for connections ...");

    while (TRUE) {
        //clear the socket set
        FD_ZERO(&readfds);

        //add master socket to set
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;

        //add child sockets to set
        for (i = 0; i < max_clients; i++) {
            //socket descriptor
            sd = client_socket[i];

            //if valid socket descriptor then add to read list
            if (sd > 0)
                FD_SET(sd, &readfds);

            //highest file descriptor number, need it for the select function
            if (sd > max_sd)
                max_sd = sd;
        }

        //wait for an activity on one of the sockets , timeout is NULL ,
        //so wait indefinitely
        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

        if ((activity < 0) && (errno != EINTR)) {
            printf("select error");
        }

        //If something happened on the master socket ,
        //then its an incoming connection
        if (FD_ISSET(master_socket, &readfds)) {
            if ((new_socket = accept(master_socket,
                                     (struct sockaddr *) &address, (socklen_t *) &addrlen)) < 0) {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            //inform user of socket number - used in send and receive commands
            printf("New connection , socket fd is %d , ip is : %s , port : %d\n", new_socket,
                   inet_ntoa(address.sin_addr), ntohs
                           (address.sin_port));


            //add new socket to array of sockets
            for (i = 0; i < max_clients; i++) {
                //if position is empty
                if (client_socket[i] == 0) {
                    client_socket[i] = new_socket;
                    printf("Adding to list of sockets as %d\n", i);

                    break;
                }
            }
        }

        //else its some IO operation on some other socket
        for (i = 0; i < max_clients; i++) {
            sd = client_socket[i];

            if (FD_ISSET(sd, &readfds)) {
                //Check if it was for closing , and also read the
                //incoming message
                if ((valread = read(sd, buffer, (1025*bufferMultiplier)-1)) == 0) {
                    //Somebody disconnected , get his details and print
                    getpeername(sd, (struct sockaddr *) &address, \
                        (socklen_t *) &addrlen);
                    printf("Host disconnected , ip %s , port %d \n",
                           inet_ntoa(address.sin_addr), ntohs(address.sin_port));

                    //Close the socket and mark as 0 in list for reuse
                    close(sd);
                    client_socket[i] = 0;
                }

                    //Echo back the message that came in
                else {
                    std::string json = std::string(buffer, valread);

                    bool found = false;

                    std::string delimeter = "\e";
                    if(json.find(delimeter) == std::string::npos) {
                        while (!found) {
                            std::cout << "in" << std::endl;
                            fcntl(sd, F_SETFL, fcntl(sd, F_GETFL) | O_NONBLOCK);
                            int bytesLeft = recv(sd, buffer, 1025, 0);
                            std::string left = std::string(buffer, bytesLeft);
                            json += left;
                            if (left.find('/e') != std::string::npos) {
                                json = json.substr(0, json.length() - 1);
                                found = true;
                            }
                        }
                    }else{
                        json = json.substr(0, json.find(delimeter));
                    }

                    rapidjson::Document doc = NetPackage::convertToRJ_Document(json);

                    std::string command = doc["NetPackage"]["command"].GetString();

                    std::string user = doc["NetPackage"]["from"].GetString();
                    std::cout << command << std::endl;
                    int commandInt = convertCommandToInter(command);
                    std::cout << commandInt << std::endl;
                    NetPackage *netpack = new NetPackage();
                    netpack->setFrom("Server");
                    switch (commandInt) {
                        case ROLLBACK:
                        {
                            std::string current = metaController->rollBack() + "\e";
                            send(sd, current.c_str(), strlen(current.c_str()), 0);
                        }break;
                        case getDatabase: {
                            std::string current = metaController->getCurrent() + "\e";
                            send(sd, current.c_str(), strlen(current.c_str()), 0);
                        }break;
                        case setDatabase:
                        {
                            std::string update = doc["NetPackage"]["data"].GetString();
                            metaController->commit(update);
                            netpack->setCommand("UPDATED");
                            std::string final = netpack->getJSONPackage() + "\e";
                            send(sd, final.c_str(), strlen(final.c_str()), 0);
                        }break;
                        default:
                            netpack->setCommand("INVALID");
                            std::string final = netpack->getJSONPackage();
                            send(sd, final.c_str(), strlen(final.c_str()), 0);
                            break;
                    }
                }
            }
        }

        //return -2;
    }
}

bool Server::isUser(std::string user) {
    for(int i = 0; i < *users->getLength(); i++){
        std::string current = users->get(i)->getData();
        if(user == current){
            return true;
        }
    }
    return false;
}
