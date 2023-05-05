#include "Menu.h"
#include <ncurses.h>
#include <sys/ioctl.h>
#include <unistd.h>

Menu::Menu()
{
}
// 0 = play, 1 = exit
int Menu::run()
{
    printw("Before playing the game, please make sure that the terminal size is enough for the game to be printed.\n");
    printw("The minimum requirement of the terminal size is 201x50.\n");
    printw("You can decrease font size to increase terminal size.\n");
    printw("Press any key to continue.");
    while ((input = getch()) != KEY_F(1))
    {
        // Check size
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        erase();
        if (w.ws_row >= 50 && w.ws_col >= 201)
        { // Scrren size is enough
            break;
        }
        else
        { // Not yet
            printw("Before playing the game, please make sure that the terminal size is enough for the game to be printed.\n");
            printw("The minimum requirement of the terminal size is 201x50.\n");
            printw("You can decrease font size to increase terminal size.\n\n");
            printw("Current terminal size: %dx%d", w.ws_col, w.ws_row);
        }
    }
    loading_screen();

    while (true)
    {

        if (current_page == 1)
        {
            // Home screen choosing
            home_screen(input, select, max_choice);
            while ((input = getch()) != KEY_F(1))
            {
                // Receiving input
                if (input == 'W' || input == 'w' || input == 'A' || input == 'a')
                { // Up
                    select -= 1;
                }
                else if (input == 'S' || input == 's' || input == 'D' || input == 'd')
                { // Down
                    select += 1;
                }
                else if (input == 10)
                { // Enter
                    if (select == 1)
                    {
                        current_page = 2;
                    }
                    else if (select == 2)
                    {
                        current_page = 3; // change to options
                    }
                    else if (select == 3)
                    {
                        current_page = 4;
                    }
                    else if (select == 4)
                    {
                        current_page = 5;
                    }
                    erase();
                    break;
                }
                if (select <= 0)
                {
                    select = max_choice;
                }
                else if (select > max_choice)
                {
                    select = 1;
                }

                // Screen
                home_screen(input, select, max_choice);
            }
        }
        else if (current_page == 2)
        {
            erase();
            return 0;
        }

        else if (current_page == 3)
        {
            int selection = 1; // 1 difficulty, 2 car color, 3 go back
            options_screen(selection, false, false, difficulty, car_color);
            while ((input = getch()) != KEY_F(1))
            {
                options_screen(selection, false, false, difficulty, car_color);
                // Receiving input
                if (input == 'W' || input == 'w' || input == 'A' || input == 'a')
                { // Up
                    selection -= 1;
                    options_screen(selection, false, false, difficulty, car_color);
                }
                else if (input == 'S' || input == 's' || input == 'D' || input == 'd')
                { // Down
                    selection += 1;
                    options_screen(selection, false, false, difficulty, car_color);
                }
                else if (input == 10)
                {                       // Enter
                    if (selection == 1) // difficulty
                    {
                        int pick = difficulty;
                        options_screen(selection, true, false, pick, car_color);
                        while ((input = getch()) != KEY_F(1))
                        {
                            options_screen(selection, true, false, pick, car_color);
                            // Receiving input
                            if (input == 'A' || input == 'a')
                            { // Up
                                pick -= 1;
                            }
                            else if (input == 'D' || input == 'd')
                            { // Down
                                pick += 1;
                            }
                            else if (input == 10)
                            {
                                break;
                            }
                            if (pick <= 0)
                            {
                                pick = 3;
                            }
                            else if (pick > 3)
                            {
                                pick = 1;
                            }
                            options_screen(selection, true, false, pick, car_color);
                        }
                        difficulty = pick;
                        state->difficulty = difficulty;
                    }
                    else if (selection == 2) // car color
                    {
                        int pick = car_color;
                        options_screen(selection, false, true, difficulty, pick);
                        while ((input = getch()) != KEY_F(1))
                        {
                            options_screen(selection, false, true, difficulty, pick);
                            // Receiving input
                            if (input == 'A' || input == 'a')
                            { // Up
                                pick -= 1;
                            }
                            else if (input == 'D' || input == 'd')
                            { // Down
                                pick += 1;
                            }
                            else if (input == 10)
                            {
                                break;
                            }
                            if (pick <= 0)
                            {
                                pick = 3;
                            }
                            else if (pick > 3)
                            {
                                pick = 1;
                            }
                            options_screen(selection, false, true, difficulty, pick);
                        }
                        car_color = pick;
                        state->carColor = car_color;
                    }
                    else if (selection == 3)
                    {
                        current_page = 1;
                        break;
                    }
                }
                if (selection <= 0)
                {
                    selection = 3;
                }
                else if (selection > 3)
                {
                    selection = 1;
                }
                options_screen(selection, false, false, difficulty, car_color);
            }
        }
        else if (current_page == 4)
        {
            credits_screen();
            while ((input = getch()) != KEY_F(1))
            {
                break;
            }
            current_page = 1;
        }
        else if (current_page == 5)
        {
            erase();
            return 1;
        }
    }
    return 1;
}

