#include <iostream>
#include "header.h"
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

enum user { comp , user1, user2};

/*#define USER1 1
#define USER2 2
#define COMP 0*/

/* 						Menu						*/
int getBoard(){

	int choice;

	cout << "Size of board? : " << endl <<
	"1) 6x6\n" << "2) 7x7" << endl << "3) 8x8" << endl <<"4) 9x9" << 
	endl <<"5) 10x10" << endl <<"6) 11x11" << endl <<"7) 12x12" << endl << "Choice..: ";

	cin >> choice;

	switch(choice){

		case 1:
			return 6;
		case 2:
			return 7;
		case 3:	
			return 8;
		case 4:	
			return 9;
		case 5:	
			return 10;
		case 6:	
			return 11;
		case 7:	
			return 12;
		default:
			cout<< "Invalid input." << endl;
			exit;
			return 0;
	}
}
void printBoard(int boardSize , char board[12][12]){

	//cout << "\033c";
	cout<< endl << "  ";
	for(auto j = 0; j<boardSize; j++){

		cout << static_cast<char>('a' + j) << " "; // columns.	
	}

	cout << endl;

	for(auto i = 0; i<boardSize; i++){

	
		cout << static_cast<int>(1 + i) << " " ; // rows.

		if( i >= 9){
			for(int a = 1; a<i; a++){
				cout << " ";
			}
		}
		else{
			for(int a = 0; a<i; a++){

				cout  << " ";			// Adding spaces so the map can look like the way it should.
			}
		}

		for(decltype(i) j  = 0; j<boardSize; j++){

			cout << board[i][j] << " "; // printing the board.
		}
		cout << endl;

	}

}
void UserVsUser(char board[12][12] , int boardSize , int turn){

	user USER1 = user1, USER2 = user2, COMP = comp;
	int x = 0 , row , buffer[12][12] , a , b;
	char col;
	string line ,command,file = "empty";

	while(x <145){ // I don't need to exit from while so it is just true.

		if( turn == USER1){
			
			printBoard(boardSize , board);

			cout << "player 1's move : ";

			getCommand(command , file);

			if(file == "empty"){

				col = command[0];
				row = stoi(command.substr(1)) ;

			}
			else{

				if(command == "SAVE"){
					ofstream MyFile;
					MyFile.open(file);

					if(MyFile.is_open()){
						MyFile << turn << " ";
						MyFile << 1 << " ";
						MyFile << boardSize << " ";

						for(int i = 0; i< boardSize; i++){
							for(int j = 0; j< boardSize; j++){
								MyFile << board[i][j] << " ";
							}
						}
					}
					else{
						cerr << "Error openning file.";
					}
					MyFile.close();
					file="empty";
					continue;
					
				}
				else if(command == "LOAD"){

					char value;
					int UserOrBot;

					ifstream secFile;
					secFile.open(file);

					if(secFile.is_open()){
						secFile >> turn;
						secFile >> UserOrBot;
						secFile >> boardSize;
						//cout << turn;
						for(int i = 0; i< boardSize; i++){
							for(int j = 0; j< boardSize; j++){
								secFile >> value;
								board[i][j] = value;
							}
						}
					}
					else{
						cerr << "Error openning file. ";
					}
					secFile.close();
					file="empty";

					user_or_bot(UserOrBot , board , boardSize , turn);
					continue;
	
				}
			}

			if(board[row - 1][col - 97] == '.' && (row-1) <= boardSize && (col-97) < boardSize){ // Is the move valid ?

				board[row - 1][col- 97] = 'x';

				for(a = 0; a<boardSize; a++){ // Find the start of the winning path.

					if( board[a][0] == 'x'){

						turn = USER2;

						for(int i = 0; i<boardSize; i++){

							for(int j = 0; j<boardSize; j++){ // Resetting the buffer.

								buffer[i][j] = 0 ;
							}
						}

						if( winCondition_x(board , buffer , boardSize , a , 0) ){

					
							printWinningBoard(boardSize , board , buffer);

							cout << "PLAYER1 HAS WON!" << endl ;
							exit(0);
						}

					}
				}

			}
			else{
				cerr << "Something is wrong...I can feel it.\n";
				continue;
			}	
		}
		else if(turn == USER2){

			printBoard(boardSize , board);

			cout << "player 2's move :  ";

			getCommand(command , file);

			if(file == "empty"){

				col = command[0];
				row = stoi(command.substr(1)) ;

			}
			else{

				if(command == "SAVE"){
					ofstream MyFile;
					MyFile.open(file);

					if(MyFile.is_open()){
						MyFile << turn << " ";
						MyFile << 1 << " "; // UserVsUser
						MyFile << boardSize << " ";


						for(int i = 0; i< boardSize; i++){
							for(int j = 0; j< boardSize; j++){
								MyFile << board[i][j] << " ";
							}
						}
					}
					else{

					}
					continue;
					
				}
				else if(command == "LOAD"){

					char value;
					int UserOrBot;

					ifstream secFile;
					secFile.open(file);

					if(secFile.is_open()){
						secFile >> turn;
						secFile >> UserOrBot;
						secFile >> boardSize;
						//cout << turn;
						for(int i = 0; i< boardSize; i++){
							for(int j = 0; j< boardSize; j++){
								secFile >> value;
								board[i][j] = value;
							}
						}
					}
					else{
						cerr << "Error openning file. ";
					}
					secFile.close();
					user_or_bot(UserOrBot , board , boardSize , turn);
					continue;
	
				}
			}

			/* Is the move valid ?  */
			if(board[row - 1][col- 97] == '.' && (row-1) <= boardSize && (col-97) < boardSize){ 

				board[row - 1][col- 97] = 'o';

				turn = USER1;

				for(b = 0; b<boardSize; b++){
					if(board[0][b] == 'o'){

						for(int i = 0; i<boardSize; i++){

							for(int j = 0; j<boardSize; j++){ // Resetting the buffer.

								buffer[i][j] = 0 ;
							}
						}
						
						if( winCondition_y(board , buffer , boardSize , 0 , b) ){

							printWinningBoard(boardSize , board , buffer);

							cout << "PLAYER2 HAS WON!" << endl ;
							exit(0);
						}
					}
				}
			}
			else{
				cerr << "Something is wrong...I can feel it.\n";
				turn = USER2;
			}
			
		}
	}getline(std::cin , line);

	return;
	
}
void getCommand(string &command  , string &file ){

	string line;
	int length , i = 0;

	getline(cin>>ws , line);

	command = line;
	file = "empty";

	if(line.find("SAVE") != -1){

		length = line.find(" ");

		command = line.substr(0 , length);
		file = line.substr(length+1) ;

	}
	else if(line.find("LOAD") != -1){
		length = line.find(" ");

		command = line.substr(0 , length);
		file = line.substr(length+1) ;
	}
	else if(line.length() > 3){
		cerr << "Invalid Input "  << endl;
		cout << "Try again: ";
		getCommand(command , file);
	}

}
int user_or_bot(const int &choice , char board[12][12] , int boardSize , int turn){

	switch(choice){
		case 1: //user vs user.
			UserVsUser(board , boardSize , turn);
			return 1;
		case 2:
			BotVsUser(board , boardSize , turn);
			return 1;
		default:
			cout << "Invalid input";
			return 0;

	}
}
bool winCondition_x(char board[12][12] , int buffer[12][12] , int boardSize , int row , int col ){
	
	/* FINISH LINE */ 
	if(col == (boardSize-1) && board[row][col] == 'x'){
		buffer[row][col] = 2;
		return true;
	}

	/* Is valid? */
	if( row < 0 || row >= boardSize || col < 0 || col >= boardSize || buffer[row][col] == 2){

		return false;
	}
	else{

		buffer[row][col] = 2; // Keeping the places I have been to not going back through them.

		/* CHECKING ALL SIX DIRECTIONS. */ 
		if( board[row][col + 1] == 'x' && buffer[row][col+1] != 2){

			return winCondition_x(board , buffer , boardSize , row , col + 1);
		}

		if( board[row-1][col + 1] == 'x' && buffer[row-1][col+1] != 2){

			return winCondition_x(board , buffer , boardSize , row-1 , col + 1);
		}

		if( board[row-1][col ] == 'x' && buffer[row-1][col] != 2){

			return winCondition_x(board , buffer , boardSize , row-1 , col );
		}

		if( board[row][col-1 ] == 'x' && buffer[row][col-1] != 2){

			return winCondition_x(board , buffer , boardSize , row , col - 1);
		}

		if( board[row+1][col -1] == 'x' && buffer[row+1][col-1] != 2){

			return winCondition_x(board , buffer , boardSize , row+1 , col - 1);
		}

		if( board[row+1][col ] == 'x' && buffer[row+1][col] != 2){

			return winCondition_x(board , buffer , boardSize , row+1 , col);
		}

		return false;
	}
}
bool winCondition_y(char board[12][12] , int buffer[12][12] , int boardSize , int row , int col ){
	/* FINISH LINE.  */
	if(row == (boardSize-1) && board[row][col] == 'o'){
		buffer[row][col] = 2;
		return true;
	}


	/* is valid ? */
	if( row < 0 || row >= boardSize || col < 0 || col >= boardSize || buffer[row][col] == 2){

		return false;
	}
	else{

		buffer[row][col] = 2; // Keeping the places I have been to not going back through them.

		/* CHECKING ALL SIX DIRECTIONS. */ 
		if( board[row][col + 1] == 'o' && buffer[row][col+1] != 2){

			return winCondition_y(board , buffer , boardSize , row , col + 1);
		}

		if( board[row-1][col + 1] == 'o' && buffer[row-1][col+1] != 2){

			return winCondition_y(board , buffer , boardSize , row-1 , col + 1);
		}

		if( board[row-1][col ] == 'o' && buffer[row-1][col] != 2){

			return winCondition_y(board , buffer , boardSize , row-1 , col );
		}

		if( board[row][col-1 ] == 'o' && buffer[row][col-1] != 2){

			return winCondition_y(board , buffer , boardSize , row , col - 1);
		}

		if( board[row+1][col -1] == 'o' && buffer[row+1][col-1] != 2){

			return winCondition_y(board , buffer , boardSize , row+1 , col - 1);
		}

		if( board[row+1][col ] == 'o' && buffer[row+1][col] != 2){

			return winCondition_y(board , buffer , boardSize , row+1 , col);
		}


		return false;
	}
}
void printWinningBoard(int boardSize , char board[12][12] , int buffer[12][12]){

	cout << "\033c";
	cout<< "  ";
	for(int j = 0; j<boardSize; j++){

		cout << static_cast<char>('a' + j) << " "; // columns.	
	}

	cout << endl;

	for(int i = 0; i<boardSize; i++){

	
		cout << static_cast<int>(1 + i) << " " ; // rows.

		for(int a = 0; a<i; a++){
			cout  << " ";			// Adding spaces so the map can look like the way it should.
		}

		for(int j = 0; j<boardSize; j++){

			if(buffer[i][j] == 2){
				cout << static_cast<char>(board[i][j] - 32)<< " "; // printing the board with capital letters.
			}
			else{
				cout << board[i][j]<< " "; // printing the board.
			}
		}
		cout << endl;

	}

}
void BotVsUser(char board[12][12] , int boardSize , int turn ){

	user USER1 = user1, USER2 = user2, COMP = comp;
	int buffer[12][12] , row , a , b;
	char col;
	string line ,command,file = "empty";

	while(true){
		if(turn == USER1){

			printBoard(boardSize, board);

			cout << "Your move: ";

			getCommand(command , file);

			if(file == "empty"){

				col = command[0];
				row = stoi(command.substr(1)) ;

			}
			else{

				if(command == "SAVE"){
					ofstream MyFile;
					MyFile.open(file);

					if(MyFile.is_open()){
						MyFile << turn << " ";
						MyFile << 2 << " ";
						MyFile << boardSize << " ";

						for(int i = 0; i< boardSize; i++){
							for(int j = 0; j< boardSize; j++){
								MyFile << board[i][j] << " ";
							}
						}
					}
					else{
						cerr << "Error openning file.";
					}
					MyFile.close();
					file="empty";
					continue;
					
				}
				else if(command == "LOAD"){

					char value;
					int UserOrBot;

					ifstream secFile;
					secFile.open(file);

					if(secFile.is_open()){
						secFile >> turn;
						secFile >> UserOrBot;
						secFile >> boardSize;
						//cout << turn;
						for(int i = 0; i< boardSize; i++){
							for(int j = 0; j< boardSize; j++){
								secFile >> value;
								board[i][j] = value;
							}
						}
					}
					else{
						cerr << "Error openning file." << endl;
					}

					secFile.close();
					file="empty";

					user_or_bot(UserOrBot , board , boardSize , turn);
					continue;
	
				}
			}

			/* is the move valid ? */
			if(board[row - 1][col- 97] == '.' && (row-1) <= boardSize && (col-97) < boardSize){

				board[row - 1][col- 97] = 'x';

				turn = COMP;

				/* win condition */ 
				for(a = 0; a<boardSize; a++){

					if( board[a][0] == 'x'){
						
						for(int i = 0; i<boardSize; i++){

							for(int j = 0; j<boardSize; j++){ // Resetting the buffer.

								buffer[i][j] = 0 ;
							}

							if( winCondition_x(board , buffer , boardSize , a , 0) ){

					
								printWinningBoard(boardSize , board , buffer);

								cout << "PLAYER1 HAS WON!" << endl ;
								exit(0);
							}
						}
					}
				}

				/* -------------- */ 
			}
			else{
				cerr << "Something is wrong.. I can feel it.";
				turn = USER1;
			}
		}
		else if(turn == COMP){

			turn = USER1;
			botsMove(board , boardSize);

			for(int i = 0; i<boardSize; i++){

				for(int j = 0; j<boardSize; j++){ // Resetting the buffer.

					buffer[i][j] = 0 ;
				}
			}
			/* win condition */ 
			for(b = 0; b<boardSize; b++){
				if(board[0][b] == 'o'){
					for(int i = 0; i<boardSize; i++){

						for(int j = 0; j<boardSize; j++){ // Resetting the buffer.

							buffer[i][j] = 0 ;
						}
					}

					if( winCondition_y(board , buffer , boardSize , 0 , b) ){

						printWinningBoard(boardSize , board , buffer);

						cout << "BOT HAS WON!" << endl ;
						exit(0);
					}
				}
			}

			turn = USER1;

		}
	}
}
/* My Toxic Bot */ 
void botsMove(char board[12][12] ,int boardSize){

	for(int i = 0; i<boardSize;i++){

				for( int j = 0; j<boardSize; j++){

					if(board[i][j] == 'x'){

						if(board[i][j+1] == '.' ){

							cout << endl << "Bot's move : " << static_cast<char>(j+98) << i+1 << endl;
							board[i][j+1] = 'o';

							
							return;
														
						}
						else if(board[i][j-1] == '.'){

							cout << "Bot's move : " << static_cast<char>(j+96) << i+1 << endl;
							board[i][j-1] = 'o';
							
							return;
														
						}
						else if(board[i+1][j-1] == '.'){

							cout << "Bot's move : " << static_cast<char>(j+96) << i+2 << endl;
							board[i+1][j-1] = 'o';
							
							return;
														
						}
						else if(board[i-1][j-1] == '.'){

							cout << "Bot's move : " << static_cast<char>(j+96) << i << endl;
							board[i-1][j-1] = 'o';
							
							return;
														
						}
						else if(board[i+1][j] == '.'){

							cout << "Bot's move : " << static_cast<char>(j+97) << i+2 << endl;	
							board[i+1][j] = 'o';	
							
							return;				
						}
						else{
							for(int a = 0; a<boardSize; a++){

								for(int b= 0; b<boardSize; b++){

									if(board[a][b] == '.'){

										cout << "Bot's move : " << static_cast<char>(b+97) << a+1 << endl;

										board[a][b] = 'o';
										
										return;
									}
								}
							}
						}
						
					}
				}
	}
}



