#include "Sprite.h"
#include "State.h"
#include <fstream>

void Sprite::init()
{
    ifstream reader;
    reader.open(path);
    int val;
    reader >> sWidth >> sHeight;
    while (reader >> val)
    {
        pixel.push_back(val);
    }
}

void Sprite::draw(int x, int y)
{
    for (int i = 0; i < sHeight; i++)
    {
        for (int j = 0; j < sWidth; j++)
        {
            if (pixel[i * sWidth + j] != 0)
                state->graphic[i + y][j + x] = pixel[i * sWidth + j];
        }
    }
}