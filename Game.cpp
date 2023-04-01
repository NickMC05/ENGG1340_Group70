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
    init_pair(3, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(4, COLOR_GREEN, COLOR_GREEN);
    init_pair(5, COLOR_WHITE, COLOR_WHITE);
    init_pair(6, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(9, COLOR_BLACK, COLOR_BLACK);

    car = new Car();
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