#include <math.h>
#include "Car.h"
#include "State.h"
#include "Sprite.h"
#include "Road.h"

void Car::init()
{
    straight = new Sprite("car.txt");
    left = new Sprite("car_left.txt");
    right = new Sprite("car_right.txt");
    straight->state = state;
    left->state = state;
    right->state = state;
}

void Car::update()
{
    if (state->key == 'w')
    {
        speed += 2 * state->elapsedTime;
    }
    else if (state->key == 's')
    {
        speed -= state->elapsedTime;
    }
    else if (state->key == 'd')
    {
        curvature += 0.7 * state->elapsedTime * (1 - speed / 2);
        // means right
        dir = 1;
    }
    else if (state->key == 'a')
    {
        curvature -= 0.7 * state->elapsedTime * (1 - speed / 2);
        // means left
        dir = 2;
    }

    else
    {
        // means straight
        dir = 0;
    }

    if (fabs(curvature - road->totalCurvature) >= 0.8f)
    {

        speed -= 5 * state->elapsedTime;
    }
    if (speed < 0)
    {

        speed = 0;
    }
    else if (speed > 1)
    {

        speed = 1;
    }
    state->distance += (70 * speed) * state->elapsedTime;

    x = state->WIDTH / 2 + ((int)(state->WIDTH * (curvature - road->totalCurvature)) / 2.0) - 4;
    if (x < 0)
    {
        x = 0;
    }
    else if (x > 91)
    {
        x = 91;
    }
}

void Car::draw()
{
    if (dir == 1)
    {
        right->draw(x, y);
    }
    else if (dir == 2)
    {
        left->draw(x, y);
    }
    else
    {
        straight->draw(x, y);
    }
}