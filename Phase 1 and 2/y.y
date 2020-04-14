%{
	
#include<stdio.h>

%}

%token INT FLOAT CHAR WHILE DO IF FOR ELSE NUMBER
%%
statements: statement | statements statement
;
statement: keyword 
;
keyword : INT {printf(">KEYWORD INT\n");}
|FLOAT {printf(">KEYWORD FLOAT\n");}
|CHAR {printf(">KEYWORD CHAR\n");}
|WHILE {printf(">KEYWORD WHILE\n");}
|DO {printf(">KEYWORD DO\n");}
|IF {printf(">KEYWORD IF\n");}
|FOR {printf(">KEYWORD FOR\n");}
|ELSE {printf(">KEYWORD ELSE\n");}
|"\n"
;
%%



void yyerror(){
	printf("Invalid\n");
	
}