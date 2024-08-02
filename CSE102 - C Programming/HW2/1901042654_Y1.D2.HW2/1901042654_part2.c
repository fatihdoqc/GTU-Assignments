#include <stdio.h>
#include <math.h>

int number_length(int);
int find_digit(int number,int index);

void main(){
	int number,index;
	printf("Enter a number (maximum 6 digits): \n");
	scanf("%d",&number);

	if(number_length(number) != 0){ 
		printf("Your number has %d digits",number_length(number));
	}
	else{
		printf("Max digits should be 6 !");
	}
	printf("\nWhen your number written 100 times next to each other, which digit of this number would you like to see? : \n");
	scanf("%d",&index);
	if(index > number_length(number) * 100){ 
		// IF the user's input is greater than the maximum possible digit,program will print an error message.
		printf("Error, max index must be : %d" , number_length(number) * 100);
	}
	else{
		printf("%dth digit of the big number sequence : %d\n",index ,find_digit(number,index));
	}	
}
int find_digit(int number,int index){

	int length = number_length(number);
	int digit = index % length; // number ≡ X (mod number_length)

	switch(digit){ // Let the number is 123456 for example.
		case 1:
			return (int)(number / pow(10,length -1)) % 10; // IF you want to find the first digit; 123456/ 10^(6-1) = 1
		case 2: 
			return (int)(number / pow(10,length -2)) % 10; // For the second digit ; 123456 / 10^(6-2) = 12 then take the (mod 10)
		case 3: 										   // == 2
			return (int)(number / pow(10,length -3)) % 10;
		case 4: 
			return (int)(number / pow(10,length -4)) % 10;
		case 5: 
			return (int)(number / pow(10,length -5)) % 10;
		case 0:
			return number % 10; // Here you don't need to do the math. Just take the number's mod for 10 and it will give you the last digit.
	}
	
}



int number_length(int number){
		
	/* Function works like this: Since C language deletes the after dot parts of an integer
	If your number is 4567 when you divide it by 10 , C will return to you 456. Not 456,7 
	So basicly function checks the number by dividing by 10 since there is nothing left to divide ( 0 )*/


	if(number / 10 > 0){
		number = number/10;

		if(number / 10 > 0){
			number = number/10;

			if(number / 10 > 0){
				number = number/10;

				if(number / 10 > 0){
					number = number/10;

					if(number / 10 > 0){
						number = number/10;

						if(number / 10 > 0){
							number = number/10;
							
							return 0;
						}
						else{
							return 6;
						}
		
					}
					else{
						return 5;
					}
					
				}
				else{
					return 4;
				}

		
				}
			else{
				return 3;
			}
		}
		else{
		return 2;
		}
	}
	else{
		return 1;
	}
}

