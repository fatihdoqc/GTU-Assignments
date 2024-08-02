#ifndef ABSTRACTHEX
#define ABSTRACTHEX

#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace MyHexGame{
	enum user { comp , user1, user2};
	enum cellState { empty = '.' , u1 = 'x' , u2 = 'o' , cmptr = 'o'};

	class AbstractHex
	{
		public:

		AbstractHex(){/* intentionally empty */ }

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

		virtual void print() = 0;
		virtual void reset() = 0;
		virtual int playGame()=0;
		virtual char operator()(int i , int j) = 0;
		virtual bool setSize(int size) = 0;
		virtual int play(Cell &temp_cell) = 0;
		virtual AbstractHex::Cell play() = 0;
		virtual bool isEnd(int row , int col , char state) = 0;
		virtual void showWinningBoard() = 0;
		virtual void writeToFile(string &file, int turn) = 0;
		virtual void readFromFile(string &file , int &turn , int &UserOrBot) = 0;
		void Reset_Buffer();
		int user_or_bot(const int &choice );
		void getCommand(string &command  , string &file );
		int getBuffer(int x , int y , int boardSize);
		string lastMove();
		int numberOfMoves();
		int getBoardSize();
		bool operator==(AbstractHex &a1);

	protected:

		vector<vector<int> > buffer;
		vector<string> moves;
		int boardSize = 5;
		int turn = 1;
		int move_number = 0;
		int UserOrBot = 1;

	};


}
#endif