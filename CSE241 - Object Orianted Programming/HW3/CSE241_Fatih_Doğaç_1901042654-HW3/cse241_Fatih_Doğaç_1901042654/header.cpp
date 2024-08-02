#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

enum user { comp= 0 , user1 = 1, user2 = 2};
enum cellState { empty = '.' , u1 = 'x' , u2 = 'o' , cmptr = 'o'};

class Hex
{
private:

	class Cell{
	public:
		Cell(){
			state = empty;
		}
		Cell(char x){
			state = x;
		}
		Cell(int a , char b){
			row = a;
			col = b;
		}

		inline void setState(char a){ state = a;}
		inline void setRow(int a){ row = a;}
		inline void setCol(int a){ col = a + 97;}

		int row;
		char col , state;

	};
public:

	void playGame();
	void initialize_board();
	void initialize_buffer();
	void show_board();
	char getState(int , int);
	int play();
	int play(int row , int col , int &turn);
	int user_or_bot(const int &choice);
	void showWinningBoard();
	void save_game(string &file , int turn);
	void load_game(string &file , int &turn , int &UserOrBot);
	bool winCondition_x( int row , int col );
	bool winCondition_y( int row , int col );
	int getBuffer(int x, int y);
	void setBuffer(int x , int y , int value);
	void getCommand(string &command  , string &file );
	void setTurn(int i){ turn = i;}
	void setBoard(int x , int y , char state);
	int getMarkedCells();
	bool compareGames(Hex Game);
	static int count;
	int totalMarkedCells();


private:
	vector<vector<Cell> > hexCells;
	vector<vector<int> > buffer;
	int boardSize;
	int turn = 1;

};
int Hex::count = 0;

int Hex::totalMarkedCells(){
	return count;
}

