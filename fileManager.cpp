#include "fileManager.h"
#include <iostream>

fileManager::fileManager()
{
    filePath = "cards.memorybrain";
}
void fileManager::loadToFile(card *c)
{
    FILE *file = fopen(filePath.c_str(), "rb");
    int pos = ((c->id % 10) + (c->id / 10) - 2) * 7; // position in file

    /* Get the file size */
    fseek(file, 0, SEEK_END);
    int lSize = ftell(file);
    rewind(file);

    /* Allocate memory for entire content */
    char *buffer = (char *)malloc(sizeof(char) * lSize);
    fread(buffer, 1, lSize, file);

    /* Reopen the file */
    freopen(filePath.c_str(), "wb", file);

    /* Convert card to text and replace it into the file */
    fputs(buffer, file);
    fseek(file, pos, SEEK_SET);
    std::string text = std::to_string(c->id) + "," + std::to_string(c->type) + "," + std::to_string(c->status) + "\n";
    fputs(text.c_str(), file);

    fclose(file);
}
card *fileManager::loadFromFile(int id)
{
    FILE *file = fopen(filePath.c_str(), "rb");
    int pos = ((id % 10) + (id / 10) - 2) * 7; // position in file

    /* Allocate memory for entire content */
    char *buffer = (char *)malloc(sizeof(char) * 6);
    fread(buffer, 1, 6, file);

    card *c = new card();
    std::string id_str;
    id_str.push_back(buffer[0]);
    id_str.push_back(buffer[1]);

    c->id = std::stoi(id_str);
    c->type = atoi((buffer + 3));
    c->status = atoi((buffer + 5));

    return c;
    fclose(file);
}
void fileManager::initailizeFile()
{
    FILE *file = fopen(filePath.c_str(), "w+");
    std::string text = "";

    for (int m = 1; m < 7; m++)
    {
        for (int n = 1; n < 7; n++)
        {
            text += std::to_string(m * 10 + n) + ",0,0\n";
        }
    }
    fprintf(file, "%s", text.c_str());
    fclose(file);
}

// int main()
// {
//     fileManager *file = new fileManager();
//     file->initailizeFile();
//     card *c = new card();
//     c->id = 11;
//     c->type = 1;
//     c->status = 0;
//     file->loadToFile(c);
//     c->id = 12;
//     file->loadToFile(c);
//     // file->loadFromFile(11);
//     std::cout<<file->loadFromFile(11)->id<<std::endl;
//     return 0;
// }