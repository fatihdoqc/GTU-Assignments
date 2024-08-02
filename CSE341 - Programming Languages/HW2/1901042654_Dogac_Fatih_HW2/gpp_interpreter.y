%{

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "structs.h"

int yylex();
void yyerror (char *s);

int power_of(int a , int b);
int_list* add_to_intList(int_list* list , char *name , int val);
int get_val_int(char* name);
void print_list(int_list* list);
int set_val_int(char* name , int val);

int_list* int_head = NULL;
double_list* double_head = NULL;


%}

/*and, or, not, equal, less, nil, list, append, concat,
set, deffun, for, if, exit, load, disp, true, false*/

%union {
	int 	i_val;
	char* str;
	int_list* int_lst;
	double_list* double_lst;

}
%token COMMENT KW_AND KW_OR KW_NOT KW_EQUAL KW_LESS
%token KW_NIL KW_LIST KW_APPEND KW_CONCAT KW_SET
%token KW_DEFFUN KW_FOR KW_IF KW_EXIT KW_LOAD KW_DISP
%token KW_TRUE KW_FALSE OP_PLUS OP_MINUS OP_DIV OP_OP
%token OP_CP OP_DBLMULT OP_MULT OP_COMMA OP_OC OP_CC STRING

%token <str> IDENTIFIER
%token <i_val> VALUE
%type <i_val> EXPI EXPB
%type <int_lst> EXPLISTI VALUES LISTVALUE

%%

start : start input
		| input
		;

input	: 	EXPI 
		|  EXPB
		|  EXPLISTI
		|	COMMENT
		;

EXPI 	: VALUE	{$$ = $1;}
		| OP_OP OP_PLUS EXPI EXPI OP_CP		{$$ = $3 + $4;}
		| OP_OP OP_MINUS EXPI EXPI OP_CP		{$$ = $3 - $4;}	
		| OP_OP OP_MULT EXPI EXPI OP_CP		{$$ = $3 * $4;}
		| OP_OP OP_DBLMULT EXPI EXPI OP_CP	{$$ = power_of($3,$4);}
		| KW_EXIT  {exit(EXIT_SUCCESS);}
		| OP_OP OP_DIV EXPI EXPI OP_CP		{	
															if($4 == 0) printf("Cannot divide to zero.\n"); 
															else {$$ = $3 / $4;}
														}	
		| IDENTIFIER								{$$ = get_val_int($1);}	
		| OP_OP KW_SET IDENTIFIER EXPI OP_CP { int_head = add_to_intList(int_head , $3 , $4); $$ = 1;}
		| OP_OP KW_DISP EXPI OP_CP				{$$ = 1; // true.
														 printf("%d\n",$3);}
		| OP_OP KW_DISP EXPLISTI OP_CP		{$$ = 1; // true.
														 print_list($3);
														}
		| OP_OP KW_IF EXPB EXPI OP_CP			{ if($3) $$ = $4; else $$ = 0;}
		| OP_OP KW_IF EXPB EXPLISTI OP_CP	{ if($3) {
																if($4 != NULL){
																	int_list* iter = $4;
																	while(iter != NULL){
																		iter = iter->next;
																	}
																	$$ = iter->val;
																}
																else{
																	$$ = 0;
																}
															} 
														}
		| OP_OP KW_IF EXPB EXPLISTI EXPLISTI OP_CP	{if($3) {
																		if($4 != NULL){
																			int_list* iter = $4;
																			while(iter != NULL){
																				iter = iter->next;
																			}
																			$$ = iter->val;
																		}
																		else{
																			$$ = 0;
																		}
																	}
																	else{
																		if($5 != NULL){
																			int_list* iter = $5;
																			while(iter != NULL){
																				iter = iter->next;
																			}
																			$$ = iter->val;
																		}
																		else{
																			$$ = 0;
																		}
																	} 

																	}
		| OP_OP KW_FOR OP_OP IDENTIFIER EXPI EXPI OP_CP EXPLISTI OP_CP	{

			while(get_val_int($4) < $5){
				set_val_int($4 , get_val_int($4) + $6);
				if($8 == NULL){
					return 0;
				}
				else{
					int_list* iter = $8;
					while(iter != NULL){
						iter = iter->next;
					}
					$$ = iter->val;
				}
			}
		}
		| OP_OP KW_FOR OP_OP IDENTIFIER EXPI EXPI OP_CP EXPI OP_CP	{

			while(get_val_int($4) < $5){
				set_val_int($4 , get_val_int($4) + $6);
				$$ = $8;
			}
		}			
		;

