#ifndef GAME_H
#define GAME_H

#include <ncurses.h>
#include <chrono>
#include <time.h>
#include "Car.h"
#include "Background.h"
#include "Map.h"
#include "Road.h"
#include "State.h"

class Game
{
public:
    // Call this method to start the game
    void run();
private:
    // init method will be called at the start of the game
    // load resources or things that will be done only once here
    void init();
    // menu will handle all the graphics and key inputs that will happen inside menu
    // call this function and menu screen will show up
    void menu();
    // update() will be called every frame, difference between update() and draw()
    // is that the update() method calls before draw() so movement key strokes all are coded here
    void update();
    // all the graphics will be drawen here
    void draw();
    // ends the game, this will free up the memory and end the game
    void end();
    // this functions controls the length and curvature of the track 
    void createTrack();

    // this boolean indicates whether game is running or not
    // if you set it false then game loop will stop
    bool gameRunning = true;

    std::chrono::system_clock::time_point lastFrameTime;
    std::chrono::steady_clock::time_point lastKeyTime; // count accumulate ERR from getch()

    // Actors
    // Actors acts seperately from Game.cpp
    // It handles its own input and its position
    // Actors and Game will communicate via static variables through State
    Car *car;
    Background *background;
    Map *map;
    Road *road;
    State *state;

    // It will store the key user presses
    char input;
};

#endif