#include <stdio.h>

int sum(int n,int flag);
int mult(int n,int flag);

void main(){

	int number,selection,op;

	printf("Enter an integer: \n");
	scanf("%d",&number);

	printf("Please enter '0' for sum, '1' for multiplication\n" );
	scanf("%d",&selection);

	switch(selection){

		case 0: // Program's job if the selection is 0.

			printf("Please enter '0' to work on even numbers, '1' to work on odd numbers\n");
			scanf("%d",&op);
			if(op == 0 || op == 1){ // Program only accepts "0" and "1" here.Else, program will shut down.

				printf("= %d",sum(number,op));
			}
			else printf("Invalid value for odd/even selection.");
			break;

		case 1: // Program's job if the selection is 1.

			printf("Please enter '0' to work on even numbers, '1' to work on odd numbers\n");
			scanf("%d",&op);
			if(op == 0 || op == 1){ // Program only accepts "0" and "1" here.Else, program will shut down.
				printf("= %d",mult(number,op));
			}
			else printf("Invalid value for odd/even selection.");
			break;
			

		default: // Program will shut down if the operation that program asked for is not 0 or 1.
			printf("Please enter '0' to work on even numbers, '1' to work on odd numbers\n");
			scanf("%d",&op);
			printf("Unsported operation.");
			break;
	}
}
int sum(int n,int flag){

	int i ,sum,
	odd = 1, // Program will return 1 if the number is odd.
	even = 0; // Program will return 0 if the number is even.

	if(flag == even){ // If user wants to work on even numbers, program will accept it here.

		sum = 2; // I am printing the "2" here because I don't want "+" (pluses) at the beginning.
		printf("%d",sum);

		for(i = 4; i <= n ; i+=2 ){ // Since user wants to see summation of the even numbers,
			printf(" + %d ",i);     //      numbers must be increased by two each step.
			sum = sum + i ;
		}
		return sum; 
	}

	else if(flag == odd){ // If user wants to work on odd numbers, program will accept it here.

		sum = 1; // I am printing the "1" here because I don't want "+" (pluses) at the beginning.
		printf("%d",sum);

		for(i = 3; i <= n ; i +=2 ){ // Since user wants to see summation of the odd numbers,
			printf(" + %d",i);		 //      numbers must be increased by two each step.
			sum = sum + i;  // Numbers will be added again and again since the number is equal or greater than the wanted number.
		}
		return sum;
	}
}
int mult(int n,int flag){

	int i ,mult,
	odd = 1,
	even = 0;


	if(flag == even){ // If user wants to work on even numbers, program will accept it here.

		mult = 2; // I am printing the "2" here because I don't want "*" (multiplication sign) at the beginning.
		printf("%d",mult);

		for(i = 4; i <= n ; i+=2 ){
			printf(" * %d ",i);
			mult = mult * i ; // Numbers will be multiplied by each other again and again since the number is equal or greater than the wanted number.
		}
		return mult;
	}

	else if(flag == odd){ // If user wants to work on odd numbers, program will accept it here.

		mult = 1; // I am printing the "1" here because I don't want "*" (multiplication sign) at the beginning.
		printf("%d",mult);

		for(i = 3; i <= n ; i +=2 ){
			printf(" * %d",i);
			mult = mult * i; // Numbers will be multiplied by each other again and again since the number is equal or greater than the wanted number.
		}
		return mult;
	}
}