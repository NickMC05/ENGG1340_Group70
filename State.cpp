#include "State.h"

int State::WIDTH = 100;
int State::HEIGHT = 50;
vector<vector<int>> State::graphic = vector<vector<int>>(50, vector<int>(100, 5));
char State::key = 'w';

float State::carDistance = 0.0f;
float State::carCurvature = 0.0f;    // Current track curvature, lerped between track sections
float State::trackCurvature = 0.0f;  // Accumulation of track curvature
float State::trackDistance = 0.0f;   // Total distance of track
float State::carPosition = 45;       // Current car position
float State::playerCurvature = 0.0f; // Accumulation of player curvature
float State::carSpeed = 0.0f;        // Current player speed

// vector<pair<float, float>> State::vecTrack; // Track sections, sharpness of bend, length of section

// list<float> State::listLapTimes; // List of previous lap times
float State::fCurrentLapTime; // Current lap time