int Hex::getMarkedCells(){

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
bool Hex::compareGames(Hex Game){

	if(Game.getMarkedCells() > getMarkedCells()){

		return false;
	}
	else{
		return true;
	}


}
int Hex::getBuffer(int x , int y){
	if(x < boardSize && y < boardSize && x > -1 && y > -1){

		return buffer[x][y];
	}
	else{
		return 2;
	}
}
void Hex::setBuffer(int x , int y , int value){

	vector<vector<int> > old_buffer; // Creating a second vector of vectors.

	for( int i = 0; i< boardSize; i++){

		vector<int> temp;
		
		for( int j = 0; j< boardSize; j++){	

			if(i == x && j == y){

				temp.push_back(value);
			}
			else{
				temp.push_back(getBuffer(i,j));
			}	
		} 
		old_buffer.push_back(temp);
	}
	buffer = old_buffer; // Copying the second vector of vectors to original one.

}
void Hex::setBoard(int x , int y , char state){

	hexCells[x][y].setState(state); 
}
char Hex::getState(int i , int j){

	if(i < boardSize && j < boardSize && i > -1 && j > -1){

		return hexCells[i][j].state;
	}
	else{
		return 'k';
	}
	

}
void Hex::playGame(){

	int temp , choice , row , col , turn = user1 , x = 0;
	string command , file = "empty" ;

	cout << "Size of board? : ";
	cin >> temp;

	while(temp < 5){
		cout << " Board size must be larger than 5." << endl;
		cout << " Enter again: ";
		cin >> temp;
	}

	boardSize = temp;
	initialize_board();

	cout << "User vs User (1) / Bot vs User (2) : ";
	cin >> choice;

	while(1){

		show_board();
		cout << "Player"<< turn <<  "'s turn: " ;
		getCommand(command , file);

		if(file == "empty"){

			col = command[0] ;
			row = stoi(command.substr(1)) ;

		}
		else if(command == "LOAD"){
			load_game(file , turn , choice);
			continue;
		}
		else if(command == "SAVE"){
			save_game(file,turn);
		}

			 // user vs user

		if(user_or_bot(choice) == 1){	

			if(play(row,col,turn) == 4){
				return;
			}
						
		

		}
		else if( user_or_bot(choice) == 2){ // bot vs user

			turn = user1;

			if(play(row,col,turn) == 4){
				return;
			}
			turn = user1;
			
			if(play() == 4){
				return;
			}		

		}
		else{
			//exit(0);
		}
	}
}
// Creeating vector of vectors.
void Hex::initialize_board(){

	hexCells.clear();

	for( int i = 0; i< boardSize; i++){ 
		vector<Cell> temp;

		for(int j = 0; j< boardSize; j++){

			Cell temp_cell;
			temp_cell.setState(empty);
			temp_cell.setRow(i);
			temp_cell.setCol(j);

			temp.push_back(temp_cell);
		} 
		hexCells.push_back(temp);
	}
}
void Hex::initialize_buffer(){

	buffer.clear();

	for( int i = 0; i< boardSize; i++){

		vector<int> temp;

		for( int j = 0; j< boardSize; j++){	

			temp.push_back(0);
		} 

		buffer.push_back(temp);
	}

}
void Hex::show_board(){

	cout<< endl << "  ";

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

			cout << getState(i,j) << " "; // printing the board.
		}
		cout << endl;

	}
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

		for(int i = 0; i< boardSize; i++){
			for(int j = 0; j< boardSize; j++){
				MyFile << getState(i,j) << " ";
			}
		}
	}
	else{
		cerr << "Error openning file.";
	}
	MyFile.close();
	file="empty";

}
void Hex::load_game(string &file , int &turn , int &UserOrBot){

	char value;
	int temp;

	ifstream secFile;
	secFile.open(file);

	if(secFile.is_open()){

		hexCells.clear(); 

		secFile >> temp;
		turn = temp;

		secFile >> temp;
		UserOrBot = temp;

		secFile >> boardSize;

		initialize_board();

		for(int i = 0; i< boardSize; i++){
			for(int j = 0; j< boardSize; j++){
				secFile >> value;
				
				setBoard(i, j , value);
			}
		}
	}
	else{
		cerr << "Error openning file. ";
	}
	secFile.close();

}
int Hex::play(int row , int col , int &turn){

	user USER1 = user1, USER2 = user2, COMP = comp;
	int a,b ;
	
	if( turn == USER1){

			if(getState(row-1 , col-97) == empty && (row-1) <= boardSize && (col-97) < boardSize){ // Is the move valid ?
		
				hexCells[row - 1][col- 97].setState(u1);
				count++;
				turn = USER2;

				for(a = 0; a<boardSize; a++){ // Find the start of the winning path.

			
					if( getState(a,0) == u1){

						buffer.clear();
						initialize_buffer();		

						if( winCondition_x( a , 0) ){
				
							showWinningBoard();

							cout << "PLAYER1 HAS WON!" << endl ;
							return 4;
						} 
					}
				}

			}
			else{
				cerr << "Something is wrong...I can feel it.\n";
				turn = USER1;

			}	
		}
		else if(turn == USER2){

			/* Is the move valid ?  */
			if(getState(row-1 , col-97) == empty && (row-1) <= boardSize && (col-97) < boardSize){ 

				hexCells[row - 1][col- 97].setState(u2);
				count++;
				turn = USER1;

				for(b = 0; b<boardSize; b++){
					if(getState(0 , b) == u2){

						initialize_buffer();
						
						if( winCondition_y( 0 , b) ){

							showWinningBoard();

							cout << "PLAYER2 HAS WON!" << endl ;
							return 4;
						}
					}
				}
			}
			else{
				cerr << "Something is wrong...I can feel it.\n";
				turn = USER2;
			}
			
		}
		return 1;

}
int Hex::play(){
	int a, b;

	for(int i = 0; i<boardSize;i++){

		for( int j = 0; j<boardSize; j++){

			if(getState(i,j) == u1){

				if(getState(i,j+1) == empty ){

					cout << endl << "Bot's move : " << static_cast<char>(j+98) << i+1 << endl;
					setBoard(i,j+1,cmptr);
							
					return 0;
														
				}
				else if(getState(i,j-1) == empty){

					cout << "Bot's move : " << static_cast<char>(j+96) << i+1 << endl;
					setBoard(i,j-1,cmptr);
								
					return 0;
													
				}
				else if(getState(i+1,j-1) == empty){

					cout << "Bot's move : " << static_cast<char>(j+96) << i+2 << endl;
					setBoard(i+1,j-1,cmptr);
								
					return 0;
															
				}
				else if(getState(i-1,j-1) == empty){

					cout << "Bot's move : " << static_cast<char>(j+96) << i << endl;
					setBoard(i-1,j-1,cmptr);
								
					return 0;
															
				}
				else if(getState(i+1,j) == empty){

					cout << "Bot's move : " << static_cast<char>(j+97) << i+2 << endl;	
					setBoard(i+1,j,cmptr);	
								
					return 0;				
				}
				else{
					for(int a = 0; a<boardSize; a++){

						for(int b= 0; b<boardSize; b++){

							if(getState(a,b) == empty){

								cout << "Bot's move : " << static_cast<char>(b+97) << a+1 << endl;

								setBoard(a,b,cmptr);
											
								return 0;
							}
						}
					}
				}	

			}
		}
	}
	for(b = 0; b<boardSize; b++){
		if(getState(0 , b) == u2){

			initialize_buffer();
						
			if( winCondition_y( 0 , b) ){

				showWinningBoard();
				count++;
				cout << "PLAYER2 HAS WON!" << endl ;
				return 4;
			}
		}
	}
	count++;
	return 0;
}
void Hex::getCommand(string &command  , string &file ){

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
	else if(line.length() > 3 || line.length() < 2){

		cerr << "Invalid Input "  << endl;
		cout << "Try again: ";
		getCommand(command , file);
	}

}

