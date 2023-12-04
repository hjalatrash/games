#include <stdio.h>
#include <SDL2/SDL.h>

bool game_step(SDL_Renderer *renderer)
{
    SDL_Event event;
    static bool quit = false;

    static uint8_t red=0, green=0, blue=0;
    static uint8_t x=0, y=0;


    // Set the drawing color to red
    //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Clear the screen (background color)
    //SDL_RenderClear(renderer);

    // Set the drawing color to red
    SDL_SetRenderDrawColor(renderer, red, green, blue, 255);

    // Draw a line
    SDL_RenderDrawLine(renderer, x+100, y+100, x+300, y+300);

    // Update the screen
    SDL_RenderPresent(renderer);

    y++;
        /* Poll for events */
        while( SDL_PollEvent( &event ) ){

            switch( event.type ){
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                    switch(event.key.keysym.sym){
                        case SDLK_x:
                            x++;
                            break;
                        case SDLK_r:
                            red++;
                            break;
                        case SDLK_g:
                            green++;
                            break;
                        case SDLK_b:
                            blue++;
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
    return quit;
}

int main( int argc, char * argv[] ) {
    SDL_Window *window;
    SDL_Renderer *renderer;

    // Setup
    // =====

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window
    window = SDL_CreateWindow("Drawing Example", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, 1000, 800, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Event loop
    // ==========
    while( !game_step(renderer) );

    // Clean up
    // ========
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
