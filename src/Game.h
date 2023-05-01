#ifndef GAME_H
#define GAME_H

#include <ncurses.h>
#include <chrono>
#include <time.h>
#include "Car.h"
#include "Background.h"
#include "Map.h"
#include "Road.h"
#include "State.h"

class Game
{

public:
    void init();
    void run();

private:
    void menu();
    void update();
    void draw();
    void end();
    void createTrack();

    bool gameRunning = true;

    std::chrono::_V2::system_clock::time_point lastFrameTime;
    std::chrono::_V2::steady_clock::time_point lastKeyTime; // count accumulate ERR from getch()

    Car *car;
    Background *background;
    Map *map;
    Road *road;
    State *state;
    char input;
};

#endif