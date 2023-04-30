#ifndef GAME_H
#define GAME_H

#include <ncurses.h>
#include <chrono>
#include "Car.h"
#include "Background.h"
#include "Map.h"
#include <time.h>

class Game
{

public:
    void run();

private:
    void init();
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
    char input;
};

#endif