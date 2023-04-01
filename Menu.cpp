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
    printw("The minimum requirement of the terminal size is 200x60.\n");
    printw("Press any key to continue.");
    while ((input = getch()) != KEY_F(1)) {
        // Check size
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        erase();
        if (w.ws_row >= 60 && w.ws_col >= 200) { // Scrren size is enough
            break;
        } else { // Not yet
            printw("Current terminal size: %dx%d", w.ws_col, w.ws_row);
        }
    }
    loading_screen();

    while (true) {

        if (current_page == 1) {
            // Home screen choosing
            home_screen(input, select, max_choice);
            while ((input = getch()) != KEY_F(1)) {
                // Receiving input
                if (input == 97 || input == 119 || input == 259 || input == 260) { // Down
                    select -= 1;
                } else if (input == 100 || input == 115 || input == 258 || input == 261) { // Up
                    select += 1;
                } else if (input == 10) { // Enter
                    if (select == 1) {
                        current_page = 2;
                    } else if (select == 2) {
                        current_page = 1; // change to options
                    } else if (select == 3) {
                        current_page = 4;
                    } else if (select == 4) {
                        current_page = 5;
                    } 
                    erase();
                    break;
                }
                if (select <= 0) {
                    select = max_choice;
                } else if (select > max_choice) {
                    select = 1;
                }

                // Screen
                home_screen(input, select, max_choice);
            }
        } else if (current_page == 2) {
            erase();
            return 0;
        } else if (current_page == 4) {
            credits_screen();
            while ((input = getch()) != KEY_F(1)) {
                break;
            }
            current_page = 1;
        } else if (current_page == 5) {
            erase();
            return 1;
        }
    }
    return 1;
}

void Menu::loading_screen() {
    erase();
    mvprintw(27, 80, " _    ___   _   ___ ___ _  _  ____      ");
    mvprintw(28, 80, "| |  / _ \\ /_\\ |   \\_ _| \\| |/ ___| ");
    mvprintw(29, 80, "| |_| (_) / _ \\| |) | || .` | (__|     ");
    mvprintw(30, 80, "|____\\___/_/ \\_\\___/___|_|\\_|\\____|");
    move(0,0); refresh();
    for (int i = 0; i <= 80; i++) {
        for (int j = 0; j < i; j++) {
            mvprintw(33, j+60, "#");
        }
        for (int j = i; j < 80; j++) {
            mvprintw(33, j+60, "_");
        }
        usleep(30*(80-i)*(80-i));
        move(0,0); refresh();
    }
    usleep(500000);
}

