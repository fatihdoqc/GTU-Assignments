#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct node{
	int x;
	struct node *next;
};
struct diff{
	int n1,n2;
};

int *read_array(char *file_path,int *count);
float *stats_array(int *arr);
struct node *read_linkedlist( char *file_path , int *count);
float *stats_linkedlist();
struct diff *fix_the_diff();

int main(){

	int count1, count2 , *arr , choice ,index_counter ,i ;
	clock_t start,end;
	double t1 = 0.0 ,t2 = 0.0 , t3 = 0.0 , t4 = 0.0;
	float *results_a, *results_ll;

	struct diff *seperate_array;

	
	while(choice != 3){

		printf("Which one you want to execute ? Part1(1) or Part2(2) or none(3) ?\n");
		scanf("%d",&choice);

		switch(choice){
			case 2:
				seperate_array = fix_the_diff(&index_counter); // index counter keeps the number of different values for "for" loop.
				printf("Here is the different values:\n");
				
				for(i =0; i<index_counter; i++){
					printf("Number in array:%d\tand\tNumber in Linked List\t%d\n",seperate_array[i].n1 , seperate_array[i].n2);
				}
				
				break;
			case 1:
				start = clock();
				arr = read_array("list.txt",&count1);
				end = clock();
				t1 = t1 + (double)(end-start) / CLOCKS_PER_SEC;

				start = clock();
				read_linkedlist("list.txt",&count2);
				end = clock();
				t2 = t2 + (double)(end-start) / CLOCKS_PER_SEC;

				start = clock();
				read_linkedlist("list.txt",&count2);
				end = clock();
				t2 = t2 + (double)(end-start) / CLOCKS_PER_SEC;

				start = clock();
				arr = read_array("list.txt",&count1);
				end = clock();
				t1 = t1 + (double)(end-start) / CLOCKS_PER_SEC;

				start = clock();
				arr = read_array("list.txt",&count1);
				end = clock();
				t1 = t1 + (double)(end-start) / CLOCKS_PER_SEC;

				start = clock();
				read_linkedlist("list.txt",&count2);
				end = clock();
				t2 = t2 + (double)(end-start) / CLOCKS_PER_SEC;

				start = clock();
				read_linkedlist("list.txt",&count2);
				end = clock();
				t2 = t2 + (double)(end-start) / CLOCKS_PER_SEC;

				start = clock();
				arr = read_array("list.txt",&count1);
				end = clock();
				t1 = t1 + (double)(end-start) / CLOCKS_PER_SEC;

				start = clock();
				results_a = stats_array(arr);
				end = clock();
				t3 = t3 + (double)(end-start) / CLOCKS_PER_SEC;

				start = clock();
				results_ll = stats_linkedlist();
				end = clock();
				t4 = t4 + (double)(end-start) / CLOCKS_PER_SEC;

				start = clock();
				results_ll = stats_linkedlist();
				end = clock();
				t4 = t4 + (double)(end-start) / CLOCKS_PER_SEC;

				start = clock();
				results_a = stats_array(arr);
				end = clock();
				t3 = t3 + (double)(end-start) / CLOCKS_PER_SEC;

				start = clock();
				results_a = stats_array(arr);
				end = clock();
				t3 = t3 + (double)(end-start) / CLOCKS_PER_SEC;

				start = clock();
				results_a = stats_array(arr);
				end = clock();
				t3 = t3 + (double)(end-start) / CLOCKS_PER_SEC;

				start = clock();
				results_ll = stats_linkedlist();
				end = clock();
				t4 = t4 + (double)(end-start) / CLOCKS_PER_SEC;

				start = clock();
				results_ll = stats_linkedlist();
				end = clock();
				t4 = t4 + (double)(end-start) / CLOCKS_PER_SEC;


				t1 = t1 / 4; // Average of the time taken for each function.
				t2 = t2 / 4;
				t3 = t3 / 4;
				t4 = t4 / 4;
				printf("For array: Min 		Max 	    Mean 	 StdDev		ByteUsed\n");
				printf("	   %.2f 	%.2f   %.2f    %.2f 	%d\n\n",results_a[1] , results_a[0] , results_a[2] , results_a[3] , count2 * 4);
				printf("Time needed for (read_array)	: 	%f\n",t1);
				printf("Time needed for (stats_array)	:	%f\n\n",t3);
				printf("For linked list: Min 	Max    		 Mean 	 	StdDev		ByteUsed\n");
				printf("	  	 %.2f 	%.2f  	 %.2f 	%.2f 	%d\n\n",results_ll[1] , results_ll[0] , results_ll[2] , results_ll[3] , count1 * 8);
				printf("Time needed for (read_linkedlist)	: 	%f\n",t2);
				printf("Time needed for (stats_linkedlist)	:	%f\n",t4);
				break;
			default:
				printf("Exiting...\n");
				return 0;
		}
	}

	
	

	
}
int *read_array(char *file_path , int *count){

	int *arr, i = 0;
	FILE *fp = fopen(file_path,"r");

	arr= malloc(1 * sizeof(int));
	fscanf(fp, "%d,", &arr[i] );
	i++;
	arr = realloc(arr , i * sizeof(int));

	while(fscanf(fp, "%d,", &arr[i] ) != EOF){
		
		i++; 
		arr = realloc(arr , (i +1) * sizeof(int)); // Allocating current index + 1 size to scan the next 

	}
	arr[i] = -1;
	*count = i;
	return (arr); 	
}
float *stats_array(int *arr){

	int i = 0, max = arr[i], min = arr[i] ;
	float *results ,  sum = 0 ,var = 0;

	results = malloc(4 * sizeof(float));

	while(arr[i] != -1){

		sum = sum + arr[i];

		if(max < arr[i]){
			max = arr[i];
		}
		else if(min > arr[i]){
			min = arr[i];
		}
		i++;
	}
	results[0] = max;
	results[1] = min;
	results[2] = sum / i; // mean

	i = 0;
	while(arr[i] != -1){
		var = var + ( (results[2] - arr[i]) * (results[2] - arr[i]) );
		i++;
	}

	results[3] = sqrt(var / i); // standard deviation
	return results;
}
struct node *read_linkedlist( char *file_path , int *count){

