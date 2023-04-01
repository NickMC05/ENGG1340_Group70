#include "Car.h"

Car::Car()
{
    texture = new Sprite("car.txt");
}

void Car::draw(int x, int y)
{
    texture->draw(x,y);
}