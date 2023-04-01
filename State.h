//

#ifndef STATE_H
#define STATE_H

#include <vector>
#include <utility>
#include <list>
using namespace std;

struct State
{
    float carDistance = 0.0f;    // Distance car has travelled around track
    float carCurvature = 0.0f;   // Current track curvature, lerped between track sections
    float trackCurvature = 0.0f; // Accumulation of track curvature
    float trackDistance = 0.0f;  // Total distance of track

    float carPosition = 0.0f;     // Current car position
    float playerCurvature = 0.0f; // Accumulation of player curvature
    float carSpeed = 0.0f;        // Current player speed

    vector<pair<float, float>> vecTrack; // Track sections, sharpness of bend, length of section

    list<float> listLapTimes; // List of previous lap times
    float fCurrentLapTime;    // Current lap time
};

#endif