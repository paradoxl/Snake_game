#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <fcntl.h>
#include <termios.h>

int i, j, height = 30;

int width = 30;
int gameover, score;
int x, y, fruitx, fruity, flag;

// KBHIT workout for unix systems found on https://cboard.cprogramming.com/c-programming/63166-kbhit-linux.html
// still shows characters in buffer.
int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

// Draw the initial board.
void draw()
{
    system("clear");
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            if (i == 0 || i == width - 1 || j == 0 || j == height - 1)
            {
                printf("#");
            }
            else
            {
                if (i == x && j == y)
                {
                    printf("0");
                }
                else if (i == fruitx && j == fruity)
                {
                    printf("*");
                }
                else
                {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }

    printf("score = %d", score);
    printf("\n");
    printf("press X to quit the game");
}

void setup()
{
    gameover = 0;
    x = height / 2;
    y = width / 2;
label1:
    fruitx = rand() % 20;
    if (fruitx == 0)
    {
        goto label1;
    }
label2:
    fruity = rand() % 20;
    if (fruity == 0)
    {
        goto label2;
    }
    score = 0;
}
//  Swithc statement to parse the keyboard input for movement.
void input()
{
    if (!kbhit()){
        switch (getchar())
        {
        case 'a':
            flag = 1;
            printf("a");
            break;
        case 's':
            flag = 2;
            printf("s");
            break;
        case 'd':
            flag = 3;
            break;
        case 'w':
            flag = 4;
            break;
        case 'x':
            gameover = 1;
            break;
        }
   }
    
}

void gameLogic()
{
    sleep(0.01);
    switch (flag)
    {
    case 1:
        y--;
        break;
    case 2:
        x++;
        break;
    case 3:
        y++;
        break;
    case 4:
        x--;
        break;
    default:
        break;
    }

    if (x < 0 || x > height || y < 0 || y > width)
    {
        gameover = 1;
    }

    if (x == fruitx && y == fruity)
    {
    label3:
        fruitx = rand() % 20;
        if (fruitx == 0)
        {
            goto label3;
        }

    label4:
        fruity = rand() % 20;
        if (fruity == 0)
        {
            goto label4;
        }
        score += 10;
    }
}

int main()
{
    int m,n;
    setup();

    while (!gameover)
    {
        draw();
        input();
        gameLogic();
    }
}
