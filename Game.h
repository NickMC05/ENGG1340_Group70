#ifndef GAME_H
#define GAME_H

#include <ncurses.h>

class Game
{

public:
    Game(){};
    void run();

private:
    void init();
    void update();
    void draw();
    void end();

    WINDOW *window;
    bool gameRunning = true;
    // Map map;
};

#endif