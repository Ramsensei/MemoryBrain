#include "server.h"
#include "server.cpp"

int main(){
    std::string ip = "192.168.0.15";
    Server* s = new Server(ip, 8080);

}