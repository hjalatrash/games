#ifndef RENDERING_H
    #define RENDERING_H

    #define TEXT_SIZE       (24)
    #define SCREEN_WIDTH    (800)
    #define SCREEN_HEIGHT   (800)

    int setup_graphics_window(void);
    void print_text(char text[], unsigned int row);
    void close_graphics(void);

#endif // RENDERING_H
