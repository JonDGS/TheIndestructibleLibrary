#include "connector.h"
#include "string"
#include <sstream>

#define bufferMultiplier 1

Connector::Connector()
{
}

GenericLinkedList<std::string>* convertStringToLL(std::string data){
    std::stringstream ss(data);
    GenericLinkedList<std::string>* list = new GenericLinkedList<std::string>;

    while( ss.good() )
    {
        std::string substr;
        getline( ss, substr, ',' );
        list->add(substr);
    }
    return list;
}

bool Connector::checkLogInCredentials(std::string user, std::string password){
    std::string answer = get(user, "registerAccount", password);
    if(answer == "ACCEPTED"){
        return true;
    }return false;
}

int convertCommandToInt(std::string data) {
    enum commands {
        requestImage = 0,
        uploadImage,
        uploadMetadata,
        deleteImage,
        logIn,
        logOut,
        CHECK,
        registerAccount
    };
    if (data == "requestImage") {
            return requestImage;
    }
    if (data == "uploadImage") {
        return uploadImage;
    }
    if (data == "uploadMetadata") {
        return uploadMetadata;
    }
    if (data == "deleteImage") {
        return deleteImage;
    }
    if (data == "logIn") {
        return logIn;
    }
    if (data == "logOut") {
        return logOut;
    }
    if (data == "CHECK") {
        return CHECK;
    }
    if (data == "registerAccount") {
        return registerAccount;
    }
    return -1;
}

std::string Connector::get(std::string user, std::string request, std::string data){
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == -1)
        {
        }
        int port = 8888;
        std::string ipAddress = "127.0.0.1";

        sockaddr_in hint;
        hint.sin_family = AF_INET;
        hint.sin_port = htons(port);
        inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

        int connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));

        char buf[4096*bufferMultiplier];
        NetPackage netpack = NetPackage();
        netpack.setFrom(user);
        int requestStr = convertCommandToInt(request);
        std::cout << requestStr << std::endl;
        switch(requestStr){
        case 0:
        {

        }
            break;
        case 1:
        {
            //uploadImage
            GenericLinkedList<std::string>* bitsInfoList = convertStringToLL(data);
            std::string bitsName = bitsInfoList->get(0)->getData();
            std::string bitsLen = bitsInfoList->get(1)->getData();
            std::string bits = bitsInfoList->get(2)->getData();
            std::string bitsDataString = bitsName + ',' + bitsLen + ',' + bits;
            netpack.setData(bitsDataString);
            netpack.setCommand("uploadImage");
            std::string bitsDataInfo = netpack.getJSONPackage()  + "\e";
            send(sock, bitsDataInfo.c_str(), strlen(bitsDataInfo.c_str()), 0);
            int bytesReceived = recv(sock, buf, 4096*bufferMultiplier, 0);
            std::string preResponse = std::string(buf, bytesReceived);
            rapidjson::Document doc = netpack.convertToRJ_Document(preResponse);
            std::string response = doc["NetPackage"]["command"].GetString();
            close(sock);
            return response;
        }
            break;
        case 4:
            //LogIn
        {
           netpack.setCommand("LogIn");
           std::string final = netpack.getJSONPackage()  + "\e";
           send(sock, final.c_str(), strlen(final.c_str()), 0);
           memset(buf, 0, 4096);
           int bytesReceived = recv(sock, buf, 4096*bufferMultiplier, 0);
           std::string preResponse = std::string(buf, bytesReceived);
           rapidjson::Document doc = netpack.convertToRJ_Document(preResponse);
           std::string response = doc["NetPackage"]["command"].GetString();
           close(sock);
           return response;
        }break;
        case 6:
            //CHECK
        {
            netpack.setCommand("CHECK");
            std::string final = netpack.getJSONPackage()  + "\e";
            send(sock, final.c_str(), strlen(final.c_str()), 0);
            memset(buf, 0, 4096);
            int bytesReceived = recv(sock, buf, 4096*bufferMultiplier, 0);
            std::string preResponse = std::string(buf, bytesReceived);
            rapidjson::Document doc = netpack.convertToRJ_Document(preResponse);
            std::string response = doc["NetPackage"]["command"].GetString();
            close(sock);
            return response;
        }break;
        case 7:
        {
          netpack.setCommand(request);
          std::string final = netpack.getJSONPackage() + "\e";
          send(sock, final.c_str(), strlen(final.c_str()), 0);
          memset(buf, 0, 4096);
          int bytesReceived = recv(sock, buf, 4096*bufferMultiplier, 0);
          std::string preResponse = std::string(buf, bytesReceived);
          rapidjson::Document doc = netpack.convertToRJ_Document(preResponse);
          std::string response = doc["NetPackage"]["command"].GetString();
          close(sock);
          return response;
        }break;
        default:
            close(sock);
            break;
        }

        //close(sock);
}
