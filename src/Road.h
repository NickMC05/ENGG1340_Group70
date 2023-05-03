#ifndef ROAD_H
#define ROAD_H

#include "Sprite.h"
#include <vector>
using namespace std;

class State;
class Car;

class Road
{
public:
    float currentCurvature = 0;          // Current road curvature, lerped between track sections
    float totalCurvature = 0;            // Accumulation of track curvature
    float length = 5000;                    // Total distance of track
    vector<pair<float, float>> sections; // Track sections, sharpness of bend, length of section

    void update();

    State *state;
    Car *car;
};

#endif