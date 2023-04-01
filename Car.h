#ifndef CAR_H
#define CAR_H

#include "Sprite.h"
#include <ncurses.h>

class Car
{
public:
    Car();
    void draw(int x, int y);
private:
    Sprite *texture;
};

#endif