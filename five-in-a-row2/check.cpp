#include "define.h"
#include "stdio.h"
#include "check.h"
#include "graphics.h"
#include "draw.h"

Chessmsg checkWin(Chessmsg board[][17] , int x , int y , Chessmsg target)  // to check if one side win/return the result
{
   int number = 1;  // to check how many cheese are in a row
   int i = 0 , i2 = 0; // counter

   for(i = -1 ; i != 3 ; i += 2)
   {
      for(i2 = 1 ; i2 < 5 ; i2++)
      {
         if(board[x+i*i2][y]==target)
            number++;
         else
            break;
      }
   }
   if(number>=5)
      return target;
   else
      number = 1;

   for(i = -1 ; i != 3 ; i += 2)
   {
      for(i2 = 1 ; i2 < 5 ; i2++)
      {
         if(board[x][y+i*i2]==target)
            number++;
         else
            break;
      }
   }
   if(number>=5)
      return target;
   else
      number = 1;

   for(i = -1 ; i != 3 ; i += 2)
   {
      for(i2 = 1 ; i2 < 5 ; i2++)
      {
         if(board[x+i*i2][y+i*i2]==target)
            number++;
         else
            break;
      }
   }
   if(number>=5)
      return target;
   else
      number = 1;

   for(i = -1 ; i != 3 ; i += 2)
   {
      for(i2 = 1 ; i2 < 5 ; i2++)
      {
         if(board[x-i*i2][y+i*i2]==target)
            number++;
         else
            break;
      }
   }
   if(number>=5)
      return target;
   else
      number = 1;

   return blank;
}

int checkpeace(Chessmsg board[][17])  // 0 = no blank, 1 = continue
{
   int result = 0;
   int i = 0,i2 = 0;
   for(i = 1 ; i <=15 ; i++)
   {
      for(i2 = 1 ; i2 <=15 ; i2++)
      {
         if(board[i][i2]==blank)
         {
            result = 1;
            break;
         }
      }
      if(result==0)
         break;
   }
   return result;
}

void copyboard(Chessmsg fromboard[][17] , Chessmsg toboard[][17]) // copy formboard to toboard
{
   int i = 0, i2 = 0;
   for(i = 0 ; i <= 16 ; i++)
   {
      for(i2 = 0 ; i2 <= 16 ; i2++)
      {
         toboard[i][i2] = fromboard[i][i2];
      }
   }

   return;
}

void ifischoice(Chessmsg board[][17] , int x , int y , ChessPos choices[])  // check the x and y and 45' line all choices
{
   int i = 0 , i2 = 0 ; // counter

   for(i = 1 ; i <= 5 ; i++)
   {
      if(x+i<=15&&board[x+i][y]==blank)
      {
         choices[i2].x = x + i;
         choices[i2].y = y;
         i2++;
      }
      if(y+i<=15&&board[x][y+i]==blank)
      {
         choices[i2].x = x;
         choices[i2].y = y+i;
         i2++;
      }
      if(x-i>=1&&board[x-i][y]==blank)
      {
         choices[i2].x = x - i;
         choices[i2].y = y;
         i2++;
      }
      if(y-i>=1&&board[x][y-i]==blank)
      {
         choices[i2].x = x ;
         choices[i2].y = y -i ;
         i2++;
      }
      if(x+i<=15&&y+i<=15&&board[x+i][y+i]==blank)
      {
         choices[i2].x = x + i;
         choices[i2].y = y + i;
         i2++;
      }
      if(x+i<=15&&y-i>=1&&board[x+i][y-i]==blank)
      {
         choices[i2].x = x + i;
         choices[i2].y = y - i;
         i2++;
      }
      if(x-i>=1&&y+i<=15&&board[x-i][y+i]==blank)
      {
         choices[i2].x = x - i;
         choices[i2].y = y + i;
         i2++;
      }
      if(x-i>=1&&y-i>=1&&board[x-i][y-i]==blank)
      {
         choices[i2].x = x - i;
         choices[i2].y = y - i;
         i2++;
      }

   }

   return ;
}

