//*********
// Includes
//*********
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#include "FunctionLibrary\FunctionLibrary.h"
#include "Constants\Constants.h"
#include "Globals\Globals.h"

#include "Point\Point.h"
#include "Player\Player.h"
#include "Pickup\Pickup.h"

//**********************
// Function Declarations
//**********************
void intro  ();
void menu   ();
void game   ();
void pause  ();
void lose   ();
void restart();
void end    ();

void displayScoreAndLives();
void drawGameBackground();
void drawFrame();
void initializeConsoleWindow();
void spawnPickups();

//********************
// Program entry point
//********************
int main()
{   
    initializeConsoleWindow();

    SetConsoleTextAttribute(consoleHandle, 0x000E | FOREGROUND_INTENSITY);//0x0006
    gotoxy(0,0);

    //Main loop
    for(;;)
    {
        switch(g_GameState)
        {
            case (INTRO):
            intro();
            break;

            case (MENU):
            menu();
            break;

            case (GAME):
            game();
            break;

            case (PAUSE):
            pause();
            break;

            case (LOSE):
            lose();
            break;

            case (RESTART):
            restart();
            break;

            case (END):
            end();
            break;

            case (TERMINATE):
            return;
            break;

            
        
        }

        Sleep(50); //replace this with a proper frame limiter

    }
    

}

//*********************
// Function definitions
//*********************
void intro()
{
    static bool flop = true;
    static short timer = 0;
    static short limit = 10;

    if (flop == true)
    {
        system("cls");
        drawFrame();

        gotoxy( 1, 0 + 2); printf("        XXXXXXXXXXX                                                          "); Sleep( 80);
        gotoxy( 1, 1 + 2); printf("  XXXXXX                                          X                          "); Sleep( 80);
        gotoxy( 1, 2 + 2); printf("  X                                               X                          "); Sleep( 80);
        gotoxy( 1, 3 + 2); printf("  X                                               XX        X           XXX  "); Sleep( 80);
        gotoxy( 1, 4 + 2); printf("  XXX        XX                 X                  X    XXXXX     XXXXXX     "); Sleep( 80);
        gotoxy( 1, 5 + 2); printf("    XXXXXXXXXXXXXX       X      XX    XXXXXX       X  XXX        X           "); Sleep( 80);
        gotoxy( 1, 6 + 2); printf("                  X     XXX      X  XXX    XXX     XXXX         XX           "); Sleep( 80);
        gotoxy( 1, 7 + 2); printf("                  XX   XX XX    XX XX        XX    X  XXXX      XX   XXXXXX  "); Sleep( 80);
        gotoxy( 1, 8 + 2); printf("                 XX   XX   X    X  X XXXXXXXXXX    X     XX      XX          "); Sleep( 80);
        gotoxy( 1, 9 + 2); printf("XX            XXX    XX    XXX XX  X          X   X        XX     XX         "); Sleep( 80);
        gotoxy( 1,10 + 2); printf(" XXXXXXXXXXXXXX      X       XXX              X  XX         XX      XX       "); Sleep( 80);
        gotoxy( 1,11 + 2); printf("                                                 X            XX      XX     "); Sleep( 80);
        gotoxy( 1,12 + 2); printf("                                                X             XX        XXX  "); Sleep( 80);
        gotoxy( 1,13 + 2); printf("                                                                           XX"); Sleep(340);
        gotoxy(70, 2    ); printf("'86"                                                                          ); Sleep(340);
        gotoxy( 4,14    ); printf("An exciting new game for your home computer!"                                 ); Sleep(340);
        
        flop = false;
    }

    if (timer > limit)
    {
        gotoxy(  33,20  ); printf("           ");
            
    
    }
    else
    {
        gotoxy(  33,20  ); printf("Press enter");
        
    
    }

    if (timer > limit*2)
        timer = 0;
    else
        timer++;

    if (GetAsyncKeyState(VK_RETURN))
    {
        g_GameState = RESTART;
        system("cls");
        drawFrame();
        flop = true;
    }

}

void menu ()
{


}

void game ()
{
    int i = 0;

    spawnPickups();

    for (i = 0; i < c_MaximumSimultaneousPickups; i++)
        if (g_Pickups[i].active == true)
            pickup_Draw(&g_Pickups[i]);

    g_Player->update(g_Player);
    g_Player->draw  (g_Player);

    displayScoreAndLives();

    if (GetAsyncKeyState(VK_ESCAPE))
        g_GameState = PAUSE;

}

