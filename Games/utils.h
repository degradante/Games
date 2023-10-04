#pragma once

#include <windows.h>

#define WIDTH 80
#define HEIGHT 25

#define BORDER "#"

void ConsoleCursorVisible(bool show, short size);
void GoToXY(short x, short y);
bool operator ==(COORD const& lhs, COORD const& rhs);
void DrawField();
