#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "State.h"
#include "Sprite.h"
#include "Road.h"
#include "Car.h"
class Background
{
public:
    ~Background();
    void init();
    void draw();

    State *state;
    Road *road;

private:
    Sprite *sprite;
};

#endif