#include "Background.h"
#include <ncurses.h>

void Background::draw()
{
    for (int y = 0; y < 60; y++)
    {
        for (int x = 0; x < 200; x++)
        {

            printw(" ");
        }
    }
}