#include <stdio.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <cstdlib>

char* getHost()
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
}

int main(int argc, const char *argv[])
{
   char *host = getHost();
   printf("%s\n",host);
   return 0;
}
