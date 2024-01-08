#include "levels.h"

void get_level_walls(unsigned int level, unsigned int squares[X_MAX][Y_MAX])
{
    // clear level
    for(unsigned int x=0; x<X_MAX; x++)
    {
        for(unsigned int y=0; y<Y_MAX; y++)
        {
            squares[x][y] = 0;
        }
    }

    // common boundary
    for(unsigned int x = 0; x<X_MAX; x++)
    {
        squares[x][0] = 3;
        squares[x][Y_MAX-1] = 3;
    }
    for(unsigned int y = 0; y<Y_MAX; y++)
    {
        squares[0][y] = 3;
        squares[X_MAX-1][y] = 3;
    }

    switch(level)
    {
        case 0:
        default:
            // no additional walls
            break;

        case 1:
            for(unsigned int x = 0; x<X_MAX/2; x++)
            {
                squares[x][Y_MAX/3] = 3;
            }
            for(unsigned int x = X_MAX/2; x<X_MAX; x++)
            {
                squares[x][2*Y_MAX/3] = 3;
            }
            break;

        case 2:
            for(unsigned int i = 0; i<X_MAX/3; i++)
            {
                squares[i][i+10] = 3;
                squares[X_MAX-1-i][Y_MAX-1-i-10] = 3;
            }
            break;

        case 3:
            for(unsigned int x = X_MAX/3; x<X_MAX*2/3-2; x++)
            {
                squares[x][Y_MAX/3] = 3;
                squares[X_MAX-x][Y_MAX*2/3] = 3;
            }
            for(unsigned int y = Y_MAX/3; y<Y_MAX*2/3-1; y++)
            {
                squares[X_MAX/3][y] = 3;
                squares[X_MAX*2/3][Y_MAX-y-1] = 3;
            }
            break;

        case 4:
            for(unsigned int x = X_MAX/3; x<X_MAX*2/3-2; x++)
            {
                squares[x][Y_MAX/3] = 3;
                squares[X_MAX-x][Y_MAX*2/3] = 3;
            }
            for(unsigned int y = Y_MAX/3; y<Y_MAX*2/3-1; y++)
            {
                squares[X_MAX/3][y] = 3;
                squares[X_MAX*2/3][Y_MAX-y-1] = 3;
            }
            break;

        case 5:
            for(unsigned int x = X_MAX/3; x<X_MAX*2/3-2; x++)
            {
                squares[x][Y_MAX/3] = 3;
                squares[X_MAX-x][Y_MAX*2/3] = 3;
            }
            for(unsigned int y = Y_MAX/3; y<Y_MAX*2/3-1; y++)
            {
                squares[X_MAX/3][y] = 3;
                squares[X_MAX*2/3][Y_MAX-y-1] = 3;
            }

            for(unsigned int x = X_MAX/6; x<X_MAX*5/6-2; x++)
            {
                squares[x][Y_MAX/6] = 3;
                squares[X_MAX-x][Y_MAX*5/6] = 3;
            }
            for(unsigned int y = Y_MAX/6; y<Y_MAX*5/6-1; y++)
            {
                squares[X_MAX/6][y] = 3;
                squares[X_MAX*5/6][Y_MAX-y-1] = 3;
            }
            break;

    }
}

unsigned int get_level_fruit_count(unsigned int level)
{
    unsigned int fruit_count = 1;

    switch(level)
    {
        case 0:
        default:
            fruit_count = 5;
            break;
        case 1:
            fruit_count = 6;
            break;
        case 2:
            fruit_count = 8;
            break;
        case 3:
            fruit_count = 8;
            break;
        case 4:
            fruit_count = 20;
            break;
        case 5:
            fruit_count = 15;
            break;
    }

    return fruit_count;
}
