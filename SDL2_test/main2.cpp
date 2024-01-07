#include "rendering.h"
#include "gameloop.h"


int main( int argc, char * argv[] ) {

    if(setup_graphics_window())
        return 1;

    // initialize game
    game_init();

    // Event loop
    // ==========
    while( !game_step() );

    close_graphics();

    return 0;
}
