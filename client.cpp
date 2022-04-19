#include "client.h"
#include "image.cpp"

/*standard symbols */
#include <unistd.h>

/* sockets */
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <arpa/inet.h>

/* strings / errors*/
#include <errno.h>
#include <stdio.h>
#include <string.h>


#include <cstdlib>
Client::Client(int port)
{
    PORT = port;
    CHAR_IP = getHost();
    buff_rx = Data();
    buff_tx = (preData *)malloc(sizeof(preData));
    packSize = (preData *)malloc(sizeof(preData));
    packSize->data = 0;
}

void Client::getImage()
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

    buff_tx->data = 1;
    /* send petition to server*/
    write(sockfd, buff_tx, sizeof(buff_tx)); 

    /* receive image in temp*/
    char* temp = (char*)malloc(sizeof(char) * packSize->data);
    len_rx = read(sockfd, temp, packSize->data);
    std::cout<<"len_rx: "<<len_rx<<std::endl;

    buff_rx.control.clear();
    /* copy image to buff_rx*/
    for(int i = 0; i < len_rx; i++){
        buff_rx.control.push_back(*(temp+i));
    }
    // std::cout << "Control: " << buff_rx.control << std::endl;
    delete temp;
    temp = nullptr;

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
        // fprintf(stdout, "Mensaje recibido: %s \n", buff_rx.control);

        /* build the image */
        image* img = new image();
        img->decodeImage(buff_rx.control);
        delete img;
        img = nullptr;
    }

    

    /* close the socket */
    close(sockfd);
}

void Client::getSize()
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
    buff_tx->data = 0;
    /* send test sequences*/
    write(sockfd, buff_tx, sizeof(buff_tx));
    printf("Despues write \n");
    len_rx = read(sockfd, packSize, sizeof(packSize));
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
        fprintf(stdout, "Mensaje recibido: %d \n", packSize->data);
    }

    

    /* close the socket */
    close(sockfd);
}

void Client::setMessage(int message){
    buff_tx->value = message;
}

char* Client::getHost()
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