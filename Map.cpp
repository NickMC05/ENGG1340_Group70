#include <ncurses.h>

int main() {
    initscr();
    //start_color();
    //noecho();
    //nodelay(stdscr, true);

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

    refresh();
    getch();

    endwin();
    return 0;
}
