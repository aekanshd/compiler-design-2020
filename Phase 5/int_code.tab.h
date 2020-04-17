
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
#line 331 ".\\int_code.y"





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
     INC_OP = 267,
     DEC_OP = 268,
     PLUS = 269,
     MINUS = 270,
     STAR = 271,
     SLASH = 272,
     LT = 273,
     LTEQ = 274,
     GT = 275,
     GTEQ = 276,
     EQ = 277,
     NEQ = 278,
     ASSIGN = 279,
     SEMI = 280,
     COMMA = 281,
     LPAREN = 282,
     RPAREN = 283,
     LSQUAR = 284,
     RSQUAR = 285,
     LBRACE = 286,
     RBRACE = 287,
     LCOMMENT = 288,
     RCOMMENT = 289,
     ID = 290,
     NUM = 291,
     FLT = 292,
     CHR = 293,
     LETTER = 294,
     DIGIT = 295,
     NONTOKEN = 296,
     ERROR = 297,
     ENDFILE = 298,
     NL = 299,
     ENDL = 300,
     STR = 301,
     INSERTION = 302,
     EXTRACTION = 303,
     CIN = 304,
     COUT = 305,
     CLASS = 306,
     PREPROC = 307,
     THEN = 308,
     LOWER_THAN_IF = 309
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 334 ".\\int_code.y"

	char chr;
	int integer;
	float ft;
	char *str;



/* Line 1676 of yacc.c  */
#line 126 "int_code.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


