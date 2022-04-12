#define IMAGE_H
#ifdef IMAGE_H
#include <string>

class image
{
public:
    char ch;
    std::string img;
    image();
    int encodeImage(std::string picture);
    int decodeImage();
};

#endif