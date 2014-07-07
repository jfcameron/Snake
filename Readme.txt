================================================
Project name: CSnake
Description: A simple game of snake written in C
================================================

Object diagram:
    https://docs.google.com/drawings/d/1YVa1dPlSctYNb_eAmf8KTN4Y0q-LRdKLWnC4FU0__a0/edit?usp=sharing

Data flow diagram:
    https://docs.google.com/drawings/d/1BBT02X9-cvda6J0j2K3ETws7YCRfTbXRC7fifd7sDX8/edit?usp=sharing


Changelog:

7/7/2014 1:37AM
    Refactored Pickup draw code into a function, now accessed via a function pointer stored in the Pickup struct.
    Updated data flow and object diagrams to reflect changes made to the design.
    Moved pickups pointer and player pointer from main.c to globals.h and renamed them g_Player, g_Pickups.

7/6/2014 5:00PM
    Finished game. Menu input handling needs tweaking. Small Graphical glitch with player_Grow needs fixing.

7/5/2014 5:00PM
    Player collision with the player's own segments has been implemented.

7/5/2014 3:00AM
    Boundary collision, random item spawning and lose state implemented.

7/4/2014 12:22PM
    Project started. 
    Looking into mocking up object inheritance etc. and drawing unicode characters.