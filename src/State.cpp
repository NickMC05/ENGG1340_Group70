#include "State.h"
#include "Road.h"
#include <string>

void State::update()
{
    // Update the current lap time
    currentLapTime += elapsedTime;

    // Check if the car has completed a lap
    if (distance >= road->length)
    {
        // Subtract the length of the road from the distance travelled
        distance -= road->length;

        // Check if the current lap time is faster than the previous best time
        if (best == 0 || currentLapTime < best)
        {
            // Update the best time and the corresponding lap time statistic
            best = currentLapTime;
            stats[0] = "Best: " + to_string(best);
        }
        // Update the last lap time statistic and reset the current lap time
        stats[1] = "Last: " + to_string(currentLapTime);
        currentLapTime = 0;
    }
    endLine = distance - road->length + 25;
    // Update the finished percentage and the corresponding statistic
    float finished = distance / road->length * 100;
    stats[2] = "Finished: " + to_string(finished).substr(0, 5) + "%";
    stats[3] = "Time: " + to_string(currentLapTime);
    stats[4] = "Speed: " + to_string(car->speed / car->maxSpeed * 100).substr(0, 5) + "%";
}