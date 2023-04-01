#include "Game.h"
#include <ncurses.h>

Game::Game()
{
}

void Game::run()
{
    // Start curses mode
    window = initscr();
    newwin(100, 320, 0, 0);
    start_color();
    //Start the game
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
    spr = new Sprite("test_image.txt");
}

// Listen to user key input
void Game::update()
{

}

void Game::draw()
{
    spr->draw();
    refresh();
    wmove(window, 0, 0);
}

void Game::end()
{
    endwin();
}