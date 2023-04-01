#ifndef MENU_H
#define MENU_H

class Menu
{
public:
    Menu();
    int run();
    void loading_screen();
    void home_screen(int input, int select, int max_choice);
    void credits_screen();

private:
    int input;
    int select = 1;
    int current_page = 1; // home_screen, play, options, credits, exit
    int max_choice = 4;   // adjustable depends on how many choices
};

#endif