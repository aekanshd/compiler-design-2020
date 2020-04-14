%option noyywrap
%{

#include<stdio.h>
#include <strings.h>

%}
start \/\*
end \*\/
%%
			
"/*"+([^*]|\*+[^/])*\*+\/.*\n			{fprintf(yyout, "");printf("\n New Comment - %s\n", yytext);}
"//"(.)*(\n)		{fprintf(yyout, "");}


.			{fprintf(yyout, "%s", yytext);}
%%
int main() 
{ 
  
    
    extern FILE *yyin, *yyout; 
  
    
    yyin = fopen("input.cpp", "r"); 
    yyout = fopen("Output.cpp", "w"); 
  
    yylex(); 
    return 0; 
} 

