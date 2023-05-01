#include "Map.h"
#include "State.h"
#include "Road.h"

void Map::draw()
{

    for (int y = 0; y < state->HEIGHT / 2; y++)
    {
        for (int x = 0; x < state->WIDTH; x++)
        {

            float fPerspective = (float)y / (state->HEIGHT / 2.0f);

            float fMiddlePoint = 0.5f + road->currentCurvature * powf((1.0f - fPerspective), 3);
            float fRoadWidth = 0.1f + fPerspective * 0.8f;
            float fClipWidth = fRoadWidth * 0.15f;

            fRoadWidth *= 0.5f;

            int nLeftGrass = (fMiddlePoint - fRoadWidth - fClipWidth) * state->WIDTH;
            int nLeftClip = (fMiddlePoint - fRoadWidth) * state->WIDTH;
            int nRightClip = (fMiddlePoint + fRoadWidth) * state->WIDTH;
            int nRightGrass = (fMiddlePoint + fRoadWidth + fClipWidth) * state->WIDTH;

            int nRow = (state->HEIGHT / 2) + y;

            int nClipColour = 0;
            if (sinf(20.0f * powf(1.0f - fPerspective, 3) + state->distance * 0.1f) > 0.0f)
            {
                nClipColour = 1;
            }
            else
            {
                nClipColour = 5;
            }

            if (x >= 0 && x < nLeftGrass)
            {
                state->graphic[nRow][x] = 4;
            }
            if (x >= nLeftGrass && x < nLeftClip)
            {
                state->graphic[nRow][x] = nClipColour;
            }
            if (x >= nLeftClip && x < nRightClip)
            {
                state->graphic[nRow][x] = 2;
            }
            if (x >= nRightClip && x < nRightGrass)
            {
                state->graphic[nRow][x] = nClipColour;
            }
            if (x >= nRightGrass && x < 200)
            {
                state->graphic[nRow][x] = 4;
            }
        }
    }
}