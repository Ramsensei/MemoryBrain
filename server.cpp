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
#include <stdio.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <cstdlib>

Server::Server(int port)
{
    PORT = port;
    len = sizeof(client);
    CHAR_IP = getHost();

    buff_tx = Data();
    buff_rx = (preData *)malloc(sizeof(preData));
    packSize = (preData *)malloc(sizeof(preData));

    /* socket creation */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        fprintf(stderr, "[SERVER-error]: socket creation failed. %d: %s \n", errno, strerror(errno));
        return;
    }
    else
        printf("[SERVER]: Socket successfully created..\n");

    /* clear structure */
    memset(&servaddr, 0, sizeof(servaddr));

    /* assign IP, SERV_PORT, IPV4 */
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(CHAR_IP);
    servaddr.sin_port = htons(PORT);

    /* Bind socket */
    if ((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
    {
        fprintf(stderr, "[SERVER-error]: socket bind failed. %d: %s \n", errno, strerror(errno));
        return;
    }
    else
        printf("[SERVER]: Socket successfully binded \n");

    /* Listen */
    if ((listen(sockfd, BACKLOG)) != 0)
    {
        fprintf(stderr, "[SERVER-error]: socket listen failed. %d: %s \n", errno, strerror(errno));
        return;
    }
    else
        printf("[SERVER]: Listening on SERV_PORT %d \n\n", ntohs(servaddr.sin_port));
    board = new game();
    this->start();
}

void Server::start()
{
    while (1)
    {
        connfd = accept(sockfd, (struct sockaddr *)&client, &len);
        if (connfd < 0)
        {
            fprintf(stderr, "[SERVER-error]: connection not accepted. %d: %s \n", errno, strerror(errno));
            return;
        }
        else
        {
            while (1)
            { /* read data from a client socket till it is closed */
                /* read client message, copy it into buffer */
                len_rx = read(connfd, buff_rx, sizeof(buff_rx));

                if (len_rx == -1)
                {
                    fprintf(stderr, "[SERVER-error]: connfd cannot be read. %d: %s \n", errno, strerror(errno));
                }
                else if (len_rx == 0)
                { /* if length is 0 client socket closed, then exit */
                    printf("[SERVER]: client socket closed \n\n");
                    break;
                }
                else
                {
                    if (buff_rx->data == 0)
                    {
                        int id = buff_rx->value;
                        packSize->data = board->getSize(id);
                        packSize->value = board->update(id);
                        buff_tx.control = board->getImage(id);
                        write(connfd, packSize, sizeof(packSize));
                        printf("Envio de tamaño \n");
                    }
                    else if (buff_rx->data == 1)
                    {

                        write(connfd, buff_tx.control.data(), buff_tx.control.size());
                    }
                }
            }
            close(connfd);
        }
    }
}

char* Server::getHost()
{
   struct ifaddrs *ifAddrStruct = NULL;
   struct ifaddrs *ifa = NULL;
   void *tmpAddrPtr = NULL;
   getifaddrs(&ifAddrStruct);
   for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next)
   {

      if (ifa->ifa_addr->sa_family == AF_INET)
      {
         // check it is IP4
         // is a valid IP4 Address
         tmpAddrPtr = &((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
         char addressBuffer[INET_ADDRSTRLEN];
         inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
         if (strcmp(ifa->ifa_name, "wlan0") == 0)
         {
            // printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer);
            char* ip = (char*)malloc(sizeof(char)*INET_ADDRSTRLEN);
            strcpy(ip, addressBuffer);
            return ip;
         }
      }
   }
   char *ret = (char *)"Null";
   return ret;
}