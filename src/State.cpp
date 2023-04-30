#include "State.h"

int State::WIDTH = 80;
int State::HEIGHT = 40;
vector<vector<int>> State::graphic = vector<vector<int>>(50, vector<int>(100, 5));
char State::key = 'w';

float State::elapsedTime = 0;
float State::distance = 0;
float State::currentCurvature = 0.0f; // Current track curvature, lerped between track sections
float State::trackCurvature = 0.0f;   // Accumulation of track curvature
float State::trackDistance = 0.0f;    // Total distance of track
float State::carSpeed = 0.0f;         // Current player speed

vector<pair<float, float>> State::vecTrack; // Track sections, sharpness of bend, length of section

list<float> State::listLapTimes = {0, 0, 0, 0, 0}; // List of previous lap times
float State::currentLapTime = 0;

void State::update()
{
    float offset = 0;
    int trackSection = 0;
    currentLapTime += elapsedTime;
    if (distance >= trackDistance)
    {
        distance -= trackDistance;
        listLapTimes.push_front(currentLapTime);
        listLapTimes.pop_back();
        currentLapTime = 0;
    }
    while (trackSection < vecTrack.size() && offset <= distance)
    {
        offset += vecTrack[trackSection].second;
        trackSection++;
    }
    float targetCurvature = vecTrack[trackSection - 1].first;
    float trackCurveDiff = (targetCurvature - currentCurvature) * elapsedTime * carSpeed;
    currentCurvature += trackCurveDiff;
    trackCurvature += (currentCurvature)*elapsedTime * carSpeed;
}