int oneStepToWin(Chessmsg board[][17] , ChessPos chess , Chessmsg side)  // to check how many ways can win in one more step
{
   int way = 0;  // how many ways to win
   int i = 0;  // counter
   ChessPos choices[41] = {0};  // to storage all the possible choices / the tail always be {0,0}
   ifischoice(board , chess.x , chess.y , choices);  // to find out all the choices at most 40 ways
   for(i = 0 ; choices[i].x !=0 ; i++)
   {
      if(checkWin(board , choices[i].x , choices[i].y , side)!= blank)
      {
         way++;
      }
   }

   return way;
}

int calculateThreatDegree(Chessmsg board[][17] , ChessPos competitor , Chessmsg sideC)  // to calculate the threat degree of the whole board
{
   int degree = 0;
   ChessPos choices[41] = {0};   // to storage all the choices(on x and y and two 45' line)
   int i = 0 , i2 = 0; // counters
   int hold = 0;
   int way[3] = {0};  //how many ways can win in one step
   /*way[0]: competitor can use this step to win
     way[1]: competitor can use this and next steps to win
     way[2]: competitor can use this and then two steps to win(the last step have two choices at least)*/
   if(checkWin(board , competitor.x , competitor.y , sideC)!=blank)
      way[0] = 1;
   else
   {
      board[competitor.x][competitor.y] = sideC;
      // the second step
      way[1] = oneStepToWin(board , competitor , sideC)/2;
      // the third step
      ifischoice(board , competitor.x , competitor.y , choices);
      for(i = 0 ; choices[i].x != 0 ; i++)
      {
         board[choices[i].x][choices[i].y] = sideC;
         hold = oneStepToWin(board , choices[i] , sideC);
         if(hold>=2)
         {
            way[2]++;
         }
         board[choices[i].x][choices[i].y] = blank;
      }

      board[competitor.x][competitor.y] = blank;
   }

   degree = way[0]*10000 + way[1]*100 + way[2];

   return degree;
}

int wholeThreatDegree(Chessmsg board[][17] , ChessPos competitor , Chessmsg sideC)
{
   int degree = 0;
   int i = 0;
   ChessPos choices[41] = {0};   // to storage all the choices(on x and y and two 45' line)
   ifischoice(board , competitor.x , competitor.y , choices);
   for(i = 0 ; choices[i].x != 0 ; i++)
   {
      degree += calculateThreatDegree(board , choices[i] , sideC);
   }

   return degree;
}

int calculateAdvantage(Chessmsg board[][17] , ChessPos chess , Chessmsg side)
{
   int degree = 0;
   ChessPos choices[41] = {0};   // to storage all the choices(on x and y and two 45' line)
   ChessPos choices2[41] = {0};
   int i = 0 , i2 = 0; // counters
   int hold = 0;
   int way[2] = {0};  //how many ways can win in one step
   board[chess.x][chess.y] = side;
   ifischoice(board , chess.x , chess.y , choices);
   for(i = 0 ; choices[i].x!=0 ; i++)
   {
      board[choices[i].x][choices[i].y] = side;
      hold = oneStepToWin(board , choices[i] , side);
      way[0] += hold;
      ifischoice(board , choices[i].x , choices[i].y , choices2);
      for(i2 = 0 ; choices2[i2].x != 0 ; i2++)
      {
         board[choices2[i].x][choices2[i].y] = side;
         hold = oneStepToWin(board , choices2[i] , side);
         way[1] += hold;
         board[choices2[i].x][choices2[i].y] = blank;
      }
      board[choices[i].x][choices[i].y] = blank;
   }
   board[chess.x][chess.y] = blank;

   degree = way[0]*1000 + way[1];
   return degree;
}










