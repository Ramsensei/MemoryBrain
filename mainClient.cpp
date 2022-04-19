#include "client.h"
#include "client.cpp"

int main(int argc, char *argv[]){
    std::string ip = "192.168.0.17";
    Client* s = new Client(ip, 8080);
    s->setMessage(stoi(argv[1]));
    s->getSize();
    s->getImage();
}