#include "memoryManager.h"
#include "image.cpp"
#include <stdlib.h>
#include <time.h>
#include <vector>

memoryManager::memoryManager()
{
    printf("[MEMORY MANAGER]: Memory manager created\n");
    tree = new SplayTree();
    file = new fileManager();
    file->initailizeFile();
    srand(time(NULL));
    vector<int> data{1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9};
    for (int m = 1; m < 7; m++)
    {
        for (int n = 1; n < 7; n++)
        {
            // Create  a new card
            card *c = new card();
            c->id = m * 10 + n;
            // Get a random type
            int random = rand() % data.size();
            c->type = data[random];
            data.erase(data.begin() + random);
            // Status 0 = not flipped, 1 = flipped
            c->status = 0;

            // Encode the image
            image *img = new image();
            img->encodeImage("assets/" + std::to_string(c->type) + ".png");
            c->img = img->img;
            delete img;

            // Add the card to the tree
            // file->loadToFile(c);
            tree->insert(c);
            fprintf(stdout, "[MEMORY MANAGER]: Card %d inserted\n", c->id);
        }
    }
    // loadTree();
}
void memoryManager::loadTree()
{
    srand(time(NULL));
    vector<int> data;
    for (int m = 1; m < 7; m++)
    {
        for (int n = 1; n < 7; n++)
        {
            data.insert(data.end(), m * 10 + n);
        }
    }
    for (int m = 0; m < 12; m++)
    {
        int random = rand() % data.size();
        card *c = new card();
        c = file->loadFromFile(data[random]);
        tree->insert(c);
    }
}
card *memoryManager::getCard(int id)
{
    if(tree->search(id)->id == NULL){
        card *c = new card();
        c->id = id;
        c->type = file->loadFromFile(id)->type;
        c->status = file->loadFromFile(id)->status;
        tree->replaceLast(c); 
    }
    return tree->search(id);
}

void memoryManager::flipCards(int id1, int id2)
{
    getCard(id1)->status = 1;
    getCard(id2)->status = 1;
}