#include "Sprite.h"
#include "State.h"
#include <fstream>

Sprite::Sprite(const char* path)
{
    ifstream reader;
    reader.open(path);
    int val;
    reader>>sWidth>>sHeight;
    while(reader>>val)
    {
        pixel.push_back(val);
    }
}

void Sprite::draw(int x, int y)
{
    vector<vector<int>> &v = State::graphic;
    for (int i = 0; i < sHeight; i++)
    {
        for (int j = 0; j < sWidth; j++)
        {
            if(pixel[i * sWidth + j] != 0)
                v[i+y][j+x] = pixel[i * sWidth + j];                
        }
    }
}