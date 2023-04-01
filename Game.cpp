#include "Game.h"
#include <ncurses.h>

Game::Game()
{
}

void Game::run()
{
    // Start the game
    init();

    while (gameRunning)
    {
        update();
        draw();
    }
    end();
}

void Game::init()
{
    // Initialize ncurses
    initscr();

    // Start color mode
    start_color();

    // Set color pairs
    init_pair(1, COLOR_RED, COLOR_RED);
    init_pair(2, COLOR_BLUE, COLOR_BLUE);
    init_pair(3, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(4, COLOR_GREEN, COLOR_GREEN);
    init_pair(5, COLOR_WHITE, COLOR_WHITE);
    init_pair(6, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(9, COLOR_BLACK, COLOR_BLACK);

    car = new Car();
}

// Listen to user key input
void Game::update()
{
    
}

void Game::draw()
{
    car->draw(80,35);
    refresh();
    wmove(stdscr, 0, 0);
}

void Game::end()
{
    // todo: savefile

    // end
    endwin();
}