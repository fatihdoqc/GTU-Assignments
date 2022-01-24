#include <stdio.h>
#include <math.h>

#define N 8

void menu();
void generate_hofstadters_sequence(int *arr,int n);
int find_max(int arr[], int index, int max_value);
int sum_array(int arr[]);
double std_array(int arr[], double *mean, int n, int index);
char *remove_duplicates(char *str);
void install_pipes(int visited[N][N] , int x, int y, int orientation);


void main(){

	menu();
}
void menu(){

	int choice,array[500],n,max_value = 0 , i, visited[N][N] , orientation;
	double mean;
	char str[500];

	/*for (i=0; i<8; i++){
		for(max_value = 0; max_value<8; max_value++){
			visited[i][max_value] = 0;
		}
	}*/

	while(choice != 4){
		printf("\n1) Execute part 1.\n");
		printf("2) Execute part 2.\n");
		printf("3) Execute part 3.\n");
		printf("4) Exit.\n");

		scanf("%d",&choice);
		switch(choice){
			case 1:
			while(choice != 5){
					printf("\n1) Fill array.");
					printf("\n2) Find biggest number.");
					printf("\n3) Calculate sum.");
					printf("\n4) Calculate standart deviation.");
					printf("\n5) Exit.\n");
					printf("\nYour choice : ");

					scanf("%d",&choice);
					switch(choice){

						case 1:
							printf("How many times? : ");
							scanf("%d", &array[0]);		// I used the first index of array as the wanted times.
							if(array[0] < 2){
								printf("Invalid option, please try again.\n");
								break;
							}
							array[0] = array[0] + 1;	// I need to increment the wanted value by one		
							// Just because the index problem of arrays which is "first index of an array is array[0]"	

							n = 3;						// n must be > 2, so the start value is 3.
							generate_hofstadters_sequence(array,n);
							break;
						case 2:							
							printf("Biggest number is %d.\n",find_max(array, 1 ,max_value));
							break;
						case 3:
							array[499] = 1; // Index.
							array[500] = 0;	// Place to keep sum.
							
							printf("Sum of items: %d\n",sum_array(array));
							break;
						case 4:
							array[500] = 0;
							array[499] = 0; // It is my flag. If it is 0 program calculates the mean,
											// if it is 1 program calculates the standard deviation.											
							printf("Standard deviation of the array: %f\n",std_array(array, &mean , array[0] - 1 , 1));
							break;
						
					}
				}
				break;
			case 2:
				visited[0][0] = 1;
				install_pipes(visited , 0 , 0 , orientation);
				break;
			case 3:
				printf("Enter the text that you want to remove duplicate characters in it.:\n");
				scanf(" %[^\n]",str); // Taking the allll of the input.
				printf("Your string becomes : ");
				remove_duplicates(str);
				break;
		}
	}

}
void generate_hofstadters_sequence(int *arr,int n){

	arr[1] = 1; // Q(1)
	arr[2] = 1; // Q(2)

	arr[n] = ( arr[n - ( arr[n-1] )] ) + ( arr[n - ( arr[n-2] )] ); 
	n++;

	if(arr[0] != n){  // arr[0] has the value of how many indexes will the array be filled.
		generate_hofstadters_sequence(arr,n);
	}
}
int find_max(int arr[], int index, int max_value){

	if(arr[0] > index ){ // arr[0] has the value of how many items are in the array.
		
		if(max_value < arr[index]){
			max_value = arr[index];
		}

		index++;	
		find_max(arr, index ,max_value);
	}
	else{
		return max_value;
	}
}
int sum_array(int arr[]){

	if(arr[499] < arr[0] ){// arr[499] is index number and arr[0] is item count in the array.

		arr[500] = arr[500] + arr[ arr[499] ]; // sum.
		arr[499]++; // index
		sum_array(arr);
	}
	else{
		return arr[500];
	}
}
double std_array(int arr[], double *mean, int n, int index){

	if( index < n && arr[499] == 0){ // If flag = 0 function will calcualte the mean value.

		arr[500] = arr[500] + arr[ index ]; // sum.
		index++; 
		std_array(arr, mean , n , index);
	}
	else{ // If flag is not 0 function will calculate the standard deviation by using the mean value.
		*mean = arr[500] / (float)(n);
		arr[499] = 1; // Flag.

		if(index > 1){
			arr[0] = arr[0] + (( (arr[index - 1] - *mean) * (arr[index - 1] - *mean) ) / n ) ;
			index--;
			std_array(arr, mean , n , index);

		}
		else{		
			 return sqrt(arr[0] - n + 1);
		}

	}
}
char *remove_duplicates(char *str){

	if(*str != '\0'){			// str pointer is leading to str[0] at the beginning.
		if(*str != *(str+1)){	// If I increment the adress, funciton will look at the next char.
			printf("%c",*str);
		}
		str++;
		remove_duplicates(str);
	}
}
void install_pipes(int visited[N][N] , int x, int y, int orientation){

	

	/*if(visited[x][y] == 1){	// The idea was filling the array with numbers 1,2,3,etc.
		visited[y+2][x+1] = 2;	// For example x and y are 0.
		visited[y+1][x+2] = 2;	// visited[y][x] = 1 and program would check o1,o2,o3 movement if is there any "2"s.
		install_pipes(visited, x+1 , y+2 , orientation);	// visited[y+2][x+1] was 2 and program would check again the around it
	}														// If is there any "3"s
	if(visited[x][y] == 2){			// So by keeping doing this all of the table would be scanned.
		visited[y+2][x-1] = 3;
		visited[y+2][x+1] = 3;
		visited[y+1][x+2] = 3;
		visited[y-1][x+2] = 3;
		visited[y-2][x+1] = 3;
		if(y == 2 && x == 1){

			install_pipes(visited, x+1 , y-1 , orientation);
		}
		if(y == 1 && x == 2){
			visited[y+1][x-2] = 3;
			install_pipes(visited, x , y-1 , orientation);
		}
	}

	if(visited[x][y] == 3){
		visited[y+1][x+2] = 4;
		visited[y+1][x-2] = 4;
		visited[y+2][x+1] = 4;
		if(x == 2 && y == 0){
			install_pipes(visited, x+1 , y+1 , orientation);
		}
	}*/
}