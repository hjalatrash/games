#include <SDL2/SDL.h>
#include "gameloop.h"
#include <time.h>

struct moves
{
    unsigned int direction;
    unsigned int length;
};

struct moves moves[MAX_MOVES];
unsigned int head_x=X_MAX/2, head_y=Y_MAX/2;
unsigned int squares_filled[X_MAX][Y_MAX];

void render(SDL_Renderer *renderer);

void game_init()
{
    srand ( time(NULL) );

    moves[0] = {.direction = 0, .length = 4};
    for(unsigned int x = 0; x<X_MAX; x++)
    {
        squares_filled[x][0] = 3;
        squares_filled[x][Y_MAX-1] = 3;
    }
    for(unsigned int y = 0; y<Y_MAX; y++)
    {
        squares_filled[0][y] = 3;
        squares_filled[X_MAX-1][y] = 3;
    }

    for(int i =0; i<5; i++)
    {
        squares_filled[1+rand()%(X_MAX-2)][1+rand()%(Y_MAX-2)] = 2;
    }
}

void add_move(unsigned int direction)
{
    for(unsigned int i = MAX_MOVES-1; i>0; i--)
    {
        moves[i] = moves[i-1];
    }
    moves[0]={.direction = direction, .length=0};
}

bool game_step(SDL_Renderer *renderer)
{
    SDL_Event event;
    static bool quit = false;
    static unsigned int growth = 0;

    static uint8_t red=0, green=0, blue=0;
    static int mouse_x=0, mouse_y=0;

    /* Poll for events */
    if( SDL_PollEvent( &event ) )
    {
        switch( event.type ){
            case SDL_KEYDOWN:
            //case SDL_KEYUP:
                switch(event.key.keysym.sym){
                    case SDLK_x:
                        quit = true;
                        break;
                    case SDLK_UP:
                        add_move(1);
                        break;
                    case SDLK_DOWN:
                        add_move(3);
                        break;
                    case SDLK_LEFT:
                        add_move(0);
                        break;
                    case SDLK_RIGHT:
                        add_move(2);
                        break;
                }
                break;

            /* SDL_QUIT event (window close) */
            case SDL_QUIT:
                quit = true;
                break;

            default:
                break;
        }
    }

    // empty event log
    //while( SDL_PollEvent( &event ) );

    // Move snake by making first move longer
    switch(moves[0].direction)
    {
        case 0:
            head_x--;
            break;
        case 1:
            head_y--;
            break;
        case 2:
            head_x++;
            break;
        case 3:
            head_y++;
            break;
    }
    moves[0].length++;

    // update squares_filled matrix
    unsigned int x = head_x, y = head_y;

    bool collision = false;

    switch(squares_filled[x][y])
    {
        case 1: // snake body
        case 3: // wall
            collision = true;
            break;

        case 2:     // fruit
            growth+=5;
            squares_filled[x][y] = 1;   // overwrite
            break;

        case 0:
        default:
            squares_filled[x][y] = 1;
            break;
    }

    // traverse snake and make it a step shorter
    for(unsigned int i=0; i<MAX_MOVES; i++)
    {
        for(unsigned int j=0; j<moves[i].length; j++)
        {
            switch(moves[i].direction)
            {
                case 0:
                    x++;
                    break;
                case 1:
                    y++;
                    break;
                case 2:
                    x--;
                    break;
                case 3:
                    y--;
                    break;
            }
        }
        if(moves[i+1].length == 0)
        {
            if(growth)
                growth--;
            else
            {
                moves[i].length--;
                squares_filled[x][y]=0;
            }
            break;
        }
    }

    if(collision) quit = true;

    render(renderer);
    SDL_Delay(50);

    return quit;
}

void render(SDL_Renderer *renderer)
{
    // Clear background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Set the drawing color
    //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    unsigned int red, blue, green;

    for(int x=0; x<X_MAX; x++)
    {
        for(int y=0; y<Y_MAX; y++)
        {
            switch(squares_filled[x][y])
            {
                case 1:
                    green = 0;
                    red = 255;
                    blue = 0;
                    break;
                case 2:
                    green = 255;
                    red = 0;
                    blue = 0;
                    break;
                case 3:
                    green = 0;
                    red = 0;
                    blue = 255;
                    break;
                case 0:
                    green = 0;
                    red = 0;
                    blue = 0;
                    break;
            }

            SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
            SDL_Rect rectangle = {.x = 1 + x * SQUARE_SIZE, .y = 1 + y * SQUARE_SIZE, .w = SQUARE_SIZE-2, .h = SQUARE_SIZE-2};
            SDL_RenderFillRect(renderer, &rectangle);
        }
    }

    // Update the screen
    SDL_RenderPresent(renderer);
}
