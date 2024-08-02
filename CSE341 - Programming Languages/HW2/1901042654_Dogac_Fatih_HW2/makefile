target: test

test:

		yacc -d gpp_interpreter.y
		lex gpp_lexer.l
		gcc lex.yy.c y.tab.c
		./a.out <input.txt> output.txt