#include "Car.h"
#include "State.h"

Car::Car()
{
    straight = new Sprite("car.txt");
    left = new Sprite("car_left.txt");
    right = new Sprite("car_right.txt");
}

void Car::draw()
{
    int x = State::carPosition;
    int y = 38;

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
        right->draw(x, y);
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
        left->draw(x, y);
    }
    else
    {
        straight->draw(x, y);
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