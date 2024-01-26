#ifndef GAMELOOP_H
    #define GAMELOOP_H

    #define X_MAX       (96)
    #define Y_MAX       (64)
    #define MAX_MOVES   (100)
    #define MAX_LEVEL   (5)

    bool game_step(void);
    void game_init();

    struct game_state
    {
        unsigned int level;
        unsigned int fruit_count;
        unsigned int lives;
    };

#endif // GAMELOOP_H
