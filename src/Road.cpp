#include "Road.h"
#include "State.h"
#include "Car.h"
#include <cmath>

// this functions controls the length and curvature of the track
void Road::init()
{
    float totalLength = 200;
    while (totalLength < length)
    {
        // random curvature
        // higher chance for straighter road
        float curvature = pow(50, (((float)(rand() % 50)) / 50) - 1);

        // bend left or right
        int sign = rand() % 2;
        if (sign == 1)
        {
            curvature *= -1;
        }

        // random length
        float l = rand() % 500;
        // total length is constant
        if (l > length - totalLength)
        {
            l = length - totalLength;
        }
        sections.push_back(make_pair(curvature, l));

        // record total pushed length
        totalLength += l;
    }
    sections.push_back(make_pair(0, 200));
}
void Road::update()
{
    // Determine the offset of the car from the start of the current road section
    float offset = 0;
    int index = 0;

    while (index < sections.size() && offset <= state->distance)
    {
        offset += sections[index].second;
        index++;
    }
    // Determine the target curvature of the current road section
    float targetCurvature = sections[index - 1].first;
    // Calculate the change in curvature based on the difference between the current and target curvatures
    float trackCurveDiff = (targetCurvature - currentCurvature) * state->elapsedTime * car->speed;
    currentCurvature += trackCurveDiff;
    // Add the change in curvature to the total curvature so far
    totalCurvature += (currentCurvature)*state->elapsedTime * car->speed;
}