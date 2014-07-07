fix input to check if the window has focus

fix system font issue.

change player input to else ifs not a bunch of ifs

prevent collision on tail segment

fix keyboard input. 
    It needs to check if the game has focus. So wrap clals... also might as well add timers and junk	

Update object diagram
    out of date as of July/06/2014

Edit code for style.
    Rename functions etc. for legibility.

Fix player_Grow glitch
    Sometimes when the player increases in size the new segment's xy is wrong, which
    causes that segment to appear outside the player's body for a few frames.

Fix menu input handling
    Inputting a choice on pause is akward. 
    Pausing and unpausing can sometimes behave strangely
    Sometimes the quit screen message is skipped.

make a common parent for player and pickup

------------------------------------------------------------------------------------------------------
DONE
------------------------------------------------------------------------------------------------------

encapsulate pickup draw calls in the pickup struct

Replace all magic numbers with globals and constants.
    start position of player etc.

Make a pickup list, add pickup detection with the player.
    What is a pickup? An x,y and a character.
    Spawning a pickup is:
    1) randomizing an xy, 
    2) placing a character at that position
    3) and storing the xy in a list of xys that is then iterated every frame
    4) if the player's xy is the same as a xy in the list, a point is awarded and that xy is deactivated.

    so... int,int,bool.


Resize the player based on score. This'll be fun...
    1) create an int* of length
    2) copy current segments into the new array
    3) delete the current segment array
    4) point to the new array

Fix erasing method