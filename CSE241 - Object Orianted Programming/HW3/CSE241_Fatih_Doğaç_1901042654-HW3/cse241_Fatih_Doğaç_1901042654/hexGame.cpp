#include <iostream>
#include "header.h"
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;


int main(){

	Hex a,b,c,d,e;
	cout << "GAME A "<< endl;
	a.playGame();
	cout << "GAME B "<< endl;
	b.playGame();
	cout << "GAME C "<< endl;
	c.playGame();
	cout << "GAME D "<< endl;
	d.playGame();
	cout << "GAME E "<< endl;
	e.playGame();

	cout << "Compare games, A and B : "<< endl;
	if(a.compareGames(b) == true){
		cout << " B has less marked cells than A" << endl;
	}
	else{
		cout << " A has less marked cells than B" << endl;
	}

	cout << endl << " Total moves : " << e.totalMarkedCells();



	return 0;
}