void pause()
{
    static bool justPaused = true;
    int i = 0;
    
    if (justPaused == true)
    {
        gotoxy(0,consoleScreenBufferInfo.dwSize.Y-1);
        for (i = 0; i < consoleScreenBufferInfo.dwSize.X-1; i++)
            printf("%c",0);

        justPaused = false;
        
    }

    gotoxy(consoleScreenBufferInfo.dwSize.X/2 - 5,consoleScreenBufferInfo.dwSize.Y-1);
    printf("GAME PAUSED");

    gotoxy(consoleScreenBufferInfo.dwSize.X/2 + 21,consoleScreenBufferInfo.dwSize.Y-1);
    printf("Space to continue");

    if (GetAsyncKeyState(VK_SPACE))
    {
        g_GameState = GAME;

        gotoxy(0,consoleScreenBufferInfo.dwSize.Y-1);
        for (i = 0; i < consoleScreenBufferInfo.dwSize.X-1; i++)
            printf("%c",0);

        justPaused = true;

    }

}

void lose ()
{
    static int cursorIndex =0;
    static int counter = 0;

    if (g_Score > g_HighScore)
        g_HighScore = g_Score;

    gotoxy(50,10);
    printf("You died :(!");
    gotoxy(50,11);
    printf("Play again?");
    gotoxy(45,12);
    printf(" Yes  |  Menu |  Quit");

    if (GetAsyncKeyState(VK_LEFT))
        cursorIndex--;

    if (GetAsyncKeyState(VK_RIGHT))
        cursorIndex++;

    if (cursorIndex > 2)
        cursorIndex = 0;
    
    if (cursorIndex < 0)
        cursorIndex = 2;

    gotoxy(45+cursorIndex*8,12);

    printf("%c",128);

    if (GetAsyncKeyState(VK_RETURN))
    {
        if (cursorIndex == 0)
            g_GameState = RESTART;
        else if (cursorIndex == 1)
            g_GameState = INTRO;
        else if (cursorIndex == 2)
            g_GameState = END;

    }

    

}

void restart()
{
    int i = 0;

    free(g_Pickups);

    g_Pickups = (Pickup*)malloc (sizeof (Pickup) * (c_MaximumSimultaneousPickups));

    for (i = 0; i < c_MaximumSimultaneousPickups; i++)
        g_Pickups[i] = pickup_New(0,0);

    system("cls");
    drawFrame();

    //Free the heap memory
    if (g_Player)
        player_Free(g_Player);
    
    free(g_Player);
    //Create a new player
    g_Player = (Player*)malloc(sizeof(Player));
   *g_Player = player_New(30,10);

    g_GameState = GAME;
    g_Score     = 0;

}

void end()
{
    static int timer = 0;
    static bool flop = false;
    int i = 0;

    if (flop == false)
    {
        system("cls");
        SetConsoleTextAttribute(consoleHandle, 0x0006 | FOREGROUND_INTENSITY);
        
        gotoxy(11, 0);printf("                                                     ");
        gotoxy(11, 1);printf("                       SNAKE                         ");
        gotoxy(11, 2);printf("-----------------------------------------------------");
        gotoxy(11, 3);printf("  You just played SNAKE, the critically acclaimed    ");
        gotoxy(11, 4);printf("  game designed for the home PC.                     ");
        gotoxy(11, 5);printf("                                                     ");
        gotoxy(11, 6);printf("                                                     ");
        gotoxy(11, 7);printf("                                                     ");
        gotoxy(11, 8);printf("                                                     ");
        gotoxy(11, 9);printf("  I hope you enjoyed playing this cutting edge game. ");
        gotoxy(11,10);printf("  I fully expect it to spawn 100s of sequels,        ");
        gotoxy(11,11);printf("  a line of plush toys, and inspire all future       ");
        gotoxy(11,12);printf("  generations.                                       ");
        gotoxy(11,13);printf("                                                     ");
        gotoxy(11,14);printf("  Programming: Joseph Cameron                        ");
        gotoxy(11,15);printf("                                                     ");
    
        gotoxy(1,consoleScreenBufferInfo.dwSize.Y-4);

        flop = true;

    }

    if (timer > 50)
    {
        gotoxy(1,consoleScreenBufferInfo.dwSize.Y-4);
        SetConsoleTextAttribute(consoleHandle, 0x000F | FOREGROUND_INTENSITY);
        printf("Press enter to continue...");



    }
    else
        timer++;   

    if (GetAsyncKeyState(VK_RETURN))
    {
        g_GameState = TERMINATE;
        gotoxy(0,consoleScreenBufferInfo.dwSize.Y-2);

    }

}

void drawGameBackground()
{
    int x = 0;
    int y = 0;

    gotoxy(1,1);
    
    for (y = 0; y < consoleScreenBufferInfo.dwSize.Y-3; y++)
        for (x = 0; x < consoleScreenBufferInfo.dwSize.X -2; x++)
        {
            gotoxy(x+1,y+1);
            printf("%c",0);

        }

}

void displayScoreAndLives()
{
    gotoxy(1,consoleScreenBufferInfo.dwSize.Y-1);
    printf("Lives: "    );
    printf("%i",g_Lives );
    printf(" Score: "   );
    printf("%i",g_Score );

    gotoxy(30,consoleScreenBufferInfo.dwSize.Y-1);
    printf("Highscore: ");
    printf("%i",g_HighScore);

    gotoxy(66,consoleScreenBufferInfo.dwSize.Y-1);
    printf("ESC to pause");

}