void Menu::loading_screen()
{
    // Set color pairs (still not sure how to use init_pair from other scripts)

    // Code
    erase();
    attron(COLOR_PAIR(1));
    for (int y = 0; y < 50; y++)
    {
        for (int x = 0; x < 200; x++)
        {
            mvprintw(y, x, " ");
        }
    }
    mvprintw(22, 80, " _    ___   _   ___ ___ _  _  ____      ");
    mvprintw(23, 80, "| |  / _ \\ /_\\ |   \\_ _| \\| |/ ___| ");
    mvprintw(24, 80, "| |_| (_) / _ \\| |) | || .` | (__|     ");
    mvprintw(25, 80, "|____\\___/_/ \\_\\___/___|_|\\_|\\____|");
    attroff(COLOR_PAIR(1));
    move(0, 0);
    refresh();
    attron(COLOR_PAIR(1));
    for (int i = 0; i <= 80; i++)
    {
        for (int j = 0; j < i; j++)
        {
            mvprintw(28, j + 60, "#");
        }
        for (int j = i; j < 80; j++)
        {
            mvprintw(28, j + 60, "_");
        }
        usleep((80 - i) * (80 - i));
        move(0, 0);
        refresh();
    }
    attroff(COLOR_PAIR(1));
    usleep(700000);
}

// Home screen
void Menu::home_screen(int input, int select, int max_choice)
{
    // Set color pairs (still not sure how to use init_pair from other scripts)

    erase();
    attron(COLOR_PAIR(1));
    for (int y = 0; y < 50; y++)
    {
        for (int x = 0; x < 200; x++)
        {
            mvprintw(y, x, " ");
        }
    }
    // Title
    mvprintw(2, 0, "                     CCCCCCCCCCCCC                                          RRRRRRRRRRRRRRRRR                  AAA                  CCCCCCCCCCCCCEEEEEEEEEEEEEEEEEEEEEERRRRRRRRRRRRRRRRR                ");
    mvprintw(3, 0, "                  CCC::::::::::::C                                          R::::::::::::::::R                A:::A              CCC::::::::::::CE::::::::::::::::::::ER::::::::::::::::R               ");
    mvprintw(4, 0, "                CC:::::::::::::::C                                          R::::::RRRRRR:::::R              A:::::A           CC:::::::::::::::CE::::::::::::::::::::ER::::::RRRRRR:::::R              ");
    mvprintw(5, 0, "               C:::::CCCCCCCC::::C       +++++++              +++++++       RR:::::R     R:::::R            A:::::::A         C:::::CCCCCCCC::::CEE::::::EEEEEEEEE::::ERR:::::R     R:::::R             ");
    mvprintw(6, 0, "              C:::::C       CCCCCC       +:::::+              +:::::+         R::::R     R:::::R           A:::::::::A       C:::::C       CCCCCC  E:::::E       EEEEEE  R::::R     R:::::R             ");
    mvprintw(7, 0, "             C:::::C                     +:::::+              +:::::+         R::::R     R:::::R          A:::::A:::::A     C:::::C                E:::::E               R::::R     R:::::R             ");
    mvprintw(8, 0, "             C:::::C               +++++++:::::+++++++  +++++++:::::+++++++   R::::RRRRRR:::::R          A:::::A A:::::A    C:::::C                E::::::EEEEEEEEEE     R::::RRRRRR:::::R              ");
    mvprintw(9, 0, "             C:::::C               +:::::::::::::::::+  +:::::::::::::::::+   R:::::::::::::RR          A:::::A   A:::::A   C:::::C                E:::::::::::::::E     R:::::::::::::RR               ");
    mvprintw(10, 0, "             C:::::C               +:::::::::::::::::+  +:::::::::::::::::+   R::::RRRRRR:::::R        A:::::A     A:::::A  C:::::C                E:::::::::::::::E     R::::RRRRRR:::::R              ");
    mvprintw(11, 0, "             C:::::C               +++++++:::::+++++++  +++++++:::::+++++++   R::::R     R:::::R      A:::::AAAAAAAAA:::::A C:::::C                E::::::EEEEEEEEEE     R::::R     R:::::R             ");
    mvprintw(12, 0, "             C:::::C                     +:::::+              +:::::+         R::::R     R:::::R     A:::::::::::::::::::::AC:::::C                E:::::E               R::::R     R:::::R             ");
    mvprintw(13, 0, "              C:::::C       CCCCCC       +:::::+              +:::::+         R::::R     R:::::R    A:::::AAAAAAAAAAAAA:::::AC:::::C       CCCCCC  E:::::E       EEEEEE  R::::R     R:::::R             ");
    mvprintw(14, 0, "               C:::::CCCCCCCC::::C       +++++++              +++++++       RR:::::R     R:::::R   A:::::A             A:::::AC:::::CCCCCCCC::::CEE::::::EEEEEEEE:::::ERR:::::R     R:::::R             ");
    mvprintw(15, 0, "                CC:::::::::::::::C                                          R::::::R     R:::::R  A:::::A               A:::::ACC:::::::::::::::CE::::::::::::::::::::ER::::::R     R:::::R             ");
    mvprintw(16, 0, "                  CCC::::::::::::C                                          R::::::R     R:::::R A:::::A                 A:::::A CCC::::::::::::CE::::::::::::::::::::ER::::::R     R:::::R             ");
    mvprintw(17, 0, "                     CCCCCCCCCCCCC                                          RRRRRRRR     RRRRRRRAAAAAAA                   AAAAAAA   CCCCCCCCCCCCCEEEEEEEEEEEEEEEEEEEEEERRRRRRRR     RRRRRRR             ");
    mvprintw(49, 191, "@Group-70");

    // Screen

    mvprintw(20, 30, "               ____  __           ");
    mvprintw(21, 30, "              / __ \\/ /___ ___  __");
    mvprintw(22, 30, "             / /_/ / / __ `/ / / /");
    mvprintw(23, 30, "            / ____/ / /_/ / /_/ / ");
    mvprintw(24, 30, "           /_/   /_/\\__,_/\\__, /  ");
    mvprintw(25, 30, "                         /____/   ");

    mvprintw(28, 30, "              ____        __                    ");
    mvprintw(29, 30, "             / __ \\____  / /_(_)___  ____  _____");
    mvprintw(30, 30, "            / / / / __ \\/ __/ / __ \\/ __ \\/ ___/");
    mvprintw(31, 30, "           / /_/ / /_/ / /_/ / /_/ / / / (__  ) ");
    mvprintw(32, 30, "           \\____/ .___/\\__/_/\\____/_/ /_/____/  ");
    mvprintw(33, 30, "               /_/                              ");

    mvprintw(36, 30, "              ______              __  __");
    mvprintw(37, 30, "             / ____/_______  ____/ (_) /______");
    mvprintw(38, 30, "            / /   / ___/ _ \\/ __  / / __/ ___/");
    mvprintw(39, 30, "           / /___/ /  /  __/ /_/ / / /_(__  ) ");
    mvprintw(40, 30, "           \\____/_/   \\___/\\____/_/\\__/____/  ");

    mvprintw(43, 30, "               ______       __ ");
    mvprintw(44, 30, "              / ____/  __(_) /_");
    mvprintw(45, 30, "             / __/ | |/_/ / __/");
    mvprintw(46, 30, "            / /____>  </ / /_");
    mvprintw(47, 30, "           /_____/_/|_/_/\\__/");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(1));
    switch (select)
    {
    case 1:
        mvprintw(20, 30, "____           ____  __           ");
        mvprintw(21, 30, "\\ \\ \\         / __ \\/ /___ ___  __");
        mvprintw(22, 30, " \\ \\ \\       / /_/ / / __ `/ / / /");
        mvprintw(23, 30, " / / /      / ____/ / /_/ / /_/ / ");
        mvprintw(24, 30, "/_/_/      /_/   /_/\\__,_/\\__, /  ");
        mvprintw(25, 30, "                         /____/   ");
        break;
    case 2:
        mvprintw(28, 30, "____          ____        __                    ");
        mvprintw(29, 30, "\\ \\ \\        / __ \\____  / /_(_)___  ____  _____");
        mvprintw(30, 30, " \\ \\ \\      / / / / __ \\/ __/ / __ \\/ __ \\/ ___/");
        mvprintw(31, 30, " / / /     / /_/ / /_/ / /_/ / /_/ / / / (__  ) ");
        mvprintw(32, 30, "/_/_/      \\____/ .___/\\__/_/\\____/_/ /_/____/  ");
        mvprintw(33, 30, "               /_/                              ");
        break;
    case 3:
        mvprintw(36, 30, "____          ______              __  __");
        mvprintw(37, 30, "\\ \\ \\        / ____/_______  ____/ (_) /______");
        mvprintw(38, 30, " \\ \\ \\      / /   / ___/ _ \\/ __  / / __/ ___/");
        mvprintw(39, 30, " / / /     / /___/ /  /  __/ /_/ / / /_(__  ) ");
        mvprintw(40, 30, "/_/_/      \\____/_/   \\___/\\____/_/\\__/____/  ");
        break;
    case 4:
        mvprintw(43, 30, "____           ______       __ ");
        mvprintw(44, 30, "\\ \\ \\         / ____/  __(_) /_");
        mvprintw(45, 30, " \\ \\ \\       / __/ | |/_/ / __/");
        mvprintw(46, 30, " / / /      / /____>  </ / /_");
        mvprintw(47, 30, "/_/_/      /_____/_/|_/_/\\__/");
        break;
    }
    attroff(COLOR_PAIR(1));

    move(0, 0);
    refresh();
}

