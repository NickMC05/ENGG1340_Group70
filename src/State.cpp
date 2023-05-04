#include "State.h"
#include "Road.h"
#include <string>

void State::update()
{
    currentLapTime += elapsedTime;
    if (distance >= road->length)
    {
        distance -= road->length;
        if (best == 0 || currentLapTime < best)
        {
            best = currentLapTime;
            stats[0] = "Best: " + to_string(best);
        }
        currentLapTime = 0;
    }
    endLine = distance - road->length + 25;
    float finished = distance / road->length * 100;
    stats[1] = "Finished: " + to_string(finished).substr(0, 5) + "%";
    stats[2] = "Time: " + to_string(currentLapTime);
    stats[3] = "Speed: " + to_string(car->speed / car->maxSpeed * 100).substr(0, 5) + "%";
}