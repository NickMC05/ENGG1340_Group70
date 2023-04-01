#include "Sprite.h"

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
    for (int i = 0; i < sHeight; i++)
    {
        for (int j = 0; j < sWidth; j++)
        {
            if(pixel[i * sWidth + j] == 1)
            {
                attron(COLOR_PAIR(1));
            }
            if(pixel[i * sWidth + j] == 2)
            {
                attron(COLOR_PAIR(2));
            }
            if(pixel[i * sWidth + j] == 3)
            {
                attron(COLOR_PAIR(3));
            }
            mvprintw(y,x,"  ");
        }
        printw("\n");
    }
    
}