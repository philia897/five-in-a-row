#include "graphics.h"
#include "draw.h"
#include "define.h"
#include "check.h"
#include <stdio.h>
#include "robotbrain.h"

/*robot's action is divided to 4 stages
stage1: to check if robot can use one step to win
stage2: to check if robot must to defend(only can put
        chess on several position) or competitor will win
stage3: to check if robot can step one to guarantee win
stage4: to check put chess on which position can have
        the biggest advantage
*/


/*stage1: to check if robot can use one step to win*/
Chance stage1(Chessmsg board[][17] , Chessmsg sideR , ChessPos * chessR)   // return "yes" or "no"
{
   int i = 1 , i2 = 1;  // counters
   Chance judge = no;
   for(i = 1 ; i <= 15 ; i++)
   {
      for(i2 = 1 ; i2 <= 15 ; i2++)
      {
         if(board[i][i2]==blank&&checkWin(board , i , i2 , sideR)!=blank)
         {
            chessR->x = i;
            chessR->y = i2;
            judge = yes;
            break;
         }
      }
   }

   return judge;
}

///////////////////////////////////////////////////////////////////////////////////////////

/*stage2: to check if robot must to defend(only can put
          chess on several position) or competitor will win*/
Chance stage2(Chessmsg inboard[][17] , Chessmsg sideR , ChessPos * chessR , ChessPos competitor)
{
   Chessmsg board[17][17];   // a copy board in this scope
   copyboard(inboard , board);   // to copy board in case of revise in mistake
   Chance judge = no;
   ChessPos chess = {1,1};
   ChessPos choices[41] = {0};   // to storage all the choices(on x and y and two 45' line)
   Chessmsg sideC = (sideR==whiteside?blackside:whiteside);  // the competitor's side
   int degree = 0 , degree2 = 0 , degreeA = 0 , degreeA2 = 0;
   int i = 0 ; // counters
   // one step to win
   ifischoice(board , competitor.x , competitor.y , choices);

   degree = wholeThreatDegree(board , competitor , sideC);
   //outtextxy(600,300,"stage 2");drawinteger(degree);
   if(degree >= 100 || degree%100 >=8)  // must to defend
   {
      judge = yes;
      for(i = 0 ; choices[i].x !=0 ; i++)   // to choose the best choice to decrease the threat degree
      {
         board[choices[i].x][choices[i].y] = sideR;
         degree2 = wholeThreatDegree(board , competitor , sideC);
         if(degree2 < degree)
         {
            chess = choices[i];
            degree = degree2;
         }
         else if(degree2 == degree)  // when two ways is ok ,check which is better for robot
         {
            degreeA = calculateAdvantage(board , chess , sideR);
            degreeA2 = calculateAdvantage(board , choices[i] , sideC);
            if(degreeA <degreeA2)
            {
               chess = choices[i];
            }
         }
         board[choices[i].x][choices[i].y] = blank;
      }
   }

   if(judge == yes)
      *chessR = chess;
   return judge;
}


////////////////////////////////////////////////////////////////////////////////////////////

/*stage3: to check if robot can step one to guarantee win*/
Chance stage3(Chessmsg inboard[][17] , Chessmsg sideR , ChessPos * chessR)
{
   Chessmsg board[17][17];
   copyboard(inboard , board);
   Chance judge = no;
   ChessPos chess = {1,1};
   Chessmsg sideC = (sideR==whiteside?blackside:whiteside);
   int degree = 0 , degree2 = 0;
   int i = 0 , i2 = 0;
   ChessPos hold = {0};
   for(i = 1 ; i <= 15 ; i++)
   {
      for(i2 = 1 ; i2 <= 15 ; i2 ++)
      {
         if(board[i][i2]==blank)
         {
            hold.x = i;
            hold.y = i2;
            board[i][i2] = sideR;
            degree2 = wholeThreatDegree(board , hold , sideR);
            board[i][i2] = blank;
            if(degree2>=degree)
            {
               degree = degree2;
               chess = hold;
            }
         }
      }
   }
   //outtextxy(600,300,"stage 3");drawinteger(degree);
   if(degree >= 100 || degree%100 >=12)  // to judge if degree is large enough
      judge = yes;

   if(judge == yes)
      *chessR = chess;
   return judge;
}



////////////////////////////////////////////////////////////////////////////////////////////

/*stage4: to check put chess on which position can have
          the biggest advantage*/
Chance stage4(Chessmsg inboard[][17] , Chessmsg sideR , ChessPos * chessR)
{
   Chessmsg board[17][17];
   copyboard(inboard , board);
   Chance judge = yes;
   ChessPos chess = {1,1};
   Chessmsg sideC = (sideR==whiteside?blackside:whiteside);
   int degree = 0 , degree2 = 0;
   int i = 0 , i2 = 0;
   ChessPos hold = {0};
   for(i = 1 ; i <= 15 ; i++) // to check on which place robot have the most advantage
   {
      for(i2 = 1 ; i2 <= 15 ; i2 ++)
      {
         if(board[i][i2]==blank)
         {
            hold.x = i;
            hold.y = i2;
            board[i][i2]==sideR;
            degree2 = calculateAdvantage(board , hold , sideR);
            board[i][i2]==blank;
            if(degree2>=degree)
            {
               degree = degree2;
               chess = hold;
            }
         }
      }
   }
   //outtextxy(600,300,"4 attack");drawinteger(degree);
   degree *= 2;    // to supplement and to make the robot more attactive
   for(i = 1 ; i <= 15 ; i++)   // to check one which place competitor have the most advantage
   {
      for(i2 = 1 ; i2 <= 15 ; i2 ++)
      {
         if(board[i][i2]==blank)
         {
            hold.x = i;
            hold.y = i2;
            board[i][i2] == sideC;
            degree2 = calculateAdvantage(board , hold , sideC);
            board[i][i2] == blank;
            if(degree2>=degree)
            {
               degree = degree2;
               chess = hold;
            }
         }
      }
   }
   //outtextxy(600,300,"4 defend");drawinteger(degree);

   if(judge == yes)
      *chessR = chess;
   return judge;
}




