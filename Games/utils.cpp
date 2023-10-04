#include <iostream>
#include <conio.h>
#include "utils.h"

using namespace std;

void ConsoleCursorVisible(bool show, short size) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(handle, &structCursorInfo);
    structCursorInfo.dwSize = size;
    structCursorInfo.bVisible = show;
    SetConsoleCursorInfo(handle, &structCursorInfo);
}

void GoToXY(short x, short y) {
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { x, y });
}

bool operator ==(COORD const& lhs, COORD const& rhs) {
    return lhs.X == rhs.X && lhs.Y == rhs.Y;
}

void DrawField() {
    for (short y = 0; y < HEIGHT + 2; ++y) {
        cout << BORDER;
        for (short x = 0; x < WIDTH + 2; ++x) {
            if (y == 0 || y == HEIGHT + 1) cout << BORDER;
            else cout << ' ';
        }
        cout << BORDER << endl;
    }
}
