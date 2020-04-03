#ifndef FUN_H
#define FUN_H

typedef enum menuChoice  // the choice of menu
{
   useless = 0,
   pvp = 1,
   pvc = 2,
   out = 3
} MenuChoice;

typedef enum chessmsg   // the board and the chess ' message
{
   whiteside = 1,
   blackside = -1,
   blank = 0,
   wall = 2
} Chessmsg;

typedef struct chessPos   // to storage the position of a chess
{
   int x;
   int y;
} ChessPos;

typedef enum button   // to represent what the mouse hit on
{
   regret = 9,
   cancel = 10,
   inboard = 11,
   nobutton = 12
} Button;

typedef enum chance
{
   yes = 20,
   no = 21
} Chance;

#endif // FUN_H

