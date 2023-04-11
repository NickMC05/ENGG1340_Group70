#include "Background.h"
#include "Sprite.h"
#include "State.h"
#include <ncurses.h>
#include <fstream>

void Background::draw()
{
<<<<<<< HEAD
    vector<vector<int> > &graphic = State::graphic;
    for (int y = 0; y < State::HEIGHT / 2; y++)
    {
        for (int x = 0; x < State::WIDTH; x++)
        {

            graphic[y][x] = 1;
        }
    }
}
=======
    vector<vector<int>> &graphic = State::graphic;
    sprite = new Sprite("background.txt");
    sprite->draw(0, 0);
}
>>>>>>> c376b2e7068e0746ab0b8d54956d82088b51d429
