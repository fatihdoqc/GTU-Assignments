#ifndef header
#define header

#include <string>
using namespace std;

int getBoard();
void printBoard(int boardSize , char board[12][12]);
void UserVsUser(char board[12][12] , int boardSize , int turn = 1);
bool winCondition_x(char board[12][12] , int buffer[12][12] , int boardSize , int row , int col );
bool winCondition_y(char board[12][12] , int buffer[12][12] , int boardSize , int row , int col );
void printWinningBoard(int boardSize , char board[12][12] , int buffer[12][12]);
void BotVsUser(char board[12][12] , int boardSize , int turn = 1);
void botsMove(char board[12][12] ,int boardSize);
void getCommand(string &command  , string &file);
int user_or_bot(const int &choice , char board[12][12] , int boardSize , int turn  = 1);

#endif