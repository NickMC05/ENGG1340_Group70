#ifndef SPRITE_H
#define SPRITE_H

#include <vector>
#include <ncurses.h>

using namespace std;

class State;

class Sprite
{
public:
    Sprite(const char *path);
    void draw(int x, int y);

    State *state;

private:
    int sHeight, sWidth;
    vector<int> pixel;
};

#endif