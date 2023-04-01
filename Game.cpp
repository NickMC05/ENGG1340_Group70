#include "Game.h"
#include <ncurses.h>
#include "State.h"

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
    vector<vector<int>> &graphic = State::graphic;
    for (int i = 0; i < 60; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            attron(COLOR_PAIR(graphic[i][j]));
            printw("  ");
            attroff(COLOR_PAIR(graphic[i][j]));
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