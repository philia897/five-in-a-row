#include "graphics.h"
#include <stdio.h>
#include "define.h"

MenuChoice hitmenu(void)  // to check which function you choose in the menu
{
   MenuChoice choose = useless;  // storage the choice
   mouse_msg mouse = {0};   // the mouse message

   for(;is_run() ; delay_fps(60))
   {
      while(mousemsg())
         mouse = getmouse();
      if((int)mouse.is_down()==1)
      {
         if(mouse.x>300&&mouse.x<500)
         {
            if(mouse.y>200&&mouse.y<250)   // choose PVC
            {
               choose = pvc;
               break;
            }
            else if(mouse.y>300&&mouse.y<350)   // choose PVP
            {
               choose = pvp;
               break;
            }
            else if(mouse.y>400&&mouse.y<450)   // choose EXIT
            {
               choose = out;
               break;
            }
         }
      }
   }

   return choose;
}

Button hitchesspos(const Chessmsg board[][17], int * x , int * y)   // to get the position of the hit of mouse/ return if button is hit
{
   mouse_msg mouse = {0};
   for(;is_run();delay_fps(60))   // to check the position mouse hit on
   {
      while(mousemsg())
      {
         mouse = getmouse();
      }
      if((int)mouse.is_down()==1)
      {
         *x = (mouse.x)/40 + 1;
         *y = (mouse.y)/40 + 1;
         break;
      }
   }
   // check if buttons be hit and return the result
   if((*x==17||*x==18)&&*y==3)
   {
      return regret;
   }
   else if((*x==17||*y==18)&&*y==5)
   {
      return cancel;
   }
   else if((1<=*x)&&(*x<=15)&&(1<=*y)&&(*y<=15)&&board[*x][*y]==blank)
   {
      return inboard;
   }
   else
   {
      return nobutton;
   }

}


