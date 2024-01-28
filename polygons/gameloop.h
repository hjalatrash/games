#ifndef GAMELOOP_H
    #define GAMELOOP_H


    struct point
    {
        unsigned int x;
        unsigned int y;
    };

    bool game_step(void);
    void game_init();
    void render(struct point points[]);

    #define NUM_POINTS  (16)

#endif // GAMELOOP_H
