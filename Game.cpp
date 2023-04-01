#include "Game.h"
#include <ncurses.h>

Game::Game()
{
    spr = new Sprite("test_image.txt");
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
    
}

// Listen to user key input
void Game::update()
{

}

void Game::draw()
{
    refresh();
    wmove(window, 0, 0);
}

void Game::end()
{
    endwin();
}