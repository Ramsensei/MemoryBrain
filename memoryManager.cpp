#include "memoryManager.h"
#include "image.cpp"
#include <stdlib.h>
#include <time.h>
#include <vector>

memoryManager::memoryManager()
{
    printf("[MEMORY MANAGER]: Memory manager created\n");
    tree = new SplayTree();
    srand (time(NULL));
    vector<int> data{1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9};
    for (int m = 1; m < 7; m++)
    {
        for (int n = 1; n < 7; n++)
        {
            card *d = new card();
            d->id = m * 10 + n;

            int random = rand() % data.size();
            d->type = data[random];
            data.erase(data.begin() + random);

            d->status = 0;

            image *img = new image();
            img->encodeImage("assets/" + std::to_string(d->type) + ".png");
            d->img = img->img;
            delete img;

            tree->insert(d);
            fprintf(stdout, "[MEMORY MANAGER]: Card %d inserted\n", d->id);
        }
    }
    // tree->preOrder();
}

card *memoryManager::getCard(int id)
{
    return tree->search(id);
}