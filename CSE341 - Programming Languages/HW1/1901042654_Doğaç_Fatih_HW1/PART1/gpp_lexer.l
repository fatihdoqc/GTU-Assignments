
%{
int count = 0;
%}
and, or, not, equal, less, nil, list, append, concat,
set, deffun, for, if, exit, load, disp, true, false
%%
\n {return 0;}

and 			{ printf("KW_AND\n"); }
or 				{ printf("KW_OR\n"); }	
not  			{ printf("KW_NOT\n"); }	
equal			{ printf("KW_EQUAL\n"); }
less			{ printf("KW_LESS\n"); }
nil				{ printf("KW_NIL\n"); }
list			{ printf("KW_LIST\n"); }	
append			{ printf("KW_APPEND\n"); }
concat			{ printf("KW_CONCAT\n"); }
set 			{ printf("KW_SET\n"); }
deffun			{ printf("KW_DEFFUN\n"); }
for				{ printf("KW_FOR\n"); }	
if				{ printf("KW_IF\n"); }
exit			{ printf("KW_EXIT\n"); }
load			{ printf("KW_LOAD\n"); }	
disp			{ printf("KW_DISP\n"); }
true			{ printf("KW_TRUE\n"); }
false			{ printf("KW_FALSE\n"); }

"+" 			{ printf("OP_PLUS\n"); }
"-"				{ printf("OP_MINUS\n"); }
"/"				{ printf("OP_DIV\n"); }
"*"				{ printf("OP_MULT\n"); }
[(]				{ printf("OP_OB\n"); }
[)]				{ printf("OP_CB\n"); }
"**"			{ printf("OP_DBLMULT\n"); }
["].*["]		{ printf("OP_OC {string} OP_CC\n"); }
","				{ printf("OP_COMMA\n"); }

;;.*				{ printf("COMMENT\n"); }

[1-9]+[0-9]*			{ printf("VALUE\n");}
[1-9]+[0-9]*[.][0-9]*	{ printf("VALUE\n");}

[A-Za-z]+[0-9]*			{ printf("IDENTIFIER\n");}

%%

int yywrap(){}
int main(){

yylex();
return 0;
}
