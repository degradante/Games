#include <iostream>
#include "ping_pong.h"
#include "utils.h"

using namespace std;


void PingPongGame() {
    ConsoleCursorVisible(false, 100);

    short score_p1 = 0, score_p2 = 0;
    short coord_p1 = HEIGHT / 2, coord_p2 = HEIGHT / 2;
    short b_x = (WIDTH + 2) / 2, b_y = 5;
    short nb_x = 1, nb_y = 1;

    DrawField();
    while (score_p1 < WIN_SCORE && score_p2 < WIN_SCORE) {
        DrawbBallPLayers(coord_p1, coord_p2, b_x, b_y, score_p1, score_p2);
        MovePlayers(coord_p1, coord_p2);
        //move_ball(coord_p1, coord_p2);
        if (b_y == 1) nb_y = 1;
        if (b_y == HEIGHT) nb_y = -1;

        if (b_x == 1) {
            if (b_y >= coord_p1 - 1 && b_y <= coord_p1 + 1) {
                nb_x = 1;
                b_x += nb_x;
            }
            else {
                score_p2++;
                b_x = (WIDTH + 2) / 2;
                b_y = (HEIGHT + 2) / 2;
            }
        }
        else if (b_x == WIDTH) {
            if (b_y >= coord_p2 - 1 && b_y <= coord_p2 + 1) {
                nb_x = -1;
                b_x += nb_x;
            }
            else {
                score_p1++;
                b_x = (WIDTH + 2) / 2;
                b_y = (HEIGHT + 2) / 2;
            }
        }
        else {
            b_x += nb_x;
            b_y += nb_y;
        }
    }

    score_p1 == WIN_SCORE ? printf("\nпоздравляем победителя! (1 игрок)\n")
        : printf("\nпоздравляем победителя! (2 игрок)\n");
}

void DrawbBallPLayers(short coord_p1, short coord_p2, short b_x, short b_y, short score_p1, short score_p2) {
    for (short y = 1; y < HEIGHT + 1; ++y) {
        GoToXY(1, y);
        for (short x = 1; x < WIDTH + 2; ++x) {
            if (x == 1 && y >= coord_p1 - 1 && y <= coord_p1 + 1)
                cout << '|';
            else if (x == WIDTH + 1 && y >= coord_p2 - 1 && y <= coord_p2 + 1) {
                GoToXY(x, y);
                cout << '|';
            }
            else if (x == b_x && y == b_y) {
                GoToXY(x, y);
                cout << 'o';
            }
            //else
              //  cout << ' ';
        }
    }
    GoToXY(0, HEIGHT + 2);
    cout << score_p1 << score_p2;
}

void MovePlayers(short& coord_p1, short& coord_p2) {
    if ((GetKeyState('W') & 0x08000) && coord_p1 > 2) --coord_p1;
    else if ((GetKeyState('S') & 0x08000) && coord_p1 < HEIGHT - 1) ++coord_p1;

    //if (key == KEY_UP_P2 && *coord_p2 > 2) --(*coord_p2);
    //else if (key == KEY_DOWN_P2 && *coord_p2 < HEIGHT - 1) ++(*coord_p2);
}
