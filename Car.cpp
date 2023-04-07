#include "Car.h"
#include "State.h"

Car::Car()
{
    straight = new Sprite("car.txt");
    left = new Sprite("car_left.txt");
    right = new Sprite("car_right.txt");
}

void Car::draw(int x, int y)
{

    if (State::key == 'w')
    {
        straight->draw(x, y);
    }
    else if (State::key == 'd')
    {
        right->draw(x, y);
    }
    else if (State::key == 'a')
    {
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