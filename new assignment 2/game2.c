#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

void wipeScreen()
{
    system("cls");
}

int loadBest()
{
    FILE *f = fopen("catch_record.txt", "r");
    if (!f)
        return 0;
    int s;
    fscanf(f, "%d", &s);
    fclose(f);
    return s;
}

void writeBest(int s)
{
    FILE *f = fopen("catch_record.txt", "w");
    fprintf(f, "%d", s);
    fclose(f);
}

int main()
{
    srand(time(NULL));

    printf("=== FALLING BLOCKS ===\n");
    printf("Press R to reset high score\n");
    printf("Press any key to continue...\n");

    char key = getch();
    if (key == 'r' || key == 'R')
    {
        writeBest(0);
        printf("High score cleared!\n");
        Sleep(700);
    }

    int pos = 1;
    int fallY = 0;
    int blockLane = rand() % 3;
    int points = 0;
    int lives = 3;

    char catcher = 254;
    char block = 219;

    int record = loadBest();

    while (1)
    {

        if (_kbhit())
        {
            char k = getch();
            if (k == 75 && pos > 0)
                pos--;
            else if (k == 77 && pos < 2)
                pos++;
        }

        wipeScreen();

        printf("SCORE: %d   BEST: %d   LIVES: %d\n", points, record, lives);
        printf("-----------------------------------\n");

        for (int row = 0; row < 10; row++)
        {
            if (row == fallY)
            {
                char lanes[3] = {' ', ' ', ' '};
                lanes[blockLane] = block;
                printf("   %c     %c     %c\n", lanes[0], lanes[1], lanes[2]);
            }
            else
            {
                printf("                 \n");
            }
        }

        if (pos == 0)
            printf("   %c\n", catcher);
        else if (pos == 1)
            printf("        %c\n", catcher);
        else
            printf("              %c\n", catcher);

        Sleep(110);
        fallY++;

        if (fallY > 10)
        {
            if (pos == blockLane)
            {
                points++;
            }
            else
            {
                lives--;
                printf("\nYou missed a block! -1 life\n");
                Sleep(300);
            }

            fallY = 0;
            blockLane = rand() % 3;
        }

        if (lives == 0)
        {
            
            wipeScreen();
            printf("GAME OVER!\n");
            printf("Final Score: %d\n", points);

            if (points > record)
            {
                printf("New Record Achieved!\n");
                writeBest(points);
            }
            return 0;
        }
    }

    return 0;
}
