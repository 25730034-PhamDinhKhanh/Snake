//
// Created by Phạm Đình Khánh on 11/30/2025.
//

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdio>

using namespace std;

struct Node {
    int x, y;
};

struct Snake {
    Node A[100];
    int Leng;
};

void gotoxy(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hConsole, pos);
}

void Init(Snake &snake) {
    snake.Leng = 7;
    
    snake.A[0].x = 9; snake.A[0].y = 5;
    snake.A[1].x = 8; snake.A[1].y = 5;
    snake.A[2].x = 7; snake.A[2].y = 5;
    snake.A[3].x = 7; snake.A[3].y = 4;
    snake.A[4].x = 7; snake.A[4].y = 3;
    snake.A[5].x = 6; snake.A[5].y = 3;
    snake.A[6].x = 5; snake.A[6].y = 3;
}

void Draw(Snake snake) {
    for (int i = 0; i < snake.Leng; i++) {
        gotoxy(snake.A[i].x * 2, snake.A[i].y);
        printf("%c%c", 219, 219);
    }
    gotoxy(40, 20);
}

void Run(Snake &snake, int dir) {
    // doi cac dot than di theo dot dau
    for (int i = snake.Leng - 1; i > 0; i--) {
        snake.A[i] = snake.A[i - 1];
    }

    switch (dir) {
        case 0: // sang phai
            snake.A[0].x = snake.A[0].x + 1;
            break;
        case 1: // di xuong
            snake.A[0].y = snake.A[0].y + 1;
            break;
        case 2: // sang trai
            snake.A[0].x = snake.A[0].x - 1;
            break;
        case 3: // di len
            snake.A[0].y = snake.A[0].y - 1;
            break;
    }
}

int main() {
    Snake snake;
    int dir = 0;
    char ch = 0;

    CONSOLE_CURSOR_INFO ci;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(hConsole, &ci);
    ci.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &ci);

    Init(snake);
    system("cls");
    Draw(snake);

    while (1) {
        if (kbhit()) {
            ch = getch();
            switch (ch) {
                case 's': // di sang phai
                    dir = 0;
                    break;
                case 'z': // di xuong
                    dir = 1;
                    break;
                case 'a': // di sang trai
                    dir = 2;
                    break;
                case 'w': // di len
                    dir = 3;
                    break;
                case 27: // ESC de thoat
                    return 0;
            }
        }

        // xoa duoi con ran cu
        int tailIndex = snake.Leng - 1;
        gotoxy(snake.A[tailIndex].x * 2, snake.A[tailIndex].y);
        printf("  ");

        // cap nhat vi tri
        Run(snake, dir);

        // ve lai con ran
        Draw(snake);

        Sleep(100);
    }

    return 0;
}
