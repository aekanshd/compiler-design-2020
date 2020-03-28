D   [0-9]
NZ  [1-9]
L   [a-zA-Z_]
A   [a-zA-Z_0-9]
WS  [ \t\v\n\f]
TE  [a-zA-Z_0-9!@#$%^&* \t\v\n\f]
%option yylineno

%{  
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "int_code.tab.h"   
int yywrap(); 
int scope = 0;
void printToken(char* type){
    FILE *fp = fopen("tokens.txt", "a");
fprintf(fp,"  <token line=\"%d\" type=\"%s\" string=\"%s\" />\n", 
	yylineno, 
	type,
	yytext);
    fclose(fp);
}
static void comment(void);
%}
%%

"/*"                                    { comment(); }
"//".*                                    { /* consume //-comment */ }

"if"					{printToken("IF"); return(IF); }
"else"					{printToken("ELSE"); return(ELSE);}
"while"					{printToken("WHILE"); return(WHILE);}
"return"					{printToken("RETURN"); return(RETURN);}
"void"					{printToken("VOID");yylval.str = strdup(yytext); 
                         return(VOID);}
"int"					{printToken("INT");yylval.str = strdup(yytext); 
                        return(INT);}
"float"					{printToken("FLOAT");yylval.str = strdup(yytext); 
                        return(FLOAT);}
"char"                  {printToken("CHAR"); yylval.str=strdup(yytext); return(CHAR);}
"for"                   {printToken("FOR"); return FOR;}
"class"                 {printToken("CLASS"); return CLASS;}
"++"				{printToken("INC_OP");return INC_OP;} 
"--"				{printToken("DEC_OP");return DEC_OP;} 
"+"				{printToken("PLUS");return PLUS;}     
"-"				{printToken("MINUS");return MINUS; }     
"*"				{printToken("STAR");return STAR; }     
"/"				{printToken("SLASH");return SLASH; }     
"<"				{printToken("LT");return LT; }     
"<="				{printToken("LTEQ"); return LTEQ;} 
">"				{printToken("GT");return GT;}     
">="				{printToken("GTEQ");return GTEQ;} 
"=="				{printToken("EQ");return EQ;} 
"!="				{printToken("NEQ");return NEQ;} 
"="				{printToken("ASSIGN");return ASSIGN;}
"<<"            {printToken("INSERTION"); return INSERTION;}
">>"            {printToken("EXTRACTION"); return EXTRACTION;}
"cin"           {printToken("CIN"); return CIN;}
"cout"          {printToken("COUT"); return COUT;}

("[")				{printToken("LSQUAR");return LSQUAR; }
("]")				{printToken("RSQUAR");return RSQUAR;}
("{")				{printToken("LBRACE");scope++; return LBRACE;}
("}")				{printToken("RBRACE");scope--; return RBRACE;}
";"				{printToken("SEMI");return SEMI;}
","				{printToken("COMMA");return COMMA;}
"("				{printToken("LPAREN");return LPAREN;}
")"				{printToken("RPAREN");return RPAREN; }
"endl"          {printToken("ENDL"); return ENDL;}
{L}{A}*					{printToken("ID");yylval.str = strdup(yytext); return ID;}
{D}+			{printToken("NUMBER");yylval.str = strdup(yytext); return NUM;}
{D}*"."{D}+     {printToken("FLOATINGPOINT");yylval.str = strdup(yytext); return FLT;}
\"{TE}*{WS}*\"       {printToken("String"); yylval.str = strdup(yytext); return STR;}
{WS}+					{}
.					{printToken("UNKNOWN LEXEME");printToken(yytext);}


%%
#include<stdio.h>

int yywrap() {
    return 1;
}


static void comment(void)
{
    int c;

    while ((c = input()) != 0)
        if (c == '*')
        {
            while ((c = input()) == '*')
                ;

            if (c == '/')
                return;

            if (c == 0)
                break;
        }
    printf("unterminated comment");
    exit(-1);
}

