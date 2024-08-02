#include <iostream>
#include <string>
#include <vector>
#include "AbstractHex.h"
#include "HexArray1D.h"
#include <fstream>
#include "MyExceptions.h"

using namespace std;
using namespace MyHexGame;

void HexArray1D::reset(){

	int row = 0;

	if(hexCells == nullptr){
		hexCells = new Cell[boardSize*boardSize];
	}

	for( int i = 0; i< boardSize*boardSize; i++){

		if(i != 0 && i % boardSize == 0){
			row++;
		}

		hexCells[i].setState(empty);
		hexCells[i].setRow(row);
		hexCells[i].setCol(i);
	}
}
void HexArray1D::print(){

	int index = 0;

	cout << endl << "  ";

	for(int j = 0; j<boardSize; j++){

		cout << static_cast<char>('a' + j) << " "; // columns.	
	}

	cout << endl;

	for(int i = 0; i<boardSize; i++){

	
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

		for(int j  = 0; j<boardSize; j++){

			cout << hexCells[index].getState() << " "; // printing the board.
			index++;
		}
		cout << endl;

	}
}
bool HexArray1D::setSize(int size){

	if(size >= 6 && size < 30){
		boardSize = size;
		reset();
		return true;
	}
	else{
		cerr << "Board size must be greater than 4 and lesser than 30. Try again: ";
		return false;
	}
}
char HexArray1D::operator()(int i , int j){

	if(i < boardSize+1 && j < boardSize+1 && i > -1 && j > -1){ // is wanted row and column valid ?

		return hexCells[(i*boardSize) + j].getState();
	}
	else{
		throw MyExceptions();
	}
}
void HexArray1D::setState(int i , int j , char state){
	if(i < boardSize+1 && j < boardSize+1 && i > -1 && j > -1){ // is wanted row and column valid ?

		hexCells[(i*boardSize) + j].setState(state);
	}
}
int HexArray1D::playGame(){

	int temp , row , col , turn = user1 , x = 0;
	string command , file = "empty" ;
	Cell temp_cell;

	cout << "Size of board? : ";
	while(1){
		cin >> temp;
		if(setSize(temp)){
			break;
		}
	}

	cout << "User vs User (1) / Bot vs User (2) : ";
	while(1){
		cin >> temp;

		if(temp == 1 || temp == 2){
			UserOrBot = temp;
			break;
		}
		else{
			cerr << "Bad Input. Enter again: ";
		}
	}

	while(1){

		print();
		cout << "Player"<< this->turn <<  "'s turn: " ;
		getCommand(command , file);

		if(file == "empty"){

			if(command == "EXIT"){
				return 0;
			}
			else{

				temp_cell.setCol(command[0]); // initializing the temporary cell.
				temp_cell.setRow( stoi(command.substr(1)) );
			}

		}
		else if(command == "LOAD"){
			readFromFile(file,turn,UserOrBot);
			continue;
		}
		else if(command == "SAVE"){
			writeToFile(file,turn);
			continue;

		}

		// user vs user
		if(user_or_bot(UserOrBot) == 1){	 // human vs human

			if(play(temp_cell) == 4){
				return 0;
			}
		}
		else if( user_or_bot(UserOrBot) == 2){ // bot vs user

			this->turn = user1;
			int tempp;

			tempp = play(temp_cell);

			if(tempp == 4){
				return 0 ;
			}
			if(tempp == 5){
				continue;
			}
			this->turn = user1;
			
			Cell temp = play();

			string n; // Memorized the move.
			n = temp.getCol();
			n += to_string(temp.getRow() + 1 );

			moves.push_back(n);
			move_number++;
			
			hexCells[temp.getRow() * boardSize + temp.getCol()-97] = temp; // played the move.

			for(int b = 0; b<boardSize; b++){ // beginning of the winning path.
				if((*this)(0 , b) == u2){

					Reset_Buffer();
							
					if( isEnd( 0 , b , u2) ){

						showWinningBoard();
						
						cout << "PLAYER2 HAS WON!" << endl ;
						return 0;
					}
				}
			}		
		}
	}
}
int HexArray1D::play(Cell &temp_cell){

	int a,b , row ;
	char col;
	row = temp_cell.getRow(); 
	col = temp_cell.getCol(); 
	
	try{
		if( this->turn == user1){

				if((*this)(row-1 , col-97) == empty && (row-1) <= boardSize && (col-97) < boardSize){ // Is the move valid ?

					string x = col + to_string(row); // Memorized the move
					moves.push_back(x);
					move_number++;
			
					setState(row - 1 , col -97 , u1);
					this->turn = user2;

					for(a = 0; a<boardSize; a++){ // Find the start of the winning path.

						if( (*this)(a,0) == u1){

							Reset_Buffer();		

							if( isEnd( a , 0 , u1) ){

								showWinningBoard();

								cout << "PLAYER1 HAS WON!" << endl ;
								return 4;
							} 
						}
					}
				}
				else{
					cerr << "Bad Input.\n";
					this->turn = user1;
					return 5;
				}	
			}
		else if(this->turn == user2){

			/* Is the move valid ?  */
			if((*this)(row-1 , col-97) == empty && (row-1) <= boardSize && (col-97) < boardSize){ 

				string x = col + to_string(row); // Memorized the move.
				moves.push_back(x);
				move_number++;

				setState(row-1, col -97 ,u2);
				this->turn = user1;

				Reset_Buffer();

				for(b = 0; b<boardSize; b++){ // Beginning of the winning path.

					if((*this)(0 , b) == u2){
							
						if( isEnd( 0 , b , u2) ){

							showWinningBoard();

							cout << "PLAYER2 HAS WON!" << endl ;
							return 4;
						}
					}
				}
			}
			else{
				cerr << "Bad Input.\n";
				this->turn = user2;
			}
				
		}
	}catch(MyExceptions &e){
		e.showErr();
	}
	return 1;
}
AbstractHex::Cell HexArray1D::play(){
	int a, b;
	Cell temp;

	try{
		for(int i = 1; i<boardSize;i++){

			for( int j = 1; j<boardSize; j++){

				if((*this)(i,j) == u1){ // Searching a x to put the bot's move next to it.

					if((*this)(i,j+1) == empty ){

						cout << endl << "Bot's move : " << static_cast<char>(j+98) << i+1 << endl;
						temp.setRow(i);
						temp.setCol(j+98);
						temp.setState(cmptr);
						return temp;
															
					}
					else if((*this)(i+1,j-1) == empty){

						cout << "Bot's move : " << static_cast<char>(j+96) << i+2 << endl;
						temp.setRow(i+1);
						temp.setCol(j+96);
						temp.setState(cmptr);			
						return temp;
																
					}
					else if(i != 0 && j != 0){

						if((*this)(i-1,j-1) == empty){

							cout << "Bot's move : " << static_cast<char>(j+96) << i << endl;
							temp.setRow(i-1);
							temp.setCol(j+96);
							temp.setState(cmptr);			
							return temp;
						}
						else if((*this)(i,j-1) == empty){

						cout << "Bot's move : " << static_cast<char>(j+96) << i+1 << endl;
						temp.setRow(i);
						temp.setCol(j+96);
						temp.setState(cmptr);	
						return temp;
														
					}
																
					}
					else if((*this)(i+1,j) == empty){

						cout << "Bot's move : " << static_cast<char>(j+97) << i+2 << endl;		
						temp.setRow(i+1);
						temp.setCol(j+97);
						temp.setState(cmptr);		
						return temp;				
					}
				}
				else{ // If there isn't any 'x' , putting 'o' the the first empty place at the board.
					for(int a = 0; a<boardSize; a++){

						for(int b= 0; b<boardSize; b++){

							if((*this)(a,b) == empty){

								cout << "Bot's move : " << static_cast<char>(b+97) << a+1 << endl;
								temp.setRow(a);
								temp.setCol(b+97);
								temp.setState(cmptr);		
												
								return temp;
							}
						}
					}
				}	

				
			}
		}
	}catch(MyExceptions &e){

	}
	return temp;
}
bool HexArray1D::isEnd(int row , int col , char state){
	try{
		if(state== u1){
			/* FINISH LINE */ 
			if(col == (boardSize-1) && (*this)(row , col) == u1){

				buffer[row][col] = 2;		
				return true;
			}

			/* Is valid? */
			if( row < 0 || row >= boardSize || col < 0 || col >= boardSize || getBuffer(row , col , boardSize) == 2){
				return false;
			}
			else{

				buffer[row][col] = 2; // Keeping the places I have been to not going back through them.

				/* CHECKING ALL SIX DIRECTIONS. */ 
				if( (*this)(row , col+1) == u1 && getBuffer(row , col+1 , boardSize) != 2){

					return isEnd( row , col + 1 , u1);
				}

				if( (*this)(row-1 , col+1) == u1 && getBuffer(row-1 , col+1 , boardSize) != 2){

					return isEnd( row-1 , col + 1 , u1);
				}

				if( (*this)(row-1 , col) == u1 && getBuffer(row-1 , col , boardSize) != 2){

					return isEnd( row-1 , col  , u1);
				}

				if( (*this)(row , col-1) == u1 && getBuffer(row , col-1 , boardSize) != 2){

					return isEnd( row , col - 1 , u1);
				}

				if( (*this)(row+1 , col-1) == u1 && getBuffer(row+1 , col-1 , boardSize) != 2){

					return isEnd( row+1 , col - 1 , u1);
				}

				if( (*this)(row+1 , col) == u1 && getBuffer(row+1 , col , boardSize) != 2){

					return isEnd( row+1 , col , u1);
				}
			}
		}
		else if(state == u2){
			/* FINISH LINE.  */
			if(row == (boardSize-1) && (*this)(row , col) == u2){
				buffer[row][col] = 2;
				return true;
			}


			/* is valid ? */
			if( row < 0 || row >= boardSize || col < 0 || col >= boardSize || getBuffer(row , col , boardSize) == 2){

				return false;
			}
			else{

				buffer[row][col] = 2; // Keeping the places I have been to not going back through them.

				/* CHECKING ALL SIX DIRECTIONS. */ 
				if( (*this)(row , col+1) == u2 && getBuffer(row , col+1 , boardSize) != 2){

					return isEnd( row , col + 1 , u2);
				}

				if( (*this)(row-1 , col+1) == u2 && getBuffer(row-1 , col+1 , boardSize) != 2){

					return isEnd( row-1 , col + 1 , u2);
				}

				if( (*this)(row-1 , col) == u2 && getBuffer(row-1 , col , boardSize) != 2){

					return isEnd( row-1 , col , u2 );
				}

				if( (*this)(row , col-1) == u2 && getBuffer(row , col-1 , boardSize) != 2){

					return isEnd( row , col - 1 , u2);
				}

				if( (*this)(row+1 , col-1) == u2 && getBuffer(row+1 , col-1 , boardSize) != 2){

					return isEnd( row+1 , col - 1 , u2);
				}

				if( (*this)(row+1 , col) == u2 && getBuffer(row+1 , col , boardSize) != 2){

					return isEnd( row+1 , col , u2);
				}
			}
		}
	}catch(MyExceptions &e){
		/* just handled the exceptions */
	}
	return false;
}
void HexArray1D::showWinningBoard(){

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

			if(getBuffer(i,j,boardSize) == 3 || getBuffer(i,j,boardSize) == 2 ){
				cout << static_cast<char>((*this)(i ,j) - 32)<< " "; // printing the board with capital letters.
			}
			else{
				cout << (*this)(i , j) << " "; // printing the board.
			}
		}
		cout << endl;
	}
}
void HexArray1D::writeToFile(string &file, int turn){

	ofstream MyFile;
	MyFile.open(file);

	if(MyFile.is_open()){
		MyFile << this->turn << " ";
		MyFile << UserOrBot << " ";
		MyFile << boardSize << " ";
		MyFile << move_number << " ";

		for(int i = 0; i< moves.size(); i++){
			MyFile << moves[i] << " ";
		}
	}
	else{
		cerr << "Error openning file.";
	}
	MyFile.close();
	file="empty";

}
void HexArray1D::readFromFile(string &file , int &turn , int &UserOrBot){

	char value;
	string a;
	int temp;

	ifstream secFile;
	secFile.open(file);

	if(secFile.is_open()){

		moves.clear();

		secFile >> temp;
		(*this).turn = temp;

		secFile >> temp;
		UserOrBot = temp;

		secFile >> boardSize;
		secFile >> move_number;

		moves.resize(move_number);

		hexCells = nullptr; // To initialize the board, it must be deleted first. -Ghandi Doğaç 1901042654
		reset();

		for(int i = 0; i< moves.size(); i++){

			secFile >> a;
		
			
			string str;
			str = a.substr(1);

			if( a[0] - 97 < boardSize && stoi(str)-1 < boardSize && a[0] - 97 > -1 && stoi(str)-1 > -1){ // is the move valid.
				if(i%2 != 0){
					moves[i] = a;
					setState( stoi(str)-1 , a[0] - 97 , u2); // user2 's move.
				}
				else{
					moves[i] = a;
					setState( stoi(str)-1 , a[0] - 97 , u1); // user1 's move.
				}
			}
		}
	}
	else{
		cerr << "Error openning file. ";
	}
	secFile.close();
}