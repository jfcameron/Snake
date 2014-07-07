#ifndef PLAYER_H
#define PLAYER_H
//*********
// Includes
//*********
//std, win includes
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <Windows.h>
//project includes
#include "../FunctionLibrary/FunctionLibrary.h"
#include "../Globals/Globals.h"
#include "../Constants/Constants.h"
#include "../Point/Point.h"

typedef struct Player //applying a label here allows for forward declarations
{
  int x, y;

  int length;
  int tailIndex;
  
  direction dir;
  
  Point* segments;

  

  void (*update)(Player);
  void (*draw)  (Player);

} Player;

//Interface functions
void    player_Update                  (Player* aPlayer);
void    player_Draw                    (Player* aPlayer);
//Private functions
void    player_HandleInput             (Player* aPlayer);
void    player_Move                    (Player* aPlayer);
void    player_DetectCollisionWithSelf (Player* aPlayer);
void    player_PreventOutOfBounds      (Player* aPlayer);
void    player_Grow                    (Player* aPlayer);
void    player_DetectPickupCollisions  (Player* aPlayer);
//Constructor
Player  player_New                     (int x, int y   );
//Destructor
void    player_Free                    (Player* aPlayer);



#endif