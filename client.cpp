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

Client::Client(std::string ip, int port)
{
    SERVER_IP = ip;
    PORT = port;
    CHAR_IP = const_cast<char *>(SERVER_IP.c_str());
    buff_rx = (Data *)malloc(sizeof(Data));
    buff_tx = (Data *)malloc(sizeof(Data));
    buff_tx->img = 'c';
}

void Client::sendMessage()
{
    /* socket creation */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        fprintf(stderr, "[CLIENT-error]: socket creation failed. %d: %s \n", errno, strerror(errno));
        return;
    }
    else
        printf("[CLIENT]: Socket successfully created..\n");

    /* clear structure */
    memset(&servaddr, 0, sizeof(servaddr));

    /* assign IP, SERV_PORT, IPV4 */
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(CHAR_IP);
    servaddr.sin_port = htons(PORT);

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
    {
        printf("connection with the server failed...\n");
        return;
    }

    printf("connected to the server..\n");

    /* send test sequences*/
    write(sockfd, buff_tx, sizeof(buff_tx));
    printf("Despues write \n");
    len_rx = read(sockfd, buff_rx, sizeof(buff_rx));
    printf("Despues read \n");

    if (len_rx == -1)
    {
        fprintf(stderr, "[CLIENT-error]: connfd cannot be read. %d: %s \n", errno, strerror(errno));
    }
    else if (len_rx == 0){
        printf("[CLIENT]: client socket closed \n\n");
        // break;
    }
    else
    {
        fprintf(stdout, "Mensaje recibido: %c \n", buff_rx->img);
    }

    

    /* close the socket */
    close(sockfd);
}