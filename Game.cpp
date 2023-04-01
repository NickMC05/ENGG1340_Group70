#include "Game.h"
#include "Menu.h"
#include <ncurses.h>
#include "State.h"

Game::Game()
{
}

void Game::run()
{
    // Initialize ncurses
    // Start color mode
    initscr();
    start_color();
    noecho();
    nodelay(stdscr, true);

    // Create menu
    Menu menu;
    if (menu.run())
    {
        end();
        return;
    };
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
    // Set color pairs
    init_pair(1, COLOR_RED, COLOR_RED);
    init_pair(2, COLOR_BLUE, COLOR_BLUE);
    init_pair(3, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(4, COLOR_GREEN, COLOR_GREEN);
    init_pair(5, COLOR_WHITE, COLOR_WHITE);
    init_pair(6, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(9, COLOR_BLACK, COLOR_BLACK);

    car = new Car();
    background = new Background();
}

void Game::menu()
{
}

// Listen to user key input
// Logics will update here
void Game::update()
{
    int ch = getch();
    if (ch == 'q')
    {
        gameRunning = false;
    }

    //control car
    if(ch == 'a')
    {
        car->turnLeft();
    }
    else if(ch == 'd')
    {
        car->turnRight();
    }
    else if(ch == 'w')
    {
        car->turnStraight();
    }
}

void Game::draw()
{
    vector<vector<int>> &graphic = State::graphic;
    //draw all white
    for (int i = 0; i < State::HEIGHT; i++)
    {
        for (int j = 0; j < State::WIDTH; j++)
        {
            graphic[i][j] = 5;
        }
    }

    // draw functions
    //car->draw(40, 20);
    background->draw();

    // this will update all the pixels on the screen
    for (int i = 0; i < State::HEIGHT; i++)
    {
        for (int j = 0; j < State::WIDTH; j++)
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