#include "gameloop.h"

#include <SDL2/SDL.h>
#include <time.h>
//#include <cstdio>

#include <windows.h>    // for sound, among other things
#include "rendering.h"

void game_init();

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

    render();
    SDL_Delay(70);

    return quit;
}

void game_init()
{
    srand ( time(NULL) );
}
