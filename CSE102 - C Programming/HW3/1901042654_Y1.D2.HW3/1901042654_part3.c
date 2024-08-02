#include <stdio.h>
int length_checker(int num);
int binary_checker(int,int);
int andop(int,int);

int main(){

	int first,second;

	while(1){
		printf("First integer : ");
		scanf("%d",&first);
		printf("Second integer : ");
		scanf("%d",&second);

		int length1 = length_checker(first), // Program will get the lengths of numbers.
		length2 = length_checker(second);

		if(length1 == length2){ /* If lengths are not equal to each other,
								 Program will print an error message and ask user for new integers.*/

			if(binary_checker(first,second) == 1){ // Program is checking if the numbers are binary.If yes, then program will let the numbers in.
			
				printf("\n%d AND %d = %d",first,second,andop(first,second)); // Program will print: "first number" AND "second number" = "RESULT"
				return 0;													 // andop() function returns the result.
			}
			else{
				printf("Integers should be binary. Please enter 2 new integers.\n");
			}
		}
		else 
		{
			printf("Integers should have the same length. Please enter 2 new integers.\n");
			
		}
	}
}
int length_checker(int num){

	int length = 1;

	while(num > 9){ // Program divides the number by 10 and checks the integer part of the number
					// And increases the number of digits (length) by one until the number is lesser than 10.
		++length;
		num = num / 10;

	}
	return length; // Then returns the length.
}
int binary_checker(int num1,int num2){
		
	while(num1 > 0){ //To check all digits I am taking the mod of the number with 10 and dividing it by 10 to get the next digit until there is no digit left.

		if(num1 % 10 > 1 || num2 % 10 > 1){ // Since the binary numbers can only include 0 or 1 ,ry.
			return 0;						// If any digit of the number is greater than 1, then the number is not binary.
		}
		num1 = num1 / 10;	// Since the program is checking the integer parts, I only need to divide the number by ten. ( 12345 / 10 = 1234.5 )
		num2 = num2 / 10;
	}
	return 1;
}

int andop(int a,int b){

	int count = 1,
	final = 0;

	while( a > 0){ /* To check all digits I am taking the mod of the number with 10 and dividing it by 10 to get the next digit until there is no digit left.
		And I am keeping implementing the and operation*/

		if(a % 10 == 1 && b % 10 == 1){ // The and operation will return 0 if any or both of the numbers is 0. So I only need to check the "1" ones

			final = final + 1 * count; // To work on the binary numbers, I need to count digits and find the numbers at their proper places.
		}

		a = a / 10;
		b = b / 10;

		count *= 10; // To get the digits and work on the number as binary, I need to count the digits.


	}
	return final;
}