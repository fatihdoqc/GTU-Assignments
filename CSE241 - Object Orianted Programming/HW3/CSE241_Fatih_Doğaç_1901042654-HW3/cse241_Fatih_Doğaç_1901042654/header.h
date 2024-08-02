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

#endif