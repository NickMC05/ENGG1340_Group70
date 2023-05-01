#include "Background.h"
#include "Sprite.h"
#include <ncurses.h>
#include <fstream>

void Background::init()
{
    sprite = new Sprite("background.txt");
    sprite->state = state;
}

void Background::draw()
{
    sprite->draw(0, 0);
}
