#include "gameloop.h"

#include <SDL2/SDL.h>
#include <time.h>

#include "sounds.h"
#include "rendering.h"
#include "levels.h"

struct moves
{
    unsigned int direction;
    unsigned int length;
};

// snake state
struct moves moves[MAX_MOVES];
unsigned int head_x=X_MAX/2, head_y=Y_MAX/2;
unsigned int squares[X_MAX][Y_MAX];

// level state
unsigned int level;
unsigned int fruit_count;

// declarations
void move_snake(bool grow);

void init_level(unsigned int level);
void game_init();
void add_move(unsigned int direction);

bool game_step(void)
{
    SDL_Event event;
    static bool quit = false;
    static unsigned int growth = 0;

    bool complete_level = false;

    //static uint8_t red=0, green=0, blue=0;
    //static int mouse_x=0, mouse_y=0;

    /* Poll for events */
    if( SDL_PollEvent( &event ) )
    {
        switch( event.type ){
            case SDL_KEYDOWN:
            //case SDL_KEYUP:
                switch(event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    case SDLK_UP:
                        if(3!=moves[0].direction)
                            add_move(1);
                        break;
                    case SDLK_DOWN:
                        if(1!=moves[0].direction)
                            add_move(3);
                        break;
                    case SDLK_LEFT:
                        if(2!=moves[0].direction)
                            add_move(0);
                        break;
                    case SDLK_RIGHT:
                        if(0!=moves[0].direction)
                            add_move(2);
                        break;
                    case SDLK_TAB:
                        complete_level = true;
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

    move_snake(growth>0);
    if(growth>0)
        growth--;

    switch(squares[head_x][head_y])
    {
        case 1: // snake body
        case 3: // wall
            collision_sound();
            quit = true;
            break;

        case 2:     // fruit
            growth+=5;
            squares[head_x][head_y] = 1;   // overwrite
            fruit_sound();

            fruit_count--;
            complete_level = (0==fruit_count);
            break;

        case 0:
        default:
            squares[head_x][head_y] = 1;
            break;
    }

    render(squares);
    SDL_Delay(70);

    if(complete_level)
    {
        level++;
        init_level(level);
        next_level_sound();
        SDL_Delay(500);

        if(level>MAX_LEVEL)
        {
            SDL_Delay(2000);
            quit = true;
        }
    }

    return quit;
}

// other routines
// --------------

void init_level(unsigned int level)
{
    // initialize snake
    moves[0] = {.direction = 0, .length = 4};

    for(unsigned int i=1; i<MAX_MOVES; i++)
    {
        moves[i].length=0;
    }

    head_x = X_MAX/2;
    head_y = Y_MAX/2;

    // get level info
    get_level_walls(level, squares);
    fruit_count = get_level_fruit_count(level);

    // add fruit
    for(unsigned int i =0; i<fruit_count;)
    {
        unsigned int x = rand() % X_MAX;
        unsigned int y = rand() % Y_MAX;

        if(0==squares[x][y])
        {
            squares[x][y]= 2;
            i++;
        }
    }
}

void game_init()
{
    srand ( time(NULL) );

    level = 0;
    init_level(level);
}

void add_move(unsigned int direction)
{
    for(unsigned int i = MAX_MOVES-1; i>0; i--)
    {
        moves[i] = moves[i-1];
    }
    moves[0]={.direction = direction, .length=0};
}

void move_snake(bool grow)
{
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

    // update squares matrix
    unsigned int x = head_x, y = head_y;

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
        // if last move, reduce the length (unless we're growing the snake)
        if(moves[i+1].length == 0)
        {
            if(!grow)
            {
                moves[i].length--;
                squares[x][y]=0;
            }
            break;
        }
    }
}
