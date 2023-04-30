#include "Car.h"
#include "State.h"

Car::Car()
{
    straight = new Sprite("car.txt");
    left = new Sprite("car_left.txt");
    right = new Sprite("car_right.txt");
    y = 30;
}

void Car::update()
{
    x = State::carPosition;

    static chrono::steady_clock::time_point currentTime;
    auto newTime = std::chrono::steady_clock::now();                                                                     // Current Time
    float fElapsedTime = chrono::duration_cast<std::chrono::nanoseconds>(newTime - currentTime).count() / 1000000000.0f; // 100000000.0f;    // Time between Loops
    currentTime = std::chrono::steady_clock::now();

    if (State::key == 'd')
    {
        if (State::carPosition < 91)
        {
            // State::carPosition += 0.05;
            if (State::playerCurvature < 0.9)
            {
                State::playerCurvature += 0.7 * fElapsedTime;
            }
        }
        //means right
        dir = 1;
    }
    else if (State::key == 'a')
    {
        if (State::carPosition > 0)
        {
            // State::carPosition -= 0.05 ;
            if (State::playerCurvature > -0.9)
            {
                State::playerCurvature -= 0.7 * fElapsedTime;
            }
        }
        //means left
        dir = 2;
    }
    else
    {
        //means straight
        dir = 0;
    }
}

void Car::draw()
{
    if(dir == 1)
    {
        right->draw(x,y);
    }
    else if(dir == 2)
    {
        left->draw(x,y);
    }
    else
    {
        straight->draw(x,y);
    }
}

void Car::turnRight()
{
    dir = 1;
}

void Car::turnLeft()
{
    dir = 2;
}

void Car::turnStraight()
{
    dir = 0;
}