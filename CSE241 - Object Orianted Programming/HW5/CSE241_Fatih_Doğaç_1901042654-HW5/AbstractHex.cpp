#include <iostream>
#include <string>
#include <vector>
#include "AbstractHex.h"
#include "MyExceptions.h"

using namespace std;
using namespace MyHexGame;

int AbstractHex::getBuffer(int x , int y , int boardSize){
	if(x < boardSize && y < boardSize && x > -1 && y > -1){ // checking if the wanted index is valid ?

		return buffer[x][y];
	}
	else{
		return 9;
	}
}
void AbstractHex::Reset_Buffer(){
	buffer.clear();

	for( int i = 0; i< boardSize; i++){

		vector<int> temp;

		for( int j = 0; j< boardSize; j++){	

			temp.push_back(0); // 0 means clear. So I am filling buffer with zeros.
		} 

		buffer.push_back(temp);
	}
}
int AbstractHex::user_or_bot(const int &choice ){

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
void AbstractHex::getCommand(string &command  , string &file ){

	string line;
	int length , i = 0;

	getline(cin>>ws , line);

	command = line;
	file = "empty";

	if(line.find("SAVE") != -1){

		length = line.find(" "); 

		command = line.substr(0 , length); // Taking the command which is the part of the string until the space.
		file = line.substr(length+1) ; // The rest is file name.

	}
	else if(line.find("LOAD") != -1){
		length = line.find(" ");

		command = line.substr(0 , length);
		file = line.substr(length+1) ;
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
string AbstractHex::lastMove(){

	if(moves.size() != 0){
		return moves[moves.size()-1];
	}
	else{
		throw "There isn't any move yet.\n";
	}
	
	return "There isn't any move yet.\n";
}
int AbstractHex::numberOfMoves(){
	return move_number;
}
int AbstractHex::getBoardSize(){
	return boardSize;
}
bool AbstractHex::operator==(AbstractHex &a1){

	if(a1.getBoardSize() != this->getBoardSize() ) { // If the board size's are different , they are different.
		return false;
	}

	for(int i = 0; i<a1.getBoardSize(); i++){

		for(int j = 0; j< this->getBoardSize(); j++){

			if(a1(i,j) != (*this)(i,j)){ // Same chars must be at the same indexes.
				return false;
			}
		}
	}
				
	return true;
}		