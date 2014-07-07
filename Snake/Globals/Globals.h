#ifndef GLOBALS_H
#define GLOBALS_H

#include<Windows.h>
#include"../Constants/Constants.h"
#include"../Pickup/Pickup.h"
#include"../Point/Point.h"
#include"../Player/Player.h"

struct Player; //Forward declaration because of order compilation

//Window instance handles
CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
HWND                       windowHandle;
HANDLE                     consoleHandle;

//Game stuff
extern int       g_Score     ;
extern int       g_HighScore ;
extern int       g_Lives     ;
extern gameState g_GameState ;

struct Player*   g_Player;
struct Pickup*   g_Pickups;

#endif