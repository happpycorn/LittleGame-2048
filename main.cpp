#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include <conio.h>

#define SIZE 4 // size
#define FINISH 2048 // finish number
#define TABLE_LINE "+ - - + - - + - - + - - +\n"

void draw_table(int (*table)[SIZE])
{
    system("cls") ;
    printf(TABLE_LINE) ;
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            if(table[i][j] == 0) printf("|     ") ;
            else printf("|%5d", table[i][j]) ;
        }
        printf("|\n") ;
        printf(TABLE_LINE) ;
    }

    printf("type arrow to move\r") ;
}

int rand24()
{
    // init random only once
    static int initialized = 0 ;
    if (!initialized) {
        srand((unsigned)time(NULL)) ;
        initialized = 1 ;
    }

    // return 4 or 2 as 1:7
    return (rand() % 8 == 0) ? 4 : 2 ;
}

char input()
{
    int ch ;
    ch = getch() ;

    switch (ch)
    {
    case 72: return 'U' ; break ; // up
    case 80: return 'D' ; break ; // down
    case 77: return 'R' ; break ; // right
    case 75: return 'L' ; break ; // left
    
    default:
        printf("Key Error         \r") ;
        return input() ;
    }
}

void creat(int (*table)[SIZE])
{
    int i, j ;
    srand((unsigned)time(NULL)) ;

    do
    {
        i=(rand())%4 ;
        j=(rand())%4 ;	
	}
    while(table[i][j]!=0) ;
	
    table[i][j]=rand24() ;
}

void move(int (*table)[SIZE])
{
    // get input

    char enter = input() ;

    // clone table (to check)

    int orgtable[SIZE][SIZE] ;

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            orgtable[i][j] = table[i][j] ;
        }
    }

    // move

    switch (enter)
    {
    case 'U':
        for(int i = 0; i < SIZE; i++) // columns
        {
            for(int _ = 0; _ < SIZE-1; _++)
            {
                for(int j = 1; j < SIZE; j++) // rows
                {
                    if(table[j-1][i] == 0) // go to side
                    {
                        table[j-1][i] = table[j][i] ;
                        table[j][i] = 0 ;
                    }
                }
            }
            for(int j = 1; j < SIZE; j++) // rows
            {
                if(table[j-1][i] == table[j][i]) // merge
                {
                    table[j-1][i] = table[j-1][i] + table[j][i] ;
                    table[j][i] = 0 ;
                }
            }
            for(int _ = 0; _ < SIZE-1; _++)
            {
                for(int j = 1; j < SIZE; j++) // rows
                {
                    if(table[j-1][i] == 0) // go to side
                    {
                        table[j-1][i] = table[j][i] ;
                        table[j][i] = 0 ;
                    }
                }
            }
        }
        break;
    
    case 'D':
        for(int i = 0; i < SIZE; i++) // columns
        {
            for(int _ = 0; _ < SIZE-1; _++)
            {
                for(int j = SIZE-1; j >= 0; j--) // rows
                {
                    if(table[j+1][i] == 0) // go to side
                    {
                        table[j+1][i] = table[j][i] ;
                        table[j][i] = 0 ;
                    }
                }
            }
            for(int j = SIZE-1; j >= 0; j--) // rows
            {
                if(table[j+1][i] == table[j][i]) // merge
                {
                    table[j+1][i] = table[j+1][i] + table[j][i] ;
                    table[j][i] = 0 ;
                }
            }
            for(int _ = 0; _ < SIZE-1; _++)
            {
                for(int j = SIZE-1; j >= 0; j--) // rows
                {
                    if(table[j+1][i] == 0) // go to side
                    {
                        table[j+1][i] = table[j][i] ;
                        table[j][i] = 0 ;
                    }
                }
            }
        }
        break;
    
    case 'R':
        for(int i = 0; i < SIZE; i++) // columns
        {
            for(int _ = 0; _ < SIZE-1; _++)
            {
                for(int j = SIZE-1; j >= 0; j--) // rows
                {
                    if(table[i][j+1] == 0) // go to side
                    {
                        table[i][j+1] = table[i][j] ;
                        table[i][j] = 0 ;
                    }
                }
            }
            for(int j = SIZE-1; j >= 0; j--) // rows
            {
                if(table[i][j+1] == table[i][j]) // merge
                {
                    table[i][j+1] = table[i][j+1] + table[i][j] ;
                    table[i][j] = 0 ;
                }
            }
            for(int _ = 0; _ < SIZE-1; _++)
            {
                for(int j = SIZE-1; j >= 0; j--) // rows
                {
                    if(table[i][j+1] == 0) // go to side
                    {
                        table[i][j+1] = table[i][j] ;
                        table[i][j] = 0 ;
                    }
                }
            }
        }
        break;
    
    case 'L':
        for(int i = 0; i < SIZE; i++) // columns
        {
            for(int _ = 0; _ < SIZE-1; _++)
            {
                for(int j = 1; j < SIZE; j++) // rows
                {
                    if(table[i][j-1] == 0) // go to side
                    {
                        table[i][j-1] = table[i][j] ;
                        table[i][j] = 0 ;
                    }
                }
            }
            for(int j = 1; j < SIZE; j++) // rows
            {
                if(table[i][j-1] == table[i][j]) // merge
                {
                    table[i][j-1] = table[i][j-1] + table[i][j] ;
                    table[i][j] = 0 ;
                }
            }
            for(int _ = 0; _ < SIZE-1; _++)
            {
                for(int j = 1; j < SIZE; j++) // rows
                {
                    if(table[i][j-1] == 0) // go to side
                    {
                        table[i][j-1] = table[i][j] ;
                        table[i][j] = 0 ;
                    }
                }
            }
        }
        break;
    }

    // is work ?

    bool work = false;

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if(orgtable[i][j] != table[i][j])
            {
                work = true ;
                break ;
            }
        }

        if(work) break ;
    }

    if(work)
    {
        creat(table) ;
        draw_table(table) ;
    }
}

bool over(int (*table)[SIZE])
{
    int win, space ;

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if(table[i][j] == FINISH)
            {
                printf("You win !!") ;
                return false ;
            }
            else if(table[i][j] == 0)
            {
                space = true ;
            }
        }
    }

    if(space)
    {
        return true ;
    }
    else
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE-1; j++)
            {
                if(table[i][j] == table[i][j+1] || table[j][i] == table[j+1][i])
                {
                    return true ;
                }
            }
        }

        printf("Game over :P") ;

        return false ;
    }
}

int main()
{
    int table[SIZE][SIZE] = {0} ;

    creat(table) ; creat(table) ; draw_table(table) ;

    while (over(table)) move(table) ;
    
    while (1) ;  

    return 0 ;
}