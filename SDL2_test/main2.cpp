#include <stdio.h>
#include <SDL2/SDL.h>

int main( int argc, char * argv[] ) {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

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

    // Set the drawing color to red
    SDL_SetRenderDrawColor(renderer, 255, 150, 0, 255);

    // Clear the screen (background color)
    //SDL_RenderClear(renderer);

    // Draw a line
    SDL_RenderDrawLine(renderer, 100, 100, 300, 300);

    // Update the screen
    SDL_RenderPresent(renderer);

    // Wait for a few seconds before closing the window
    //SDL_Delay(3000);


    // Event loop
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
            else if (event.type == SDL_TEXTINPUT) {
                // Handle text input events
                //printf("Text Input: %s\n", event.text.text);
                if(event.text.text[0] == 'x')
                    quit = 1;
            }
        }
    }


    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

