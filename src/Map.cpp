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

            float fPerspective = (float)y / (mapHeight / 2.0f);

            float fMiddlePoint = 0.5f + State::currentCurvature * powf((1.0f - fPerspective), 3);
            float fRoadWidth = 0.1f + fPerspective * 0.88f;
            float fClipWidth = fRoadWidth * 0.15f;

            fRoadWidth *= 0.5f;

            int nLeftGrass = (fMiddlePoint - fRoadWidth - fClipWidth) * mapWidth;
            int nLeftClip = (fMiddlePoint - fRoadWidth) * mapWidth;
            int nRightClip = (fMiddlePoint + fRoadWidth) * mapWidth;
            int nRightGrass = (fMiddlePoint + fRoadWidth + fClipWidth) * mapWidth;

            int nRow = (mapHeight / 2) + y;

            int nClipColour = 0;
            if (sinf(20.0f * powf(1.0f - fPerspective, 3) + State::distance * 0.1f) > 0.0f)
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