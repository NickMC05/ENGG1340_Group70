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
    spr = new Sprite("test_image.txt");
}

// Listen to user key input
void Game::update()
{
}

void Game::draw()
{
    refresh();
    wmove(stdscr, 0, 0);
}

void Game::end()
{
    // todo: savefile

    // end
    endwin();
}