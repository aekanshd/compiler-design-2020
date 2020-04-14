%option yylineno

%{
#ifndef TRUE
#define TRUE 1 
#endif

#ifndef FALSE 
#define FALSE 0 
#endif

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "symtab.h"
#include "y.tab.h"

int badtoken_cnt = 0;
int token_cnt = 0;
int col_cnt = 0;
int lineno = 0;

%}

comment     \/\*([^*]|\n)*\*\/
digit       [0-9]
ichar       [A-Z_a-z]
integer     {digit}+
newline     \n
strchar     ([ ~]|\\n)
identifier  {ichar}([0-9]|{ichar})*
whitespace  [ \t]+
float       ([+-]?{digit}+)?\.{digit}*(e?[+-]?{digit}+)?
chrliteral  '([!*]|\\n)'
nullstring  \"\"
escquote    [^"]*\\\"[^"]*
strliteral  \"[^"]*{escquote}*\"
%%

"if"            { return IF;}
"then"          { return THEN;}
"else"          { return ELSE;}
"while"         { return WHILE;}
"return"        { return RETURN;}
"break"         { return GOTO;}
"goto"          { return GOTO;}
"read"          { return READ;}
"write"         { return WRITE;}
"float"         { return REAL;}
"int"           { return INT;}
"void"          { return VOID;}
"char"          { return CHAR;}

"="             { return ASSIGN;}
"!="            { return NE;}
"=="            { return EQ;}
"<"             { return LT;}
"<="            { return LE;}
">"             { return GT;}
">="            { return GE;}
"&&"            { return AND;}
"||"            { return OR;}

"+"             { return PLUS;}
"-"             { return MINUS;}
"*"             { return TIMES;}
"/"             { return OVER;}
"%"             { return MOD;}

"{"             { return LBRACE;}
"}"             { return RBRACE;}
"["             { return LBRACK;}
"]"             { return RBRACK;}
"("             { return LPAREN;}
")"             { return RPAREN;}
";"             { return SEMI;}
","             { return COMMA;}

{float}         { 
                  yylval.tokname = malloc(sizeof(yytext));
                  strncpy(yylval.tokname,yytext,yyleng);
                  printf("yylval: %s\n",yylval.tokname);
                  insert(yytext, yyleng, REAL_TYPE, lineno);
                  printf("yytext: %s\n",yytext);
                  return FLOAT;
                }
{integer}       { 
                  yylval.tokname = malloc(sizeof(yytext));
                  printf("yylval: %s\n",yylval.tokname);
                  strncpy(yylval.tokname,yytext,yyleng);
                  insert(yytext, yyleng, INT_TYPE, lineno);
                  printf("yytext: %s\n",yytext); 
                  return INTEGER;
                }


{chrliteral}    { 
                  yylval.tokname = malloc(sizeof(yytext));
                  strncpy(yylval.tokname,yytext,yyleng);
                  printf("yylval: %s\n",yylval.tokname);
                  insert(yytext, yyleng, -1, lineno);
                  printf("yytext: %s\n",yytext);
                  return CHRLIT;
                }

{nullstring}    { 
                  yylval.tokname = malloc(sizeof(yytext));
                  strncpy(yylval.tokname,yytext,yyleng);
                  printf("yylval: %s\n",yylval.tokname);
                  insert(yytext, yyleng, -1, lineno);
                  printf("yytext: %s\n",yytext);
                  return STRLIT;
                }

{strliteral}    { 
                  yylval.tokname = malloc(sizeof(yytext));
                  strncpy(yylval.tokname,yytext,yyleng);
                  printf("yylval: %s\n",yylval.tokname);
                  insert(yytext, yyleng, STR_TYPE, lineno);
                  printf("yytext: %s\n",yytext);
                  return STRLIT;
                }

{identifier}    { 

                  return IDENT;
                }
{newline}       { col_cnt = 1; }

{whitespace}    { col_cnt+=yyleng; }

{comment}       { col_cnt = 0; }

"//"            { /* handle C++ style comments */
                    char c;
                    do { c = input();
                    } while (c != '\n');
                    lineno++;
                }

.               { return ERROR;}

%%