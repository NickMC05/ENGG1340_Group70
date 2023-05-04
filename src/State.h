#ifndef STATE_H
#define STATE_H

#include "Road.h"
#include "Car.h"
#include <string>
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
    float best = 0;           // Fastest time in one loop
    float currentLapTime = 0; // Current lap time
    string stats[4] = {"Best: ", "Finished: ", "Time: ", "Speed: "};
    int endLine;

    int WIDTH = 100;
    int HEIGHT = 50;

    void update();

    Road *road;
    Car *car;
};

#endif
