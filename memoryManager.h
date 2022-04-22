#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H
#include "SplayTree.cpp"
#include "fileManager.cpp"


class memoryManager
{
private:
    SplayTree *tree;
    fileManager *file;
public:
    memoryManager();
    card *getCard(int id);
    void flipCards(int id1, int id2);
    void loadTree();
};


#endif