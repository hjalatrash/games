#include "gameloop.h"

#include <SDL2/SDL.h>
#include <time.h>
//#include <cstdio>

#include <windows.h>    // for sound, among other things
#include "rendering.h"

extern SDL_Renderer *renderer;

struct point points[NUM_POINTS];

void game_init()
{
    srand ( time(NULL) );

    for(unsigned int i=0; i<NUM_POINTS; i++)
    {
        points[i].x = rand() % SCREEN_WIDTH;
        points[i].y = rand() % SCREEN_HEIGHT;
    }
}

bool game_step(void)
{
    SDL_Event event;
    static bool quit = false;

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

    render(points);
    SDL_Delay(70);

    return quit;
}


void render(struct point points[])
{
    // Clear background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Set the drawing color
    //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    unsigned int red=55, blue=200, green=100;


    SDL_SetRenderDrawColor(renderer, red, green, blue, 255);

    for(unsigned int i=0; i<NUM_POINTS; i++)
    {
        SDL_Rect rectangle = {.x = points[i].x, .y = points[i].y, .w = 20, .h = 30};
        SDL_RenderFillRect(renderer, &rectangle);
    }

    print_text("testing", 4);

    // Update the screen
    SDL_RenderPresent(renderer);
}
