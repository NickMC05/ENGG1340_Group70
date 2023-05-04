// Sprite class will load txt file and read pixels
// it can draw to the screen accordingly at any positon

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
    // path is location of sprite fiel (aka txt file)
    string path;
    // init() will load the file and read the values and push it to vector<int> pixel
    void init();
    // it won't print anything to screen but update state->graphics so later game will print for it
    void draw(int x, int y);
    // We need state to access graphics vector
    State *state;

private:
    int sHeight, sWidth;
    vector<int> pixel;
};

#endif