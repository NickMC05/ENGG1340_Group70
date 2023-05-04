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