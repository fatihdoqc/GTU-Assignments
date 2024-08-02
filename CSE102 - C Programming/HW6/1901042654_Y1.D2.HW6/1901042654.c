#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ENTRY_COUNT 150
#define MAX_ENTRY_LENGTH 100

void rand_words_to_array(char buffer[MAX_ENTRY_COUNT][MAX_ENTRY_LENGTH]);
void print_the_word_to_table(char buffer[MAX_ENTRY_COUNT][MAX_ENTRY_LENGTH],char answers[MAX_ENTRY_COUNT][MAX_ENTRY_LENGTH]);

typedef char c_arr[20];
c_arr rows = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T'};

int main(){

	FILE *words = fopen("words.txt","r");
	char buffer[MAX_ENTRY_COUNT][MAX_ENTRY_LENGTH],word[30],r,
	answers[MAX_ENTRY_COUNT][MAX_ENTRY_LENGTH];
	int	i,j,count = 0,colm,check = 0;

	rand_words_to_array(buffer);
	print_the_word_to_table(buffer,answers);
	printf("\nTop left is A0 and bottom right is T19\n\n");

	do{	
		// PUZZLE TABLE 20X20 
		printf("	 	       1 1 1 1 1 1 1 1 1 1\n");
		printf("   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9\n");
		for(i = 0; i<20; i++){
			printf("%c| ",rows[i]);	
			for(j = 0; j<20; j++){

				printf("%c ",buffer[i][j]);
			}	
			printf("\n");
		}
		//---------------------
		printf("Please enter the coordinate and the word:\n");
		scanf(" %[^\n]",word);

		if (strcmp(word, "exit") == 0){ // Searching "exit" in the input.
	      	return printf("Exiting, thanks for playing!\n"), 0; // If yes terminate the program.
		}

		sscanf(word,"%c%d %s",&r,&colm,word); // Seperating the input to a char an integer and a string.
											  // So I will get a row , a column and the guess.

		while(r != count){  // a == 97, b == 98 in ASCII table. That way I will communicate with the user easily
							// To get the row number I just need to ;
			count++;
		}
		if(word[0] == buffer[count-97][colm]){  // subtract 97. If user enters "a", the user means the first row and 97-97 = 0 
												//, so first row.

			if(answers[count-97][colm] == '*'){ // At the second table(answer table) a star exist at the start of the word and checked here.
				printf("Well done ! Keep going.\n");
				check++;
				if(check == 10){ // There are 10 words hidden in the puzzle. If the user finds all 10 program should terminate.

					for(i = 0; i<20; i++){
						printf("%c| ",rows[i]);	

						for(j = 0; j<20; j++){														
							printf("%c ",buffer[i][j] -32); // Upper casing the table.
							
						}	
					printf("\n");
					}

					printf("Thanks for playing\n");
					return 0;
				}
			}
			else{
				printf("Ahhh, so close.\n");		
			}
		}
		else{
			printf("Try again\n");
		}
	}while(strcmp(word, "exit") != 0); // Searching the "exit" in the input every round.
}
void rand_words_to_array(char buffer[MAX_ENTRY_COUNT][MAX_ENTRY_LENGTH]){

	FILE *fp;
	srand(time(NULL));
	int i,j = 0,row = rand() % 100,
	temp = 0,count = 0,a = 0;
	char c;
	

	for(i = 0; i<20; i++){
		fp = fopen("words.txt","r");

		while(row == temp){ // I don't want to get the same word twice in a roll.
		
			row = rand() % 100;
		}
		temp = row;
		if(row == 0){		
			strcpy(buffer[i],"wall\n");	// wall is at the start of the file. And program was getting trouble about it.
										// I had to add it manually.	
		
			while(row == temp){	
				row = rand() % 100;
			}		
		}
		else{
			while(!feof(fp)){
				fscanf(fp , "%c", &c);

				if (c == '\n'){	// Taking the line information by counting.
					count++;
					
					if(count == row){ // When I reach the wanted row. Just taking it.
						count = 0; // To use that variable next time, I am resetting it.
						c = '#';
						j = 0;
						if(row == 99){ // Same as the "wall", end of the file was trouble to get it to array.
							
							strcpy(buffer[i],"bait\n");
						}
						else{

							while(!feof(fp)){			
								fscanf(fp , "%c", &c);
								if(c == '\n'){ // Taking only one line except the "\n"
									break;
								}
								else{										
									buffer[i][j] = c; // printing it to array char by char.
									j++;
									
								}
										
							}
						}
						break;
					}
				}
				
			}
		}
		fclose(fp);
	}	

}

