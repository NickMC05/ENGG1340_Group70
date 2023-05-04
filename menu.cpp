#include "Menu.h"
#include <ncurses.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <cstdlib>
#include <unistd.h>
#include <locale.h>

Menu::Menu()
{
}
// 0 = play, 1 = exit
int Menu::run()
{
    printw("Before playing the game, please make sure that the terminal size is enough for the game to be printed.\n");
    printw("The minimum requirement of the terminal size is 200x50.\n");
    printw("Press any key to continue.");
    while ((input = getch()) != KEY_F(1))
    {
        // Check size
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        erase();
        if (w.ws_row >= 50 && w.ws_col >= 200)
        { // Scrren size is enough
            break;
        }
        else
        { // Not yet
            printw("Before playing the game, please make sure that the terminal size is enough for the game to be printed.\n");
            printw("The minimum requirement of the terminal size is 200x50.\n\n");
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
                if (input == 'W' || input == 'w' || input == 'A' || input == 'a' || input == KEY_UP || input == KEY_LEFT)
                { // Up
                    select -= 1;
                }
                else if (input == 'S' || input == 's' || input == 'D' || input == 'd' || input == KEY_DOWN || input == KEY_RIGHT)
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
                        current_page = 1; // change to options
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
        else if (current_page == 4)
        {
            credits_screen();
            while ((input = getch()) != KEY_F(1))
            {
                if (input == 10)
                {
                    break;
                }
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
    init_pair(1, COLOR_RED, COLOR_WHITE);
    init_pair(2, COLOR_BLACK, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_RED);

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
    for (int i = 0; i <= 80; i++)
    {
        for (int j = 0; j < i; j++)
        {
            attron(COLOR_PAIR(3));
            mvprintw(28, j + 60, "#");
            attroff(COLOR_PAIR(3));
        }
        for (int j = i; j < 80; j++)
        {
            attron(COLOR_PAIR(2));
            mvprintw(28, j + 60, "_");
            attroff(COLOR_PAIR(2));
        }
        usleep(30 * (80 - i) * (80 - i));
        move(0, 0);
        refresh();
    }
    usleep(700000);
}

// Home screen
void Menu::home_screen(int input, int select, int max_choice)
{
    // Set color pairs (still not sure how to use init_pair from other scripts)
    init_pair(1, COLOR_WHITE, COLOR_RED);
    init_pair(2, COLOR_BLACK, COLOR_RED);

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

    attron(COLOR_PAIR(2));
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
    attroff(COLOR_PAIR(2));

    move(0, 0);
    refresh();
}

// Credits screen
void Menu::credits_screen()
{
    // Set color pairs (still not sure how to use init_pair from other scripts)
    init_pair(1, COLOR_RED, COLOR_WHITE);

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

    mvprintw(49, 178, "Press ENTER to return.");

    attroff(COLOR_PAIR(1));
    move(0, 0);
    refresh();
}