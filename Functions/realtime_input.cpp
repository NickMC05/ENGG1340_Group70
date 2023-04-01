#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <ncurses.h>
using namespace std;

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    cout << "\033[22;0H";
    printw("hi");
    cout << "you" << endl;
    int ch;
    while ((ch = getch()) != KEY_F(1)) {
        if (ch == 'q' || ch == 'Q') {
            cout << "quitting" << endl;
            usleep(1000000);
            break;
        }
        cout << ch << endl;
    }
    endwin();
    return 0;
}
