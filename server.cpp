#include "server.h"
#include "image.cpp"

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

    buff_tx = Data();
    buff_rx = (preData *) malloc(sizeof(preData));
    packSize = (preData *)malloc(sizeof(preData));

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
                    break; 
                }
                else {
                    if (buff_rx->data == 0){
                        printf("op 1 \n");
                        image* img = new image();
                        std::string path = "assets/" + std::to_string(buff_rx->value) + ".png";
                        img->encodeImage(path);
                        buff_tx.control = img->img;
                        delete img;
                        img = nullptr;
                        packSize->data = buff_tx.control.size();
                        write(connfd, packSize, sizeof(packSize));
                        printf("Envio de tamaño \n");
                    }
                    else if(buff_rx->data == 1){
                        printf("op 2 \n");
                        
                        write(connfd, buff_tx.control.data(), buff_tx.control.size());
                    }
                }
            }
            close(connfd);          
        }  
    }
}