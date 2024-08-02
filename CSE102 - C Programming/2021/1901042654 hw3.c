#include <stdio.h>

void calculate_fibonacci_sequence();
int is_Harmonic(int x);
int is_Perfect(int x);
void difference_max_min ();
void decide_perfect_harmonic_number();
void bmi_calculation ();

void main(){

	calculate_fibonacci_sequence();
	decide_perfect_harmonic_number();
	difference_max_min();
	bmi_calculation();
}

void calculate_fibonacci_sequence(){

	int a = 0,  /* First term. */
		b = 1 ,	/* Second term.*/
		c ,		/* Third term. */
		input = 9999999; /* Thıs variable is like a flag. If it is still 9999999 , then it is untouched.*/

	char bad_input;

	printf("Please enter term(s) number : ");

	scanf("%d",&input);
	bad_input = getchar();

	while(bad_input != '*'){		

		if(input == 9999999){ /* Flag */
			printf("Please enter “numeric” term(s) number: \n");
		}
		else if(input < 1){
			printf("Please enter “positive” term(s) number: \n");	
		}
		else{
			a = 0; b = 1;

			printf("Fibonacci Sequence: \n");

			printf("1\n");

			for(int i = 1; i< input ; i++){

				c = a + b; /* Every next term is the sum of last two ones. */
				printf("%d\n",c);

				a = b; /* Shifting the term holders. */
				b = c;
			}
		}

		input = 9999999;

		printf("Please enter term(s) number : ");

		scanf("%d",&input);
		bad_input = getchar();
	}
	


}
void decide_perfect_harmonic_number(){
	int input = 9999999;
	char bad_input;

	printf("\nPerfect , harmonic number\n");
	printf("\nPlease enter input number: ");

	scanf("%d",&input);
	bad_input = getchar();

	while(bad_input != '*'){

		if(input == 9999999){ /* error check */
			printf("Please enter “numeric” term(s) number: \n");
		}
		else if(input < 1){
			printf("Please enter “positive” term(s) number: \n");	
		}
		else{

			if(is_Perfect(input)){
				printf("\nIs Perfect Number? : Yes \n");
			}
			else{
				printf("\nIs Perfect Number? : No \n");
			}
			if(is_Harmonic(input)){
				printf("Is Harmonic Divisor Number? : Yes\n");
			}
			else{
				printf("Is Harmonic Divisor Number? : No\n");	
			}
		}

		input = 9999999;
			
		printf("\nPlease enter input number: ");

		scanf("%d",&input);
		bad_input = getchar();
		
	}
}
int is_Perfect(int x){

	int sum = 0;

	printf("Natural number divisors: ");

	for(int i = 1; i<x; i++){
		if( x % i == 0 ){ /* Finding the divisors. */
			printf("%d, ", i);
			sum += i;
		}
	}
	printf("%d\n", x);
	if( sum == x ){
		return 1;
	}
	else{
		return 0;
	}

}
int is_Harmonic(int x){
	int counter = 0;
	double result , sum = 0;

	for(int i = 1; i<=x; i++){
		if( x % i == 0 ){
			counter++;		/* Divisor part.	*/
			sum += 1.0/i; 	/* Fraction part. 	*/
		}
	}
	result = counter / sum;

	if(result - (int)result == 0){
		return 1;
	}
	else{
		return 0;
	}
}
void difference_max_min (){

	float x , min = 9999999, max = -9999999;
	int i;

	printf("\nDifference max min:\n\n");
	printf("\nPlease enter 5 number: ");

	for(i = 0; i<5; i++){
		scanf("%f",&x); /* x is the input. */

		if(x < min){
			min = x;
		}
		if(x > max){
			max = x;
		}
	}

	if(max - (int)max == 0){ 	/* Checking if the number is integer. */
		printf("\nMaximum number is %d\n", (int)max );
	}
	else{
		printf("\nMaximum number is %.2f\n", max);
	}

	if(min - (int)min != 0){	/* Checking if the number is integer. */
		printf("Minimum number is %.2f\n", min);
	}
	else{
		printf("Minimum number is %d\n", (int)min );
	}

	printf("Difference between maximum and minimum is %.2f\n", max - min);

}
void bmi_calculation (){

	float weight , height , bmi;

	printf("Please enter weight(kg) : ");
	scanf("%f",&weight);

	printf("Please enter height(m) : ");
	scanf("%f",&height);

	printf("Your category is ");

	bmi = weight / (height * height);

	if(bmi < 16.0){
		printf("Severely Underweight\n");
	}
	else if(bmi < 18.40){
		printf("Underweight\n");
	}
	else if(bmi < 24.90){
		printf("Normal\n");
	}
	else if(bmi < 29.9){
		printf("Overweight\n");
	}
	else if(bmi > 29.9){
		printf("Obese\n");
	}
}