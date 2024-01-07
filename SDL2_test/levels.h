#ifndef LEVELS_H
    #define LEVELS_H

    #include "gameloop.h"

    void get_level_walls(unsigned int level, unsigned int squares[X_MAX][Y_MAX]);
    unsigned int get_level_fruit_count(unsigned int level);

#endif // LEVELS_H
