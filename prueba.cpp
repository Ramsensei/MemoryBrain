#include <string>
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int main () {
    string str = "Lorem ipsum dolor sit amet, cons";
    char* cstr = (char *) malloc(30000);
    char a = 's';
    cstr[0] = a;
    cstr[1] = '\n';
    cstr[2] = 't';
    cstr[3] = '\n';
    cstr[4] = 'l';
    cout<<cstr<<endl;
}