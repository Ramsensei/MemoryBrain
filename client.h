#ifndef CLIENT_H
#define CLIENT_H

#include "dataStruct.cpp"

/*standard symbols */
#include <unistd.h>  

/* sockets */
#include <netdb.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <arpa/inet.h>

/* strings / errors*/
#include <errno.h>
#include <stdio.h> 
#include <string>

class Client {
private:
    static const int BUFF_SIZE = 1024;
    std::string SERVER_IP;
    const char* CHAR_IP;
    int PORT;

    int sockfd;
    struct sockaddr_in servaddr;
    
    int  len_rx, len_tx = 0;
    Data* buff_tx;
    Data* buff_rx;
public:
    Client(std::string ip, int port);
    void setMessage();
    void sendMessage();
};

#endif