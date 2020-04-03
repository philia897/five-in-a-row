#ifndef ROBOTBRAIN_H_INCLUDED
#define ROBOTBRAIN_H_INCLUDED
Chance stage1(Chessmsg board[][17] , Chessmsg sideR , ChessPos * chessR);   // return "yes" or "no"
Chance stage2(Chessmsg inboard[][17] , Chessmsg sideR , ChessPos * chessR , ChessPos competitor);
Chance stage3(Chessmsg inboard[][17] , Chessmsg sideR , ChessPos * chessR);
Chance stage4(Chessmsg inboard[][17] , Chessmsg sideR , ChessPos * chessR);

#endif // ROBOTBRAIN_H_INCLUDED

/*robot's action is divided to 4 stages
stage1: to check if robot can use one step to win
stage2: to check if robot must to defend(only can put
        chess on several position) or competitor will win
stage3: to check if robot can step one to guarantee win
stage4: to check put chess on which position can have
        the biggest advantage
*/
