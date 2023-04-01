#include "Game.h"
#include <ncurses.h>

Game::Game()
{
<<<<<<< HEAD
    sprite = new Sprite("test_image.txt");
=======
>>>>>>> 51e2c3c6f49751ace3e25586129b7de599a024fa
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
<<<<<<< HEAD
    // Initialize ncurses
    initscr();

    // Start color mode
    start_color();

    // Set color pairs
    init_pair(1, COLOR_RED, COLOR_RED);
    init_pair(2, COLOR_BLUE, COLOR_BLUE);
=======
    spr = new Sprite("test_image.txt");
>>>>>>> 51e2c3c6f49751ace3e25586129b7de599a024fa
}

// Listen to user key input
void Game::update()
{
}

void Game::draw()
{
    for (int i = 0; i < 40; i++)
    {
        for (int j = 0; j < 160; j++)
        {
            attron(COLOR_PAIR(i % 2 + 1));
            printw(" ");
            attroff(COLOR_PAIR(i % 2 + 1));
        }
        printw("\n");
    }
    refresh();
    wmove(stdscr, 0, 0);
}

void Game::end()
{
    // todo: savefile

    // end
    endwin();
}