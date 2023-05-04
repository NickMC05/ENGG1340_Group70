#include "Map.h"
#include "State.h"
#include "Road.h"

void Map::draw()
{

    for (int y = 0; y < state->HEIGHT / 2; y++)
    {
        for (int x = 0; x < state->WIDTH; x++)
        {
            // Calculate the perspective of the current row
            float fPerspective = (float)y / (state->HEIGHT / 2.0f);

            // Calculate the middle point of the road section and the road width at the current row
            float fMiddlePoint = 0.5f + road->currentCurvature * powf((1.0f - fPerspective), 3);
            float fRoadWidth = 0.1f + fPerspective * 0.8f;
            // Calculate the clip width, which is a portion of the road width that is not drivable
            float fClipWidth = fRoadWidth * 0.15f;

            // Scale the road width by 0.5 to center it on the middle point
            fRoadWidth *= 0.5f;

            // Calculate the pixel indices of the left and right grass, clip, and road sections
            int nLeftGrass = (fMiddlePoint - fRoadWidth - fClipWidth) * state->WIDTH;
            int nLeftClip = (fMiddlePoint - fRoadWidth) * state->WIDTH;
            int nRightClip = (fMiddlePoint + fRoadWidth) * state->WIDTH;
            int nRightGrass = (fMiddlePoint + fRoadWidth + fClipWidth) * state->WIDTH;
            
            // Calculate the row index for the current pixel
            int nRow = (state->HEIGHT / 2) + y;

            // Choose the color of the clip based on a sine wave
            int nClipColour = 0;
            if (sinf(20.0f * powf(1.0f - fPerspective, 3) + state->distance * 0.1f) > 0.0f)
            {
                nClipColour = 1;
            }
            else
            {
                nClipColour = 5;
            }
            // Determine the color of the current pixel based on its position relative to the road
            if (x >= 0 && x < nLeftGrass)
            {
                state->graphic[nRow][x] = 4;
            }
            else if (x >= nLeftGrass && x < nLeftClip)
            {
                state->graphic[nRow][x] = nClipColour;
            }
            else if (x >= nLeftClip && x < nRightClip && y == state->endLine && x % 2 == 0)
            {
                state->graphic[nRow][x] = 5;
            }
            else if (x >= nLeftClip && x < nRightClip && state->endLine == y && x % 2 != 0)
            {
                state->graphic[nRow][x] = 9;
            }
            else if (x >= nLeftClip && x < nRightClip)
            {
                state->graphic[nRow][x] = 2;
            }
            else if (x >= nRightClip && x < nRightGrass)
            {
                state->graphic[nRow][x] = nClipColour;
            }
            else if (x >= nRightGrass && x < 200)
            {
                state->graphic[nRow][x] = 4;
            }
        }
    }
}