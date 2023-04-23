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
    if (State::key == 'w')
    {
        straight->draw(x, y);
    }
    else if (State::key == 'd')
    {
        if (State::carPosition < 91)
        {
            State::carPosition += 0.05;
        }
        right->draw(x, y);
    }
    else if (State::key == 'a')
    {
        if (State::carPosition > 0)
        {
            State::carPosition -= 0.05;
        }
        left->draw(x, y);
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