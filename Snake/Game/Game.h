#ifndef _GAME_H
#define _GAME_H

typedef struct 
{
  int x, y;

  direction dir;

  int length;
  Point* segments;

  int tailIndex;

  void (*update)(Player);
  void (*draw)  (Player);

} Game;

#endif