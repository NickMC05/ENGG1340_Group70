#include "Sprite.h"
#include "State.h"
#include <fstream>

// We will be using ifstream to load the file
// All sprite file should start with width then height
// Then it should have width * height integers which is color value
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
    reader.close();
}

// update state->graphic value at x, y position with sprite color
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