// Options screen
void Menu::options_screen(int select, bool choosing_mode_1, bool choosing_mode_2, int choice_1, int choice_2)
{
    // Set color pairs (still not sure how to use init_pair from other scripts)

    erase();
    attron(COLOR_PAIR(1));

    for (int y = 0; y < 50; y++)
    {
        for (int x = 0; x < 200; x++)
        {
            mvprintw(y, x, " ");
        }
    }

    mvprintw(2, 20, "________          __  .__                      ");
    mvprintw(3, 20, "\\_____  \\ _______/  |_|__| ____   ____   ______");
    mvprintw(4, 20, " /   |   \\\\____ \\   __\\  |/  _ \\ /    \\ /  ___/");
    mvprintw(5, 20, "/    |    \\  |_> >  | |  (  <_> )   |  \\\\___ \\ ");
    mvprintw(6, 20, "\\_______  /   __/|__| |__|\\____/|___|  /____  >");
    mvprintw(7, 20, "        \\/|__|                       \\/     \\/ ");

    switch (choice_1)
    {
    case 1:
        mvprintw(12, 20, "      _____  _  __  __ _            _ _                     ______                     ");
        mvprintw(13, 20, "     |  __ \\(_)/ _|/ _(_)          | | |              _    |  ____|                    ");
        mvprintw(14, 20, "     | |  | |_| |_| |_ _  ___ _   _| | |_ _   _      (_)   | |__   __ _ ___ _   _      ");
        mvprintw(15, 20, "     | |  | | |  _|  _| |/ __| | | | | __| | | |           |  __| / _` / __| | | |     ");
        mvprintw(16, 20, "     | |__| | | | | | | | (__| |_| | | |_| |_| |      _    | |___| (_| \\__ \\ |_| |     ");
        mvprintw(17, 20, "     |_____/|_|_| |_| |_|\\___|\\__,_|_|\\__|\\__, |     (_)   |______\\__,_|___/\\__, |     ");
        mvprintw(18, 20, "                                           __/ |                             __/ |     ");
        mvprintw(19, 20, "                                          |____/                            |____/     ");
        if (select == 1)
        {
            mvprintw(12, 20, "||||  _____  _  __  __ _            _ _                     ______                 ||||");
            mvprintw(13, 20, "||   |  __ \\(_)/ _|/ _(_)          | | |              _    |  ____|                  ||");
            mvprintw(14, 20, "||   | |  | |_| |_| |_ _  ___ _   _| | |_ _   _      (_)   | |__   __ _ ___ _   _    ||");
            mvprintw(15, 20, "||   | |  | | |  _|  _| |/ __| | | | | __| | | |           |  __| / _` / __| | | |   ||");
            mvprintw(16, 20, "||   | |__| | | | | | | | (__| |_| | | |_| |_| |      _    | |___| (_| \\__ \\ |_| |   ||");
            mvprintw(17, 20, "||   |_____/|_|_| |_| |_|\\___|\\__,_|_|\\__|\\__, |     (_)   |______\\__,_|___/\\__, |   ||");
            mvprintw(18, 20, "||                                         __/ |                             __/ |   ||");
            mvprintw(19, 20, "||||                                      |____/                            |____/ ||||");
        }
        if (choosing_mode_1)
        {
            mvprintw(12, 20, "      _____  _  __  __ _            _ _               ||||  ______                 ||||");
            mvprintw(13, 20, "     |  __ \\(_)/ _|/ _(_)          | | |              ||   |  ____|                  ||");
            mvprintw(14, 20, "     | |  | |_| |_| |_ _  ___ _   _| | |_ _   _       ||   | |__   __ _ ___ _   _    ||");
            mvprintw(15, 20, "     | |  | | |  _|  _| |/ __| | | | | __| | | |      ||   |  __| / _` / __| | | |   ||");
            mvprintw(16, 20, "     | |__| | | | | | | | (__| |_| | | |_| |_| |      ||   | |___| (_| \\__ \\ |_| |   ||");
            mvprintw(17, 20, "     |_____/|_|_| |_| |_|\\___|\\__,_|_|\\__|\\__, |      ||   |______\\__,_|___/\\__, |   ||");
            mvprintw(18, 20, "                                           __/ |      ||                     __/ |   ||");
            mvprintw(19, 20, "                                          |____/      ||||                  |____/ ||||");
        }
        break;
    case 2:
        mvprintw(12, 20, "      _____  _  __  __ _            _ _                     __  __          _ _                      ");
        mvprintw(13, 20, "     |  __ \\(_)/ _|/ _(_)          | | |              _    |  \\/  |        | (_)                     ");
        mvprintw(14, 20, "     | |  | |_| |_| |_ _  ___ _   _| | |_ _   _      (_)   | \\  / | ___  __| |_ _   _ _ __ ____      ");
        mvprintw(15, 20, "     | |  | | |  _|  _| |/ __| | | | | __| | | |           | |\\/| |/ _ \\/ _` | | | | | '_ ` _  \\     ");
        mvprintw(16, 20, "     | |__| | | | | | | | (__| |_| | | |_| |_| |      _    | |  | |  __/ (_| | | |_| | | | | | |     ");
        mvprintw(17, 20, "     |_____/|_|_| |_| |_|\\___|\\__,_|_|\\__|\\__, |     (_)   |_|  |_|\\___|\\__,_|_|\\__,_|_| |_| |_|     ");
        mvprintw(18, 20, "                                           __/ |                                                     ");
        mvprintw(19, 20, "                                          |____/                                                     ");
        if (select == 1)
        {
            mvprintw(12, 20, "||||  _____  _  __  __ _            _ _                     __  __          _ _                  ||||");
            mvprintw(13, 20, "||   |  __ \\(_)/ _|/ _(_)          | | |              _    |  \\/  |        | (_)                   ||");
            mvprintw(14, 20, "||   | |  | |_| |_| |_ _  ___ _   _| | |_ _   _      (_)   | \\  / | ___  __| |_ _   _ _ __ ____    ||");
            mvprintw(15, 20, "||   | |  | | |  _|  _| |/ __| | | | | __| | | |           | |\\/| |/ _ \\/ _` | | | | | '_ ` _  \\   ||");
            mvprintw(16, 20, "||   | |__| | | | | | | | (__| |_| | | |_| |_| |      _    | |  | |  __/ (_| | | |_| | | | | | |   ||");
            mvprintw(17, 20, "||   |_____/|_|_| |_| |_|\\___|\\__,_|_|\\__|\\__, |     (_)   |_|  |_|\\___|\\__,_|_|\\__,_|_| |_| |_|   ||");
            mvprintw(18, 20, "||                                         __/ |                                                   ||");
            mvprintw(19, 20, "||||                                      |____/                                                 ||||");
        }
        if (choosing_mode_1)
        {
            mvprintw(12, 20, "      _____  _  __  __ _            _ _               ||||  __  __          _ _                  ||||");
            mvprintw(13, 20, "     |  __ \\(_)/ _|/ _(_)          | | |              ||   |  \\/  |        | (_)                   ||");
            mvprintw(14, 20, "     | |  | |_| |_| |_ _  ___ _   _| | |_ _   _       ||   | \\  / | ___  __| |_ _   _ _ __ ____    ||");
            mvprintw(15, 20, "     | |  | | |  _|  _| |/ __| | | | | __| | | |      ||   | |\\/| |/ _ \\/ _` | | | | | '_ ` _  \\   ||");
            mvprintw(16, 20, "     | |__| | | | | | | | (__| |_| | | |_| |_| |      ||   | |  | |  __/ (_| | | |_| | | | | | |   ||");
            mvprintw(17, 20, "     |_____/|_|_| |_| |_|\\___|\\__,_|_|\\__|\\__, |      ||   |_|  |_|\\___|\\__,_|_|\\__,_|_| |_| |_|   ||");
            mvprintw(18, 20, "                                           __/ |      ||                                           ||");
            mvprintw(19, 20, "                                          |____/      ||||                                       ||||");
        }
        break;
    case 3:
        mvprintw(12, 20, "      _____  _  __  __ _            _ _                     __  __               _      ");
        mvprintw(13, 20, "     |  __ \\(_)/ _|/ _(_)          | | |              _    | |  | |             | |     ");
        mvprintw(14, 20, "     | |  | |_| |_| |_ _  ___ _   _| | |_ _   _      (_)   | |__| | __ _ _ __ __| |     ");
        mvprintw(15, 20, "     | |  | | |  _|  _| |/ __| | | | | __| | | |           |  __  |/ _` | '__/ _` |     ");
        mvprintw(16, 20, "     | |__| | | | | | | | (__| |_| | | |_| |_| |      _    | |  | | (_| | | | (_| |     ");
        mvprintw(17, 20, "     |_____/|_|_| |_| |_|\\___|\\__,_|_|\\__|\\__, |     (_)   |_|  |_|\\__,_|_|  \\__,_|     ");
        mvprintw(18, 20, "                                           __/ |                                        ");
        mvprintw(19, 20, "                                          |____/                                        ");
        if (select == 1)
        {
            mvprintw(12, 20, "||||  _____  _  __  __ _            _ _                     __  __               _  ||||");
            mvprintw(13, 20, "||   |  __ \\(_)/ _|/ _(_)          | | |              _    | |  | |             | |   ||");
            mvprintw(14, 20, "||   | |  | |_| |_| |_ _  ___ _   _| | |_ _   _      (_)   | |__| | __ _ _ __ __| |   ||");
            mvprintw(15, 20, "||   | |  | | |  _|  _| |/ __| | | | | __| | | |           |  __  |/ _` | '__/ _` |   ||");
            mvprintw(16, 20, "||   | |__| | | | | | | | (__| |_| | | |_| |_| |      _    | |  | | (_| | | | (_| |   ||");
            mvprintw(17, 20, "||   |_____/|_|_| |_| |_|\\___|\\__,_|_|\\__|\\__, |     (_)   |_|  |_|\\__,_|_|  \\__,_|   ||");
            mvprintw(18, 20, "||                                         __/ |                                      ||");
            mvprintw(19, 20, "||||                                      |____/                                    ||||");
        }
        if (choosing_mode_1)
        {
            mvprintw(12, 20, "      _____  _  __  __ _            _ _               ||||  __  __               _  ||||");
            mvprintw(13, 20, "     |  __ \\(_)/ _|/ _(_)          | | |              ||   | |  | |             | |   ||");
            mvprintw(14, 20, "     | |  | |_| |_| |_ _  ___ _   _| | |_ _   _       ||   | |__| | __ _ _ __ __| |   ||");
            mvprintw(15, 20, "     | |  | | |  _|  _| |/ __| | | | | __| | | |      ||   |  __  |/ _` | '__/ _` |   ||");
            mvprintw(16, 20, "     | |__| | | | | | | | (__| |_| | | |_| |_| |      ||   | |  | | (_| | | | (_| |   ||");
            mvprintw(17, 20, "     |_____/|_|_| |_| |_|\\___|\\__,_|_|\\__|\\__, |      ||   |_|  |_|\\__,_|_|  \\__,_|   ||");
            mvprintw(18, 20, "                                           __/ |      ||                              ||");
            mvprintw(19, 20, "                                          |____/      ||||                          ||||");
        }
        break;
    }

    switch (choice_2)
    {
    case 1:
        mvprintw(23, 20, "       _____              _____      _                      _____          _      ");
        mvprintw(24, 20, "      / ____|            / ____|    | |               _    |  __ \\        | |     ");
        mvprintw(25, 20, "     | |     __ _ _ __  | |     ___ | | ___  _ __    (_)   | |__) |___  __| |     ");
        mvprintw(26, 20, "     | |    / _` | '__| | |    / _ \\| |/ _ \\| '__|         |  _  // _ \\/ _` |     ");
        mvprintw(27, 20, "     | |___| (_| | |    | |___| (_) | | (_) | |       _    | | \\ \\  __/ (_| |     ");
        mvprintw(28, 20, "     \\______\\__,_|_|     \\_____\\___/|_|\\___/|_|      (_)   |_|  \\_\\___|\\__,_|     ");
        mvprintw(29, 20, "                                                                                  ");
        mvprintw(30, 20, "                                                                                  ");
        if (select == 2)
        {
            mvprintw(22, 20, "||||                                                                          ||||");
            mvprintw(23, 20, "||     _____              _____      _                      _____          _    ||");
            mvprintw(24, 20, "||    / ____|            / ____|    | |               _    |  __ \\        | |   ||");
            mvprintw(25, 20, "||   | |     __ _ _ __  | |     ___ | | ___  _ __    (_)   | |__) |___  __| |   ||");
            mvprintw(26, 20, "||   | |    / _` | '__| | |    / _ \\| |/ _ \\| '__|         |  _  // _ \\/ _` |   ||");
            mvprintw(27, 20, "||   | |___| (_| | |    | |___| (_) | | (_) | |       _    | | \\ \\  __/ (_| |   ||");
            mvprintw(28, 20, "||   \\______\\__,_|_|     \\_____\\___/|_|\\___/|_|      (_)   |_|  \\_\\___|\\__,_|   ||");
            mvprintw(29, 20, "||||                                                                          ||||");
        }
        if (choosing_mode_2)
        {
            mvprintw(22, 20, "                                                      ||||                    ||||");
            mvprintw(23, 20, "       _____              _____      _                ||    _____          _    ||");
            mvprintw(24, 20, "      / ____|            / ____|    | |               ||   |  __ \\        | |   ||");
            mvprintw(25, 20, "     | |     __ _ _ __  | |     ___ | | ___  _ __     ||   | |__) |___  __| |   ||");
            mvprintw(26, 20, "     | |    / _` | '__| | |    / _ \\| |/ _ \\| '__|    ||   |  _  // _ \\/ _` |   ||");
            mvprintw(27, 20, "     | |___| (_| | |    | |___| (_) | | (_) | |       ||   | | \\ \\  __/ (_| |   ||");
            mvprintw(28, 20, "     \\______\\__,_|_|     \\_____\\___/|_|\\___/|_|       ||   |_|  \\_\\___|\\__,_|   ||");
            mvprintw(29, 20, "                                                      ||||                    ||||");
        }
        break;
    case 2:
        mvprintw(23, 20, "       _____              _____      _                     __     __  _ _                    ");
        mvprintw(24, 20, "      / ____|            / ____|    | |               _    \\ \\   / / | | |                   ");
        mvprintw(25, 20, "     | |     __ _ _ __  | |     ___ | | ___  _ __    (_)    \\ \\_/ /__| | | _____      __     ");
        mvprintw(26, 20, "     | |    / _` | '__| | |    / _ \\| |/ _ \\| '__|           \\   / _ \\ | |/ _ \\ \\ /\\ / /     ");
        mvprintw(27, 20, "     | |___| (_| | |    | |___| (_) | | (_) | |       _       | |  __/ | | (_) \\ V  V /      ");
        mvprintw(28, 20, "     \\______\\__,_|_|     \\_____\\___/|_|\\___/|_|      (_)      |_|\\___|_|_|\\___/ \\_/\\_/       ");
        mvprintw(29, 20, "                                                                                             ");
        mvprintw(30, 20, "                                                                                             ");
        if (select == 2)
        {
            mvprintw(22, 20, "||||                                                                                     ||||");
            mvprintw(23, 20, "||     _____              _____      _                     __     __  _ _                  ||");
            mvprintw(24, 20, "||    / ____|            / ____|    | |               _    \\ \\   / / | | |                 ||");
            mvprintw(25, 20, "||   | |     __ _ _ __  | |     ___ | | ___  _ __    (_)    \\ \\_/ /__| | | _____      __   ||");
            mvprintw(26, 20, "||   | |    / _` | '__| | |    / _ \\| |/ _ \\| '__|           \\   / _ \\ | |/ _ \\ \\ /\\ / /   ||");
            mvprintw(27, 20, "||   | |___| (_| | |    | |___| (_) | | (_) | |       _       | |  __/ | | (_) \\ V  V /    ||");
            mvprintw(28, 20, "||   \\______\\__,_|_|     \\_____\\___/|_|\\___/|_|      (_)      |_|\\___|_|_|\\___/ \\_/\\_/     ||");
            mvprintw(29, 20, "||||                                                                                     ||||");
        }
        if (choosing_mode_2)
        {
            mvprintw(22, 20, "                                                      ||||                               ||||");
            mvprintw(23, 20, "       _____              _____      _                ||   __     __  _ _                  ||");
            mvprintw(24, 20, "      / ____|            / ____|    | |               ||   \\ \\   / / | | |                 ||");
            mvprintw(25, 20, "     | |     __ _ _ __  | |     ___ | | ___  _ __     ||    \\ \\_/ /__| | | _____      __   ||");
            mvprintw(26, 20, "     | |    / _` | '__| | |    / _ \\| |/ _ \\| '__|    ||     \\   / _ \\ | |/ _ \\ \\ /\\ / /   ||");
            mvprintw(27, 20, "     | |___| (_| | |    | |___| (_) | | (_) | |       ||      | |  __/ | | (_) \\ V  V /    ||");
            mvprintw(28, 20, "     \\______\\__,_|_|     \\_____\\___/|_|\\___/|_|       ||      |_|\\___|_|_|\\___/ \\_/\\_/     ||");
            mvprintw(29, 20, "                                                      ||||                               ||||");
        }
        break;
    case 3:
        mvprintw(23, 20, "       _____              _____      _                      __  __                        _             ");
        mvprintw(24, 20, "      / ____|            / ____|    | |               _    |  \\/  |                      | |            ");
        mvprintw(25, 20, "     | |     __ _ _ __  | |     ___ | | ___  _ __    (_)   | \\  / | __ _  __ _  ___ _ __ | |_ __ _      ");
        mvprintw(26, 20, "     | |    / _` | '__| | |    / _ \\| |/ _ \\| '__|         | |\\/| |/ _` |/ _` |/ _ \\ '_ \\| __/ _` |     ");
        mvprintw(27, 20, "     | |___| (_| | |    | |___| (_) | | (_) | |       _    | |  | | (_| | (_| |  __/ | | | || (_| |     ");
        mvprintw(28, 20, "     \\______\\__,_|_|     \\_____\\___/|_|\\___/|_|      (_)   |_|  |_|\\__,_|\\__, |\\___|_| |_|\\__\\__,_|     ");
        mvprintw(29, 20, "                                                                          __/ |                         ");
        mvprintw(30, 20, "                                                                         |___/                          ");
        if (select == 2)
        {
            mvprintw(23, 20, "||||   _____              _____      _                      __  __                        _         ||||");
            mvprintw(24, 20, "||    / ____|            / ____|    | |               _    |  \\/  |                      | |          ||");
            mvprintw(25, 20, "||   | |     __ _ _ __  | |     ___ | | ___  _ __    (_)   | \\  / | __ _  __ _  ___ _ __ | |_ __ _    ||");
            mvprintw(26, 20, "||   | |    / _` | '__| | |    / _ \\| |/ _ \\| '__|         | |\\/| |/ _` |/ _` |/ _ \\ '_ \\| __/ _` |   ||");
            mvprintw(27, 20, "||   | |___| (_| | |    | |___| (_) | | (_) | |       _    | |  | | (_| | (_| |  __/ | | | || (_| |   ||");
            mvprintw(28, 20, "||   \\______\\__,_|_|     \\_____\\___/|_|\\___/|_|      (_)   |_|  |_|\\__,_|\\__, |\\___|_| |_|\\__\\__,_|   ||");
            mvprintw(29, 20, "||                                                                        __/ |                       ||");
            mvprintw(30, 20, "||||                                                                     |___/                      ||||");
        }
        if (choosing_mode_2)
        {
            mvprintw(23, 20, "       _____              _____      _                ||||  __  __                        _         ||||");
            mvprintw(24, 20, "      / ____|            / ____|    | |               ||   |  \\/  |                      | |          ||");
            mvprintw(25, 20, "     | |     __ _ _ __  | |     ___ | | ___  _ __     ||   | \\  / | __ _  __ _  ___ _ __ | |_ __ _    ||");
            mvprintw(26, 20, "     | |    / _` | '__| | |    / _ \\| |/ _ \\| '__|    ||   | |\\/| |/ _` |/ _` |/ _ \\ '_ \\| __/ _` |   ||");
            mvprintw(27, 20, "     | |___| (_| | |    | |___| (_) | | (_) | |       ||   | |  | | (_| | (_| |  __/ | | | || (_| |   ||");
            mvprintw(28, 20, "     \\______\\__,_|_|     \\_____\\___/|_|\\___/|_|       ||   |_|  |_|\\__,_|\\__, |\\___|_| |_|\\__\\__,_|   ||");
            mvprintw(29, 20, "                                                      ||                  __/ |                       ||");
            mvprintw(30, 20, "                                                      ||||               |___/                      ||||");
        }
        break;
    }

    mvprintw(36, 20, "                                          ");
    mvprintw(37, 20, "     ______     _                         ");
    mvprintw(38, 20, "     | ___ \\   | |                        ");
    mvprintw(39, 20, "     | |_/ /___| |_ _   _ _ __ _ __       ");
    mvprintw(40, 20, "     |    // _ \\ __| | | | '__| '_ \\      ");
    mvprintw(41, 20, "     | |\\ \\  __/ |_| |_| | |  | | | |     ");
    mvprintw(42, 20, "     \\_| \\_\\___|\\__|\\__,_|_|  |_| |_|     ");
    mvprintw(43, 20, "                                          ");
    if (select == 3)
    {
        mvprintw(36, 20, "||||                                  ||||");
        mvprintw(37, 20, "||   ______     _                       ||");
        mvprintw(38, 20, "||   | ___ \\   | |                      ||");
        mvprintw(39, 20, "||   | |_/ /___| |_ _   _ _ __ _ __     ||");
        mvprintw(40, 20, "||   |    // _ \\ __| | | | '__| '_ \\    ||");
        mvprintw(41, 20, "||   | |\\ \\  __/ |_| |_| | |  | | | |   ||");
        mvprintw(42, 20, "||   \\_| \\_\\___|\\__|\\__,_|_|  |_| |_|   ||");
        mvprintw(43, 20, "||||                                  ||||");
    }

    attroff(COLOR_PAIR(1));
    move(0, 0);
    refresh();
}

