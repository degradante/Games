#include <vector>
#include <random>

#include <windows.h>
#include <conio.h>

#include "snake.h"
#include "utils.h"

void SnakeGame() {
    setlocale(LC_ALL, "ru");
    system("CLS");
    //system("mode con cols=84 lines=26");
    vector<COORD> snake = { 1, {WIDTH / 2, HEIGHT / 2 + 1} };
    vector<COORD> food = { 2, {0, 0} };
    Go go = UP;
    
    bool game_lose = false;
    bool game_win = false;
    DrawField();
    while (!game_lose && !game_win) {
        GoToXY(0, 0);
        AddFood(food);
        DrawObjects(snake, food, go);
        ChangeMove(go);
        MoveSnake(snake, go);
        game_lose = IsGameOver(snake);
        game_win = snake.size() == WIDTH * HEIGHT;
    }

    if (game_lose) cout << "\n\tВы проиграли\n\n";
    if (game_win) cout << "\n\tПоздравляем победителя!\n\n";
}

void AddFood(vector<COORD>& food) {
    srand(time(NULL));
    COORD zero = { 0, 0 };
    for (size_t i = 0; i < food.size(); ++i) {
        if (food[i] == zero) {
            food[i].X = rand() % WIDTH + 1;
            food[i].Y = rand() % HEIGHT + 1;
        }
    }
}

void DrawObjects(vector<COORD>& snake, vector<COORD>& food, Go go) {
    for (short y = 1; y < HEIGHT + 1; ++y) {
        GoToXY(1, y);
        for (short x = 1; x < WIDTH + 1; ++x) {
            COORD pixel = { x, y };
            bool check = false;
            if (snake[0] == pixel) {
                switch (go) {
                case UP:
                    cout << '^';
                    break;
                case LEFT:
                    cout << '<';
                    break;
                case DOWN:
                    cout << 'v';
                    break;
                case RIGHT:
                    cout << '>';
                    break;
                }
                check = true;
            }
            // i = 1 because head drawing upper
            for (size_t i = 1; !check && i < snake.size(); ++i) {
                if (snake[i] == pixel) {
                    cout << 'o';
                    check = true;
                }
            }
            for (size_t i = 0; i < food.size(); ++i) {
                if (food[i] == pixel) {
                    if (food[i] == snake[0]) {
                        snake.resize(snake.size() + 1);
                        food[i] = { 0, 0 };
                    }
                    else {
                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                        cout << 'o';
                        SetConsoleTextAttribute(hConsole, 15);
                    }
                    check = true;
                }
            }
            if (!check) cout << " ";
        }
    }
    GoToXY(32, HEIGHT + 3);
    cout << "Длина змейки - " << snake.size();
}

void ChangeMove(Go& go) {
    if ((GetKeyState('W') & 0x08000) && go != DOWN) go = UP;
    else if ((GetKeyState('S') & 0x08000) && go != UP) go = DOWN;
    else if ((GetKeyState('A') & 0x08000) && go != RIGHT) go = LEFT;
    else if ((GetKeyState('D') & 0x08000) && go != LEFT) go = RIGHT;
}

void MoveSnake(vector<COORD>& snake, Go go) {
    for (size_t i = snake.size() - 1; i >= 1; --i) snake[i] = snake[i - 1];
    if (go == UP) snake[0].Y--;
    else if (go == DOWN) snake[0].Y++;
    else if (go == LEFT) snake[0].X--;
    else if (go == RIGHT) snake[0].X++;
}

bool IsGameOver(vector<COORD>& snake) {
    bool check = false;
    COORD head = snake[0];
    if (head.X <= 0 || head.X > WIDTH || head.Y <= 0 || head.Y > HEIGHT) check = true;
    else {
        for (size_t i = 1; i < snake.size() && !check; ++i)
            if (head == snake[i])
                check = true;
    }

    return check;
}