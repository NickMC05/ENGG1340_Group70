#include "Game.h"
#include <ncurses.h>

void Game::run()
{
    init();
}

void Game::init()
{
    // Initialize ncurses
    window = initscr();
    newwin(100, 320, 0, 0);
    bool ctu = true;
    while (ctu)
    {
        update();
        draw();
    }
    end();
}

// Listen to user key input
void Game::update()
{
}

void Game::draw()
{
    refresh();
    wmove(window, 0, 0);
}

void Game::end()
{
    // todo: savefile

    // end
    endwin();
}