#include "Sprite.h"

#include <fstream>

Sprite::Sprite(const char* path)
{
    ifstream reader;
    reader.open(path);
    int val;
    while(reader>>val)
    {
        pixel.push_back(val);
    }
}

void Sprite::draw()
{
    string t = "Hello this is example sprite";
    printw(t.c_str());
}