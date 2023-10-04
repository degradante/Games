#include <iostream>
#include "ping_pong.h"
#include "utils.h"

using namespace std;


void PingPongGame() {
    ConsoleCursorVisible(false, 100);

    short score_p1 = 0, score_p2 = 0;
    short coord_p1 = HEIGHT / 2, coord_p2 = HEIGHT / 2;
    COORD ball = { (WIDTH + 2) / 2, 5 };
    short nb_x = 1, nb_y = 1;

    DrawField();
    while (score_p1 < WIN_SCORE && score_p2 < WIN_SCORE) {
        DrawbBallPLayers(coord_p1, coord_p2, ball, score_p1, score_p2);
        MovePlayers(coord_p1, coord_p2);
        //move_ball(coord_p1, coord_p2);
        if (ball.Y == 1) nb_y = 1;
        if (ball.Y == HEIGHT) nb_y = -1;

        if (ball.X == 1) {
            if (ball.Y >= coord_p1 - 1 && ball.Y <= coord_p1 + 1) {
                nb_x = 1;
                ball.X += nb_x;
            }
            else {
                score_p2++;
                ball.X = (WIDTH + 2) / 2;
                ball.Y = (HEIGHT + 2) / 2;
            }
        }
        else if (ball.X == WIDTH) {
            if (ball.Y >= coord_p2 - 1 && ball.Y <= coord_p2 + 1) {
                nb_x = -1;
                ball.X += nb_x;
            }
            else {
                score_p1++;
                ball.X = (WIDTH + 2) / 2;
                ball.Y = (HEIGHT + 2) / 2;
            }
        }
        else {
            ball.X += nb_x;
            ball.Y += nb_y;
        }
    }

    cout << "\nпоздравляем победителя! (";
    score_p1 == WIN_SCORE ? cout << 1 : cout << 2;
    cout << "игрок)\n";
}

void DrawbBallPLayers(short coord_p1, short coord_p2, COORD ball, short score_p1, short score_p2) {
    for (short y = 1; y < HEIGHT + 1; ++y) {
        GoToXY(1, y);
        for (short x = 1; x < WIDTH + 2; ++x) {
            if (x == 1 && y >= coord_p1 - 1 && y <= coord_p1 + 1)
                cout << '|';
            else if (x == WIDTH + 1 && y >= coord_p2 - 1 && y <= coord_p2 + 1) {
                GoToXY(x, y);
                cout << '|';
            }
            else if (x == ball.X && y == ball.Y) {
                GoToXY(x, y);
                cout << 'o';
            }
            else
                cout << ' ';
        }
    }
    GoToXY(40, HEIGHT + 2);
    cout << score_p1 << ':' << score_p2;
}

void MovePlayers(short& coord_p1, short& coord_p2) {
    if ((GetKeyState('W') & 0x08000) && coord_p1 > 2) --coord_p1;
    else if ((GetKeyState('S') & 0x08000) && coord_p1 < HEIGHT - 1) ++coord_p1;

    //if (key == KEY_UP_P2 && *coord_p2 > 2) --(*coord_p2);
    //else if (key == KEY_DOWN_P2 && *coord_p2 < HEIGHT - 1) ++(*coord_p2);
}
