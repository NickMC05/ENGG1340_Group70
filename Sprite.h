#ifndef SPRITE_H
#define SPRITE_H

#include <vector>
#include <curses.h>

using namespace std;

class Sprite
{
public:
    Sprite(const char* path);
    void draw(WINDOW* win);
private:
    vector<int> pixel;
};

#endif