void print_the_word_to_table(char buffer[MAX_ENTRY_COUNT][MAX_ENTRY_LENGTH],char answers[MAX_ENTRY_COUNT][MAX_ENTRY_LENGTH]){

	srand(time(NULL));
	char word[10][50];
	word[10][50] = '\0';

	int c = rand() % 20,
	r = 0,temp,temp2,
	i,j,direction,check = 1;

	for(i = 0; i<20; i++){		
		for(j = 0; j<20; j++){

			answers[i][j] = '#'; // I will use stars on that table to know the start of the word.
								// So I am filling it with something else.
		}	
	}

	printf("Hidden words are:\n"); // listing the hidden words.
	for(i=0; i<10; i++){
		strcpy(word[i],buffer[i]); // Getting the words to a more basic array to reach them easily.
		printf("%s\n",word[i]);
	}

	for(i = 0; i<20; i++){		// filling my actual table with "#" because I don't want the words get mixed.
		for(j = 0; j<20; j++){

			buffer[i][j] = '#';
		}	
	}

	r=rand() % 20;
	c=rand() % 20;
	temp = c;

	for(i = 0;i<10; i++){ // Ten times because there are ten words.
		direction = rand() % 7 + 1; // picking the direction
		switch(direction){
			case 1:
				for(j=0; j<strlen(word[i]) - 1; j++){ // Checking if is there enough space for picked word.
					
					if(buffer[r][c] != '#' || 21 - strlen(word[i]) < c){ // Checking if the wanted space is empty.
						// Empty means '#', if is there a word or something I mean not '#' then it is not empty.
						// Pick a new row and column.

						r=rand() % 20;
						c=rand() % 20;
						j= 0;
						temp = c; // Getting the initial position for my star.
					}
					else{
						c++;
					}
				}
				answers[r][temp] = '*'; // Printing the star at the start of the word to second table.
				for(j=0; j<strlen(word[i]) - 1; j++){ // Printing the word to reserved and checked space.
					buffer[r][temp] = word[i][j];
					temp++;
				}		
				break;
			case 2:
				for(j=0; j<strlen(word[i]) - 1; j++){
					
					if(buffer[r][c] != '#' || 21 - strlen(word[i]) < c){

						r=rand() % 20;
						c=rand() % 20;
						j= 0;
						temp = c;
					}
					else{
						c++;
					}
				}
				for(j=strlen(word[i]) - 2; j >= 0; j--){

					buffer[r][temp] = word[i][j];
					temp++;
					
				}
				answers[r][temp-1] = '*';
				break;
			case 3:
				for(j=0; j<strlen(word[i]) - 1; j++){
					
					if(buffer[r][c] != '#' || r > 10){

						r=rand() % 20;
						c=rand() % 20;
						j= 0;
						temp = r;
					}
					else{
						r++;
					}
				}
				answers[temp][c] = '*';
				for(j=0; j<strlen(word[i]) - 1; j++){
					buffer[temp][c] = word[i][j];
					temp++;
				}
				break;
			case 4:
				for(j=0; j<strlen(word[i]) - 1; j++){
					
					if(buffer[r][c] != '#' || 21 - strlen(word[i]) < r){

						r=rand() % 20;
						c=rand() % 20;
						j= 0;
						temp = r;
						printf("%c",r);
					}
					else{
						r++;
					}
				}		
				for(j=strlen(word[i]) - 2; j >= 0; j--){

					buffer[temp][c] = word[i][j];
					temp++;
					
				}
				answers[temp-1][c] = '*';
				break;
			case 5:
				for(j=0; j<strlen(word[i]) - 1; j++){
					
					
					if(buffer[r][c] != '#' || 21 - strlen(word[i]) < r || 21 - strlen(word[i]) < c){

						r=rand() % 20;
						c=rand() % 20;
						j= 0;
						temp = r;
						temp2 = c;
					}
					else{
						r++;
						c++;
					}
				}
				answers[temp][temp2] = '*';
				for(j = 0; j< strlen(word[i]) - 1; j++){
					buffer[temp][temp2] = word[i][j];
					temp++;
					temp2++;
				}
				break;
			case 6:
				for(j=0; j<strlen(word[i]) - 1; j++){
									
					if(buffer[r][c] != '#' || c < strlen(word[i]) || r < strlen(word[i])){

						r=rand() % 20;
						c=rand() % 20;
						j= 0;
						temp = r;
						temp2 = c;
					}
					else{
						r--;
						c--;
					}
				}
				answers[temp][temp2] = '*';
				for(j = 0; j< strlen(word[i]) - 1; j++){
					buffer[temp][temp2] = word[i][j];
					temp--;
					temp2--;
				}
				break;
			case 7:
				for(j=0; j<strlen(word[i]) - 1; j++){
									
					if(buffer[r][c] != '#' || 21 - strlen(word[i]) < r || c < strlen(word[i]) - 1){

						r=rand() % 20;
						c=rand() % 20;
						j= 0;
						temp = r;
						temp2 = c;

					}
					else{
						
						r++;
						c--;
					}
				}
				answers[temp][temp2] = '*';
				for(j = 0; j< strlen(word[i]) - 1; j++){
					buffer[temp][temp2] = word[i][j];
					temp++;
					temp2--;
				}
				break;
			case 8:
				for(j=0; j<strlen(word[i]) - 1; j++){
									
					if(buffer[r][c] != '#' || r > 20 || c < 0){

						r=rand() % 20;
						c=rand() % 20;
						j= 0;
						temp = r;
						temp2 = c;
					}
					else{
						r++;
						c--;
					}
				}
				answers[temp][temp2] = '*';
				for(j = strlen(word[i]) - 2; j >= 0; j--){
					
					buffer[temp][temp2] = word[i][j];
					temp++;
					temp2--;
				}
				break;
			
		}
	}
	for(i = 0; i<20; i++){		// Filling the remaining tiles in the table with random characters.
		for(j = 0; j<20; j++){

			if(buffer[i][j] == '#'){
				r = rand() % 10;
				c = rand() % 3;
				buffer[i][j] = word[r][c];
			}
		}	
	}
	
}