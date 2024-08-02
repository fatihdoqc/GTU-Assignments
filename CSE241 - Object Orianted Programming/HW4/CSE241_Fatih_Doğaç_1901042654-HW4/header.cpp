#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "header.h"

using namespace std;

vector<vector<int> > buffer;
int Hex::count = 0;

void Hex::initialize_moves(){

	moves = new string[boardSize*boardSize]; // Number of max moves = boardsize^2 
	for(int i = 0; i< boardSize * boardSize; i++){

		moves[i] = "0"; 
	}
}
void Hex::operator--(){

	int col , row ;

	if(move_number == 0){
		cerr << "There is no more move." << endl;
	}
	else{
		col = moves[move_number - 1][0] - 97; // Taking column.
		row = stoi(moves[move_number - 1].substr(1)) - 1; // Taking row.

		hexCells[row][col].setState(empty);
		moves[move_number - 1] = "0";
		move_number--;

		if(turn == user1){ // When undo, the other user gets the turn
			score_x = score_x - 1;
			turn = user2;
		}
		else if(turn == user2){
			score_y = score_y - 1;
			turn = user1;
		}

	}
}
void Hex::operator--(int){ // same as above.

	int col , row ;

	if(move_number == 0){
		cerr << "There is no more move." << endl;
	}
	else{
		if(UserOrBot == 1){

			col = moves[move_number - 1][0] - 97;
			row = stoi(moves[move_number - 1].substr(1)) - 1;

			hexCells[row][col].setState(empty);

			moves[move_number - 1] = "0";
			move_number--;

			if(turn == user1){
				score_y = score_y - 1;
				turn = user2;
			}
			else if(turn == user2){
				score_x = score_x- 1;
				turn = user1;
			}
		}
		else{
			col = moves[move_number - 1][0] - 97;
			row = stoi(moves[move_number - 1].substr(1)) - 1;

			hexCells[row][col].setState(empty);
			moves[move_number - 1] = "0";
			move_number--;

			col = moves[move_number - 1][0] - 97;
			row = stoi(moves[move_number - 1].substr(1)) - 1;

			hexCells[row][col].setState(empty);
			moves[move_number - 1] = "0";
			move_number--;

			if(score_x != 0.0){
				score_x--;
			}
			if(score_y != 0.0){
				score_y--;
			}
		}
	}
	
	
}
int Hex::totalMarkedCells(){
	return count;
}

