#include "graphics.h"
#include <stdio.h>
#include "define.h"

void drawMenu(void)   // to draw the main menu
{
   setbkcolor(YELLOW);
   setfont(50,0,"楷体");
   setcolor(BLACK);
   outtextxy(300,200,"人机对战");
   outtextxy(300,300,"人人对战");
   outtextxy(300,400,"退出游戏");

   return;
}

void drawInterface(void)  // to draw the game interface:the board and two buttons/to regret or back
{
   cleardevice();  // to clean the screen
   setbkcolor(YELLOW);  //set background color as yellow
   PIMAGE img;    // to storage the image we used to draw
   int i = 0 ;    //counter

   img = newimage();    // create a new image
   getimage(img , 0,0,800,640);
   // to print the flame
   setcolor(BLACK);
   setfillcolor(BLACK);
   bar(18,18,580,20);
   bar(580,18,582,580);
   bar(18,580,582,582);
   bar(18,20,20,580);
   //print the lines inside
   setlinewidth(1);
   for(i = 1 ; i < 14 ; i++)
   {
      line(20+40*i,20,20+40*i,580);
   }
   for(i = 1 ; i < 14 ; i++)
   {
      line(20,20+40*i,580,20+40*i);
   }
   //set special point
   fillellipse(140,140,3,3);
   fillellipse(140,460,3,3);
   fillellipse(460,140,3,3);
   fillellipse(460,460,3,3);
   fillellipse(300,300,3,3);
   //two buttons
   outtextxy(640 , 80 , "悔棋");
   outtextxy(640 , 160 , "退出");
   //put image only the board without background
   putimage_transparent(NULL,img,20,20,YELLOW);

   delimage(img);   // delete image

   return;
}

void putboundary(Chessmsg board[][17])  // to build the boundary of the board
{
   int i = 0;
   for(i = 0 ; i < 17 ; i++)
   {
      board[i][0] = wall;
      board[0][i] = wall;
      board[16][i] = wall;
      board[i][16] = wall;
   }

   return;
}

void drawchess(int x , int y , Chessmsg side , PIMAGE * img)  // to draw chess and the green flame on the board
{
   x = x*40 - 20;    //exchange x and y to the real coordinate
   y = y*40 - 20;

   if(side == whiteside)
   {
      setfillcolor(WHITE);
   }
   else
   {
      setfillcolor(BLACK);
   }
   fillellipse(x, y, 15 , 15);  // to draw the chess

   *img = newimage();    // to get a image without green flame
   getimage(*img , 0 ,0 , 800 , 640);
   setcolor(GREEN);
   setfillcolor(GREEN);
   bar(x-20,y-20,x+20,y-18);          // to draw the green flame
   bar(x-20,y-20,x-18,y+20);
   bar(x+20,y-20,x+18,y+20);
   bar(x-20,y+20,x+20,y+18);

   return;
}

void drawWinner(Chessmsg side)   // to announce winner or heqi
{
   setfont(30,0,"楷体");
   setcolor(BLACK);
   if(side == blackside)
      outtextxy(300,300,"黑棋获胜");
   else if(side == whiteside)
      outtextxy(300,300,"白棋获胜");
   else if(side == blank)
      outtextxy(300,300,"和棋");
   else
      outtextxy(300,300,"??????");
   return;
}

void drawinteger(int x)
{
   char m[10] = {0};
   sprintf(m , "%d" , x);
   outtextxy(600,400,m);
   getch();
   return;
}





