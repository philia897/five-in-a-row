#include "define.h"
void drawMenu(void) ;  // to draw the main menu
void drawInterface(void) ; // to draw the game interface:the board and two buttons/to regret or back
void putboundary(Chessmsg board[][17]) ; // to build the boundary of the board
void drawchess(int x , int y , Chessmsg side , PIMAGE * img) ; // to draw chess and the green flame on the board
void drawWinner(Chessmsg side);   // to announce winner or heqi
void drawinteger(int x);