// Home screen
void Menu::home_screen(int input, int select, int max_choice) {
    erase();
    
    // Title
    mvprintw(4 ,0,"                     CCCCCCCCCCCCC                                          RRRRRRRRRRRRRRRRR                  AAA                  CCCCCCCCCCCCCEEEEEEEEEEEEEEEEEEEEEERRRRRRRRRRRRRRRRR                ");
    mvprintw(5 ,0,"                  CCC::::::::::::C                                          R::::::::::::::::R                A:::A              CCC::::::::::::CE::::::::::::::::::::ER::::::::::::::::R               ");
    mvprintw(6 ,0,"                CC:::::::::::::::C                                          R::::::RRRRRR:::::R              A:::::A           CC:::::::::::::::CE::::::::::::::::::::ER::::::RRRRRR:::::R              ");
    mvprintw(7 ,0,"               C:::::CCCCCCCC::::C       +++++++              +++++++       RR:::::R     R:::::R            A:::::::A         C:::::CCCCCCCC::::CEE::::::EEEEEEEEE::::ERR:::::R     R:::::R             ");
    mvprintw(8 ,0,"              C:::::C       CCCCCC       +:::::+              +:::::+         R::::R     R:::::R           A:::::::::A       C:::::C       CCCCCC  E:::::E       EEEEEE  R::::R     R:::::R             ");
    mvprintw(9 ,0,"             C:::::C                     +:::::+              +:::::+         R::::R     R:::::R          A:::::A:::::A     C:::::C                E:::::E               R::::R     R:::::R             ");
    mvprintw(10,0,"             C:::::C               +++++++:::::+++++++  +++++++:::::+++++++   R::::RRRRRR:::::R          A:::::A A:::::A    C:::::C                E::::::EEEEEEEEEE     R::::RRRRRR:::::R              ");
    mvprintw(11,0,"             C:::::C               +:::::::::::::::::+  +:::::::::::::::::+   R:::::::::::::RR          A:::::A   A:::::A   C:::::C                E:::::::::::::::E     R:::::::::::::RR               ");
    mvprintw(12,0,"             C:::::C               +:::::::::::::::::+  +:::::::::::::::::+   R::::RRRRRR:::::R        A:::::A     A:::::A  C:::::C                E:::::::::::::::E     R::::RRRRRR:::::R              ");
    mvprintw(13,0,"             C:::::C               +++++++:::::+++++++  +++++++:::::+++++++   R::::R     R:::::R      A:::::AAAAAAAAA:::::A C:::::C                E::::::EEEEEEEEEE     R::::R     R:::::R             ");
    mvprintw(14,0,"             C:::::C                     +:::::+              +:::::+         R::::R     R:::::R     A:::::::::::::::::::::AC:::::C                E:::::E               R::::R     R:::::R             ");
    mvprintw(15,0,"              C:::::C       CCCCCC       +:::::+              +:::::+         R::::R     R:::::R    A:::::AAAAAAAAAAAAA:::::AC:::::C       CCCCCC  E:::::E       EEEEEE  R::::R     R:::::R             ");
    mvprintw(16,0,"               C:::::CCCCCCCC::::C       +++++++              +++++++       RR:::::R     R:::::R   A:::::A             A:::::AC:::::CCCCCCCC::::CEE::::::EEEEEEEE:::::ERR:::::R     R:::::R             ");
    mvprintw(17,0,"                CC:::::::::::::::C                                          R::::::R     R:::::R  A:::::A               A:::::ACC:::::::::::::::CE::::::::::::::::::::ER::::::R     R:::::R             ");
    mvprintw(18,0,"                  CCC::::::::::::C                                          R::::::R     R:::::R A:::::A                 A:::::A CCC::::::::::::CE::::::::::::::::::::ER::::::R     R:::::R             ");
    mvprintw(19,0,"                     CCCCCCCCCCCCC                                          RRRRRRRR     RRRRRRRAAAAAAA                   AAAAAAA   CCCCCCCCCCCCCEEEEEEEEEEEEEEEEEEEEEERRRRRRRR     RRRRRRR             ");

    mvprintw(59, 190, "@Group-70");

    // Screen

    mvprintw(29,30,"               ____  __           ");
    mvprintw(30,30,"              / __ \\/ /___ ___  __");
    mvprintw(31,30,"             / /_/ / / __ `/ / / /");
    mvprintw(32,30,"            / ____/ / /_/ / /_/ / ");
    mvprintw(33,30,"           /_/   /_/\\__,_/\\__, /  ");
    mvprintw(34,30,"                         /____/   ");

    mvprintw(37,30,"              ____        __                    ");
    mvprintw(38,30,"             / __ \\____  / /_(_)___  ____  _____");
    mvprintw(39,30,"            / / / / __ \\/ __/ / __ \\/ __ \\/ ___/");
    mvprintw(40,30,"           / /_/ / /_/ / /_/ / /_/ / / / (__  ) ");
    mvprintw(41,30,"           \\____/ .___/\\__/_/\\____/_/ /_/____/  ");
    mvprintw(42,30,"               /_/                              ");

    mvprintw(45,30,"              ______              __  __"      );
    mvprintw(46,30,"             / ____/_______  ____/ (_) /______");
    mvprintw(47,30,"            / /   / ___/ _ \\/ __  / / __/ ___/");
    mvprintw(48,30,"           / /___/ /  /  __/ /_/ / / /_(__  ) ");
    mvprintw(49,30,"           \\____/_/   \\___/\\____/_/\\__/____/  ");

    mvprintw(53,30,"               ______       __ ");
    mvprintw(54,30,"              / ____/  __(_) /_");
    mvprintw(55,30,"             / __/ | |/_/ / __/");
    mvprintw(56,30,"            / /____>  </ / /_"  );
    mvprintw(57,30,"           /_____/_/|_/_/\\__/"  );

    switch (select) {
        case 1:
            mvprintw(29,30,"____           ____  __           ");
            mvprintw(30,30,"\\ \\ \\         / __ \\/ /___ ___  __");
            mvprintw(31,30," \\ \\ \\       / /_/ / / __ `/ / / /");
            mvprintw(32,30," / / /      / ____/ / /_/ / /_/ / ");
            mvprintw(33,30,"/_/_/      /_/   /_/\\__,_/\\__, /  ");
            mvprintw(34,30,"                         /____/   ");
            break;
        case 2:
            mvprintw(37,30,"____          ____        __                    ");
            mvprintw(38,30,"\\ \\ \\        / __ \\____  / /_(_)___  ____  _____");
            mvprintw(39,30," \\ \\ \\      / / / / __ \\/ __/ / __ \\/ __ \\/ ___/");
            mvprintw(40,30," / / /     / /_/ / /_/ / /_/ / /_/ / / / (__  ) ");
            mvprintw(41,30,"/_/_/      \\____/ .___/\\__/_/\\____/_/ /_/____/  ");
            mvprintw(42,30,"               /_/                              ");
            break;
        case 3:
            mvprintw(45,30,"____          ______              __  __"      );
            mvprintw(46,30,"\\ \\ \\        / ____/_______  ____/ (_) /______");
            mvprintw(47,30," \\ \\ \\      / /   / ___/ _ \\/ __  / / __/ ___/");
            mvprintw(48,30," / / /     / /___/ /  /  __/ /_/ / / /_(__  ) ");
            mvprintw(49,30,"/_/_/      \\____/_/   \\___/\\____/_/\\__/____/  ");
            break;
        case 4:
            mvprintw(53,30,"____           ______       __ ");
            mvprintw(54,30,"\\ \\ \\         / ____/  __(_) /_");
            mvprintw(55,30," \\ \\ \\       / __/ | |/_/ / __/");
            mvprintw(56,30," / / /      / /____>  </ / /_"  );
            mvprintw(57,30,"/_/_/      /_____/_/|_/_/\\__/"  );
            break;
    }
    
    move(0,0); refresh();
}

