#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** Unfortunately the program cannot recognize the order of the datas.
*	The order must be budget,genre,name,score,year. 
*	
*	Fatih Doğaç 1901042654
*/

typedef struct Node_Budget{
	int year;
	int budget;
	char *name;
	struct Node_Budget *next;
}Movie_Budget;

typedef struct Node_Name{
	double score;
	char *genre;
	char *name;
	struct Node_Name *next;
}Movie_Name;

void to_struct_arr(Movie_Name **names , Movie_Budget **budgets , char filePath[20]);
Movie_Budget *add_to_budget_list(Movie_Budget *leaf , Movie_Budget *root);
Movie_Name *add_to_name_list(Movie_Name *leaf , Movie_Name *root);
Movie_Budget *contains_or_add_budget(Movie_Budget *leaf , Movie_Budget *root );
Movie_Name *contains_or_add_name(Movie_Name *leaf , Movie_Name *root);
int size_budget(Movie_Budget *root);
int size_name(Movie_Name *root);
void merge(Movie_Budget *leftTable , Movie_Budget *rightTable , Movie_Budget **budget);
void sort_budget(Movie_Budget **budget);
void menu();
void list_genres(Movie_Name *name_list );
void list_frequencies(Movie_Name *name_list);
void all_info_one_movie(Movie_Name *name_list , Movie_Budget *budget_list , char *name);
void through_years(Movie_Budget *budget_list , int start , int until_or_since);
void through_scores(Movie_Name *name_list , double start , int greater_or_less);
double avarage_scores(Movie_Name *name_list);