// Credits screen
void Menu::credits_screen()
{
    // Set color pairs (still not sure how to use init_pair from other scripts)

    erase();
    attron(COLOR_PAIR(1));

    for (int y = 0; y < 50; y++)
    {
        for (int x = 0; x < 200; x++)
        {
            mvprintw(y, x, " ");
        }
    }

    mvprintw(2, 20, "______________________________________  ._______________________");
    mvprintw(3, 20, "\\_   ___ \\______   \\_   _____/\\______ \\ |   \\__    ___/   _____/");
    mvprintw(4, 20, "/    \\  \\/|       _/|    __)_  |    |  \\|   | |    |  \\_____  \\ ");
    mvprintw(5, 20, "\\     \\___|    |   \\|        \\ |    `   \\   | |    |  /        \\");
    mvprintw(6, 20, " \\______  /____|_  /_______  / |______  /___| |____| /_______  /");
    mvprintw(7, 20, "        \\/       \\/        \\/         \\/                     \\/ ");

    mvprintw(10, 35, " _____ _                              _____         _    _ _             ");
    mvprintw(11, 35, "/  __ \\ |                            |_   _|       | |  | (_)            ");
    mvprintw(12, 35, "| /  \\/ |__   ___ _   _ _ __   __ _    | |___ ____ | |  | |_ _ __   __ _ ");
    mvprintw(13, 35, "| |   | '_ \\ / _ \\ | | | '_ \\ / _` |   | / __|_  / | |/\\| | | '_ \\ / _` |");
    mvprintw(14, 35, "| \\__/\\ | | |  __/ |_| | | | | (_| |   | \\__ \\/ /  \\  /\\  / | | | | (_| |");
    mvprintw(15, 35, " \\____/_| |_|\\___|\\__,_|_| |_|\\__, |   \\_/___/___|  \\/  \\/|_|_| |_|\\__, |");
    mvprintw(16, 35, "                               __/ |                                __/ |");
    mvprintw(17, 35, "                              |___/                                |___/ ");

    mvprintw(18, 35, " _____              ______                            ");
    mvprintw(19, 35, "|  __ \\             | ___ \\                           ");
    mvprintw(20, 35, "| |  \\/_   _  ___   | |_/ /__ _ __   __ _ _   _ _   _ ");
    mvprintw(21, 35, "| | __| | | |/ _ \\  |  __/ _ \\ '_ \\ / _` | | | | | | |");
    mvprintw(22, 35, "| |_\\ \\ |_| | (_) | | | |  __/ | | | (_| | |_| | |_| |");
    mvprintw(23, 35, " \\____/\\__,_|\\___/  \\_|  \\___|_| |_|\\__, |\\__, |\\__,_|");
    mvprintw(24, 35, "                                     __/ | __/ |      ");
    mvprintw(25, 35, "                                    |___/ |___/       ");

    mvprintw(26, 35, " _   __                 _                             _   _ _      _           _             _    _ _ _                 ");
    mvprintw(27, 35, "| | / /                (_)                           | \\ | (_)    | |         | |           | |  | (_) |                ");
    mvprintw(28, 35, "| |/ / _   _ _ __ _ __  _  __ ___      ____ _ _ __   |  \\| |_  ___| |__   ___ | | __ _ ___  | |  | |_| |___  ___  _ __  ");
    mvprintw(29, 35, "|    \\| | | | '__| '_ \\| |/ _` \\ \\ /\\ / / _` | '_ \\  | . ` | |/ __| '_ \\ / _ \\| |/ _` / __| | |/\\| | | / __|/ _ \\| '_ \\ ");
    mvprintw(30, 35, "| |\\  \\ |_| | |  | | | | | (_| |\\ V  V / (_| | | | | | |\\  | | (__| | | | (_) | | (_| \\__ \\ \\  /\\  / | \\__ \\ (_) | | | |");
    mvprintw(31, 35, "\\_| \\_/\\__,_|_|  |_| |_|_|\\__,_| \\_/\\_/ \\__,_|_| |_| \\_| \\_/_|\\___|_| |_|\\___/|_|\\__,_|___/  \\/  \\/|_|_|___/\\___/|_| |_|");

    mvprintw(33, 35, " _   _                               _ _              ______           _     _                         ");
    mvprintw(34, 35, "| \\ | |                             (_|_)             |  _  \\         (_)   | |                        ");
    mvprintw(35, 35, "|  \\| | __ _ _ __ ___  ___ _ __ __ _ _ _  __ ___   __ | | | |___  _ __ _  __| | ___ _ __ ___ _ __ ___  ");
    mvprintw(36, 35, "| . ` |/ _` | '_ ` _ \\/ __| '__/ _` | | |/ _` \\ \\ / / | | | / _ \\| '__| |/ _` |/ _ \\ '__/ _ \\ '_ ` _ \\ ");
    mvprintw(37, 35, "| |\\  | (_| | | | | | \\__ \\ | | (_| | | | (_| |\\ V /  | |/ / (_) | |  | | (_| |  __/ | |  __/ | | | | |");
    mvprintw(38, 35, "\\_| \\_/\\__,_|_| |_| |_|___/_|  \\__,_|_| |\\__,_| \\_/   |___/ \\___/|_|  | |\\__,_|\\___|_|  \\___|_| |_| |_|");
    mvprintw(39, 35, "                                     _/ |                            _/ |                              ");
    mvprintw(40, 35, "                                    |__/                            |__/                               ");

    mvprintw(41, 35, " _    _ _ _                   _               ______ _      _     _      ");
    mvprintw(42, 35, "| |  | (_) |                 | |              | ___ (_)    | |   (_)     ");
    mvprintw(43, 35, "| |  | |_| |_   _ _ __  _ __ | |_ ___  _ __   | |_/ /_  ___| |__  _  ___ ");
    mvprintw(44, 35, "| |/\\| | | | | | | '_ \\| '_ \\| __/ _ \\| '_ \\  |    /| |/ __| '_ \\| |/ _ \\");
    mvprintw(45, 35, "\\  /\\  / | | |_| | | | | | | | || (_) | | | | | |\\ \\| | (__| | | | |  __/");
    mvprintw(46, 35, " \\/  \\/|_|_|\\__, |_| |_|_| |_|\\__\\___/|_| |_| \\_| \\_|_|\\___|_| |_|_|\\___|");
    mvprintw(47, 35, "             __/ |                                                       ");
    mvprintw(48, 35, "            |___/                                                        ");

    mvprintw(59, 180, "Press any key to return.");

    attroff(COLOR_PAIR(1));
    move(0, 0);
    refresh();
}
