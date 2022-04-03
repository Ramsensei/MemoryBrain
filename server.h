#ifndef SERVER_H
#define SERVER_H

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


class Server{
    private:
        static const int BUFF_SIZE = 100;
        static const int BACKLOG = 5;

        std::string SERVER_IP;
        const char* CHAR_IP;
        int PORT;

        int sockfd, connfd;
        unsigned int len;
        struct sockaddr_in servaddr, client;
        
        int  len_rx, len_tx = 0;
        char buff_tx[BUFF_SIZE] = "Hello client, I am the server";
        char buff_rx[BUFF_SIZE];
    
    public:
        Server(std::string ip, int port);
        void start();

};

#endif