EXPB	: OP_OP KW_AND EXPB EXPB OP_CP		{$$ = $3 && $4;}
		| OP_OP KW_OR EXPB EXPB OP_CP		{$$ = $3 || $4;}
		| OP_OP KW_EQUAL EXPB EXPB OP_CP		{$$ = $3 == $4;}
		| OP_OP KW_NOT EXPB OP_CP		{$$ = !$3;}
		| OP_OP KW_EQUAL EXPI EXPI OP_CP		{$$ = $3 == $4;}
		| OP_OP KW_LESS EXPI EXPI OP_CP		{$$ = $3 < $4;}
		| KW_TRUE	{$$ = 1;}
		| KW_FALSE	{$$ = 0;}
		;

EXPLISTI		: OP_OP KW_CONCAT	EXPLISTI EXPLISTI OP_CP	{
																				int_list* iter = $3;
																				while(iter != NULL){
																					$4 = add_to_intList($4 , "list_item", iter->val);
																					iter = iter->next;
																				}
																				$$ = $4;
																		}
				| OP_OP KW_APPEND EXPI EXPLISTI OP_CP		{
																			$4 = add_to_intList($4 , "list_item", $3); $$ = $4;
																		}
				| LISTVALUE			{$$ = $1;}
				;

LISTVALUE	: OP_OP KW_LIST VALUES OP_CP 	{$$ = $3;}
				| OP_OP VALUES OP_CP				{ $$ = $2;}
				| OP_OP OP_CP				{ $$ = NULL;}
				| KW_NIL						{ $$ = NULL;}
				;

VALUES		: VALUES VALUE {  $1 = add_to_intList($1 , " list_item" , $2);  $$ = $1;
										 }
				| VALUE 	{	

								int_list* vals = NULL;
								vals = add_to_intList(vals , "list_item" , $1);
								
								$$ = vals;								
							}
				; 


%%

int_list* add_to_intList(int_list* list , char *name , int val){

	int_list* temp = malloc(sizeof(int_list) + 50);
	temp->val = val;

	temp->name = malloc(50);
	strcpy(temp->name , name);

	if(list != NULL) { temp->next = list;}
	else { temp -> next = NULL;}

   list = temp;

   return list;

}
void print_list(int_list* list){
	int_list* iter = list;

	while(iter != NULL){
		printf("---%s -> %d \n",iter->name , iter->val);
		iter = iter->next;
	}
}
int set_val_int(char* name , int val){
	int_list* iter = int_head;

	while(iter){
		if(!strcmp(iter->name , name)){
			iter->val = val;
		}
		iter = iter->next;

	}

	printf("There is no identifier named %s.\n",name);
	exit(EXIT_SUCCESS);
	return -99999999;
}
int get_val_int(char* name){

	int_list* iter = int_head;

	while(iter){
		if(!strcmp(iter->name , name)){
			return iter->val;
		}
		iter = iter->next;

	}

	printf("There is no identifier named %s.\n",name);
	exit(EXIT_SUCCESS);
	return -99999999;
}

int power_of(int a , int b){
	int result = 1;

	for(int i = 0 ; i< b; i++){
		result *= a;
	}
	return result;
}           

int main (void) {

	return yyparse ( );
}

void yyerror (char *s) {fprintf (stderr, "%s\n", s);} 
