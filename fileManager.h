#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>

// #include "dataStruct.cpp"

class fileManager
{
private:
    std::string filePath;

public:
    fileManager();
    void loadToFile(card *c);
    card *loadFromFile(int id);
    void initailizeFile();
};

#endif
