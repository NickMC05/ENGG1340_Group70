#include <ncurses.h>

int main() {
    initscr();
    start_color();
    noecho();
    nodelay(stdscr, true);

    for (int y = 0; y < 200/2; y++) {
        for (int x = 0; x < 200; x++) {

            float fMiddlePoint = 0.5f;
            float fRoadWidth = 0.6f;
            float fClipWidth = fRoadWidth * 0.15f;

            fRoadWidth *= 0.5f;

            int nLeftGrass = (fMiddlePoint - fRoadWidth - fClipWidth) * 200;
            int nLeftClip = (fMiddlePoint - fRoadWidth) * 200;
            int nRightClip = (fMiddlePoint + fRoadWidth) * 200;
            int nRightGrass = (fMiddlePoint + fRoadWidth + fClipWidth) * 200;

            int nRow = 200/2 + y;

            if (x >= 0 && x < nLeftGrass) {
                mvprintw(nRow, x, "|");
            }
            if (x >= nLeftGrass && x < nLeftClip) {
                mvprintw(nRow, x, "#");
            }
            if (x >= nLeftClip && x < nRightClip) {
                mvprintw(nRow, x, ".");
            }
            if (x >= nRightClip && x < nRightGrass) {
                mvprintw(nRow, x, "#");
            }
            if (x >= nRightGrass && x < 200) {
                mvprintw(nRow, x, "|");
            }

        }
    }

    getch(); // Wait for user input

    endwin(); // Clean up ncurses
    return 0;
}
