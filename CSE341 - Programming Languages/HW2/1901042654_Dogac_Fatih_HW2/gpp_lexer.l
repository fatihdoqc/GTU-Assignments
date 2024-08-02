
%{
#include "structs.h"	
#include "y.tab.h"
int yylex();
void yyerror (char *s);
int quote = 0;
%}

%%
and 			{ return KW_AND  ; }
or 				{ return KW_OR  ; }	
not  			{ return KW_NOT  ; }	
equal			{ return KW_EQUAL  ; }
less			{ return KW_LESS  ; }
nil				{ return KW_NIL  ; }
list			{ return KW_LIST  ; }	
append			{ return KW_APPEND  ; }
concat			{ return KW_CONCAT  ; }
set 			{ return KW_SET  ; }
deffun			{ return KW_DEFFUN  ; }
for				{ return KW_FOR  ; }	
if				{ return KW_IF  ; }
exit			{ return KW_EXIT  ; }
load			{ return KW_LOAD  ; }	
disp			{ return KW_DISP  ; }
true			{ return KW_TRUE  ; }
false			{ return KW_FALSE  ; }
"+" 			{ return OP_PLUS  ; }
"-"				{ return OP_MINUS  ; }
"/"				{ return OP_DIV  ; }
"*"				{ return OP_MULT  ; }
[(]				{ return OP_OP  ; }
[)]				{ return OP_CP  ; }
"**"			{ return OP_DBLMULT  ; }
["]		  	{ 
							quote++;
							if( quote % 2 == 1) return OP_OC;
							else return OP_CC;
 					}
","				{ return OP_COMMA  ; }
[ \n\t]+		{;}
;;.*				{ return COMMENT  ; }


0|[1-9]+[0-9]*			{ 
												yylval.i_val=atoi(yytext);
												return VALUE;
											}

[1-9]+[0-9]*[.][0-9]*	{ 
												yylval.i_val=atof(yytext);
												return VALUE;
											}

[A-Za-z]+[0-9a-zA-Z]*			{
														yylval.str=strdup(yytext);
														return IDENTIFIER;
													}
%%

int yywrap(){}
