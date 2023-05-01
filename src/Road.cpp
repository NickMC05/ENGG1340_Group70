#include "Road.h"
#include "State.h"
#include "Car.h"

void Road::update()
{
    float offset = 0;
    int index = 0;

    while (index < sections.size() && offset <= state->distance)
    {
        offset += sections[index].second;
        index++;
    }
    float targetCurvature = sections[index - 1].first;
    float trackCurveDiff = (targetCurvature - currentCurvature) * state->elapsedTime * car->speed;
    currentCurvature += trackCurveDiff;
    totalCurvature += (currentCurvature)*state->elapsedTime * car->speed;
}