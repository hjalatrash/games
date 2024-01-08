#include "sounds.h"
#include <windows.h>

void collision_sound()
{
    for(int i=0; i<6; i++)
    {
        Beep(1000 - i*100, 100);
    }
    Beep(300, 1500);
}

void fruit_sound()
{
    Beep(4000,10);
}

void next_level_sound()
{
    Beep(3000,100);
    Beep(2000,100);
    Beep(4000,200);
}
