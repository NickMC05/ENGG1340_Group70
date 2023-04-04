#include <ncurses.h>
#include <cmath>

int main() {
    initscr();
    start_color();
    //noecho();
    //nodelay(stdscr, true);
    
    // Set color pairs (still not sure how to use init_pair from other scripts)
    init_pair(1, COLOR_RED, COLOR_RED);
    init_pair(2, COLOR_BLUE, COLOR_BLUE);
    init_pair(3, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(4, COLOR_GREEN, COLOR_GREEN);
    init_pair(5, COLOR_WHITE, COLOR_WHITE);
    init_pair(6, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(9, COLOR_BLACK, COLOR_BLACK);
    
    attron(COLOR_PAIR(2));
    for (int y = 0; y < 50; y++)
    {
        for (int x = 0; x < 200; x++)
        {
            mvprintw(y,x," ");
        }
    }
    attroff(COLOR_PAIR(2));

    for (int y = 0; y < 50/2; y++) {
        for (int x = 0; x < 200; x++) {

            float fDistance = 0.0f; // Player's current distance here

            float fPerspective = (float)y / (50 / 2.0f);

            float fMiddlePoint = 0.5f;
            float fRoadWidth = 0.1f + fPerspective * 0.8f;
            float fClipWidth = fRoadWidth * 0.15f;

            fRoadWidth *= 0.5f;

            int nLeftGrass = (fMiddlePoint - fRoadWidth - fClipWidth) * 200;
            int nLeftClip = (fMiddlePoint - fRoadWidth) * 200;
            int nRightClip = (fMiddlePoint + fRoadWidth) * 200;
            int nRightGrass = (fMiddlePoint + fRoadWidth + fClipWidth) * 200;

            int nRow = 50/2 + y;

            int nClipColour = 0;
            if (sinf(20.0f * powf(1.0f - fPerspective, 3) + fDistance * 0.1f) > 0.0f) {
                nClipColour = 1;
            } else {
                nClipColour = 5;
            }

            if (x >= 0 && x < nLeftGrass) {
                attron(COLOR_PAIR(4));
                mvprintw(nRow, x, " ");
                attroff(COLOR_PAIR(4));
            }
            if (x >= nLeftGrass && x < nLeftClip) {
                attron(COLOR_PAIR(nClipColour));
                mvprintw(nRow, x, " ");
                attroff(COLOR_PAIR(nClipColour));
            }
            if (x >= nLeftClip && x < nRightClip) {
                attron(COLOR_PAIR(9));
                mvprintw(nRow, x, " ");
                attroff(COLOR_PAIR(9));
            }
            if (x >= nRightClip && x < nRightGrass) {
                attron(COLOR_PAIR(nClipColour));
                mvprintw(nRow, x, " ");
                attroff(COLOR_PAIR(nClipColour));
            }
            if (x >= nRightGrass && x < 200) {
                attron(COLOR_PAIR(4));
                mvprintw(nRow, x, " ");
                attroff(COLOR_PAIR(4));
            }

        }
    }

    refresh();
    getch();

    endwin();
    return 0;
}
