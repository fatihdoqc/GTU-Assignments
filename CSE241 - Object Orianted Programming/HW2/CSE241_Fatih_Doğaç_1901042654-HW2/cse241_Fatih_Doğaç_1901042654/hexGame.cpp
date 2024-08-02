#include <iostream>
#include "header.h"
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;


int main(){

	char board[12][12];
	int boardSize = getBoard() , choice;

	for(int i = 0; i<boardSize; i++){

		for(int j = 0; j<boardSize; j++){ // Filling the board with dots.

			board[i][j] = '.';
		}
	}

	cout << " 1) user vs user / 2) user vs computer \n";
	cin >> choice;

	switch(choice){
		case 1: //user vs user.
			UserVsUser(board , boardSize);
			return 1;
		case 2:
			BotVsUser(board , boardSize);
			return 1;
		default:
			cout << "Invalid input";
			return 0;

	}
	printBoard(boardSize , board);

	return 1;
}