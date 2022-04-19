
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include "image.h"
using namespace std;

image::image(){
}

int image::encodeImage(std::string picture){ // picture example: assets/1.png
    ifstream image(picture, ios::in | ios::binary);
    // ofstream binary("binary_image.txt", ios::out | ios::trunc);
    
    while(!image.eof())
    {
        ch = image.get();
        // binary.put(ch);
        img.push_back(ch);
    }
    cout<<"Loaded Successfully"<<endl;
    // cout<<picture<<endl;

    image.close();
    // binary.close();
    return 0;
    // cout<<binary<<endl;
}

int image::decodeImage(){
    // ifstream binary("binaryString.txt", ios::in | ios::app | ios::binary);
    ofstream image("rebuild.png", ios::out | ios::trunc);
    // while(!binary.eof())
    
    while (img.size() > 0)
    {
        ch = img.substr(0,1).c_str()[0];
        // ch = binary.get();
        image.put(ch);
        img = img.substr(1);

    }
    cout<<"ReLoaded Successfully"<<endl;
    image.clear();
    // binary.close();
    return 0;
}
int image::decodeImage(std::string picture){
    img = picture;
    decodeImage();
    return 0;
}

// int main () {
//     image img;
//     img.encodeImage("assets/1.png");
//     img.decodeImage();
//     return 0;
// }

