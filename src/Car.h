#ifndef CAR_H
#define CAR_H

#include "Sprite.h"
#include <ncurses.h>

class Car
{
public:
    Car();
    void update();
    void draw();

private:
    int x, y = 30;
    float curvature = 0;
    Sprite *straight;
    Sprite *left;
    Sprite *right;
    int dir = 0;
};

#endif