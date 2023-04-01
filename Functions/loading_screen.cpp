#include <iostream>
#include <cstdlib>
#include <unistd.h>
using namespace std;

int main(void)
{
    system("clear");
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << "\x1B[31m█░░ █▀█ ▄▀█ █▀▄ █ █▄░█ █▀▀\033[0m" << endl;
    cout << "\x1B[31m█▄▄ █▄█ █▀█ █▄▀ █ █░▀█ █▄█\033[0m" << endl;
    cout << endl;
    for (int i = 0; i <= 70; i++) {
        cout << "\033[4;0H"; // change coordinate here
        for (int j = 0; j < i; j++) {
                cout << "\033[31;41m \033[0m";
        }
        for (int j = i; j < 70; j++) {
                cout << "\033[3;100;30m \033[0m";
        }
        cout << endl;
        usleep(30*(70-i)*(70-i));
    }
    usleep(3000000);
    system("clear");
}