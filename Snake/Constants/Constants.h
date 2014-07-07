#ifndef CONSTANTS_H
#define CONSTANTS_H

#define false 0
#define true 1
#define bool unsigned char

extern const short c_PlayerCharacter;
extern const short c_PickUpCharacter;
extern const short c_PickupSpawnrate;
extern const short c_MaximumSimultaneousPickups;

typedef enum 
{
    ZERO,
    UP, 
    RIGHT, 
    DOWN,
    LEFT

} direction;

typedef enum
{
    INTRO,
    MENU,
    GAME,
    PAUSE,
    LOSE,
    TERMINATE,
    END,
    RESTART

}gameState;

#endif