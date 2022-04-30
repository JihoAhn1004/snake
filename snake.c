#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>
#define MAX_X 5
#define MAX_Y 5
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
int map[MAX_Y][MAX_X];

void get_food()
{
    
}

void display()
{
    for(int y=0;y<MAX_Y;y++)
    {
        for(int x=0;x<MAX_X;x++)
        {
            printf("%d ",map[y][x]);
        }
        printf("\n");
    }
    printf("---------------------\n");
}

int getch(void)
{
    struct termios oldt, newt;
    int ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}

void engine(char input,int* a,int* b)
{   
    switch(input)
    {
        case UP:
            if(map[*a][*b] != map[0][*b])
            {
                map[*a][*b] = 0; 
                *a -= 1;
                map[*a][*b] = 1;
                if(map[*a][*b] == map[1][1])
                {
                    get_food();
                }
                break;
            }
        case DOWN:
            if(map[*a][*b] != map[*a][4])
            {
                map[*a][*b] = 0; 
                *a += 1;
                map[*a][*b] = 1;
                break;
            }
        case LEFT:
            map[*a][*b] = 0; 
            *b -= 1;
            map[*a][*b] = 1;
            break;
        case RIGHT: 
            map[*a][*b] = 0; 
            *b += 1;
            map[*a][*b] = 1;
            break;

        
    }
}   

int main(void)
{
    char ch;
    map[MAX_Y/2][MAX_X/2] = 1;
    int cur_Y = MAX_Y/2;
    int cur_X = MAX_X/2;
    
    map[1][1] = 2;

    while(1)
    {
        ////1//// 
        ch = getch();
        ////2////
        engine(ch,&cur_Y,&cur_X);
        ////3////
        display();
    }

    return 0;
}