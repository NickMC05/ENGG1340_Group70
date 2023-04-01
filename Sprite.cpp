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

void draw(WINDOW *win)
{
    string t = "Hello this is example sprite";
    wprintw(win, t.c_str());
}