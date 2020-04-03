#include <graphics.h>  // the ege library
#include "testtest.h"   // used to test
#include <stdio.h>
#include "define.h"
#include "draw.h"
#include "mousehit.h"
#include "check.h"
#include "robotbrain.h"

void playgame(void) ;  // the game body
void PVP(void);
void PVC(void);
ChessPos robot(Chessmsg board[][17] , ChessPos prechess , ChessPos competitor , Chessmsg side);

int main()
{
	initgraph(800, 640);  //   open an ege window

   playgame();   // the game body

   getch();   // type to exit
	closegraph();  // close the window
	return 0;
}

void playgame(void)   // the game body
{
   MenuChoice choice = useless;

   while(choice != out)
   {
      cleardevice();
      drawMenu();
      choice = hitmenu();  //choice is the button you hit in the menu
      switch(choice)
      {
      case pvp:
         PVP();
         break;
      case pvc:
         PVC();
         break;
      case out:
         cleardevice();
         setfont(100,0,"楷体");
         outtextxy(300,250,"thanks");
         break;
      default:
         break;
      }
   }

   return;
}

void PVP(void)
{
   drawInterface();   // to draw the board
   Chessmsg board[17][17] = {blank};  //create the virtual board to storage the message
   putboundary(board);  // to create the boundary of the board as "wall"
   Chessmsg side = blackside;   // the chess color
   ChessPos chess = {1,1};   // the present chess position
   ChessPos prechess = chess;  // the precious chess position
   PIMAGE img = newimage();
   PIMAGE holdimg = newimage();
   Button if_button_hit = nobutton;  // to check if one button is hit to regret or go back
   int if_over = 1; //to check if game over , 0 is over
   getimage(holdimg,0,0,800,640);

   while(if_over!=0)
   {
      if_button_hit = hitchesspos(board , &chess.x , &chess.y);  // get the x and y in the board when mouse hit
      switch(if_button_hit)
      {
      case inboard:                          // hit in board
         prechess = chess;  // the latest chess put, store in "prechess"
         putimage(0,0,holdimg);   // put the image without green flame and latest chess
         getimage(img, 0 , 0 , 800 , 640);  // storage the last board image /used when regret
         drawchess(chess.x , chess.y , side , &holdimg); // draw the chess and green flame and get a image without flame
         board[chess.x][chess.y] = side;
         if(checkWin(board , chess.x , chess.y , side) != blank)
         {
            if_over = 0;
            drawWinner(side);        //print the winner on the screen
         }
         else if(checkpeace(board)==0)   // check if no blank last
         {
            if_over = 0;
            drawWinner(blank);
         }
         side = (side==whiteside?blackside:whiteside);
         break;
      case regret:                           //choose to regret
         cleardevice();
         putimage(0,0,img);
         getimage(holdimg,0,0,800,640);
         side = (side==blackside?whiteside:blackside);
         board[prechess.x][prechess.y] = blank;
         break;
      case cancel:                  //choose to cancel the game and go back
         if_over = 0;
         setcolor(BLACK);
         setfont(30,0,"Ώ¬Με");
         outtextxy(300,300,"thanks");
         break;
      default:
         break;
      }
   }
   delimage(img);
   delimage(holdimg);
   getch();
   return;
}

void PVC(void)
{
   drawInterface();   // to draw the board
   Chessmsg board[17][17] = {blank};  //create the virtual board to storage the message
   putboundary(board);  // to create the boundary of the board as "wall"
   Chessmsg side = blackside;   // the chess color
   ChessPos chessP = {1,1};   // the present chess position of player
   ChessPos chessR = {1,1};    // the present chessPosition of robot
   ChessPos prechessP = chessP;  // the precious chess of player position
   ChessPos prechessR = chessR;  // the precious chess of robot position
   PIMAGE img = newimage();
   PIMAGE holdimg = newimage();
   Button if_button_hit = nobutton;  // to check if one button is hit to regret or go back
   int if_over = 1; //to check if game over , 0 is over
   getimage(holdimg,0,0,800,640);

   while(if_over!=0)
   {
      if_button_hit = hitchesspos(board , &chessP.x , &chessP.y);  // get the x and y in the board when mouse hit
      switch(if_button_hit)
      {
      case inboard:                          // hit in board
         //player's loop  /black side
         prechessP = chessP;  // the latest chess put, store in "prechess"
         putimage(0,0,holdimg);   // put the image without green flame and latest chess
         getimage(img, 0 , 0 , 800 , 640);  // storage the last board image /used when regret
         drawchess(chessP.x , chessP.y , side , &holdimg); // draw the chess and green flame and get a image without flame
         board[chessP.x][chessP.y] = side;
         if(checkWin(board , chessP.x , chessP.y , side) != blank)
         {
            if_over = 0;
            drawWinner(side);        //print the winner on the screen
         }
         else if(checkpeace(board)==0)   // check if no blank last
         {
            if_over = 0;
            drawWinner(blank);
         }
         side = whiteside;  // change side
         if(if_over==0)
            break;

         // robot loop
         chessR = robot(board , prechessR , chessP , side);
         prechessR = chessR;
         putimage(0,0,holdimg);
         drawchess(chessR.x , chessR.y , side , &holdimg);
         board[chessR.x][chessR.y] = side;
         if(checkWin(board , chessR.x , chessR.y , side) != blank)
         {
            if_over = 0;
            drawWinner(side);        //print the winner on the screen
         }
         else if(checkpeace(board)==0)   // check if no blank last
         {
            if_over = 0;
            drawWinner(blank);
         }
         side = blackside;
         break;
      case regret:                           //choose to regret
         cleardevice();
         putimage(0,0,img);
         getimage(holdimg,0,0,800,640);
         board[prechessP.x][prechessP.y] = blank;
         board[prechessR.x][prechessR.y] = blank;
         break;
      case cancel:                  //choose to cancel the game and go back
         if_over = 0;
         setcolor(BLACK);
         setfont(30,0,"楷体");
         outtextxy(300,300,"THANKS");
         break;
      default:
         break;
      }
   }
   delimage(img);
   delimage(holdimg);
   getch();
   return;
}

ChessPos robot(Chessmsg board[][17] , ChessPos prechess , ChessPos competitor , Chessmsg side)
{
   ChessPos chess = {1,1};
   if(stage1(board , side , &chess)==yes)
      ;
   else if(stage2(board , side , &chess , competitor)==yes)
      ;
   else if(stage3(board , side , &chess)==yes)
      ;
   else
      stage4(board , side , &chess);

   return chess;
}










