#ifndef RENDERING_H
    #define RENDERING_H

    #include "gameloop.h"

    int setup_graphics_window(void);
    void render(unsigned int squares[X_MAX][Y_MAX]);
    void close_graphics(void);

#endif // RENDERING_H
