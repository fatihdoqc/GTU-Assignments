#include <iostream>
#include <string>
#include "AbstractHex.h"
#include "HexVector.h"
#include "HexArray1D.h"
#include "HexAdapter.h"
#include "HexAdapter.cpp"
#include <deque>

using namespace std;

bool check(AbstractHex *arr[] , int size);

int main(){

	int temp , x , size = 0;
	cout << "Welcome.\n";
	

	MyHexGame::AbstractHex *a , *b , *c , *d ;
	MyHexGame::AbstractHex *arr[10];



	while(temp != 5){

		cout << "Which gamemode you want to play?\n";
		cout << "1) HexVector\n2) HexArray1D\n3) HexAdapter<vector>\n" 
		<< "4) HexAdapter<deque>\n5) Exit\nChoice : ";

		cin >> temp;

		if(temp > 5 || temp < 1){
			if(temp == 5){
				return 0;
			}

			cerr << "Invalid choice.\n Try again: ";
			continue;
		}
	
		switch(temp){
			case 1:{
				MyHexGame::HexVector *game1 = new MyHexGame::HexVector;
				a = game1;
				a->playGame();

				arr[size] = a;
				size++;
				}break;

			case 2:{
				MyHexGame::HexArray1D *game2= new MyHexGame::HexArray1D;
				b = game2;
				b->playGame();

				arr[size] = b;
				size++;
				}break;

			case 3:{
				MyHexGame::HexAdapter<vector> *game3 = new MyHexGame::HexAdapter<vector>;
				c = game3;
				c->playGame();

				arr[size] = c;
				size++;
				}break;

			case 4:{
				MyHexGame::HexAdapter<deque> *game4 = new MyHexGame::HexAdapter<deque>;
				d = game4;
				d->playGame();

				arr[size] = d;
				size++;
				}break;
		}
	}

	if(size != 0){
		if(check(arr , size)){
			cout << "The games are valid." << endl;
		}
		else{
			cout << "One or more of the games are not valid. " << endl;
		}
	}
	
	for(int i = 0; i<size; i++){
		cout << "Last move of game " << i +1 << " : " << arr[i]->lastMove() << endl;
		cout << "Move number of game " << i+1 << " : " << arr[i]->numberOfMoves() << endl << endl;
	}


	if(size > 1){
		
		for(int i = 0 ; i<size-1; i++){
			if(*arr[i] == *arr[i+1]){
				cout << "Game "<< i+1 << "and Game " << i+2 << "are equal.\n";
			}
		}

	}

}
bool check(AbstractHex *arr[] , int size){

	for(int i = 0 ; i<size; i++){

		for(int j = 0; j<arr[i]->getBoardSize() ; j++){

			for(int k = 0; k<arr[i]->getBoardSize() ; k++){
				
				if( (*arr[i])(j,k) != 'x' && (*arr[i])(j,k) != 'o' && (*arr[i])(j,k) != '.' ){

					return false;
				}
			}
		}
	}
	return true;
}

