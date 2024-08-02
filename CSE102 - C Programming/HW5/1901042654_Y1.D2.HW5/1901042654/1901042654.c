#include <stdio.h>

void read_news(char buffer[500], char file_path[10] , int is_Only_title);
void menu();
void append_file(char *file_path , char c);
void read_magic_numbers(char buffer_magic[10] , char buffer_news[500]);
double f_func(int x);
double g_func(double f(int x) , int a );


void main(){

	menu();	

}
void menu(){

	int a=0 ,which_new,check,i,count;
	double sum = 0.0;
	char c,choice,select,magics[10],buffer[500];

	FILE *base;

	/* Continous menu */ 
	while(choice != 'n'){
		printf("************Daily Press**************\n\n");
		printf("Today's news are listed for you : \n\n");
		printf("Title of 1. new: ");

		a=0; // I need to do that everytime to get the first index.
		read_news(buffer , "news/1.txt" , 1); // Taking the title to buffer if the last parameter is 1.
		while(buffer[a] != '\0'){
			printf("%c",buffer[a]);
			a++;
		}

		printf("\nTitle of 2. new: ");
		read_news(buffer , "news/2.txt" , 1);
		a=0;
		while(buffer[a] != '\0'){
			printf("%c",buffer[a]);
			a++;
		}

		printf("\nTitle of 3. new: ");
		read_news(buffer , "news/3.txt" , 1);
		a=0;
		while(buffer[a] != '\0'){
			printf("%c",buffer[a]);
			a++;
		}

		printf("\nTitle of 4. new: ");
		read_news(buffer , "news/4.txt" , 1);
		a=0;
		while(buffer[a] != '\0'){
			printf("%c",buffer[a]);
			a++;
		}

		printf("\n\nWhat do you want to do?\n\n");

		printf("a.Read a new\n");
		printf("b.List the readed news\n");
		printf("c.Get decrypted information from the news\n");

		scanf(" %c",&choice);

		switch(choice){

			case 'a':
				printf("Which new you want to display ? : ");
				scanf("%d",&which_new);

				switch(which_new){

					case 1:
					
						base = fopen("CSE102-HW5/readed_news_id.txt","r");

						while(!feof(base)){			 // Scanning the data base,
							fscanf(base , "%c", &c); // To check if is there any '1', because when you read the first new
													 // Program prints '1' to database if there isn't one.
							if(c == '1'){	// If there is '1' in database,it means the new readed before.		 
												
								printf("This new is readed, would you like to read it again? Yes(y) / No(n) : ");
								scanf(" %c", &choice);


								if(choice == 'y'){ 
									read_news(buffer , "news/1.txt" , 0);
									printf("%s", buffer);
									break;
								}
								else{
									break;
								}
							}
						}
						if(c != '1'){	// Program scanned the entire database above for the first new,
									 	// c is the last scanned character from database.
										// If c is '1' program handles it above and if not,
									 	// That means the user will read the new for the first time.
							read_news(buffer , "news/1.txt" , 0);
							printf("%s", buffer);
							append_file("CSE102-HW5/readed_news_id.txt",'1'); // Adding database '1' because the new is readed.
							break;
						}
						fclose(base);
						break;


					case 2:
						base = fopen("CSE102-HW5/readed_news_id.txt","r");

						while(!feof(base)){	// Program scanned the entire database for the second new.
											// And did exactly what is done at first new,because I used ctrl+c,ctrl+v
							fscanf(base , "%c", &c);
							if(c == '2'){

								printf("This new is readed, would you like to read it again? Yes(y) / No(n) : ");
								scanf(" %c", &choice);

								if(choice == 'y'){
									read_news(buffer , "news/2.txt" , 0);
									printf("%s", buffer);
									break;
								}
								else{
									break;
								}
							}
						}
						if(c != '2'){
							read_news(buffer , "news/2.txt" , 0);
							printf("%s", buffer);
							append_file("CSE102-HW5/readed_news_id.txt",'2');
							break;
						}
						fclose(base);
						break;
					case 3:
						base = fopen("CSE102-HW5/readed_news_id.txt","r");

						while(!feof(base)){ // Program scanned the entire database for the third new.
											// And did exactly what is done at first new,because I used ctrl+c,ctrl+v
							fscanf(base , "%c", &c);
							if(c == '3'){

								printf("This new is readed, would you like to read it again? Yes(y) / No(n) : ");
								scanf(" %c", &choice);

								if(choice == 'y'){
									read_news(buffer , "news/3.txt" , 0);
									printf("%s", buffer);
									break;
								}
								else{
									break;
								}
							}
						}
						if(c != '3'){
							read_news(buffer , "news/3.txt" , 0);
							printf("%s", buffer);
							append_file("CSE102-HW5/readed_news_id.txt",'3');
							break;
						}
						fclose(base);
						break;
					case 4:
						base = fopen("CSE102-HW5/readed_news_id.txt","r");

						while(!feof(base)){	// Program scanned the entire database for the second new.
											// And did exactly what is done at first new,because I used ctrl+c,ctrl+v
							fscanf(base , "%c", &c);
							if(c == '4'){

								printf("This new is readed, would you like to read it again? Yes(y) / No(n) : ");
								scanf(" %c", &choice);

								if(choice == 'y'){
									read_news(buffer , "news/4.txt" , 0);
									printf("%s", buffer);
									break;
								}
								else{
									break;
								}
							}
						}
						if(c != '4'){
							read_news(buffer , "news/4.txt" , 0);
							printf("%s", buffer);
							append_file("CSE102-HW5/readed_news_id.txt",'4');
							break;
						}
						fclose(base);
						break;
				}
				break;
				case 'b':
					printf("Readed news are listed below;\n");
					base = fopen("CSE102-HW5/readed_news_id.txt","r");
					fscanf(base , " %c", &c);
					while(!feof(base)){	// Scanning database and printing it because user wanted to see
										// What is inside the database which means readed news.
						
						printf("%c. new is readed.\n",c);
						fscanf(base , " %c", &c);
					}
					break;
				case 'c':
					printf("Which new would you like to decrypt?: ");
					scanf("%d",&which_new);
					switch(which_new){
						case 1:
							read_news(buffer , "news/1.txt" , 0);	// Taking the new character by character to buffer.
							printf("%s",buffer);
							read_magic_numbers(magics , buffer);	// Decrypting the buffer which has the new inside of it.
							sum = 0;
							count = 0;
							
							while(magics[count] != '\0'){	// Formula should be done for the number of magic numbers times
															// And I put '\0' at the end of the numbers.
															// While loop should be done as long as there is a magic number.			
								sum = sum + g_func(f_func , magics[count]);							
								count++;
							}
							printf("\nExpected number of sick people: %.2f",sum);
							break;
						case 2:
							read_news(buffer , "news/2.txt" , 0);
							printf("%s",buffer);
							read_magic_numbers(magics , buffer);
							sum = 0;
							count = 0;
							
							while(magics[count] != '\0'){	
								sum = sum + g_func(f_func , magics[count]);							
								count++;
							}
							printf("\nExpected number of sick people: %.2f",sum);
							break;
						case 3:
							read_news(buffer , "news/3.txt" , 0);
							printf("%s",buffer);
							read_magic_numbers(magics , buffer);
							sum = 0;
							count = 0;
							
							while(magics[count] != '\0'){	
								sum = sum + g_func(f_func , magics[count]);							
								count++;
							}
							printf("\nExpected number of sick people: %.2f",sum);
							break;
						case 4:
							read_news(buffer , "news/4.txt" , 0);
							printf("%s",buffer);
							read_magic_numbers(magics , buffer);
							sum = 0;
							count = 0;
							
							while(magics[count] != '\0'){	
								sum = sum + g_func(f_func , magics[count]);							
								count++;
							}
							printf("\nExpected number of sick people: %.2f",sum);
							break;
				}
			}
			printf("\nDo you want to continue ? Yes(y)/No(n) : ");
			scanf(" %c",&choice);
			if(choice == 'n'){
				printf("\nGood Bye.\n");
			}
		}

		
}
void read_news(char buffer[500], char file_path[10] , int is_Only_title){

	char c;
	int count = 0;

	FILE *fp = fopen(file_path,"r");

	/* Reading only the title*/
	if(is_Only_title == 1){ 
		while(c != '\n'){	// Title is the first line of the file.So program reads until the end of the first line.
			fscanf(fp , "%c" , &c);
			if(c == '\n'){	// It prevents the reading one more time when the program reached the end of the line.
				break;
			}
			buffer[count] = c;
			count++;
		}
		buffer[count] = '\0'; // Program puts '\0' to end of the new to avoid printing irrelevant things.Believe me, it prints.
	}
	/* Reading the all of it. */ 
	else{
		count = 0;

		while(!feof(fp)){

			fscanf(fp, "%c" , &c);

			
			buffer[count] = c;
			count++;
			
			
		}
		buffer[count] = '\0';
	}
}
void append_file(char *file_path , char c){ // The function that provides me the talent which is printing something to database.

	FILE *base = fopen("CSE102-HW5/readed_news_id.txt","a");

	fprintf(base , "%c" , c);
	fclose(base);
	
}
void read_magic_numbers(char buffer_magic[10] , char buffer_news[500]){

	int a = 0,count=0,i;

	while(buffer_news[a] != '\0'){

		
		if(buffer_news[a] == '#'){ // After the '#' character,my magic numbers are lying down.
			
			buffer_magic[count] = buffer_news[a+1] - '0'; // And I am basicly taking them to magic buffer.
			count++;

		}
		a++;
	}
	buffer_magic[count] = '\0';
	
}
double f_func(int x){

	return (x*x*x) - (x*x) + 2;
}
double g_func(double f(int x) , int a ){

	return f(a) * f(a);
}