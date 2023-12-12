#ifndef GAMELOOP_H
    #define GAMELOOP_H

    #define SQUARE_SIZE 16
    #define X_MAX       64
    #define Y_MAX       48
    #define MAX_MOVES   100

    #define SCREEN_WIDTH    (SQUARE_SIZE * X_MAX)
    #define SCREEN_HEIGHT   (SQUARE_SIZE * Y_MAX)

    bool game_step(SDL_Renderer *renderer);
    void game_init();

#endif // GAMELOOP_H
