#ifndef SPRITE_H
#define SPRITE_H

#include <vector>
#include <ncurses.h>
#include <string>

using namespace std;

class State;

class Sprite
{
public:
    string path;
    void init();
    void draw(int x, int y);

    State *state;

private:
    int sHeight, sWidth;
    vector<int> pixel;
};

#endif