#include "client.h"
#include "client.cpp"

int main(){
    std::string ip = "192.168.18.178";
    Client* s = new Client(ip, 8080);
    s->sendMessage();

}