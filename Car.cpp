#include "Car.h"

Car::Car()
{
    straight = new Sprite("car.txt");
    left = new Sprite("car_left.txt");
    right = new Sprite("car_right.txt");
}

void Car::draw(int x, int y)
{
    if(dir == 0)
        straight->draw(x,y);
    if(dir == 1)
        right->draw(x,y);
    if(dir == 2)
        left->draw(x,y);
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