#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define ROAD_WIDTH 11
#define ROAD_LENGTH 20
#define ESCAPE_COOLDOWN 5

char road[ROAD_LENGTH][ROAD_WIDTH];
int carPosX = ROAD_WIDTH / 2;
int carPosY = ROAD_LENGTH - 3;
int score = 0;
int escapeAvailable = 1;
int escapeCooldown = 0;

void clearScreen() {
    system("cls");
}

void initializeRoad() {
    for (int i = 0; i < ROAD_LENGTH; i++) {
        for (int j = 0; j < ROAD_WIDTH; j++) {
            if (j == 0 || j == ROAD_WIDTH - 1)
                road[i][j] = '|';
            else
                road[i][j] = ' ';
        }
    }
}

void generateObstacle() {
    int pos = 1 + rand() % (ROAD_WIDTH - 2);
    road[0][pos] = '#';
}

void moveObstacles() {
    for (int i = ROAD_LENGTH - 1; i > 0; i--) {
        for (int j = 1; j < ROAD_WIDTH - 1; j++) {
            road[i][j] = road[i - 1][j];
        }
    }
    for (int j = 1; j < ROAD_WIDTH - 1; j++) {
        road[0][j] = ' ';
    }
}

void placeCar() {
    for (int i = 1; i < ROAD_LENGTH - 1; i++) {
        for (int j = 1; j < ROAD_WIDTH - 1; j++) {
            if (road[i][j] == 'A') road[i][j] = ' ';
        }
    }
    road[carPosY][carPosX] = 'A';
}

void displayRoad() {
    clearScreen();
    printf("\n\U0001F697  **CAR RACING GAME**  \U0001F697\n\n");
    for (int i = 0; i < ROAD_LENGTH; i++) {
        for (int j = 0; j < ROAD_WIDTH; j++) {
            printf("%c", road[i][j]);
        }
        printf("\n");
    }
    printf("\n\U0001F3C6 Score: %d", score);
    printf("\n\U0001F680 Escape Available: %s\n", escapeAvailable ? "\u2705 YES" : "\u274C NO");
    printf("\nControls:  [A] Left  [D] Right  [W] Forward  [S] Backward  [E] Escape");
}

int checkCollision() {
    return (road[carPosY][carPosX] == '#');
}

void gameLoop() {
    while (1) {
        moveObstacles();
        if (rand() % 3 == 0)
            generateObstacle();
        placeCar();
        displayRoad();

        if (checkCollision()) {
            if (escapeAvailable) {
                escapeAvailable = 0;
                escapeCooldown = ESCAPE_COOLDOWN;
                printf("\n⚠️  You narrowly escaped a crash! ⚠️\n");
                Sleep(700);
            } else {
                printf("\n💥 CRASH! GAME OVER! 💥\n");
                printf("\n🏁 Final Score: %d\n", score);
                break;
            }
        }

        if (_kbhit()) {
            char key = _getch();
            if (key == 'a' && carPosX > 1) carPosX--;
            if (key == 'd' && carPosX < ROAD_WIDTH - 2) carPosX++;
            if (key == 'w' && carPosY > 1) carPosY--; // Move forward
            if (key == 's' && carPosY < ROAD_LENGTH - 2) carPosY++; // Move backward
            if (key == 'e' && escapeAvailable) {
                escapeAvailable = 0;
                escapeCooldown = ESCAPE_COOLDOWN;
            }
        }

        if (escapeCooldown > 0) {
            escapeCooldown--;
            if (escapeCooldown == 0) escapeAvailable = 1;
        }

        score++;
        Sleep(150);
    }
}

int main() {
    srand(time(0));
    initializeRoad();
    gameLoop();
    printf("\nPress any key to exit...\n");
    getch();
    return 0;
}
