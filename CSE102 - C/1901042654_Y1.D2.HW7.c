#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUMBEROF_GAMES 2000

void menu();
void fill_names(char names[MAX_NUMBEROF_GAMES][100]);
void list_genres(int freqs_toggle);
void list_platforms();
void list_game_through_years();
void informations_game(char *name);
void av_of_userscores();
void geog_info(char *name);

void main(){

	menu();
	
}
void menu(){

	int choice;
	char game[20];

	while(choice != 8){
		printf("\n0: List of the Genres.\n");
		printf("1: List of the Platforms.\n");
		printf("2: List of the Games through years.\n");
		printf("3: All informations of a single game.\n");
		printf("4: Average of the user scores.\n");
		printf("5: Georogrofical information of a single game.\n");
		printf("6: Frequencies of genres.\n");
		printf("7: Frequencies of platforms.\n");
		printf("8: Exit.\n");

		printf("Please select an operation: ");

		scanf(" %d",&choice);
		switch(choice){
			case 0:
				list_genres(0); 
				break;
			case 1:
				list_platforms(0);
				break;
			case 2:
				list_game_through_years();
				break;
			case 3:
				printf("Please enter the name of the game: ");
				scanf("%s",game);
				informations_game(game);
				break;
			case 4:
				av_of_userscores();
				break;
			case 5:
				printf("Please enter the name of the game: ");
				scanf("%s",game);
				geog_info(game);
				break;
			case 6:
				list_genres(1);
				break;
			case 7:
				list_platforms(1);
				break;
		}
	}
}
void fill_names(char names[MAX_NUMBEROF_GAMES][100]){ // A function that takes the names of games from file to an array
	char lines[300],c;
	int i=0 ;

	FILE *fp = fopen("Video_Games.txt","r");
	fgets(lines, 250, fp); // First line is the titles so I don't need it. Wasting a line here.

	while(fgets(lines, 250, fp) != NULL ){

		strcpy(names[i] , strtok(lines,",")); // Copying the part up to comma to my dear array with compassion of course.
		i++; //incrementing the index everytime.
	}
	fclose(fp);

}
void list_genres(int freqs_toggle){

	char lines[300], *token, genres[30][30];
	int i=0, j, check = 4, index = 0 , a = 0 , frequency = 0, count = 0;
	float f_genres[MAX_NUMBEROF_GAMES][5];

	FILE *fp = fopen("Video_Games.txt","r");
	fgets(lines, 250, fp);

	while(fgets(lines, 250, fp)){

		token = strtok(lines , ","); // I have got the name at token string.
		token = strtok(NULL , ","); // Now I have got the genre of the game which is at that line.

		for(i=0; i<index; i++){
			
			if(strcmp(genres[i],token) == 0){ // If I already have the genre of the game in my array. I don't want it again. Just one is enough.
				check = 5;
				break;
			}
			else{ 
				check = 1;

			}
		}

		if(check != 5){
			strcpy(genres[index],token); // Taking the genre to the array.
			index++;					 // Check != 5 is checking if I want that genre in my dear array.
		}
	}
	rewind(fp); // I read the file once , now to read once again I set my pointer to the top.
	a = 0;
	while(fgets(lines, 250, fp)){
		token = strtok(lines , ",");
		token = strtok(NULL , ","); // Taking the genres again at token.
		for(i=0; i<index; i++){
			
			if(strcmp(genres[i],token) == 0){ // Setting a float number to a spesific genre.
				f_genres[a][0] = (float) i;	  // For example first index at the genre array is "simulation"	and it's index is 0.		
				a++;						  // Now when the program scans the genre of the game comparing it with the genres I aldready have.
			}								  // And when the genre of the game matches with a genre, It takes its index.
		}
		
	}

	if(freqs_toggle == 0){	// If I would like to get the list of the genres I give 0 to that variable.
		for(i = 0; i<index; i++){
			printf("%s\n",genres[i]);
		}
	}
	else{ // Otherwise that means I want the frequencies.
		for(i = 0;i<index; i++){
			for(j =0; j<MAX_NUMBEROF_GAMES; j++){
				if((int)f_genres[j][0] == i ){// Comparing the genre of the current game with the indexes of my genre array.
					count++;	// And counting.
				}
			}
			if(strlen(genres[i]) > 6){
				printf("%s \t%d\n",genres[i],count);
				count = 0;
			}
			else{
				printf("%s \t\t%d\n",genres[i],count);
				count = 0;
			}
		}
	}


	fclose(fp);

}
void list_platforms(int freqs_toggle){
	char lines[300],c, *token, platforms[30][30];
	int i=0, j, check = 4, index = 0 ,a ,count = 0;
	float f_platfs[MAX_NUMBEROF_GAMES][5];

	FILE *fp = fopen("Video_Games.txt","r");
	fgets(lines, 250, fp);

	while(fgets(lines, 250, fp)){ // Exactly what is done at listing the genres because I used ctrl+c ctrl+v.
								  // But this function scans one more comma to reach the platform information.

		token = strtok(lines , ",");
		token = strtok(NULL , ",");
		token = strtok(NULL , ",");

		for(i=0; i<index; i++){
			
			if(strcmp(platforms[i],token) == 0){
				check = 5;
				break;
			}
			else{ 
				check = 1;

			}
		}

		if(check != 5){
			strcpy(platforms[index],token);
			index++;			
		}
	}

	rewind(fp);
	a = 0;
	while(fgets(lines, 250, fp)){
		token = strtok(lines , ",");
		token = strtok(NULL , ",");
		token = strtok(NULL , ",");
		for(i=0; i<index; i++){

			if(strcmp(platforms[i],token) == 0){
				f_platfs[a][0] = (float) i;				
				a++;
			}
		}
		
	}
	if(freqs_toggle == 0){
		for(i = 0; i<index; i++){
			printf("%s\n",platforms[i]);
		}
	}
	else{
		for(i = 0;i<index; i++){
			for(j =0; j<MAX_NUMBEROF_GAMES; j++){
				if((int)f_platfs[j][0] == i ){
					count++;
				}
			}			
			printf("%s \t%d\n",platforms[i],count);
			count = 0;
				
		}
	}
	fclose(fp);
}
void list_game_through_years(){

	char lines[300],c, *token, names[MAX_NUMBEROF_GAMES][100];
	int i=0, check, index = 0 , option ,a =0;
	float years[MAX_NUMBEROF_GAMES], year;

	fill_names(names); 

	FILE *fp = fopen("Video_Games.txt","r");
	fgets(lines, 250, fp);

	while(fgets(lines, 250, fp)){

		token = strtok(lines , ",");
		token = strtok(NULL , ",");
		token = strtok(NULL , ",");
		token = strtok(NULL , ","); // Taking the year infos +

		years[index] = (float)atol(token); // + to the array
		index++;
	}
	printf("Enter a year:\n");
	scanf(" %f",&year);

	printf("Until (0) or Since (1) %.0f: ",year);
	scanf(" %d",&option);

	switch(option){
		case 0: // Until
			for(i = 0; i< 2000; i++){ // Program shows the games that is born before that year.
				if(years[i] < year){
					printf("%s\n",names[i]);
				}
			}
			break;
		case 1:		
			for(i = 0; i< 2000; i++){ // Program shows the games that is born after that year.
				if(years[i] > year){
					printf("%s\n",names[i]);
				}
			}
			break;		
	}
	fclose(fp);

}
void informations_game(char *name){

	char *token,lines[200];
	int i;
	FILE *fp = fopen("Video_Games.txt","r");
	
	for(i = 0; i<2000; i++){
		fgets(lines, 250, fp);
		token = strtok(lines , ",");
		if(strcmp(token,name) == 0){ // Finding the wanted game's line.
			break;
		}
	}

	printf("Name: %s\n",token);

	token = strtok(NULL , ",");
	printf("Genre: %s\n",token);

	token = strtok(NULL , ",");
	printf("Platform: %s\n",token);

	token = strtok(NULL , ",");
	printf("Year of release: %s\n",token);

	token = strtok(NULL , ",");
	printf("NA Sales: %s\n",token);

	token = strtok(NULL , ",");
	printf("EU Sales: %s\n",token);

	token = strtok(NULL , ",");
	if(strcmp(token,"not_available") == 0){
		printf("Global Sales: Not Avaiable\n");
	}
	else{
		printf("Global Sales: %s \n",token);
	}

	token = strtok(NULL , ",");
	printf("User Scores: %s\n",token);

	fclose(fp);
	
}
void av_of_userscores(){

	FILE *fp = fopen("Video_Games.txt","r");
	char *token,lines[200];
	float u_scores[MAX_NUMBEROF_GAMES][5], sum = 0;
	int i , a=0;
	fgets(lines, 250, fp);

	while(fgets(lines, 250, fp)){
		token = strtok(lines , ",");
		token = strtok(NULL , ",");
		token = strtok(NULL , ",");
		token = strtok(NULL , ",");
		token = strtok(NULL , ",");
		token = strtok(NULL , ",");
		token = strtok(NULL , ",");
		token = strtok(NULL , ","); // Taking the user scores.
		
		u_scores[a][0] = atof(token);
		a++;

	}
	for(i=0; i<MAX_NUMBEROF_GAMES;i++){
		sum = sum + u_scores[i][0] ; // Summed all the user scores
	}

	printf("Average: %f\n", sum / MAX_NUMBEROF_GAMES);// And found the average of them by dividing them to the number of games.


}
void geog_info(char *name){
	FILE *fp = fopen("Video_Games.txt","r");
	char *token,lines[200];
	float sales[MAX_NUMBEROF_GAMES][10];
	int a = 0,i,j;

	fgets(lines, 250, fp);


	for(i =0; i<MAX_NUMBEROF_GAMES; i++){
		fgets(lines, 250, fp);
		token = strtok(lines , ",");
		token = strtok(NULL , ",");
		token = strtok(NULL , ",");
		token = strtok(NULL , ",");

		token = strtok(NULL , ",");// Taking the sales information at North America.
		sales[a][0] = atof(token);

		token = strtok(NULL , ",");// Taking the sales information at Europe.
		sales[a][1] = atof(token);
		a++;
		
	}
	rewind(fp);
	
	for(i = 0; i<MAX_NUMBEROF_GAMES; i++){
		fgets(lines, 250, fp);
		token = strtok(lines , ",");
		if(strcmp(token,name) == 0){ // Finding the wanted game's line.
			break; // When i is equal to that line program breaks here and I am becoming having the line information in my "i" variable.
		}
	}

	if(sales[i-1][0] > sales[i-1][1]){ // First line is titles so -1.
		printf("This game was more popular in North America.\n\n");
	}
	else{
		printf("This game was more popular in Europe.\n\n");
	}
	fclose(fp);

}