int Hex::getMarkedCells() const{

	int counter = 0;

	for(int i = 0; i< boardSize; i++){

		for(int j = 0; j< boardSize; j++){

			if(getState(i,j) != empty ){

				counter++;
			}
		}
	}
	return counter;
}
bool Hex::operator==(const Hex &other) const{

	if(other.getMarkedCells() > getMarkedCells()){
		return false;
	}
	else{
		return true;
	}

}
int getBuffer(int x , int y , int boardSize){
	if(x < boardSize && y < boardSize && x > -1 && y > -1){

		return buffer[x][y];
	}
	else{
		return 2;
	}
}
void Hex::setBoard(int x , int y , char state){

	hexCells[x][y].setState(state); 
}
char Hex::getState(int i , int j) const{

	if(i < boardSize && j < boardSize && i > -1 && j > -1){ // is wanted row and column valid ?

		return hexCells[i][j].getState();
	}
	else{
		return 'k';
	}
	

}
void Hex::initialize_board(){

	char x;

	// allocating memory for board.
	hexCells = new Cell* [boardSize];

	for(int i = 0; i< boardSize; i++){
		hexCells[i] = new Cell[boardSize];
	}

	// setting up the clear board.
	for( int i = 0; i< boardSize; i++){ 

		for(int j = 0; j< boardSize; j++){

			x = j+97;

			hexCells[i][j].setState(empty);
			hexCells[i][j].setRow(i);
			hexCells[i][j].setCol(x);

		} 
	}
}
void initialize_buffer(int boardSize){

	buffer.clear();

	for( int i = 0; i< boardSize; i++){

		vector<int> temp;

		for( int j = 0; j< boardSize; j++){	

			temp.push_back(0);
		} 

		buffer.push_back(temp);
	}

}
ostream& operator<<(ostream& outputStream , Hex& temp){

	outputStream<< endl << "  ";

	for(int j = 0; j<temp.boardSize; j++){

		outputStream << static_cast<char>('a' + j) << " "; // columns.	
	}

	outputStream << endl;

	for(int i = 0; i<temp.boardSize; i++){

	
		outputStream << static_cast<int>(1 + i) << " " ; // rows.

		if( i >= 9){
			for(int a = 1; a<i; a++){
				outputStream << " ";
			}
		}
		else{
			for(int a = 0; a<i; a++){

				outputStream  << " ";			// Adding spaces so the map can look like the way it should.
			}
		}

		for(int j  = 0; j<temp.boardSize; j++){

			outputStream << temp.getState(i,j) << " "; // printing the board.
		}
		if(i == 1){
			outputStream << "	X Compeleted: %" << (temp.score_x / temp.boardSize) * 100;
		}
		if(i == 2){
			outputStream << "	Y Compeleted: %" << (temp.score_y / temp.boardSize) * 100;
		}
		outputStream << endl;

	}

	return outputStream;
}
istream& operator>>(istream& inputStream , Hex& temp){

	int TEMP;
	string x;
	char a;

	inputStream >> TEMP;
	temp.turn = TEMP;

	inputStream >> TEMP;
	temp.UserOrBot = TEMP;

	inputStream >> TEMP;
	temp.boardSize = TEMP;

	inputStream >> TEMP;
	temp.move_number = TEMP;

	temp.initialize_moves();
	temp.initialize_board();

	for(int i = 0; i< temp.move_number; i++){
		inputStream >> x;
		temp.moves[i] = x;
	}
	
	for(int i = 0; i< temp.boardSize; i++){
		inputStream >> x; // columns
	}

	for(int i = 0; i< temp.boardSize; i++){
			for(int j = 0; j< temp.boardSize + 1; j++){

				if(j == 0){
					inputStream >> x;
				}
				else{
					inputStream >> a;
					temp.setBoard(i, j-1 , a);
				}
			}
		}

	return inputStream;

}
int Hex::user_or_bot(const int &choice ){

	switch(choice){
		case 1: //user vs user
			return 1;
		case 2: // bot vs user
			return 2;
		default:
			cout << "Invalid input";
			return 0;

	}
}
void Hex::save_game(string &file, int turn){

	ofstream MyFile;
	MyFile.open(file);

	if(MyFile.is_open()){
		MyFile << turn << " ";
		MyFile << 1 << " ";
		MyFile << boardSize << " ";
		MyFile << move_number << " ";

		for(int i = 0; i< move_number; i++){
			MyFile << moves[i] << " ";
		}

		MyFile << (*this); // printing board.
	}
	else{
		cerr << "Error openning file.";
	}
	MyFile.close();
	file="empty";
	


}
int Hex::playGame(){

	int temp , row , col , turn = user1 , x = 0;
	string command , file = "empty" ;
	Cell temp_cell;

	cout << "Size of board? : ";
	cin >> temp;

	while(temp < 5 || temp >= 30){
		cout << " Board size must be larger than 5." << endl;
		cout << " Enter again: ";
		cin >> temp;
	}

	boardSize = temp;
	
	initialize_board();
	initialize_moves();
	initialize_buffer(boardSize);
	
	cout << "User vs User (1) / Bot vs User (2) : ";
	cin >> temp;
	UserOrBot = temp;

	while(1){

		cout << (*this);
		cout << "Player"<< this->turn <<  "'s turn: " ;
		getCommand(command , file);

		if(file == "empty"){

			if(command == "UNDO"){

				(*this)--;
				continue;
			}
			else if(command == "EXIT"){
				return 0;
			}
			else{
				moves[move_number] = command;
				move_number++;

				temp_cell.setCol(command[0]);
				temp_cell.setRow( stoi(command.substr(1)) );
			}

		}
		else if(command == "LOAD"){
			ifstream secFile;
			secFile.open(file);

			secFile >> (*this);

			secFile.close();
			continue;
		}
		else if(command == "SAVE"){
			save_game(file,turn);
			continue;

		}

		// user vs user
		if(user_or_bot(UserOrBot) == 1){	

			if(play(temp_cell) == 4){
				return 0;
			}
		}
		else if( user_or_bot(UserOrBot) == 2){ // bot vs user

			this->turn = user1;

			if(play(temp_cell) == 4){
				return 0 ;
			}
			this->turn = user1;
			
			Cell temp = play();

			string n;
			n = temp.getCol();
			n += to_string(temp.getRow() + 1 );

			moves[move_number] = n;
			move_number++;
			
			hexCells[temp.getRow()][temp.getCol()-97] = temp;

			for(int b = 0; b<boardSize; b++){
				if(getState(0 , b) == u2){

				initialize_buffer(boardSize);
						
				if( winCondition_y( 0 , b) ){

					show_score_y(0,b);
					showWinningBoard();
					count++;
					cout << "PLAYER2 HAS WON!" << endl ;
					return 0;
				}
			}
			show_score_y(0,b);
	}		

		}
	}
}
int Hex::play(Cell &temp_cell){

	int a,b , row ;
	char col;
	row = temp_cell.getRow();
	col = temp_cell.getCol();
	
	if( this->turn == user1){

			if(getState(row-1 , col-97) == empty && (row-1) <= boardSize && (col-97) < boardSize){ // Is the move valid ?
		
				hexCells[row - 1][col- 97].setState(u1);
				count++;
				this->turn = user2;

				for(a = 0; a<boardSize; a++){ // Find the start of the winning path.

					if( getState(a,0) == u1){

						buffer.clear();
						initialize_buffer(boardSize);		

						if( winCondition_x( a , 0) ){

							show_score_x(a,0);
							showWinningBoard();

							cout << "PLAYER1 HAS WON!" << endl ;
							return 4;
						} 
						show_score_x(a,0);
					}
				}
			}
			else{
				cerr << "Bad Input.\n";
				this->turn = user1;

			}	
		}
		else if(this->turn == user2){

			/* Is the move valid ?  */
			if(getState(row-1 , col-97) == empty && (row-1) <= boardSize && (col-97) < boardSize){ 

				hexCells[row - 1][col- 97].setState(u2);
				count++;
				this->turn = user1;

				initialize_buffer(boardSize);

				for(b = 0; b<boardSize; b++){
					if(getState(0 , b) == u2){
						
						if( winCondition_y( 0 , b) ){

							show_score_y(0,b);
							showWinningBoard();

							cout << "PLAYER2 HAS WON!" << endl ;
							return 4;
						}
						show_score_y(0,b);
					}
				}
			}
			else{
				cerr << "Bad Input.\n";
				this->turn = user2;
			}
			
		}
		return 1;

}
Hex::Cell Hex::play(){
	int a, b;
	Cell temp;

	for(int i = 0; i<boardSize;i++){

		for( int j = 0; j<boardSize; j++){

			if(getState(i,j) == u1){

				if(getState(i,j+1) == empty ){

					cout << endl << "Bot's move : " << static_cast<char>(j+98) << i+1 << endl;
					temp.setRow(i);
					temp.setCol(j+98);
					temp.setState(cmptr);
					return temp;
														
				}
				else if(getState(i,j-1) == empty){

					cout << "Bot's move : " << static_cast<char>(j+96) << i+1 << endl;
					temp.setRow(i);
					temp.setCol(j+96);
					temp.setState(cmptr);	
					return temp;
													
				}
				else if(getState(i+1,j-1) == empty){

					cout << "Bot's move : " << static_cast<char>(j+96) << i+2 << endl;
					temp.setRow(i+1);
					temp.setCol(j+96);
					temp.setState(cmptr);			
					return temp;
															
				}
				else if(getState(i-1,j-1) == empty){

					cout << "Bot's move : " << static_cast<char>(j+96) << i << endl;
					temp.setRow(i-1);
					temp.setCol(j+96);
					temp.setState(cmptr);			
					return temp;
															
				}
				else if(getState(i+1,j) == empty){

					cout << "Bot's move : " << static_cast<char>(j+97) << i+2 << endl;		
					temp.setRow(i+1);
					temp.setCol(j+97);
					temp.setState(cmptr);		
					return temp;				
				}
				else{
					for(int a = 0; a<boardSize; a++){

						for(int b= 0; b<boardSize; b++){

							if(getState(a,b) == empty){

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
	}
	count++;
	return temp;
}
void Hex::getCommand(string &command  , string &file ) const{

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
	else if(line.find("UNDO") != -1 ){
		// catching error.
	}
	else if(line.find("EXIT") != -1){
		command = line;
	}
	else if(line.length() > 3 || line.length() < 2 ){

		cerr << "Invalid Input "  << endl;
		cout << "Try again: ";
		getCommand(command , file);
	}

}
void Hex::show_score_x(int row, int col){

	if(col == boardSize-1 && buffer[row][col] == 2){
		score_x = boardSize;
		
		return;
	}

	if( row < 0 || row >= boardSize || col < 0 || col >= boardSize || getBuffer(row, col , boardSize) == 3){
		
		return;
	}
	else{
		this->score_x = col+1;
		buffer[row][col] = 3; // Keeping the places I have been to not going back through them.

		/* CHECKING ALL SIX DIRECTIONS. */ 
		if( getBuffer(row , col+1 , boardSize) != 3 && getBuffer(row , col+1 , boardSize) == 2){
			show_score_x( row , col + 1);
		}

		if( getBuffer(row-1 , col+1 , boardSize) != 3 && getBuffer(row-1 , col+1 , boardSize) == 2){
			show_score_x( row-1 , col + 1);
		}

		if( getBuffer(row-1 , col , boardSize) != 3 && getBuffer(row-1 , col , boardSize) == 2){
			
			show_score_x( row-1 , col );
		}

		if( getBuffer(row , col-1 , boardSize) != 3 && getBuffer(row , col-1 , boardSize) == 2){
			show_score_x( row , col - 1);
		}

		if( getBuffer(row+1 , col-1 , boardSize) != 3 && getBuffer(row+1 , col-1 , boardSize) == 2){
			show_score_x( row+1 , col - 1);
		}

		if( getBuffer(row+1 , col , boardSize) != 3 && getBuffer(row+1 , col , boardSize) == 2){
			show_score_x( row+1 , col);
		}
		return;
	}


}
void Hex::show_score_y(int row, int col){

	if(row == boardSize-1 && buffer[row][col] == 2){
		score_y = boardSize;
		
		return;
	}

	if( row < 0 || row >= boardSize || col < 0 || col >= boardSize || getBuffer(row, col , boardSize) == 3){
		
		return;
	}
	else if(buffer[row][col] == 2){

		this->score_y = row+1;
		buffer[row][col] = 3; // Keeping the places I have been to not going back through them.

		/* CHECKING ALL SIX DIRECTIONS. */ 
		if( getBuffer(row , col+1 , boardSize) != 3 && getBuffer(row , col+1 , boardSize) == 2){
			show_score_y( row , col + 1);
		}

		if( getBuffer(row-1 , col+1 , boardSize) != 3 && getBuffer(row-1 , col+1 , boardSize) == 2){
			show_score_y( row-1 , col + 1);
		}

		if( getBuffer(row-1 , col , boardSize) != 3 && getBuffer(row-1 , col , boardSize) == 2){
			
			show_score_y( row-1 , col );
		}

		if( getBuffer(row , col-1 , boardSize) != 3 && getBuffer(row , col-1 , boardSize) == 2){
			show_score_y( row , col - 1);
		}

		if( getBuffer(row+1 , col-1 , boardSize) != 3 && getBuffer(row+1 , col-1 , boardSize) == 2){
			show_score_y( row+1 , col - 1);
		}

		if( getBuffer(row+1 , col , boardSize) != 3 && getBuffer(row+1 , col , boardSize) == 2){
			show_score_y( row+1 , col);
		}
		return;
	}


}
bool Hex::winCondition_x( int row , int col ){
	
	/* FINISH LINE */ 
	if(col == (boardSize-1) && getState(row , col) == u1){

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
		if( getState(row , col+1) == u1 && getBuffer(row , col+1 , boardSize) != 2){

			return winCondition_x( row , col + 1);
		}

		if( getState(row-1 , col+1) == u1 && getBuffer(row-1 , col+1 , boardSize) != 2){

			return winCondition_x( row-1 , col + 1);
		}

		if( getState(row-1 , col) == u1 && getBuffer(row-1 , col , boardSize) != 2){

			return winCondition_x( row-1 , col );
		}

		if( getState(row , col-1) == u1 && getBuffer(row , col-1 , boardSize) != 2){

			return winCondition_x( row , col - 1);
		}

		if( getState(row+1 , col-1) == u1 && getBuffer(row+1 , col-1 , boardSize) != 2){

			return winCondition_x( row+1 , col - 1);
		}

		if( getState(row+1 , col) == u1 && getBuffer(row+1 , col , boardSize) != 2){

			return winCondition_x( row+1 , col);
		}
		return false;
	}
}
bool Hex::winCondition_y(int row , int col ){
	/* FINISH LINE.  */
	if(row == (boardSize-1) && getState(row , col) == u2){
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
		if( getState(row , col+1) == u2 && getBuffer(row , col+1 , boardSize) != 2){

			return winCondition_y( row , col + 1);
		}

		if( getState(row-1 , col+1) == u2 && getBuffer(row-1 , col+1 , boardSize) != 2){

			return winCondition_y( row-1 , col + 1);
		}

		if( getState(row-1 , col) == u2 && getBuffer(row-1 , col , boardSize) != 2){

			return winCondition_y( row-1 , col );
		}

		if( getState(row , col-1) == u2 && getBuffer(row , col-1 , boardSize) != 2){

			return winCondition_y( row , col - 1);
		}

		if( getState(row+1 , col-1) == u2 && getBuffer(row+1 , col-1 , boardSize) != 2){

			return winCondition_y( row+1 , col - 1);
		}

		if( getState(row+1 , col) == u2 && getBuffer(row+1 , col , boardSize) != 2){

			return winCondition_y( row+1 , col);
		}


		return false;
	}
}
void Hex::showWinningBoard(){

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
				cout << static_cast<char>(getState(i ,j) - 32)<< " "; // printing the board with capital letters.
			}
			else{
				cout << getState(i , j) << " "; // printing the board.
			}
		}
		if(i == 1){
			cout << "	X Compeleted: %" << (this->score_x / this->boardSize) * 100;
		}
		if(i == 2){
			cout << "	Y Compeleted: %" << (this->score_y / this->boardSize) * 100;
		}
		cout << endl;
	}

}



