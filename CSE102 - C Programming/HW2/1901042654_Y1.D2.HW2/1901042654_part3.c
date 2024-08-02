#include <stdio.h>

void main(){

	float amount;
	int currency,convert;

	printf("*********Welcome to ABC Exchange Office*********\n\n");
	printf("Enter your amount:\n");
	scanf("%f",&amount);

	printf("Please select your currency:\n");
	printf("1. Turkish Lira\n2. Euro\n3. Dollar\n");
	scanf("%d",&currency);

	switch(currency){ // Taking the information from the user about the money's currency.

		case 1: // Turkish Liras
			printf("You have %f Turkish Liras\n\n",amount);
			printf("Choose which currency you want to convert:\n"); 
			// Taking the information from the user about what currency he/she wants to convert the money.
			scanf("%d",&convert);

			switch(convert){
				case 2: // IF euro.
					printf("You have %f Euros",amount/6.69);
					break;

				case 3: //IF dollars
					printf("You have %f Dollars",amount/6.14);
					break;
				default:
					printf("Your choice is invalid.");
			}
			break;
		case 2: // Euros
			printf("You have %f Euros\n\n",amount);
			printf("Choose which currency you want to convert:\n");
			// Taking the information from the user about what currency he/she wants to convert the money.
			scanf("%d",&convert);

			switch(convert){
				case 1: // If TUrkish Liras
					printf("You have %f Turkish Liras",amount * 6.69);
					break;

				case 3: // If DOllars
					printf("You have %f Dollars",amount * 1.09);
					break;
				default:
					printf("Your choice is invalid.");
			}
			break;
		case 3: // Dollars

			printf("You have %f Dollars\n\n",amount);
			printf("Choose which currency you want to convert:\n");
			// Taking the information from the user about what currency he/she wants to convert the money.
			scanf("%d",&convert);

			switch(convert){
				case 2: // If Euros
					printf("You have %f Euros",amount/1.09);
					break;

				case 1: // If Turkish Liras
					printf("You have %f Turkish Liras",amount * 6.14);
					break;
				default:
					printf("Your choice is invalid.");
			}

			break;
		default:
			printf("Your choice is invalid.");
			break;
	}
	



}