// Credits screen
void Menu::credits_screen() {
    erase();

    mvprintw(2,20,"______________________________________  ._______________________");
    mvprintw(3,20,"\\_   ___ \\______   \\_   _____/\\______ \\ |   \\__    ___/   _____/");
    mvprintw(4,20,"/    \\  \\/|       _/|    __)_  |    |  \\|   | |    |  \\_____  \\ ");
    mvprintw(5,20,"\\     \\___|    |   \\|        \\ |    `   \\   | |    |  /        \\");
    mvprintw(6,20," \\______  /____|_  /_______  / |______  /___| |____| /_______  /");
    mvprintw(7,20,"        \\/       \\/        \\/         \\/                     \\/ ");

    mvprintw(12,35," _____ _                              _____         _    _ _             ");
    mvprintw(13,35,"/  __ \\ |                            |_   _|       | |  | (_)            ");
    mvprintw(14,35,"| /  \\/ |__   ___ _   _ _ __   __ _    | |___ ____ | |  | |_ _ __   __ _ ");
    mvprintw(15,35,"| |   | '_ \\ / _ \\ | | | '_ \\ / _` |   | / __|_  / | |/\\| | | '_ \\ / _` |");
    mvprintw(16,35,"| \\__/\\ | | |  __/ |_| | | | | (_| |   | \\__ \\/ /  \\  /\\  / | | | | (_| |");
    mvprintw(17,35," \\____/_| |_|\\___|\\__,_|_| |_|\\__, |   \\_/___/___|  \\/  \\/|_|_| |_|\\__, |");
    mvprintw(18,35,"                               __/ |                                __/ |");
    mvprintw(19,35,"                              |___/                                |___/ ");

    mvprintw(22,35," _____              ______                            ");
    mvprintw(23,35,"|  __ \\             | ___ \\                           ");
    mvprintw(24,35,"| |  \\/_   _  ___   | |_/ /__ _ __   __ _ _   _ _   _ ");
    mvprintw(25,35,"| | __| | | |/ _ \\  |  __/ _ \\ '_ \\ / _` | | | | | | |");
    mvprintw(26,35,"| |_\\ \\ |_| | (_) | | | |  __/ | | | (_| | |_| | |_| |");
    mvprintw(27,35," \\____/\\__,_|\\___/  \\_|  \\___|_| |_|\\__, |\\__, |\\__,_|");
    mvprintw(28,35,"                                     __/ | __/ |      ");
    mvprintw(29,35,"                                    |___/ |___/       ");

    mvprintw(32,35," _   __                 _                             _   _ _      _           _             _    _ _ _                 ");
    mvprintw(33,35,"| | / /                (_)                           | \\ | (_)    | |         | |           | |  | (_) |                ");
    mvprintw(34,35,"| |/ / _   _ _ __ _ __  _  __ ___      ____ _ _ __   |  \\| |_  ___| |__   ___ | | __ _ ___  | |  | |_| |___  ___  _ __  ");
    mvprintw(35,35,"|    \\| | | | '__| '_ \\| |/ _` \\ \\ /\\ / / _` | '_ \\  | . ` | |/ __| '_ \\ / _ \\| |/ _` / __| | |/\\| | | / __|/ _ \\| '_ \\ ");
    mvprintw(36,35,"| |\\  \\ |_| | |  | | | | | (_| |\\ V  V / (_| | | | | | |\\  | | (__| | | | (_) | | (_| \\__ \\ \\  /\\  / | \\__ \\ (_) | | | |");
    mvprintw(37,35,"\\_| \\_/\\__,_|_|  |_| |_|_|\\__,_| \\_/\\_/ \\__,_|_| |_| \\_| \\_/_|\\___|_| |_|\\___/|_|\\__,_|___/  \\/  \\/|_|_|___/\\___/|_| |_|");

    mvprintw(40,35," _   _                               _ _              ______           _     _                         ");
    mvprintw(41,35,"| \\ | |                             (_|_)             |  _  \\         (_)   | |                        ");
    mvprintw(42,35,"|  \\| | __ _ _ __ ___  ___ _ __ __ _ _ _  __ ___   __ | | | |___  _ __ _  __| | ___ _ __ ___ _ __ ___  ");
    mvprintw(43,35,"| . ` |/ _` | '_ ` _ \\/ __| '__/ _` | | |/ _` \\ \\ / / | | | / _ \\| '__| |/ _` |/ _ \\ '__/ _ \\ '_ ` _ \\ ");
    mvprintw(44,35,"| |\\  | (_| | | | | | \\__ \\ | | (_| | | | (_| |\\ V /  | |/ / (_) | |  | | (_| |  __/ | |  __/ | | | | |");
    mvprintw(45,35,"\\_| \\_/\\__,_|_| |_| |_|___/_|  \\__,_|_| |\\__,_| \\_/   |___/ \\___/|_|  | |\\__,_|\\___|_|  \\___|_| |_| |_|");
    mvprintw(46,35,"                                     _/ |                            _/ |                              ");
    mvprintw(47,35,"                                    |__/                            |__/                               ");
    
    mvprintw(50,35," _    _ _ _                   _               ______ _      _     _      ");
    mvprintw(51,35,"| |  | (_) |                 | |              | ___ (_)    | |   (_)     ");
    mvprintw(52,35,"| |  | |_| |_   _ _ __  _ __ | |_ ___  _ __   | |_/ /_  ___| |__  _  ___ ");
    mvprintw(53,35,"| |/\\| | | | | | | '_ \\| '_ \\| __/ _ \\| '_ \\  |    /| |/ __| '_ \\| |/ _ \\");
    mvprintw(54,35,"\\  /\\  / | | |_| | | | | | | | || (_) | | | | | |\\ \\| | (__| | | | |  __/");
    mvprintw(55,35," \\/  \\/|_|_|\\__, |_| |_|_| |_|\\__\\___/|_| |_| \\_| \\_|_|\\___|_| |_|_|\\___|");
    mvprintw(56,35,"             __/ |                                                       ");
    mvprintw(57,35,"            |___/                                                        ");

    mvprintw(59,180,"Press any key to return.");

    move(0,0); refresh();
}