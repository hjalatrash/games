#include "gameloop.h"

#include <SDL2/SDL.h>
#include <time.h>
//#include <cstdio>
#include <math.h>

#include <windows.h>    // for sound, among other things
#include "rendering.h"

extern SDL_Renderer *renderer;

struct point points[NUM_POINTS];
struct color
{
    unsigned int r;
    unsigned int g;
    unsigned int b;
    unsigned int brightness;
};

#define DT (1)     // msec
#define RANDOM_SPEED ((rand() % 1000) - 500)
#define PI (3.1415962)

void game_init()
{
    srand ( time(NULL) );

    for(unsigned int i=0; i<NUM_POINTS; i++)
    {
        points[i].x = rand() % SCREEN_WIDTH;
        points[i].y = rand() % SCREEN_HEIGHT;
        points[i].speed_x = RANDOM_SPEED;
        points[i].speed_y = RANDOM_SPEED;
    }
}

bool game_step(void)
{
    SDL_Event event;
    static bool quit = false;
    static float t=0;

    t+= DT * 1e-3;

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
                    case SDLK_TAB:
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

    for(unsigned int i=0; i<NUM_POINTS; i++)
    {
        points[i].x += points[i].speed_x * DT*0.001;
        points[i].y += points[i].speed_y * DT*0.001;

        if(points[i].x < 0)
        {
            points[i].x=0;
            points[i].speed_x = abs(RANDOM_SPEED);
        }
        if(points[i].x > SCREEN_WIDTH)
        {
            points[i].x=SCREEN_WIDTH;
            points[i].speed_x = -abs(RANDOM_SPEED);
        }

        if(points[i].y < 0)
        {
            points[i].y=0;
            points[i].speed_y = abs(RANDOM_SPEED);
        }
        if(points[i].y > SCREEN_HEIGHT)
        {
            points[i].y=SCREEN_HEIGHT;
            points[i].speed_y = -abs(RANDOM_SPEED);
        }
    }


    float sum_x = 0;
    float sum_y = 0;

    for(unsigned int i=0; i<NUM_POINTS; i++)
    {
        sum_x += points[i].x;
        sum_y += points[i].y;
    }


    struct color line_color =
    {
        .r = 127 + 128 * cos(t),
        .g = 127 + 128 * cos(t+2*PI/3),
        .b = 127 + 128 * cos(t-2*PI/3),
        .brightness = 255
    };


    render(points, line_color);
    SDL_Delay(DT);

    return quit;
}


void render(struct point points[], struct color line_color)
{
    // Clear background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Set the drawing color
    //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    SDL_SetRenderDrawColor(renderer, line_color.r, line_color.g, line_color.b, line_color.brightness);

    for(unsigned int i=0; i<NUM_POINTS; i++)
    {
        //unsigned int i_next = (i+1) % NUM_POINTS;
        //SDL_SetRenderDrawColor(renderer, (points[i].x*128 + points[i_next].x*128)/SCREEN_WIDTH, (points[i].y*128+points[i_next].y*128)/SCREEN_HEIGHT, 0, 255);
        //SDL_RenderDrawLine(renderer, points[i].x, points[i].y, points[i_next].x, points[i_next].y);

        SDL_RenderDrawPoint(renderer, points[i].x, points[i].y);
    }

    print_text("Maradona!", 4);

    // Update the screen
    SDL_RenderPresent(renderer);
}
