#ifndef header
#define header

int getBoard();
void printBoard(int boardSize , char board[12][12]);
void UserVsUser(char board[12][12] , int boardSize);
bool winCondition_x(char board[12][12] , int buffer[12][12] , int boardSize , int row , int col );
bool winCondition_y(char board[12][12] , int buffer[12][12] , int boardSize , int row , int col );
void printWinningBoard(int boardSize , char board[12][12] , int buffer[12][12]);
void BotVsUser(char board[12][12] , int boardSize);
void botsMove(char board[12][12] ,int boardSize);

#endif