	FILE *fp = fopen(file_path, "r");
	struct node *root , *iter;
	int holder;
	*count = 1;
	root = malloc(sizeof(struct node));
	iter = root;

	fscanf(fp, "%d,", &holder);

	while(1){
		iter->x = holder;
				
		if(fscanf(fp, "%d,", &holder) == EOF){ // In my code I always allocate memory for the next linked list.
			break;	// Needed to prevent the last one's next.
		}
		iter->next = malloc(sizeof(struct node));
		iter = iter->next; // moving the iteration pointer.
		(*count)++;
	}
	
	return root;
}
float *stats_linkedlist(){

	struct node *root ,*ptr;
	float *results , var = 0.0;
	int count = 1;
	root = read_linkedlist("list.txt",&count);

	results = malloc(4 * sizeof(float));

	ptr = root;
	results[0] = ptr->x; //max
	results[1] = ptr->x; //min
	results[2] = 0.0;

	while(ptr != NULL){

		if(results[0] < ptr->x){
			results[0] = ptr->x;
		}
		else if(results[1] > ptr->x){
			results[1] = ptr->x;
		}

		results[2] = results[2] + ptr->x; //sum
		ptr = ptr->next;
	}
	results[2] = results[2] / count; //mean

	ptr = root;
	while(ptr != NULL){
		var = var + ( (results[2] - ptr->x) * (results[2] - ptr->x) );
		ptr = ptr->next;
	}
	results[3] = sqrt(var / count);//std dev

	return results;
}
struct diff *fix_the_diff( int *diff_index_counter){

	int i , *arr , length ,j = 0;
	*diff_index_counter = 0;

	struct node *root ,*iter;
	struct diff *diff_arr; // this array will be returned.
	
	diff_arr = malloc(sizeof(struct diff));	
	root = malloc(sizeof(struct node));
	iter = root;

	printf("Array's length: ");
	scanf("%d",&length);
	arr = malloc(length * sizeof(int));
	printf("Fill the array please\n");

	for(i = 0; i<length; i++){
		printf("%dth index: ",i);
		scanf("%d",&arr[i]);
	}
	printf("\nPlease fill the linked list now\n");
	
	for(i = 0; i<length; i++){
		printf("%dth index: ",i);
		scanf("%d",&iter->x);

		if(i != length - 1){ // Length - 1 is the last one.
			iter->next = malloc(sizeof(struct node)); // Preventing last one's next.
			iter = iter->next;
		}
	}

	iter = root;

	for( i = 0; i<length; i++){
		if(arr[i] != iter->x){
			diff_arr[*diff_index_counter].n1 = arr[i];
			diff_arr[*diff_index_counter].n2 = iter->x;
			(*diff_index_counter)++;		
			
			diff_arr = realloc( diff_arr , ((*diff_index_counter) + 1) * sizeof(struct diff));	
		}
		iter = iter->next;
	}

	return diff_arr;
}