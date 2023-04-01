#include "Background.h"
#include "State.h"
#include <ncurses.h>

void Background::draw()
{
    vector<vector<int>> &graphic = State::graphic;
    for (int y = 0; y < 30; y++)
    {
        for (int x = 0; x < 100; x++)
        {

            graphic[y][x] = 1;
        }
    }
}