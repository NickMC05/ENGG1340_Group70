#include <ncurses.h>

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

    for (int y = 0; y < 50/2; y++) {
        for (int x = 0; x < 200; x++) {

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

            if (x >= 0 && x < nLeftGrass) {
                attron(COLOR_PAIR(4));
                mvprintw(nRow, x, " ");
                attroff(COLOR_PAIR(4));
            }
            if (x >= nLeftGrass && x < nLeftClip) {
                attron(COLOR_PAIR(1));
                mvprintw(nRow, x, " ");
                attroff(COLOR_PAIR(1));
            }
            if (x >= nLeftClip && x < nRightClip) {
                attron(COLOR_PAIR(5));
                mvprintw(nRow, x, " ");
                attroff(COLOR_PAIR(5));
            }
            if (x >= nRightClip && x < nRightGrass) {
                attron(COLOR_PAIR(1));
                mvprintw(nRow, x, " ");
                attroff(COLOR_PAIR(1));
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
