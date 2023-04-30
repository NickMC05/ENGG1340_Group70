#include "Car.h"
#include "State.h"

Car::Car()
{
    straight = new Sprite("car.txt");
    left = new Sprite("car_left.txt");
    right = new Sprite("car_right.txt");
}

void Car::update()
{
    if (State::key == 'w')
    {
        State::carSpeed += 2 * State::elapsedTime;
    }
    else if (State::key == 's')
    {
        State::carSpeed -= State::elapsedTime;
    }
    else if (State::key == 'd')
    {
        curvature += 0.7 * State::elapsedTime * (1 - State::carSpeed / 2);
        // means right
        dir = 1;
    }
    else if (State::key == 'a')
    {
        curvature -= 0.7 * State::elapsedTime * (1 - State::carSpeed / 2);
        // means left
        dir = 2;
    }

    else
    {
        // means straight
        dir = 0;
    }

    if (fabs(curvature - State::trackCurvature) >= 0.8f)
        State::carSpeed -= 5 * State::elapsedTime;
    if (State::carSpeed < 0)
    {

        State::carSpeed = 0;
    }
    if (State::carSpeed > 1)
    {

        State::carSpeed = 1;
    }
    State::distance += (70 * State::carSpeed) * State::elapsedTime;

    x = State::WIDTH / 2 + ((int)(State::WIDTH * (curvature - State::trackCurvature)) / 2.0) - 4;
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