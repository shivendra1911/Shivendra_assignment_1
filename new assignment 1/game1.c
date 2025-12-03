#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

void clear_screen_fast()
{
    system("cls");
}

int getHighScore()
{
    FILE *f = fopen("highscore.txt", "r");
    int hs = 0;
    if (f == NULL)
        return 0;
    fscanf(f, "%d", &hs);
    fclose(f);
    return hs;
}

void saveHighScore(int score)
{
    FILE *f = fopen("highscore.txt", "w");
    fprintf(f, "%d", score);
    fclose(f);
}

void resetHighScore()
{
    FILE *f = fopen("highscore.txt", "w");
    fprintf(f, "0");
    fclose(f);
}

int main()
{
    srand(time(0));

    printf("SOOTER GAME\n");
    printf("-----------------------\n");
    printf("Press R to reset high score\n");
    printf("Press any other key to start\n");

    char ch = getch();
    if (ch == 'r' || ch == 'R')
    {
        resetHighScore();
        printf("High score reset to 0!\n");
        Sleep(1000);
    }

    int x = 1;
    int score = 0;
    int highscore = getHighScore();
    int step = 0;

    int obstacleCount = (rand() % 2) + 1;
    int obstacles[2];

    for (int i = 0; i < obstacleCount; i++)
        obstacles[i] = rand() % 3;

    char obstacleChar = 233;
    char playerChar = 208;

    while (1)
    {

        if (_kbhit())
        {
            char key = getch();
            if (key == 75 && x > 0)
                x--;
            if (key == 77 && x < 2)
                x++;
        }

        clear_screen_fast();
        printf("SOOTER GAME SCORE: %d   HIGH SCORE: %d\n", score, highscore);
        printf("-------------------------------\n");

        for (int i = 0; i < 10; i++)
        {
            if (i == step)
            {
                char lane[3] = {' ', ' ', ' '};
                for (int j = 0; j < obstacleCount; j++)
                    lane[obstacles[j]] = obstacleChar;
                printf("|  %c    %c    %c  |\n", lane[0], lane[1], lane[2]);
            }
            else
            {
                printf("|                 |\n");
            }
        }

        if (x == 0)
            printf("|  %c              |\n", playerChar);
        else if (x == 1)
            printf("|       %c         |\n", playerChar);
        else
            printf("|             %c   |\n", playerChar);

        if (step == 10)
        {
            int hit = 0;
            for (int i = 0; i < obstacleCount; i++)
                if (x == obstacles[i])
                    hit = 1;

            if (hit)
            {
                printf("\nGAME OVER!\n");

                if (score > highscore)
                {
                    printf("NEW HIGH SCORE!\n");
                    saveHighScore(score);
                }

                return 0;
            }
        }

        Sleep(120);
        step++;

        if (step > 10)
        {
            score++;
            step = 0;

            obstacleCount = (rand() % 2) + 1;
            for (int i = 0; i < obstacleCount; i++)
                obstacles[i] = rand() % 3;
        }
    }

    return 0;
}
