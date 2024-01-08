#ifndef RENDERING_H
    #define RENDERING_H

    #include "gameloop.h"

    #define SQUARE_SIZE (12)
    #define SCREEN_WIDTH    (SQUARE_SIZE * X_MAX)
    #define SCREEN_HEIGHT   (SQUARE_SIZE * Y_MAX)


    int setup_graphics_window(void);
    void render(unsigned int squares[X_MAX][Y_MAX]);
    void close_graphics(void);

#endif // RENDERING_H