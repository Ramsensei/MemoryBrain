#include "client.h"

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


Client::Client(std::string ip, int port) {
    SERVER_IP = ip;
    PORT = port;
    CHAR_IP = const_cast<char*>(SERVER_IP.c_str());
    buff_rx = (Data *) malloc(sizeof(Data));
    buff_tx = (Data *) malloc(sizeof(Data));
    buff_tx->a = 2;
    buff_tx->b = 'b';

    /* socket creation */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        fprintf(stderr, "[CLIENT-error]: socket creation failed. %d: %s \n", errno, strerror( errno ));
        return; 
    } else printf("[CLIENT]: Socket successfully created..\n");

    /* clear structure */
    memset(&servaddr, 0, sizeof(servaddr));
  
    /* assign IP, SERV_PORT, IPV4 */
    servaddr.sin_family      = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr(CHAR_IP);
    servaddr.sin_port        = htons(PORT);
}

void Client::sendMessage(){
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) { 
        printf("connection with the server failed...\n");  
        return;
    } 
    
    printf("connected to the server..\n"); 
  
    /* send test sequences*/
    write(sockfd, buff_tx, sizeof(buff_tx));     
    read(sockfd, buff_rx, sizeof(buff_rx));
    printf("CLIENT:Received: %c \n", buff_rx->b);
    
       
    /* close the socket */
    close(sockfd);
}