#include "client.h"
#include "client.cpp"

int main(){
    std::string ip = "192.168.0.39";
    Client* s = new Client(ip, 8080);
    s->sendMessage();

}