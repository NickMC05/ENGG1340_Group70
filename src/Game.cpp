#include "Game.h"
#include "Menu.h"
#include "State.h"
#include "Road.h"
#include "Car.h"
#include <ncurses.h>
#include <string>
#include <cmath>

void Game::init()
{
    // Initialaze Ncurses
    // 1. creates window
    // 2. Enable color
    // 3. Don't wait for key input
    // 4. Assign colors a value
    initscr();
    start_color();
    noecho();
    init_pair(1, COLOR_WHITE, COLOR_RED);
    init_pair(2, COLOR_BLUE, COLOR_BLUE);
    init_pair(3, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(4, COLOR_GREEN, COLOR_GREEN);
    init_pair(5, COLOR_RED, COLOR_WHITE);
    init_pair(6, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(7, COLOR_CYAN, COLOR_CYAN);
    init_pair(9, COLOR_BLACK, COLOR_BLACK);
    menu(); // Create menu
    nodelay(stdscr, true);

    // Allocating memory for actors
    state = new State();
    road = new Road();
    background = new Background();
    car = new Car();
    map = new Map();

    // State will also store reference to actors so other files can access it
    state->road = road;
    state->car = car;
    road->state = state;
    road->car = car;
    road->init();
    map->state = state;
    map->road = road;
    car->state = state;
    car->road = road;

    // Car::init() will load the sprites from txt file
    car->init();
    background->state = state;
    background->road = road;

    // Background::init() will load the sprites from txt file
    background->init();

    // clock will be used to calculate point and track of the game
    lastFrameTime = std::chrono::system_clock::now();
}

void Game::run()
{
    init();

    // Start the game
    while (gameRunning)
    {
        // calculate elapsed time from last frame to current frame
        // by calculating this we can calculate when to curve the track
        auto now = std::chrono::system_clock::now();
        std::chrono::duration<float> elapsedTime = now - lastFrameTime;
        state->elapsedTime = elapsedTime.count();
        lastFrameTime = std::chrono::system_clock::now();

        update();
        draw();
    }
    end();
}

void Game::menu()
{
    // create menu object and run
    Menu menu;
    // if menu returns 1 it means user wants to exit
    if (menu.run() == 1)
    {
        gameRunning = false;
    };
}

// Listen to user key input
// Logics will update here
void Game::update()
{
    // get the key input and lower the characters 'A' -> 'a' etc
    input = tolower(getch());

    // q is used to quit the game so we set gameRunning to false to exit game loop
    if (input == 'q')
    {
        gameRunning = false;
        return;
    }
    // if user input is valid key then we will update State so car can act accordingly
    if (input == 'w' || input == 'a' || input == 's' || input == 'd')
    {
        lastKeyTime = std::chrono::steady_clock::now();
        state->key = input;
    }
    // if input is nothing then we handle it accordingly
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
    attron(COLOR_PAIR(5));
    for (int i = 0; i < 4; i++)
    {
        printw("%s", state->stats[i].c_str());
        for (int _ = 0; _ < state->WIDTH * 2 - state->stats[i].length(); _++)
        {
            printw(" ");
        }
        printw("\n");
    }
    attroff(COLOR_PAIR(5));
    // our program can not directly access pixel
    // we can only modify state->graphics and set its color value at its location
    // this method is more efficient and safer
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

    // move cursor to the start of the screen so it can draw again
    // we are not calling clear() because we are re painting every pixel again
    // this method is far more efficient than calling clear()

    // clear() method causes flickering
    wmove(stdscr, 0, 0);
}

void Game::end()
{
    // todo: savefile

    // end
    endwin();
}