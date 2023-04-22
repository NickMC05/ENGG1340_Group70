#ifndef CAR_H
#define CAR_H

#include "Sprite.h"
#include <ncurses.h>

class Car
{
public:
    Car();
    void draw();
    void turnLeft();
    void turnRight();
    void turnStraight();

private:
    Sprite *straight;
    Sprite *left;
    Sprite *right;
    int dir = 0;
};

#endif