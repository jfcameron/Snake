#include "Player.h"

Player player_New(int x, int y)
{
    //locals
    int i = 0;
    Player a;

    //stack variables init
    a.x         =              x ;
    a.y         =              y ;
    a.tailIndex =              0 ;
    a.dir       =          RIGHT ;
    a.length    =              6 ;
    //function pointers
    a.update    = &player_Update ;
    a.draw      = &player_Draw   ;

    //heap variables init
    a.segments = malloc (sizeof (Point) * a.length);

    //Place the snake in the top right corner
    for (i = 0; i < a.length; i++)
    {
        a.segments[i] = point_New(1+i,1);
    }

    return a;
}

void player_Update(Player* aPlayer)
{
    static int segmentIterator = 0;
    int i = 0;
    int decrementer = 0;

    player_HandleInput(aPlayer);
    player_Move(aPlayer);
    player_PreventOutOfBounds(aPlayer);

    //Iterate the segments
    if (segmentIterator >= aPlayer->length)
        segmentIterator = 0;

    aPlayer->segments[segmentIterator].x = aPlayer->x;
    aPlayer->segments[segmentIterator].y = aPlayer->y;

    //Find the tail
    decrementer = segmentIterator+1;

    for (i = 0; i < aPlayer->length; i++)
    {
        decrementer--;

        if (decrementer <0)
            decrementer = aPlayer->length-1;

    }

    aPlayer->tailIndex = decrementer;

    //Check for collisions

    //collision with the player's segments
    for (i = 0; i < aPlayer->length; i++)
    {
        if (aPlayer->x == aPlayer->segments[i].x && aPlayer->y == aPlayer->segments[i].y && i != segmentIterator)
        {
            g_GameState = LOSE;

        }

    }

    segmentIterator++;

    //bound collisions

    //left
    if (aPlayer->x <= 0)
    {
        g_GameState = LOSE;
    }
    //right
    if (aPlayer->x >= consoleScreenBufferInfo.dwSize.X -1)
    {
        g_GameState = LOSE;
    }
    //Up
    if (aPlayer->y <= 0)
    {
        g_GameState = LOSE;
    }
    //Down
    if (aPlayer->y >= consoleScreenBufferInfo.dwSize.Y -2)
    {
        g_GameState = LOSE;
    }

    if (GetAsyncKeyState(0x41) && aPlayer->dir != DOWN)
        player_Grow(aPlayer);

    player_DetectPickupCollisions(aPlayer);

}

void player_Draw(Player* aPlayer)
{
    int i = 0;

    for (i; i < aPlayer->length; i++)
    {        
        gotoxy(aPlayer->segments[i].x,aPlayer->segments[i].y);

        printf("%c", c_PlayerCharacter);

    }

    //Cleans up the end of the tail. In a console game, you cant clear a frame buffer every frame.
    gotoxy(aPlayer->segments[aPlayer->tailIndex].x,aPlayer->segments[aPlayer->tailIndex].y);
    printf("%c",0);

    

}

void player_HandleInput(Player* aPlayer)
{
    //Handle input
    if (GetAsyncKeyState(VK_UP) && aPlayer->dir != DOWN)
    {
        aPlayer->dir = UP;
    }

    if (GetAsyncKeyState(VK_RIGHT) && aPlayer->dir != LEFT)
    {
        aPlayer->dir = RIGHT;
    }

    if (GetAsyncKeyState(VK_DOWN) && aPlayer->dir != UP)
    {
        aPlayer->dir = DOWN;
    }

    if (GetAsyncKeyState(VK_LEFT) && aPlayer->dir != RIGHT)
    {
       aPlayer->dir = LEFT;
    }

}

void player_Move(Player* aPlayer)
{
        switch(aPlayer->dir)
    {
        case (UP):
        {
            aPlayer->y--;
        }break;

        case (RIGHT):
        {
            aPlayer->x++;
        }break;

        case (DOWN):
        {
            aPlayer->y++;
        }break;

        case (LEFT):
        {
            aPlayer->x--;
        }break;

    }

}

void player_PreventOutOfBounds(Player* aPlayer)
{
    //handle out of bounds
    if (aPlayer->x < 0)
        aPlayer->x = 0;

    if (aPlayer->y < 0)
        aPlayer->y = 0;

    if (aPlayer->x >= consoleScreenBufferInfo.dwSize.X)
        aPlayer->x = consoleScreenBufferInfo.dwSize.X-1;

    if (aPlayer->y >= consoleScreenBufferInfo.dwSize.Y-1)
        aPlayer->y = consoleScreenBufferInfo.dwSize.Y-2;

}

void player_DetectCollisionWithSelf(Player* aPlayer)
{


}

void player_Free(Player* aPlayer)
{
    free(aPlayer->segments);

}

void player_Grow(Player* aPlayer)
{
    Point* newSegments;
    int i = 0;

    //1. create a new segements
    newSegments = malloc (sizeof (Point) * (aPlayer->length +1));

    //2. copy information from old segments to new segements
    for (i = 0; i < aPlayer->length; i++)
    {
        newSegments[i] = aPlayer->segments[i];
    
    }

    newSegments[i] = aPlayer->segments[aPlayer->tailIndex - 1];

    //3. increment length
    aPlayer->length++;

    //4. delete segments
    free(aPlayer->segments);

    //5. swap segments
    aPlayer->segments = newSegments;

}

void player_DetectPickupCollisions(Player* aPlayer)
{
    int i = 0;

    for (i = 0; i < c_MaximumSimultaneousPickups; i++)
    {
        if (aPlayer->x == g_Pickups[i].x && aPlayer->y == g_Pickups[i].y)
        {
            g_Score ++;
            player_Grow(aPlayer);

            g_Pickups[i].active = false;

        }

    }

}