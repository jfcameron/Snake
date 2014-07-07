#include "Pickup.h"

Pickup pickup_New(int aX, int aY)
{
    Pickup a;

    //Data members
    a.x      =    aX ;
    a.y      =    aY ;
    a.active = false ;
    //Member functions
    a.draw   = &pickup_Draw;

    return a;

}

void pickup_Draw(Pickup* aPickup)
{
    gotoxy(aPickup->x,aPickup->y);
    printf("%c",c_PickUpCharacter);

}