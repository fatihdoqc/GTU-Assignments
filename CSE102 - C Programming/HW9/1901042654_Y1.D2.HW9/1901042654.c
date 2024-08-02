#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define CARD_NUMBER 52
#define FACE_NUMBER 13
#define SUIT_NUMBER 4

struct card{
	const char *face;
	const char *suit;
};
struct Hospital{
	char *name;
	char citiesServed[3];
};

int numPathsHome(int street, int avenue);
void shuffle_cards();
void menu();
void swap(int *a, int *b);
int canOfferCovidCoverage(char _cities[6] , char _locations[4][4] , int _numHospitals, struct Hospital results[4]);

void main(){

	menu();

}
void menu(){

	int choice,street,avenue , _numHospitals;
	char _cities[6] = {'A','B','C','D','E','F'},
	 _locations[4][4] = { {'A','B','C','\0'} , {'A','C','D','\0'} , {'B','F','\0'} , {'C','E','F','\0'} };


	while(choice != 4){
		printf("\n1- Lead Cin Ali to his home.\n");
		printf("2- Can you provide health care ?.\n"); // Because I couldn't.
		printf("3- Shuffle the deck.\n");
		printf("4- Exit.\n");
		printf("Your choice : ");
		scanf("%d",&choice);

		switch(choice){
			case 1:
				printf("Enter the street number: ");
				scanf("%d",&street);

				printf("Enter the avenue number: ");
				scanf("%d",&avenue);

				printf("Number of optimal paths to take back home: %d\n",numPathsHome(street - 1,avenue - 1 ));
				break;
			case 2:
				printf("Enter the max number of hospitals that can be constructed:");
				scanf("%d",& _numHospitals);
				while(_numHospitals > 4){
					printf("Max number of hospitals is 4\n Try again: ");
					scanf(" %d",& _numHospitals);
				}

				struct Hospital results[4];
				canOfferCovidCoverage(_cities , _locations , _numHospitals - 1, results);

				break;
			case 3:
				shuffle_cards();
				break;
		}
	}
}
int numPathsHome(int street, int avenue){

	// IF Cin Ali is at the (2,4) he should take 3 steps to south somehow. If I find those steps,
	// West steps must be taken in every way.So total step is 4 and 3 of them must be taken to south.But which ones ?
	// C(4,3) will give it to me. I don't even have to calculate the combination.
	// Because there is an equation like C(n , m) = C(n-1 , m-1) + C(n-1, m)
	// It goes like this until C(x , 1) and C(x,x). C(x , 1) = x and C(x,x) = 1.
	// And those x's and 1's will be added to each other. 

	//printf("C( %d , %d) will be : C( %d , %d) + C( %d , %d) \n",street+avenue , street , street + avenue -1 , street -1 , street + avenue - 1, street);

	if(street == 1){
		return street + avenue;
	}
	if(avenue == 0){
		return 1;
	}

	if(street + avenue > 1){
		return numPathsHome(street - 1,avenue) + numPathsHome(street , avenue -1);
	}
}
void shuffle_cards(){

	srand(time(NULL));
	int i = 0,j = 0,index = 0 , memory[CARD_NUMBER];
	struct card cards[CARD_NUMBER];

	char faces[FACE_NUMBER][10] = {"Ace","Deuce","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Jack","Queen","King"};
	char suits[SUIT_NUMBER][10] = {"Hearts","Diamonds","Clubs","Spades"};

	for(i = 0; i<SUIT_NUMBER; i++){

		for(j = 0; j<FACE_NUMBER; j++){

			cards[index].suit = suits[i]; // Making the cards.
			cards[index].face = faces[j];
			index++;
		}
	}
	for(i = 0; i<CARD_NUMBER; i++){ // Putting the indexes in the memory array.
		memory[i] = i;
	}
	
	for(i = 0; i<CARD_NUMBER; i++){
		index = rand() % (CARD_NUMBER-1); // Shuffling the indexes by swap.
		swap(&memory[i], &memory[index]);
	}
	
	for(i = 0; i<CARD_NUMBER-1; i+=2){

		printf("%9.9s of %s \t",cards[ memory[i] ].face , cards[ memory[i] ].suit );
		printf("%9.9s of %s\n",cards[ memory[i +1]  ].face , cards[ memory[i +1] ].suit );
	}

	/*for(i = 0; i<CARD_NUMBER; i++){ // Controller to check is there same indexes in memory more than one.
									  // I used that to see if I printed same card twice or more.
		for(j = 0; j<CARD_NUMBER; j++){

			if(memory[i] == memory[j]){
				printf("I : %d J : %d\n",i,j);
			}
		}
	}*/

}
void swap(int *a, int *b){

	int temp = *b;
	*b = *a;
	*a = temp;
}
int canOfferCovidCoverage(char _cities[6] , char _locations[4][4] , int _numHospitals, struct Hospital results[4]){

	/*if(**_locations != '\0' ){

		if(_numHospitals == -1){

			char str[20] = " ";
			strcat(str , results[0].citiesServed );
			strcat(str , results[1].citiesServed );
			strcat(str , results[2].citiesServed ); 		// Some non-sense code things.
			strcat(str , results[3].citiesServed );

			printf("%s ",str);

			if(strstr(str , _cities) == NULL){
				printf(" 0");
			
			}
			else{
				
				printf(" 1");
			}

		}
		if(_numHospitals > -1){
			strcpy(results[ _numHospitals ].citiesServed , *_locations );

			printf("%s ",results[ _numHospitals ].citiesServed);
			_numHospitals--;
			_locations++;
			canOfferCovidCoverage(_cities , _locations , _numHospitals , results);
		}
	}*/
	
}