#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void menu();
void decrypt_and_print(char* file_path);
char decrypt_numbers(int number);
void deep_decrypt_and_print(char* file_path);
void track_machine();
void refresh_position(int* x, int* y , double *R, double *D);
void encrypt_messages(char *file_path);
int  encrypter(char symbol);

void main(){

	menu();
}
void menu(){
	
	int choice;
	while(choice != 5){
		printf("\n1) Decrypt and print encrypted_p1.img\n");
		printf("2) Decrypt and print encrypted_p2.img\n");
		printf("3) Switch on the tracking machine.\n");
		printf("4) Encrypt the message.\n");
		printf("5) Switch off\n\n");
		printf("Please make your choice:  ");

		scanf("%d",&choice);

		switch(choice){
			case 1:
				decrypt_and_print("encrypted_p1.img");
				break;
			case 2:
				deep_decrypt_and_print("encrypted_p2.img");
				break;
			case 3:
				track_machine();
				break;
			case 4:
				encrypt_messages("decrypted_p4.img");
				break;
			default:
				printf("Unknown command.\n");
				break;
		}
	}
}
//------------------OOOOOOOOOOOOOOOOO PART_1 OOOOOOOOOOOOOOOOO---------------------
void decrypt_and_print(char* file_path){

	FILE *fp = fopen(file_path,"r");
	char c;
	int num;

	while(!feof(fp)){

		fscanf(fp,"%c", &c); // Program is reading the next char.

		if(c == '\n'){		 // And if it is end of the line, program will skip a line.
			printf("\n");
		}
		else{
			
			num = c - '0'; // I did typecasting here,since C language acts according to ASCII table, I should substract the zero.
						   // At ASCII 0 is 48, 1 is 49, 9 is 57. If I substract 48 from 57, it gives me 9 as I wanted to be.	

			printf("%c",decrypt_numbers(num));// The funciton that changes the numbers to characters.
		}
	}

	fclose(fp);

}
char decrypt_numbers(int number){


	switch(number){

		case 0:	
			return ' ';
		case 1:	
			return '-';
		case 2:	
			return '_';
		case 3:	
			return '|';
		case 4:	
			return '/';
		case 5:	
			return '\\';
		case 6:	
			return 'O';
		default:
			return ' ';
	}
}
//------------------OOOOOOOOOOOOOOOOO PART_1 OOOOOOOOOOOOOOOOO---------------------

//------------------OOOOOOOOOOOOOOOOO PART_2 OOOOOOOOOOOOOOOOO---------------------
void deep_decrypt_and_print(char* file_path){

	FILE *fp = fopen(file_path,"r");
	char c1,c2,c3;
	int num,i;

	fscanf(fp,"%c", &c1); // I need to scan first 3 characater.To reach the third character.
	fscanf(fp,"%c", &c2);
	fscanf(fp,"%c", &c3); // I got it here.

	printf("   ");
	while(!feof(fp)){

		if(c3 == '\n'){ // if it is end of the line, program will skip a line.
			printf("\n");
		}

		num = ( (c1 - '0') + (c2 - '0') + (c3 - '0') ) % 7; // Program is calculating the number according to formula.

		printf("%c",decrypt_numbers(num)); // Program turns the numbers to character.

		c1 = c2; // To move once and not losing the numbers that left behind. 
		c2 = c3; // first char must be equal to the second and second char must be equal to the third.
		fscanf(fp,"%c", &c3); // Now I can scan the next char.


	}
	fclose(fp);
}
//------------------OOOOOOOOOOOOOOOOO PART_2 OOOOOOOOOOOOOOOOO---------------------

