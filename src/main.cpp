#include "Game.h"

int main()
{
    //Game object will be created from here to run the game
    //Game::run() will initialiaze the game and call update(), draw() function
    // This is good practice for games and follows lot of paradigms from popular game engines

    Game game;
    game.run();
    return 0;
}