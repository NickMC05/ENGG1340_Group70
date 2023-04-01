#include "Game.h"
#include <ncurses.h>

Game::Game()
{
}

void Game::run()
{
    // Start the game
    init();
    menu();
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
    sprite = new Sprite("test_image.txt");
}

void Game::menu()
{
}

// Listen to user key input
void Game::update()
{
}

void Game::draw()
{
    sprite->draw();
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