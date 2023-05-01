#ifndef STATE_H
#define STATE_H

#include "Road.h"
#include <vector>
#include <chrono>

using namespace std;

class State
{
public:
    char key; // current key input
    float elapsedTime = 0;
    vector<vector<int>> graphic = vector<vector<int>>(50, vector<int>(100, 5));

    float distance = 0;       // Distance car has travelled around track
    vector<float> lapTimes;   // List of previous lap times
    float currentLapTime = 0; // Current lap time

    int WIDTH = 100;
    int HEIGHT = 50;

    void update();

    Road *road;
};

#endif
