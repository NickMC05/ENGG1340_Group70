#ifndef STATE_H
#define STATE_H

#include <string>
#include <vector>
#include <utility>
#include <list>

using namespace std;

class State
{
public:
    static char key; // current key input
    static vector<vector<int> > graphic;

    static float carDistance;    // Distance car has travelled around track
    static float carCurvature;   // Current track curvature, lerped between track sections
    static float trackCurvature; // Accumulation of track curvature
    static float trackDistance;  // Total distance of track

    static float carPosition;     // Current car position
    static float playerCurvature; // Accumulation of player curvature
    static float carSpeed;        // Current player speed

    static vector<pair<float, float> > vecTrack; // Track sections, sharpness of bend, length of section

    static list<float> listLapTimes; // List of previous lap times
    static float fCurrentLapTime;    // Current lap time

    static int WIDTH;
    static int HEIGHT;
};

#endif