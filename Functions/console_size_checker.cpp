#include <iostream>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
using namespace std;

int main ()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    printf ("lines %d\n", w.ws_row);
    printf ("columns %d\n", w.ws_col);
}