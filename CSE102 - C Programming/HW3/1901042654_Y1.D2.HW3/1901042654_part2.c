#include <stdio.h>

int isprime(int a);

void main(){

	int num,i;

	printf("Please enter an integer : ");
	scanf("%d",&num);


	for(i = 2; i<=num ; i++){

		if(isprime(i)){ // If the number is prime, program will print it here.
			printf("\n%d is a prime number.\n",i);
		}
		
	}
		
}
int isprime(int a){

	int i,
	not_prime = 0,
	prime = 1;

	for(i = 2;i < a ; i++){

		if( a % i == 0){ // If the number is dividible by any number,program will print the number and is divisor.

			printf("\n%d is not a prime number.It is dividible by %d\n",a,i);
			return not_prime; // Program will return 0 if the number is not prime.
		}
	}
	return prime; // Program will return 1 if the number is not prime.
}