void drawFrame()
{
    int x = 0;
    int y = 0;

    //Top right corner
    gotoxy(consoleScreenBufferInfo.dwSize.X-1,0);
    printf("%c",2);
    //Top left corner
    gotoxy(0,0);
    printf("%c",1);
    //Bottom right corner
    gotoxy(consoleScreenBufferInfo.dwSize.X-1,consoleScreenBufferInfo.dwSize.Y-2);
    printf("%c",4);
    //Bottom left corner
    gotoxy(0,consoleScreenBufferInfo.dwSize.Y-2);
    printf("%c",3);

    //Top horizontal bar
    gotoxy(1,0);

    for (x = 0; x < consoleScreenBufferInfo.dwSize.X - 2; x++)
        printf("%c",6);

    gotoxy(0,0);

    //Left vertical bar
    for (y = 0; y < consoleScreenBufferInfo.dwSize.Y - 3; y++)
    {
        gotoxy(0,y+1);
        printf("%c",5);

    }

    //Right vertical bar
    for (y = 0; y < consoleScreenBufferInfo.dwSize.Y - 3; y++)
    {
        gotoxy(consoleScreenBufferInfo.dwSize.X-1,y+1);
        printf("%c",5);

    }

    //Bottom horizontal bar
    gotoxy(1,consoleScreenBufferInfo.dwSize.Y-2);

    for (x = 0; x < consoleScreenBufferInfo.dwSize.X - 2; x++)
        printf("%c",6);

}

void spawnPickups()
{
    static int counter = 0;
    
    int x = 0;
    int y = 0;

    if (counter > c_PickupSpawnrate)
    {
        int     i      = 0;
        Pickup* pickup = 0;

        //check if there is an opening in the pickups array
        for (i = 0; i < c_MaximumSimultaneousPickups; i++)
        {
            if (g_Pickups[i].active == false)
            {
                pickup = &g_Pickups[i];
                break;
            }

        }

        //Return if there arent any open positions in the pickups array
        if (pickup == 0)
            return;

        //Generate a random position that does not overlap other pickups or the player
        {
            bool overlapDetected = true;

            while(overlapDetected == true)
            {
                overlapDetected = false; 

                x = 1 + (rand() % (consoleScreenBufferInfo.dwSize.X-2));
                y = 1 + (rand() % (consoleScreenBufferInfo.dwSize.Y-3));

                for (i = 0; i < g_Player->length; i++)
                    if (x == g_Player->segments[i].x && y == g_Player->segments[i].y)
                        overlapDetected = true;

                for (i = 0; i < c_MaximumSimultaneousPickups; i++)
                    if (x == g_Pickups[i].x && y == g_Pickups[i].y)
                        overlapDetected = true;

            }

        }

        //Give the pickup its new position and reactivate it
        pickup->x      =    x ;
        pickup->y      =    y ;
        pickup->active = true ;

        //Draw the pickup
        gotoxy(pickup->x,pickup->y);
        printf("%c", c_PickUpCharacter);

        counter = 0;

    }
    else
        counter++;

}

void initializeConsoleWindow()
{
    //Local variables
    //CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
    
    COORD bufferSize;
    SMALL_RECT windowSize;

    windowSize.Top    =  0 ;
    windowSize.Left   =  0 ;
    windowSize.Right  = 60 ;
    windowSize.Bottom = 20 ;

    //Get handles to this program's window
    windowHandle  = GetConsoleWindow();
    consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    //Initalize...
    SetConsoleTitle(L"CSnake");

    //Trying to fix the buffer size
    GetConsoleScreenBufferInfo(consoleHandle, &consoleScreenBufferInfo);
    bufferSize.X = consoleScreenBufferInfo.srWindow.Right - consoleScreenBufferInfo.srWindow.Left;
    bufferSize.Y = consoleScreenBufferInfo.srWindow.Bottom - consoleScreenBufferInfo.srWindow.Top;
    
    SetConsoleWindowInfo(consoleHandle,1,&windowSize);
    SetConsoleScreenBufferSize(consoleHandle,bufferSize);

    MoveWindow(windowHandle, 0, 0, 1000, 1000, TRUE);

    //Print
    GetConsoleScreenBufferInfo(consoleHandle, &consoleScreenBufferInfo);
    gotoxy(5,2);
    printf("Buffer width: ");
    printf("%i",consoleScreenBufferInfo.dwSize.X);
    gotoxy(5,3);
    printf("Buffer height: ");
    printf("%i",consoleScreenBufferInfo.dwSize.Y);

    gotoxy(30,2);
    printf("Window width: ");
    printf("%i",windowSize.Right);
    gotoxy(30,3);
    printf("Window height: ");
    printf("%i",windowSize.Bottom);

}

