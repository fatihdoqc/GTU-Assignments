/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    COMMENT = 258,
    KW_AND = 259,
    KW_OR = 260,
    KW_NOT = 261,
    KW_EQUAL = 262,
    KW_LESS = 263,
    KW_NIL = 264,
    KW_LIST = 265,
    KW_APPEND = 266,
    KW_CONCAT = 267,
    KW_SET = 268,
    KW_DEFFUN = 269,
    KW_FOR = 270,
    KW_IF = 271,
    KW_EXIT = 272,
    KW_LOAD = 273,
    KW_DISP = 274,
    KW_TRUE = 275,
    KW_FALSE = 276,
    OP_PLUS = 277,
    OP_MINUS = 278,
    OP_DIV = 279,
    OP_OP = 280,
    OP_CP = 281,
    OP_DBLMULT = 282,
    OP_MULT = 283,
    OP_COMMA = 284,
    OP_OC = 285,
    OP_CC = 286,
    STRING = 287,
    IDENTIFIER = 288,
    VALUE = 289
  };
#endif
/* Tokens.  */
#define COMMENT 258
#define KW_AND 259
#define KW_OR 260
#define KW_NOT 261
#define KW_EQUAL 262
#define KW_LESS 263
#define KW_NIL 264
#define KW_LIST 265
#define KW_APPEND 266
#define KW_CONCAT 267
#define KW_SET 268
#define KW_DEFFUN 269
#define KW_FOR 270
#define KW_IF 271
#define KW_EXIT 272
#define KW_LOAD 273
#define KW_DISP 274
#define KW_TRUE 275
#define KW_FALSE 276
#define OP_PLUS 277
#define OP_MINUS 278
#define OP_DIV 279
#define OP_OP 280
#define OP_CP 281
#define OP_DBLMULT 282
#define OP_MULT 283
#define OP_COMMA 284
#define OP_OC 285
#define OP_CC 286
#define STRING 287
#define IDENTIFIER 288
#define VALUE 289

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 27 "gpp_interpreter.y"

	int 	i_val;
	char* str;
	int_list* int_lst;
	double_list* double_lst;


#line 133 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
