#include "sounds.h"
#include <windows.h>

void collision_sound()
{
    Beep(800,300);
    Beep(600,100);
    Beep(2000,800);
}

void fruit_sound()
{
    Beep(4000,200);
}

void next_level_sound()
{
    Beep(3000,100);
    Beep(2000,100);
    Beep(4000,200);
}
