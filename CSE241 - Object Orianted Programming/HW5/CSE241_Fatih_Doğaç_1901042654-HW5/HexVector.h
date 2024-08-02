#ifndef HEXVECTOR
#define HEXVECTOR

#include <iostream>
#include <string>
#include <vector>
#include "AbstractHex.h"
using namespace std;

namespace MyHexGame{

	class HexVector : public AbstractHex{
	public:
		void print()override;
		void reset()override;
		int playGame() override;
		bool setSize(int size)override;
		int play(Cell &temp_cell)override;
		AbstractHex::Cell play()override;
		char operator()(int i , int j)override;
		bool isEnd(int row , int col , char state)override;
		void showWinningBoard()override;
		void writeToFile(string &file, int turn)override;
		void readFromFile(string &file , int &turn , int &UserOrBot)override;


	private:
		vector<vector<Cell> > hexCells;
	};
}
#endif