#pragma once

#include <iostream>
#include "utils.h"

#define WIN_SCORE 21

using namespace std;

void DrawbBallPLayers(short coord_p1, short coord_p2, short b_x, short b_y, short score_p1, short score_p2);
void MovePlayers(short& coord_p1, short& coord_p2);
void PingPongGame();