//------------------OOOOOOOOOOOOOOOOO PART_3 OOOOOOOOOOOOOOOOO---------------------
void track_machine(){

	int i,j,check = 0,tempx = 0,tempy = 0,
	x = rand() % 12, // Getting two number between [0,12]
	y = rand() % 12;
	while(x == 0 || y == 0){ // But I don't want "0". So if it shows up as "0", just re-roll.
		x = rand() % 12;
		y = rand() % 12;
	}

	char select;
	
	double disp = sqrt( ((x-tempx) * (x-tempx)) + ((y-tempy) * (y-tempy)) ), // I need an integer that saves the position of enemies.
	dist_to_camp = sqrt( ( (6-x) * (6-x) ) + ( (y-6) * (y-6) ) );	// When the enemy changes their positions. I can calculate the displacement
																	 // By the position I saved before.
	tempx = x, // Saving the current positions.
	tempy = y;
	while(check == 0){
		printf("\n");
		for(i = 1;i<12;i++){
			for(j = 1; j<12 ; j++){
				if(i == x && j == y){ 
					printf("E 	");
				}
				else if(i == 6 && j == 6){ // We are at (6,6)
					printf("O 	");
				}
				else{
					printf("-	");
				}
			}
			printf("\n");
		}
		printf("Enemies X position: %d , Y position: %d, Displacement: %.2f,Distance to our camp: %.2f\n",x,y,disp,dist_to_camp);
		printf("Command is waiting...: ");
		scanf("%c",&select); // Taking the selection.

		switch(select){
			case 'r': // If the user selects refreshing the position,
				refresh_position(&x,&y,&disp,&dist_to_camp); // I refresh.
				check = 0;
				scanf("%c",&select);
				break;
			case 'R':
				refresh_position(&x,&y,&disp,&dist_to_camp);
				check = 0;
				scanf("%c",&select);
				break;
			case 'e': // e or E stand for "exit".
				check = 2;
				break;
			case 'E':
				check = 2;
				break;
			default:
				printf("Unknown command.\n");
				check = 2;
				break;

		}
	}	
}
void refresh_position(int *x, int *y ,double *R, double *D){

	int tempx,tempy;
	tempx = *x; // Taking the positions to the temporary variable to calculate displacement later.
	tempy = *y;
	*x = rand() % 12;
	*y = rand() % 12;

	while(*x == 0 || *y == 0){
		*x = rand() % 12;
		*y = rand() % 12;
	}

	*R = sqrt( ((*x-tempx) * (*x-tempx)) + ((*y-tempy) * (*y-tempy)) );
	*D = sqrt( ( (6- *x) * (6- *x) ) + ( (*y - 6) * (*y - 6)) ); // Enemies's distance to our camp.

}
//------------------OOOOOOOOOOOOOOOOO PART_3 OOOOOOOOOOOOOOOOO---------------------

//------------------OOOOOOOOOOOOOOOOO PART_4 OOOOOOOOOOOOOOOOO---------------------
void encrypt_messages(char *file_path){

	FILE *f_de = fopen(file_path,"r");
	FILE *f_en = fopen("encrypted_p4.img","w");
	char c1,c2,c3;
	int num,temp1,temp2,temp3;
	fscanf(f_de ,"%c",&c3);
	temp1 = 0; // According to teacher, if I am at the beginning of the line I will assume the other numbers are zero.
	temp2 = 0;

	while(!feof(f_de)){

		if(c3 == '\n'){ // If the program is at the end of the line.
			fprintf(f_en, "\n"); // just skip a line.
			temp1 = 0;
			temp2 = 0; 
		}

		else{ 
			temp3 = encrypter(c3);

			num = (temp1 + temp2 + temp3) % 7; // Formula.
			fprintf(f_en, "%d", num );
			temp1 = temp2; // Saving the numbers that will left behind when program scans the next character.
			temp2 = temp3;

			fscanf(f_de ,"%c",&c3);

		}		
	}
	printf("\n File succesfully created. \n"); // If the program got so far. That means file succesfully created.
	fclose(f_de);
	fclose(f_en);
}
int encrypter(char symbol){

	switch(symbol){

		case ' ':
			return 0;
		case '-':
			return 1;
		case '_':
			return 2;
		case '|':
			return 3;
		case '/':
			return 4;
		case '\\':
			return 5;
		case 'O':
			return 6;
		default:
			return 0;
		
	}

}
//------------------OOOOOOOOOOOOOOOOO PART_4 OOOOOOOOOOOOOOOOO---------------------