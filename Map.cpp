#include "Map.h"
#include "State.h"
Map::Map(int width, int height)
{
    mapWidth = width;
    mapHeight = height;
}

void Map::draw()
{
    vector<vector<int>> &graphic = State::graphic;

    for (int y = 0; y < mapHeight / 2; y++)
    {
        for (int x = 0; x < mapWidth; x++)
        {
            float &fDistance = State::carDistance; // Player's current distance here

            float fPerspective = (float)y / (mapHeight / 2.0f);

            float &fCurvature = State::trackCurvature; // Current Curvature of Car (Used for smooth turns)

            static chrono::steady_clock::time_point currentTime;
            auto newTime = std::chrono::steady_clock::now();                                                                     // Current Time
            float fElapsedTime = chrono::duration_cast<std::chrono::nanoseconds>(newTime - currentTime).count() / 1000000000.0f; // 100000000.0f;    // Time between Loops
            currentTime = std::chrono::steady_clock::now();                                                                      // Updates Time

            float fOffset = 0;
            int nTrackSection = 0; // index of vecTrack

            while (nTrackSection <= State::vecTrack.size() && fOffset <= fDistance)
            {
                fOffset += State::vecTrack[nTrackSection].second;
                nTrackSection++;
            };

            float ftargetCurvature = State::vecTrack[nTrackSection - 1].first;
            float fTrackCurvatureDiff = (ftargetCurvature - fCurvature) * fElapsedTime;
            fCurvature += fTrackCurvatureDiff; // For smoothness, must add 0.000001
            float fMiddlePoint = 0.5f + fCurvature * powf((1.0f - fPerspective), 3);
            float fRoadWidth = 0.1f + fPerspective * 0.88f;
            float fClipWidth = fRoadWidth * 0.15f;

            fRoadWidth *= 0.5f;

            int nLeftGrass = (fMiddlePoint - fRoadWidth - fClipWidth) * mapWidth;
            int nLeftClip = (fMiddlePoint - fRoadWidth) * mapWidth;
            int nRightClip = (fMiddlePoint + fRoadWidth) * mapWidth;
            int nRightGrass = (fMiddlePoint + fRoadWidth + fClipWidth) * mapWidth;

            int nRow = (mapHeight / 2) + y;

            int nClipColour = 0;
            if (sinf(20.0f * powf(1.0f - fPerspective, 3) + fDistance * 0.1f) > 0.0f)
            {
                nClipColour = 1;
            }
            else
            {
                nClipColour = 5;
            }

            if (x >= 0 && x < nLeftGrass)
            {
                graphic[nRow][x] = 4;
            }
            if (x >= nLeftGrass && x < nLeftClip)
            {
                graphic[nRow][x] = nClipColour;
            }
            if (x >= nLeftClip && x < nRightClip)
            {
                graphic[nRow][x] = 2;
            }
            if (x >= nRightClip && x < nRightGrass)
            {
                graphic[nRow][x] = nClipColour;
            }
            if (x >= nRightGrass && x < 200)
            {
                graphic[nRow][x] = 4;
            }
        }
    }
}