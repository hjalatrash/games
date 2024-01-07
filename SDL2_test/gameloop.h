#ifndef GAMELOOP_H
    #define GAMELOOP_H

    #define SQUARE_SIZE (12)
    #define X_MAX       (96)
    #define Y_MAX       (64)
    #define MAX_MOVES   (100)
    #define MAX_LEVEL   (5)

    #define SCREEN_WIDTH    (SQUARE_SIZE * X_MAX)
    #define SCREEN_HEIGHT   (SQUARE_SIZE * Y_MAX)

    bool game_step(void);
    void game_init();

#endif // GAMELOOP_H
