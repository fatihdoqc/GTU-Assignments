#ifndef HEXARRAY1D
#define HEXARRAY1D

#include <iostream>
#include <string>
#include <vector>
#include "AbstractHex.h"
using namespace std;

	namespace MyHexGame{
	class HexArray1D : public AbstractHex{
	public:

		HexArray1D() : hexCells(nullptr){/* intentionally empty */}

		~HexArray1D(){
			if(hexCells != nullptr){
				delete[] hexCells;
			}
		}
		HexArray1D(const HexArray1D &other) : HexArray1D(){ // copy constructor.

			(*this) = other;
		}
		const HexArray1D& operator=(const HexArray1D &other){ // copying the game to the another game.

			if(this != &other && other.hexCells != nullptr){

				if(hexCells != nullptr){ 
					delete[] hexCells;
				}

				moves.clear();

				boardSize = other.boardSize;
				this->turn = other.turn;
				move_number = other.move_number;
				UserOrBot = other.UserOrBot;

				hexCells = new Cell[boardSize*boardSize];

				for(int i = 0; i<boardSize*boardSize; i++){

					hexCells[i].setState( other.hexCells[i].getState() );
					hexCells[i].setRow( other.hexCells[i].getRow() );
					hexCells[i].setCol( other.hexCells[i].getCol() );
				}

				moves.resize(move_number);

				for(int i = 0 ; i<move_number; i++){
					moves[i] = other.moves[i];
				}
			}
			return *this;
		}

		void print()override;
		void reset()override;
		int playGame()override;
		char operator()(int i , int j)override;
		void setState(int i , int j, char state);
		bool setSize(int size)override;
		int play(Cell &temp_cell)override;
		bool isEnd(int row , int col , char state)override;
		void showWinningBoard()override;
		AbstractHex::Cell play()override;
		void writeToFile(string &file, int turn)override;
		void readFromFile(string &file , int &turn , int &UserOrBot)override;



	private:
		Cell *hexCells;
	};
}
#endif