#pragma once

#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>

using namespace std;

enum Go { UP, RIGHT, DOWN, LEFT };

void SnakeGame();
void AddFood(vector<COORD>& food);
void DrawObjects(vector<COORD>& snake, vector<COORD>& food, Go go);
void ChangeMove(Go& go);
void MoveSnake(vector<COORD>& snake, Go go);
bool IsGameOver(vector<COORD>& snake);
