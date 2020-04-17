
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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

/* "%code requires" blocks.  */

/* Line 1676 of yacc.c  */
#line 341 ".\\int_code.y"





/* Line 1676 of yacc.c  */
#line 46 "int_code.tab.h"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IF = 258,
     ELSE = 259,
     WHILE = 260,
     RETURN = 261,
     VOID = 262,
     INT = 263,
     FLOAT = 264,
     CHAR = 265,
     FOR = 266,
     BREAK = 267,
     CONTINUE = 268,
     INC_OP = 269,
     DEC_OP = 270,
     PLUS = 271,
     MINUS = 272,
     STAR = 273,
     SLASH = 274,
     LT = 275,
     LTEQ = 276,
     GT = 277,
     GTEQ = 278,
     EQ = 279,
     NEQ = 280,
     ASSIGN = 281,
     SEMI = 282,
     COMMA = 283,
     LPAREN = 284,
     RPAREN = 285,
     LSQUAR = 286,
     RSQUAR = 287,
     LBRACE = 288,
     RBRACE = 289,
     LCOMMENT = 290,
     RCOMMENT = 291,
     ID = 292,
     NUM = 293,
     FLT = 294,
     CHR = 295,
     LETTER = 296,
     DIGIT = 297,
     NONTOKEN = 298,
     ERROR = 299,
     ENDFILE = 300,
     NL = 301,
     ENDL = 302,
     STR = 303,
     INSERTION = 304,
     EXTRACTION = 305,
     CIN = 306,
     COUT = 307,
     CLASS = 308,
     PREPROC = 309,
     THEN = 310,
     LOWER_THAN_IF = 311
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 344 ".\\int_code.y"

	char chr;
	int integer;
	float ft;
	char *str;



/* Line 1676 of yacc.c  */
#line 128 "int_code.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


