#include "Background.h"
#include "Sprite.h"
#include <ncurses.h>
#include <string>
#include <fstream>

void Background::init()
{
    int count = 120;
    sprite = new Sprite[120];
    ifstream fin;
    fin.open("assets/background.txt");
    string inputLine;
    vector<string> backgorundRaw;
    while (getline(fin, inputLine))
    {
        backgorundRaw.push_back(inputLine);
    }
    for (int a = 0; a < 239; a += 2)
    {
        ofstream fout;
        fout.open("temp.txt");
        fout << 100 << ' ' << 25 << endl;
        for (string line : backgorundRaw)
        {
            if (a < 39)
            {
                fout << line.substr(a, 199);
            }
            else
            {
                fout << line.substr(a, 239 - a) << ' ' << line.substr(0, a - 41);
            }
            fout << endl;
        }
        sprite[a / 2].path = "temp.txt";
        sprite[a / 2].state = state;
        sprite[a / 2].init();
        fout.close();
        remove("temp.txt");
    }
}

void Background::draw()
{
    int a = (state->WIDTH / 2 + ((int)(state->WIDTH * road->totalCurvature) / 2)) % 120;
    if (a < 0)
    {
        a = 120 + a;
    }
    sprite[a].draw(0, 0);
}
