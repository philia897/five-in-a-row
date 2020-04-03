#ifndef CHECK_H_INCLUDED
#define CHECK_H_INCLUDED
Chessmsg checkWin(Chessmsg board[][17] , int x , int y , Chessmsg target); // to check if one side win/return the result
int checkpeace(Chessmsg board[][17]);  // 0 = no blank, 1 = continue
void copyboard(Chessmsg fromboard[][17] , Chessmsg toboard[][17]); // copy formboard to toboard
void ifischoice(Chessmsg board[][17] , int x , int y , ChessPos choices[]);  // check the x and y and 45' line all choices
int oneStepToWin(Chessmsg board[][17] , ChessPos chess , Chessmsg side) ; // to check how many ways can win in one more step
int calculateThreatDegree(Chessmsg board[][17] , ChessPos competitor , Chessmsg sideC) ; // to calculate the threat degree of the whole board
int wholeThreatDegree(Chessmsg board[][17] , ChessPos competitor , Chessmsg sideC);
int calculateAdvantage(Chessmsg board[][17] , ChessPos chess , Chessmsg side);



#endif // CHECK_H_INCLUDED
