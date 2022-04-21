#include "game.h"

game::game()
{
    printf("[GAME]: Game created\n");
    deck = new memoryManager();
}
