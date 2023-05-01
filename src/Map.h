#ifndef MAP_H
#define MAP_H

#include "State.h"
#include <cmath>
using namespace std;

class Map
{
public:
    void draw();
    State *state;
    Road *road;
};

#endif