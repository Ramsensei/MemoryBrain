#include "server.h"

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
#include <string.h>

#define IP_SERV_ADDR "192.168.0.39"

Server::Server(std::string ip, int port){
    SERVER_IP = ip;
    PORT = port;
    len = sizeof(client);
    CHAR_IP = const_cast<char*>(SERVER_IP.c_str());

    buff_tx = (Data *) malloc(sizeof(Data));
    buff_rx = (Data *) malloc(sizeof(Data));

    buff_tx->img = 'c';

    /* socket creation */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        fprintf(stderr, "[SERVER-error]: socket creation failed. %d: %s \n", errno, strerror( errno ));
        return; 
    } else printf("[SERVER]: Socket successfully created..\n");

    /* clear structure */
    memset(&servaddr, 0, sizeof(servaddr));
  
    /* assign IP, SERV_PORT, IPV4 */
    servaddr.sin_family      = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr(CHAR_IP);
    servaddr.sin_port        = htons(PORT);

    /* Bind socket */
    if ((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) {
        fprintf(stderr, "[SERVER-error]: socket bind failed. %d: %s \n", errno, strerror( errno ));
        return;
    } else printf("[SERVER]: Socket successfully binded \n");
  
    /* Listen */
    if ((listen(sockfd, BACKLOG)) != 0) {
        fprintf(stderr, "[SERVER-error]: socket listen failed. %d: %s \n", errno, strerror( errno ));
        return;
    } else printf("[SERVER]: Listening on SERV_PORT %d \n\n", ntohs(servaddr.sin_port) );  
    this->start(); 
                
}

void Server::start(){
    while(1) {
        connfd = accept(sockfd, (struct sockaddr *)&client, &len); 
        if (connfd < 0) { 
            fprintf(stderr, "[SERVER-error]: connection not accepted. %d: %s \n", errno, strerror( errno ));
            return;
        }
        else {              
            while(1) { /* read data from a client socket till it is closed */
                /* read client message, copy it into buffer */
                len_rx = read(connfd, buff_rx, sizeof(buff_rx));  
                
                if(len_rx == -1) {
                    fprintf(stderr, "[SERVER-error]: connfd cannot be read. %d: %s \n", errno, strerror( errno ));
                }
                else if(len_rx == 0) { /* if length is 0 client socket closed, then exit */
                    printf("[SERVER]: client socket closed \n\n");
                    close(connfd);
                    break; 
                }
                else {
                    write(connfd, buff_tx, sizeof(buff_tx));
                    printf("[SERVER]: %c \n", buff_rx->img);
                }
            }            
        }  
    }
}