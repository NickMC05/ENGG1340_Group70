#ifndef MAP_H
#define MAP_H

#include <cmath>
using namespace std;

class Map
{
public:
    Map(int width, int height);
    void draw();
private:
    int mapWidth;
    int mapHeight;
};

#endif