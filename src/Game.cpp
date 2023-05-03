#include "Game.h"
#include "Menu.h"
#include "State.h"
#include "Road.h"
#include "Car.h"
#include <ncurses.h>
#include <string>
#include <iostream>
#include <cmath>

void Game::init()
{
    initscr();
    start_color();
    noecho();
    nodelay(stdscr, true);
    init_pair(1, COLOR_RED, COLOR_RED);
    init_pair(2, COLOR_BLUE, COLOR_BLUE);
    init_pair(3, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(4, COLOR_GREEN, COLOR_GREEN);
    init_pair(5, COLOR_WHITE, COLOR_WHITE);
    init_pair(6, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(7, COLOR_CYAN, COLOR_CYAN);
    init_pair(9, COLOR_BLACK, COLOR_BLACK);

    state = new State();
    road = new Road();
    background = new Background();
    car = new Car();
    map = new Map();
    state->road = road;
    road->state = state;
    road->car = car;
    map->state = state;
    map->road = road;
    car->state = state;
    car->road = road;
    car->init();
    background->state = state;
    background->road = road;
    background->init();
    createTrack();
    lastFrameTime = std::chrono::system_clock::now();
}

void Game::run()
{

    init();
    // menu(); // Create menu

    // Start the game
    while (gameRunning)
    {
        auto now = std::chrono::system_clock::now();
        std::chrono::duration<float> elapsedTime = now - lastFrameTime;
        state->elapsedTime = elapsedTime.count();
        lastFrameTime = std::chrono::system_clock::now();
        update();
        draw();
    }
    end();
}
void Game::createTrack()
{
    float totalLength = 0;
    while (totalLength < road->length)
    {
        // random curvature
        // higher chance for straighter road
        float curvature = pow(5000, (((float)(rand() % 50)) / 50) - 1);

        // bend left or right
        int sign = rand() % 2;
        if (sign == 1)
        {
            curvature *= -1;
        }

        // random length
        float length = rand() % 500;
        // total length is constant
        if (length > road->length - totalLength)
        {
            length = road->length - totalLength;
        }
        road->sections.push_back(make_pair(curvature, length));

        // record total pushed length
        totalLength += length;
    }
}

void Game::menu()
{
    Menu menu;
    if (menu.run())
    {
        end();
        return;
    };
}

// Listen to user key input
// Logics will update here
void Game::update()
{
    input = tolower(getch());
    if (input == 'q')
    {
        gameRunning = false;
        return;
    }

    if (input == 'w' || input == 'a' || input == 's' || input == 'd')
    {
        lastKeyTime = std::chrono::steady_clock::now();
        state->key = input;
    }
    else if (input == ERR)
    {
        auto now = std::chrono::steady_clock::now();
        int duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastKeyTime).count();
        if (duration > 500)
        {
            state->key = ERR;
        }
    }

    car->update();
    road->update();
    state->update();
}

void Game::draw()
{

    // draw functions
    background->draw();
    map->draw();
    car->draw();

    // this will update all the pixels on the screen
    for (int i = 0; i < state->HEIGHT; i++)
    {
        for (int j = 0; j < state->WIDTH; j++)
        {
            attron(COLOR_PAIR(state->graphic[i][j]));
            printw("  ");
            attroff(COLOR_PAIR(state->graphic[i][j]));
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