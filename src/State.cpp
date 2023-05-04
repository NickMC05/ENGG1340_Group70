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
        stats[1] = "Last: " + to_string(currentLapTime);
        currentLapTime = 0;
    }
    endLine = distance - road->length + 25;
    float finished = distance / road->length * 100;
    stats[2] = "Finished: " + to_string(finished).substr(0, 5) + "%";
    stats[3] = "Time: " + to_string(currentLapTime);
    stats[4] = "Speed: " + to_string(car->speed / car->maxSpeed * 100).substr(0, 5) + "%";
}