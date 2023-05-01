#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "State.h"
#include "Sprite.h"

class Background
{
public:
    void init();
    void draw();

    State *state;

private:
    Sprite *sprite;
};

#endif