bool Hex::winCondition_x( int row , int col ){
	
	/* FINISH LINE */ 
	if(col == (boardSize-1) && getState(row , col) == u1){

		setBuffer(row,col,2);		
		return true;
	}

	/* Is valid? */
	if( row < 0 || row >= boardSize || col < 0 || col >= boardSize || getBuffer(row , col) == 2){
		return false;
	}
	else{

		setBuffer(row,col,2); // Keeping the places I have been to not going back through them.

		/* CHECKING ALL SIX DIRECTIONS. */ 
		if( getState(row , col+1) == u1 && getBuffer(row , col+1) != 2){

			return winCondition_x( row , col + 1);
		}

		if( getState(row-1 , col+1) == u1 && getBuffer(row-1 , col+1) != 2){

			return winCondition_x( row-1 , col + 1);
		}

		if( getState(row-1 , col) == u1 && getBuffer(row-1 , col) != 2){

			return winCondition_x( row-1 , col );
		}

		if( getState(row , col-1) == u1 && getBuffer(row , col-1) != 2){

			return winCondition_x( row , col - 1);
		}

		if( getState(row+1 , col-1) == u1 && getBuffer(row+1 , col-1) != 2){

			return winCondition_x( row+1 , col - 1);
		}

		if( getState(row+1 , col) == u1 && getBuffer(row+1 , col) != 2){

			return winCondition_x( row+1 , col);
		}
		return false;
	}
}
bool Hex::winCondition_y(int row , int col ){
	/* FINISH LINE.  */
	if(row == (boardSize-1) && getState(row , col) == u2){
		setBuffer(row,col,2);
		return true;
	}


	/* is valid ? */
	if( row < 0 || row >= boardSize || col < 0 || col >= boardSize || getBuffer(row , col) == 2){

		return false;
	}
	else{

		setBuffer(row,col,2); // Keeping the places I have been to not going back through them.

		/* CHECKING ALL SIX DIRECTIONS. */ 
		if( getState(row , col+1) == u2 && getBuffer(row , col+1) != 2){

			return winCondition_y( row , col + 1);
		}

		if( getState(row-1 , col+1) == u2 && getBuffer(row-1 , col+1) != 2){

			return winCondition_y( row-1 , col + 1);
		}

		if( getState(row-1 , col) == u2 && getBuffer(row-1 , col) != 2){

			return winCondition_y( row-1 , col );
		}

		if( getState(row , col-1) == u2 && getBuffer(row , col-1) != 2){

			return winCondition_y( row , col - 1);
		}

		if( getState(row+1 , col-1) == u2 && getBuffer(row+1 , col-1) != 2){

			return winCondition_y( row+1 , col - 1);
		}

		if( getState(row+1 , col) == u2 && getBuffer(row+1 , col) != 2){

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

			if(getBuffer(i,j) == 2){
				cout << static_cast<char>(getState(i ,j) - 32)<< " "; // printing the board with capital letters.
			}
			else{
				cout << getState(i , j) << " "; // printing the board.
			}
		}
		cout << endl;
	}

}



