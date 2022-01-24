#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	double budget;
	int genre;
	char* name;
	double score;
	int year;
}Movie;

void fill_arr(char file_path[15] , Movie **movies);

void main(){

	Movie *movies = malloc(5 * sizeof(Movie));

	fill_arr("Movies.txt" , &movies);

}

void fill_arr(char file_path[15] , Movie **movies){

	FILE *fp = fopen(file_path,"r");
	char line[150];

	int i = 0 ;

	fgets(line , sizeof(line) , fp);

	fgets(line , sizeof(line) , fp);

	while(line[i] != '\0'){

		if(line[i] != ','){
			printf("%c", line[i]);
		}
		else{
			printf(" ");
		}
		i++;
	}

	fclose(fp); 
}