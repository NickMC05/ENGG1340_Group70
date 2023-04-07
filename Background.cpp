#include "Background.h"
#include "Sprite.h"
#include "State.h"
#include <ncurses.h>
#include <fstream>

void Background::draw()
{
    vector<vector<int>> &graphic = State::graphic;
    sprite = new Sprite("background.txt");
    sprite->draw(0, 0);
}
