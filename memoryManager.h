#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H
#include "SplayTree.cpp"


class memoryManager
{
private:
    SplayTree *tree;
public:
    memoryManager();
    card *getCard(int id);
};


#endif