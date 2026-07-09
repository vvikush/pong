// I WANT TO PLAY WITH YOU
//         YOUR FRIEND, AI

#include <stdio.h>

#define WIDTH 80
#define HEIGHT 25
#define WIN_SCORE 21
#define LEFT_PADDLE_X 10
#define RIGHT_PADDLE_X 69
#define PADDLE_SIZE 3

void clearScreen(void);
void drawGraphic(int rocket1Y, int rocket2Y, int ballX, int ballY, int score1, int score2);
int pongGame(int score1, int score2, int ballX, int ballY, int rocket1Y, int rocket2Y,
             int ballDirectionX, int ballDirectionY);
char proverka(void);
void printWinner(int score1, int score2);
int moveBallX(int rocket1Y, int rocket2Y, int ballX, int ballY, int ballDirectionX);
int moveBallY(int ballY, int ballDirectionY);

int main(void) {
    pongGame(0, 0, 40, 12, 11, 11, 0, 0);
    return 0;
}

void clearScreen(void) {
    printf("\033[H\033[J");
}

char proverka(void) {
    int input = getchar();
    int next;

    if (input == EOF) {
        return 0;
    }

    if (input == '\n') {
        printf("n/a\n");
        return 0;
    }

    next = getchar();

    if (next != '\n' && next != EOF) {
        while (next != '\n' && next != EOF) {
            next = getchar();
        }
        printf("n/a\n");
        return 0;
    }

    if (input >= 'a' && input <= 'z') {
        input -= 32;
    }

    if (input == 'A' || input == 'Z' || input == 'K' || input == 'M' || input == ' ') {
        return input;
    }

    printf("n/a\n");
    return 0;
}

int moveBallX(int rocket1Y, int rocket2Y, int ballX, int ballY, int ballDirectionX) {
    if (ballX == LEFT_PADDLE_X + 1 && ballDirectionX == 0) {
        if (ballY >= rocket1Y && ballY < rocket1Y + PADDLE_SIZE) {
            ballDirectionX = 1;
        }
    }

    if (ballX == RIGHT_PADDLE_X - 1 && ballDirectionX == 1) {
        if (ballY >= rocket2Y && ballY < rocket2Y + PADDLE_SIZE) {
            ballDirectionX = 0;
        }
    }

    return ballDirectionX;
}

int moveBallY(int ballY, int ballDirectionY) {
    if (ballY <= 1) {
        ballDirectionY = 0;
    } else if (ballY >= HEIGHT - 2) {
        ballDirectionY = 1;
    }

    return ballDirectionY;
}

void drawGraphic(int rocket1Y, int rocket2Y, int ballX, int ballY, int score1, int score2) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || i == HEIGHT - 1) {
                printf("-");
            } else if (i == ballY && j == ballX) {
                printf("o");
            } else if (j == 0 || j == WIDTH - 1) {
                printf("|");
            } else if (j == WIDTH / 2) {
                printf("|");
            } else if (j == LEFT_PADDLE_X && i >= rocket1Y && i < rocket1Y + PADDLE_SIZE) {
                printf("|");
            } else if (j == RIGHT_PADDLE_X && i >= rocket2Y && i < rocket2Y + PADDLE_SIZE) {
                printf("|");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    printf("Score: %d - %d\n", score1, score2);
}

int pongGame(int score1, int score2, int ballX, int ballY, int rocket1Y, int rocket2Y,
             int ballDirectionX, int ballDirectionY) {
    while (score1 < WIN_SCORE && score2 < WIN_SCORE) {
        ballX = WIDTH / 2;
        ballY = HEIGHT / 2;

        int ballIsBreak = 0;

        while (!ballIsBreak) {
            clearScreen();
            drawGraphic(rocket1Y, rocket2Y, ballX, ballY, score1, score2);

            char input = 0;

            while (input == 0) {
                printf("\nEnter action (A/Z/K/M, Space): ");
                input = proverka();
            }

            if (input == 'Z') {
                if (rocket1Y + PADDLE_SIZE < HEIGHT - 1) {
                    rocket1Y += 1;
                }
            } else if (input == 'A') {
                if (rocket1Y > 1) {
                    rocket1Y -= 1;
                }
            } else if (input == 'M') {
                if (rocket2Y + PADDLE_SIZE < HEIGHT - 1) {
                    rocket2Y += 1;
                }
            } else if (input == 'K') {
                if (rocket2Y > 1) {
                    rocket2Y -= 1;
                }
            }

            ballDirectionY = moveBallY(ballY, ballDirectionY);
            ballDirectionX = moveBallX(rocket1Y, rocket2Y, ballX, ballY, ballDirectionX);

            ballX += ballDirectionX == 0 ? -1 : 1;
            ballY += ballDirectionY == 0 ? 1 : -1;

            if (ballX <= 0) {
                score2++;
                ballIsBreak = 1;
            } else if (ballX >= WIDTH - 1) {
                score1++;
                ballIsBreak = 1;
            }
        }
    }

    clearScreen();
    drawGraphic(rocket1Y, rocket2Y, ballX, ballY, score1, score2);
    printWinner(score1, score2);

    return 0;
}

void printWinner(int score1, int score2) {
    if (score1 == WIN_SCORE) {
        printf("Player 1 WINS!\n");
    } else if (score2 == WIN_SCORE) {
        printf("Player 2 WINS!\n");
    }
}
