#include "Background.h"
#include "Sprite.h"
#include <ncurses.h>
#include <string>
#include <fstream>

void Background::init()
{
    // Load the background from a file and store it in a vector of strings
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
    // Create a new sprite for each horizontal slice of the background
    for (int a = 0; a < 239; a += 2)
    {
        // Write a temporary file containing the current slice of the background
        ofstream fout;
        fout.open("temp.txt");
        fout << 100 << ' ' << 25 << endl;
        for (string line : backgorundRaw)
        {
            // Code will try to read from left to right
            // When it reaches end of the line we want to start read from start again
            // So this code basically handles that

            // If the chunks can be taken directly in from right to left
            if (a < 39)
            {
                fout << line.substr(a, 199);
            }
            // Get everything till the end and continue from the right most until there are 100 pixels
            else
            {
                fout << line.substr(a, 239 - a) << ' ' << line.substr(0, a - 41);
            }
            fout << endl;
        }

        // Create a new sprite from the temporary file and add it to the sprite array
        sprite[a / 2].path = "temp.txt";
        sprite[a / 2].state = state;
        sprite[a / 2].init();
        fout.close();
        remove("temp.txt");
    }
}

void Background::draw()
{
    // Determine which slice of the background to draw based on the current curvature of the road
    int a = (state->WIDTH / 2 + ((int)(state->WIDTH * road->totalCurvature) / 2)) % 120;
    if (a < 0)
    {
        a = 120 + a;
    }
    // Draw the sprite at the appropriate location which is 0, 0
    // 0,0 is top left of the screen
    sprite[a].draw(0, 0);
}
