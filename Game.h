#ifndef GAME_H
#define GAME_H

#include <ncurses.h>
#include "Car.h"
#include "Background.h"

class Game
{

public:
    Game();
    void run();

private:
    void init();
    void menu();
    void update();
    void draw();
    void end();

    bool gameRunning = true;

    Car *car;
    Background *background;
};

#endif