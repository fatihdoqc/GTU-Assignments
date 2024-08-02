#ifndef header
#define header

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
using namespace std;

enum user { comp , user1, user2};
enum cellState { empty = '.' , u1 = 'x' , u2 = 'o' , cmptr = 'o'};

class Hex
{
public:

	Hex() : hexCells(nullptr) , moves(nullptr){/* intentionally empty */ }

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
		inline void setCol(char a){ col = a;}
		int getRow() const {return row;}
		char getCol() const {return col;}
		char getState() const {return state;}

	private:
		int row;
		char col , state;

	};

	~Hex(){ // destructure

		if(hexCells != nullptr){
			for(int i = 0; i< boardSize; i++){
				delete[] hexCells[i];
			}
			delete[] hexCells;
		}

		if(moves != nullptr){
			delete[] moves;
		}
	}
	Hex(const Hex &other) : Hex(){

		(*this) = other;
	}
	explicit Hex(int a) : Hex() {

		boardSize = a;
	}

	const Hex& operator=(const Hex &other){

		if(this != &other){

			if(hexCells != nullptr){
				for(int i = 0; i< boardSize; i++){
					delete[] hexCells[i];
				}
				delete[] hexCells;
			}

			if(moves != nullptr){
				delete[] moves;
			}

			boardSize = other.boardSize;
			turn = other.turn;
			move_number = other.move_number;
			UserOrBot = other.UserOrBot;
			score_x = other.score_x;
			score_y = other.score_y;

			hexCells = new Cell*[boardSize];
			moves = new string[boardSize*boardSize];

			for(int i = 0; i< boardSize; i++){
				hexCells[i] = new Cell[boardSize];

				for(int j = 0; j<boardSize; j++){
					hexCells[i][j] = other.hexCells[i][j] ;
				}
			}

			for(int i = 0; i< move_number; i++){
				moves[i] = other.moves[i];
			}	
		}
		return *this;
	}

	int playGame();
	void initialize_board();
	char getState(int , int) const;
	Cell play();
	int play(Cell &temp_cell);
	int user_or_bot(const int &choice);
	void showWinningBoard();
	void save_game(string &file , int turn);
	bool winCondition_x( int row , int col );
	bool winCondition_y( int row , int col );
	void getCommand(string &command  , string &file ) const;
	void setTurn(int i){ turn = i;}
	void setBoard(int x , int y , char state);
	int getMarkedCells() const;
	bool operator==(const Hex &other) const;
	static int count;
	int totalMarkedCells();
	void initialize_moves();
	void operator--();
	void operator--(int);
	friend ostream& operator<<(ostream& , Hex&);
	friend istream& operator>>(istream& inputStream , Hex& temp);
	void show_score_x(int , int);
	void show_score_y(int , int);

private:
	Cell **hexCells;
	int boardSize;
	int turn = 1;
	string *moves;
	int move_number = 0;
	int UserOrBot;
	float score_x = 0 ,score_y = 0;

};

int getBuffer(int x , int y);


#endif