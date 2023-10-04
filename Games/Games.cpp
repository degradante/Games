#include <iostream>
#include <string>

#include "snake.h"
#include "ping_pong.h"
#include "utils.h"

using namespace std;

int main() {
    SetConsoleTitle(L"Games");
    setlocale(0, "Rus");
    ConsoleCursorVisible(false, 100);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    string menu[] = { "Snake" , "Ping Pong", "Sapper"};
    int active_menu = 0;
    while (true) {
        for (int i = 0; i < size(menu); ++i) {
            GoToXY(50, i + 10);
            if (i == active_menu) SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            else SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN);
            cout << menu[i];
        }
        char ch = _getch();
        if (ch == -32) {
            char ch = _getch();
            switch (ch) {
                case 27:
                    exit(0);
                case 72:
                    if (active_menu > 0) --active_menu;
                    break;
                case 80:
                    if (active_menu < size(menu) - 1) ++active_menu;
                    break;
                default:
                    break;
            }
        }
        else if (ch == 27) exit(0);
        else if (ch == 13) {
            system("CLS");
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            switch (active_menu) {
            case 0:
                SnakeGame();
                break;
            case 1:
                PingPongGame();
                break;
            default:
                break;
            }
            Sleep(5 * CLOCKS_PER_SEC);
            system("CLS");
        }
    }

    return 0;
}
