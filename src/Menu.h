#ifndef MENU_H
#define MENU_H

class Menu
{
public:
    Menu();
    int run();
    void loading_screen();
    void home_screen(int input, int select, int max_choice);
    void options_screen(int select, bool choosing_mode_1, bool choosing_mode_2, int choice_1, int choice_2);
    void credits_screen();

private:
    int input;
    int select = 1;
    int current_page = 1; // home_screen, play, options, credits, exit
    int max_choice = 4;   // adjustable depends on how many choices
    int difficulty = 1;   // 1 easy, 2 medium, 3 hard
    int car_color = 1;    // 1 red, 2 yellow, 3 cyan
};

#endif