#include "game.h"

game::game()
{
    printf("[GAME]: Game created\n");
    deck = new memoryManager();
    cardsFlipped = 0;
    lastCard = 0;
    pairsFound = 0;
}

int game::getSize(int id)
{
    return deck->getCard(id)->img.size();
}

int game::update(int id)
{
    int returnValue = 0;
    cardsFlipped++;
    if (cardsFlipped == 2)
    {
        if (deck->getCard(id)->type == deck->getCard(lastCard)->type)
        {
            printf("[GAME]: Match found\n");
            deck->flipCards(id, lastCard);
            returnValue = 2;
            pairsFound++;
        }
        else
        {
            printf("[GAME]: No match found\n");
            returnValue = 1;
        }
        cardsFlipped = 0;
    }
    lastCard = id;
    if (pairsFound >= 18)
    {
        printf("[GAME]: Game finished\n");
        returnValue = 3;
    }

    return returnValue;
}

string game::getImage(int id)
{
    return deck->getCard(id)->img;
}
