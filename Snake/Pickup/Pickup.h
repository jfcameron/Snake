#ifndef PICKUP_H
#define PICKUP_H

#include "../Constants/Constants.h"
#include "../FunctionLibrary/FunctionLibrary.h"

typedef struct Pickup
{
  int  x, y;
  bool active;

  void (*draw)  (Pickup);

} Pickup;

//Interface
void pickup_Draw(Pickup* aPickup);

//Constructor
Pickup pickup_New(int aX, int aY);

#endif