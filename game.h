#ifndef GAME_H
#define GAME_H
#include "memoryManager.cpp"

class game
{
private:
    memoryManager *deck;
    int cardsFlipped;
    int lastCard;
    int pairsFound;

public:
    game();
    int getSize(int id);
    int update(int id);
    string getImage(int id);

    
};


#endif