void main(){

	menu();
}
void menu(){

	int choice = 0 , temp;
	char *name = NULL;
	double temp_score;

	Movie_Name *name_list = NULL;
	Movie_Budget *budget_list = NULL;

	to_struct_arr(&name_list , &budget_list , "Movies.txt");
	sort_budget(&budget_list);

	while(choice != 8){
		printf("\n2)List of the Genres\n");
		printf("3)List of the Movie through the Years\n");
		printf("4)List of the Movie through the Scores\n");
		printf("5)All informations of a Single Movie.\n");
		printf("6)Average of the IMDB scores.\n");
		printf("7)Frequence of the Genres.\n");
		printf("8)Exit.\n");
		printf("Choice: ");

		scanf("%d",&choice);

		switch(choice){
			case 2:
				printf("\n");
				list_genres(name_list);
				break;
			case 3:
				temp;
				printf("\nEnter a year:\n");
				scanf("%d",&temp);

				printf("Until or since %d\n",temp);
				printf("1) Until %d.\n",temp);
				printf("2) Since %d.\n",temp);
				printf("Choice: ");
				scanf("%d",&choice);

				printf("\n");
				through_years(budget_list, temp , choice);
				break;
			case 4:
				printf("Enter a score: ");
				scanf("%lf",&temp_score);

				printf("Greater or less than %.1lf\n",temp_score);
				printf("1) Greater %.1lf.\n",temp_score);
				printf("2) less %.1lf.\n",temp_score);

				printf("Choice: ");
				scanf("%d",&choice);

				printf("\n");
				through_scores(name_list , temp_score , choice);
				break;
			case 5:
				name = malloc(sizeof(char) * 300);
				printf("Enter a movie name :");
				scanf(" %[^\n]",name);
				printf("\n");
				all_info_one_movie(name_list , budget_list , name);
				break;
			case 6:
				printf("\n Avarage of the IMDB scores: %lf \n" , avarage_scores(name_list));
				break;
			case 7:
				printf("\n");
				list_frequencies(name_list);
				break;
			case 8:
				break;
			default:
				printf("Bad Input. Try again.\n");
				break;
		}
	}

	free(name);
	free(name_list);
	free(budget_list);

}
void to_struct_arr(Movie_Name **names , Movie_Budget **budgets , char filePath[20]){

	FILE *fp = fopen(filePath , "r");

	char line[300] , *token;

	fgets(line , 300 , fp); // ignore first line.

	fgets(line , 300 , fp); // first major line.
	while(!feof(fp)){

		int flag = 0;

		token = strtok(line , ",");

		Movie_Budget *temp_budget = malloc(sizeof(Movie_Budget) + 400 * sizeof(char));
		Movie_Name *temp_name = malloc(sizeof(Movie_Name) + 400 * sizeof(char) + 100 * sizeof(char));

		while(token != NULL){ // splitting the string.

			if(strchr(token , '\n') != NULL || strchr(token , '\r') != NULL){ // "year\n" becomes "year"

				int i = 0;
				while( i < strlen(token)){
					if(token[i] == '\n' || token[i] == '\r'){
						token[i] = '\0';
						break;
					}
					i++;
				}
			}
			
			switch(flag){
				case 0: // budget
					if(strcmp(token , "unknown") != 0){ 
						temp_budget->budget = atoi(token);
					}
					else{
						temp_budget->budget = -1;
					}
					flag++;
					break;
				case 1: // genre
					temp_name->genre = malloc(sizeof(char) * 100);
					temp_name -> genre = token;
					flag++;
					break;
				case 2: // name
					temp_name->name = malloc(sizeof(char) * 400);
					temp_budget->name = malloc(sizeof(char) * 400);
					temp_budget -> name = token;
					temp_name->name = token;
					flag++;
					break;
				case 3: // score
					temp_name->score = strtod(token , NULL);
					flag++;
					break;
				case 4: // year
					temp_budget->year = atoi(token);
					flag = 0;
					break;
			}
	    
	      	token = strtok(NULL, ",");
		}

		*budgets = contains_or_add_budget(temp_budget , *budgets);
		*names = contains_or_add_name(temp_name , *names);

		fgets(line , 300 , fp); // next line.
	}

	fclose(fp);
}
double avarage_scores(Movie_Name *name_list){

	Movie_Name *iter = name_list;
	double sum = 0.0;

	while( iter != NULL){
		sum += iter->score;
		iter = iter->next;
	}

	return sum / size_name(name_list);
}
/* Listing through scores. */
void through_scores(Movie_Name *name_list , double start , int greater_or_less){
	if(greater_or_less == 1){ // greater.

		Movie_Name *iter = name_list;
		int flag = 0;

		while(iter != NULL){
			if(iter->score >= start ){
				printf("%s\n", iter->name);
				flag = 1;
			}
			iter = iter->next;
		}

		if(flag == 0){ // There is no such a movie.
			printf("TRY AGAIN.\n");
		}
	}
	else{ // less
		Movie_Name *iter = name_list;

		int flag = 0;

		while(iter != NULL){
			if(iter->score <= start ){
				printf("%s\n", iter->name);
				flag = 1;
			}
			iter = iter->next;
		}

		if(flag == 0){ // There is no such a movie.
			printf("TRY AGAIN.\n");
		}
	}
}
void through_years(Movie_Budget *budget_list , int start , int until_or_since){

	if(until_or_since == 1){

		Movie_Budget *iter = budget_list;
		int flag = 0;

		while(iter != NULL){
			if(iter->year <= start ){
				printf("%s\n", iter->name);
				flag = 1;
			}
			iter = iter->next;
		}

		if(flag == 0){
			printf("TRY AGAIN.\n");
		}
	}
	else{ // since
		Movie_Budget *iter = budget_list;
		int flag = 0;

		while(iter != NULL){
			if(iter->year >= start ){
				printf("%s\n", iter->name);
				flag = 1;
			}
			iter = iter->next;
		}

		if(flag == 0){
			printf("TRY AGAIN.\n");
		}
	}
}
void all_info_one_movie(Movie_Name *name_list , Movie_Budget *budget_list , char *name){
	Movie_Name *iter = name_list;
	int flag = 1;

	while(iter != NULL){

		if( strcmp(iter->name , name) == 0){
			printf("Score:\t%.1f\n",iter->score);
			printf("Genre:\t%s\n", iter->genre);
			printf("Name:\t%s\n", iter->name);
			flag = 0;
			break;
		}
		iter = iter->next;
	}
	if(flag == 1){
		printf("There isn't such a movie.\n");
		return;
	}

	Movie_Budget *it = budget_list;
	while(it != NULL){
		if( strcmp(it->name , name) == 0){
			if(it->budget != -1){
				printf("Budget:\t%d\n",it->budget);
			}
			else{
				printf("Budget:\tunknown\n");
			}

			printf("Year:\t%d\n", it->year);
			return;
		}
		it = it->next;
	}
}
void list_genres(Movie_Name *name_list ){

	Movie_Name *iter = name_list;

	char **genres = malloc(sizeof(char*) * size_name(name_list)); // dynamic string array.
	for(int i = 0; i< size_name(name_list); i++){
		genres[i] = malloc(sizeof(char) * 100);
	}

	int index = 0 , flag = 1;

	while(iter != NULL){

		for(int i = 0; i< index; i++){
			if(strcmp( genres[i] , iter->genre) == 0){
				flag = 0; // genre of the iter is already in array.
				break;
			}
		}
		if(flag == 1){ // genre is not in the array
			strcpy(genres[index] , iter->genre);
			index++;
			printf("%s\n", iter->genre);
		}

		iter = iter->next;

		flag = 1;
	}
}
void list_frequencies(Movie_Name *name_list){
	Movie_Name *iter = name_list;

	char **genres = malloc(sizeof(char*) * size_name(name_list));
	for(int i = 0; i< size_name(name_list); i++){
		genres[i] = malloc(sizeof(char) * 100);
	}

	int index = 0 , flag = 1;

	while(iter != NULL){

		for(int i = 0; i< index; i++){
			if(strcmp( genres[i] , iter->genre) == 0){
				flag = 0; // genre of the iter is already in array.
				break;
			}
		}
		if(flag == 1){ // genre is not in the array
			strcpy(genres[index] , iter->genre);
			index++;
		}
		iter = iter->next;
		flag = 1;
	}

	int *counts = malloc(sizeof(int) * index);
	for(int i = 0; i< index ; i++){ // initialize the counters.
		counts[i] = 0;
	}

	iter = name_list;
	while( iter != NULL){

		for(int i = 0; i< index; i++){
			if( strcmp(iter->genre , genres[i]) == 0){
				counts[i]++;
				break;
			}
		}
		iter = iter->next;
	}

	for(int i = 0; i< index; i++){
		printf("%-12s%-12d\n", genres[i] , counts[i]);
	}

}
/* merge sort , I wrote it in java to study my CSE222 exam , I inspired by it*/
void sort_budget(Movie_Budget **budget){

	Movie_Budget *iter = *budget;
	int size_of_list = size_budget(*budget);

	if( size_of_list > 1 ){

		int halfSize = size_of_list / 2;

		Movie_Budget *leftTable = NULL; // Split the list from the half.
		Movie_Budget *rightTable = NULL;

		for(int i = 0; i< halfSize ; i++){
			leftTable = add_to_budget_list(iter , leftTable);
			iter = iter->next;
		}

		for(int i = halfSize; i< size_of_list; i++){
			rightTable = add_to_budget_list(iter , rightTable);
			iter = iter->next;
		}

		sort_budget(&leftTable);
		sort_budget(&rightTable);

		merge(leftTable , rightTable , budget);

	}
}
/* Merge the splitted lists according to the year and budget. */
void merge(Movie_Budget *leftTable , Movie_Budget *rightTable , Movie_Budget **budget){

	Movie_Budget *iter_left = leftTable;
	Movie_Budget *iter_right = rightTable;
	Movie_Budget *iter_root = *budget;

	Movie_Budget *new_list = NULL;

	while(iter_left != NULL && iter_right != NULL){
		if(iter_left->year < iter_right->year){
			new_list = add_to_budget_list(iter_left , new_list);
			iter_left = iter_left->next;
		}
		else{

			if(iter_left->year == iter_right->year){

				if(iter_left->budget < iter_right->budget){
					new_list = add_to_budget_list(iter_left , new_list);
					iter_left = iter_left->next;
				}
				else{
					new_list = add_to_budget_list(iter_right , new_list);
					iter_right = iter_right->next;
				}
			}
			else{
				new_list = add_to_budget_list(iter_right , new_list);
				iter_right = iter_right->next;
			}
		}
	}

	while(iter_left != NULL){
		new_list = add_to_budget_list(iter_left , new_list);
		iter_left = iter_left->next;
	}
	while(iter_right != NULL){
		new_list = add_to_budget_list(iter_right , new_list);
		iter_right = iter_right->next;
	}

	(*budget) = new_list;
}
/* size of a Movie_Budget list. */
int size_budget(Movie_Budget *root){
	if(root == NULL){
		return 0;
	}
	return 1 + size_budget( root->next);
}
/* size of a Movie_Name list. */
int size_name(Movie_Name *root){
	if(root == NULL){
		return 0;
	}
	return 1 + size_name( root->next);
}
Movie_Budget *contains_or_add_budget(Movie_Budget *leaf , Movie_Budget *root ){
	
	if(root == NULL){ // If doesn't contain , add.
		root = add_to_budget_list(leaf , root);
	}
	else if( strcmp( leaf->name , root->name)  == 0){ // If contains , change
		root->budget = leaf->budget;
		root->year = leaf->year;
	}
	else{
		root -> next = contains_or_add_budget(leaf , root->next );
	}

	return root;
}
Movie_Name *contains_or_add_name(Movie_Name *leaf , Movie_Name *root){
	if(root == NULL){ // If doesn't contain , add.
		root = add_to_name_list(leaf , root);
	}
	else if( strcmp( leaf->name , root->name)  == 0){ // If contains , change
		strcpy(root->genre , leaf->genre);
		root->score = leaf->score;
	}
	else{
		root -> next = contains_or_add_name(leaf , root->next );
	}

	return root;
}
/* insert to the Movie_Budget list. */
Movie_Budget *add_to_budget_list(Movie_Budget *leaf , Movie_Budget *root){
	if(root == NULL){
		root = malloc(sizeof(Movie_Name) + 400 * sizeof(char));
		root->name = malloc(sizeof(char) * 400);

		strcpy( root->name , leaf->name) ;

		root->year = leaf->year;
		root->budget = leaf->budget;
		root->next = NULL;
	}
	else{
		root->next = add_to_budget_list(leaf , root->next);
	}

	return root;
}
/* insert to the Movie_Name list. */
Movie_Name *add_to_name_list(Movie_Name *leaf , Movie_Name *root){
	if(root == NULL){
		root = malloc(sizeof(Movie_Name) + 400 * sizeof(char) + 100* sizeof(char));
		root->name = malloc(sizeof(char) * 400);
		root->genre = malloc(sizeof(char) * 100);
		strcpy( root->name , leaf->name) ;
		strcpy( root->genre , leaf->genre) ;
		root->score = leaf->score;
		root->next = NULL;
	}
	else{
		root->next = add_to_name_list(leaf , root->next);
	}

	return root;
}