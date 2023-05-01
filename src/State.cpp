#include "State.h"
#include "Road.h"

void State::update()
{
    currentLapTime += elapsedTime;
    if (distance >= road->length)
    {
        distance -= road->length;
        lapTimes.push_back(currentLapTime);
        currentLapTime = 0;
    }
}