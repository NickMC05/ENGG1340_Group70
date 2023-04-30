#include "Game.h"
#include "Menu.h"
#include "State.h"
#include <ncurses.h>

void Game::run()
{
    // Initialize ncurses
    // Start color mode
    initscr();
    start_color();
    noecho();
    nodelay(stdscr, true);

    // // Create menu
    // Menu menu;
    // if (menu.run())
    // {
    //     end();
    //     return;
    // };

    // Start the game
    init();
    while (gameRunning)
    {
        auto now = std::chrono::system_clock::now();
        std::chrono::duration<float> elapsedTime = now - lastFrameTime;
        State::elapsedTime = elapsedTime.count();
        lastFrameTime = std::chrono::system_clock::now();
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
    init_pair(7, COLOR_CYAN, COLOR_CYAN);
    init_pair(9, COLOR_BLACK, COLOR_BLACK);
    createTrack();
    car = new Car();
    background = new Background();
    // Map(int width, int height)
    map = new Map(State::WIDTH, State::HEIGHT);
    lastFrameTime = std::chrono::system_clock::now();
}

void Game::createTrack()
{
    // should be random
    State::vecTrack.push_back(make_pair(0.0f, 10.0f));
    State::vecTrack.push_back(make_pair(0.0f, 200.0f));
    State::vecTrack.push_back(make_pair(-1.0f, 200.0f));
    State::vecTrack.push_back(make_pair(0.0f, 400.0f));
    State::vecTrack.push_back(make_pair(-1.0f, 100.0f));
    State::vecTrack.push_back(make_pair(0.0f, 200.0f));
    State::vecTrack.push_back(make_pair(-1.0f, 200.0f));
    State::vecTrack.push_back(make_pair(1.0f, 200.0f));
    State::vecTrack.push_back(make_pair(0.0f, 200.0f));
    State::vecTrack.push_back(make_pair(0.2f, 500.0f));
    State::vecTrack.push_back(make_pair(0.0f, 200.0f));
    for (auto t : State::vecTrack)
        State::trackDistance += t.second;
}

void Game::menu()
{
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
        State::key = input;
    }
    else if (input == ERR)
    {
        auto now = std::chrono::steady_clock::now();
        int duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastKeyTime).count();
        if (duration > 500)
        {
            State::key = ERR;
        }
    }

    car->update();
    State::update();
}

void Game::draw()
{
    vector<vector<int>> &graphic = State::graphic;
    // draw all white
    for (int i = 0; i < State::HEIGHT; i++)
    {
        for (int j = 0; j < State::WIDTH; j++)
        {
            graphic[i][j] = 5;
        }
    }
    background->draw();

    // draw functions
    map->draw();
    // car->draw(int x, int y)
    car->draw();

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