#include "rendering.h"

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <windows.h>


SDL_Window *window;
SDL_Renderer *renderer;
TTF_Font *font;

int setup_graphics_window(void)
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }
/*
    // Initialize SDL_ttf
    if (TTF_Init() != 0) {
        printf("SDL_ttf initialization failed: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }
*/
    // Create a window
    window = SDL_CreateWindow("Snake Game by H. Alatrash - Dec. 2023", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

    // Load a font
    //font = TTF_OpenFont("./font/ArianaVioleta-dz2K.ttf", 24);
//    font = TTF_OpenFont("./font/Kingthings_Calligraphica_2.ttf", TEXT_SIZE);

/*
    if (!font) {
        printf("Failed to load font: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
*/
    return 0;
}
/*
void print_text(char text[], unsigned int row)
{
    SDL_Texture *textTexture;
    SDL_Color textColor = {255, 255, 255, 255}; // White color

    // Create a surface with text
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, textColor);

    // Create a texture from the surface
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    // Render the text
    SDL_Rect textRect = {SCREEN_WIDTH, row*TEXT_SIZE, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

}
*/
void render(void)
{
    // Clear background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Set the drawing color
    //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    unsigned int red=55, blue=200, green=100;


    SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
    SDL_Rect rectangle = {.x = 1 + 20, .y = 1 + 30, .w = 20, .h = 30};
    SDL_RenderFillRect(renderer, &rectangle);

//    print_status(state);

    // Update the screen
    SDL_RenderPresent(renderer);
}

void close_graphics(void)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}
