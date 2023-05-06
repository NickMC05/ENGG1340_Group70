#include <math.h>
#include "Car.h"
#include "State.h"
#include "Sprite.h"
#include "Road.h"

void Car::init()
{
    // Allocate memory to sprites
    straight = new Sprite();
    left = new Sprite();
    right = new Sprite();
    // Choose car color depending on what has user chose in main menu
    switch (state->carColor)
    {
    case 1:
        straight->path = "assets/car.txt";
        left->path = "assets/car_left.txt";
        right->path = "assets/car_right.txt";
        break;
    case 2:
        straight->path = "assets/car_y.txt";
        left->path = "assets/car_left_y.txt";
        right->path = "assets/car_right_y.txt";
        break;
    case 3:
        straight->path = "assets/car_c.txt";
        left->path = "assets/car_left_c.txt";
        right->path = "assets/car_right_c.txt";
        break;
    default:
        break;
    }

    straight->state = state;
    left->state = state;
    right->state = state;

    // Load the corresponding sprites for the car
    straight->init();
    left->init();
    right->init();
}

void Car::update()
{
    // increase the speed
    if (state->key == 'w')
    {
        // We multiply by elapsedTime so car moves independent from frame rate
        speed += 2 * state->elapsedTime;
    }
    else if (state->key == 's')
    {
        // We multiply by elapsedTime so car moves independent from frame rate
        speed -= 2 * state->elapsedTime;
    }
    else if (state->key == 'd')
    {
        // We multiply by elapsedTime so car moves independent from frame rate
        // (1 - speed / 2) scales the change in curvature based on the current
        // speed of the car. As the speed of the car increases, the change in curvature
        // becomes smaller, which allows the car to handle high speeds more smoothly.
        curvature += 0.7 * state->elapsedTime * (1.2 - speed / 2);
        // means right
        dir = 1;
    }
    else if (state->key == 'a')
    {
        // We multiply by elapsedTime so car moves independent from frame rate
        // (1 - speed / 2) scales the change in curvature based on the current
        // speed of the car. As the speed of the car increases, the change in curvature
        // becomes smaller, which allows the car to handle high speeds more smoothly.
        curvature -= 0.7 * state->elapsedTime * (1.2 - speed / 2);
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
    else if (speed > maxSpeed)
    {

        speed = maxSpeed;
    }
    state->distance += 70 * speed * state->elapsedTime;

    x = state->WIDTH / 2 + ((int)(state->WIDTH * (curvature - road->totalCurvature)) / 2) - 4;
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

Car::~Car()
{
    delete straight;
    delete left;
    delete right;
}