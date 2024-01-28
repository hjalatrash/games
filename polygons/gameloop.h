#ifndef GAMELOOP_H
    #define GAMELOOP_H


    struct point
    {
        float x;
        float y;
        float speed_x;
        float speed_y;
    };

    bool game_step(void);
    void game_init();
    void render(struct point points[]);

    #define NUM_POINTS  (8)

#endif // GAMELOOP_H
