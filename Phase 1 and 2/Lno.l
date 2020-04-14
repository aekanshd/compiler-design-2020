
%option noyywrap
%{
	int line_num = 1;

%}
%%
"/*"+([^*]|\*+[^/])*\*+\/.*\n
"//"(.)*(\n)
"\n" {fprintf(yyout, "%s  %d", yytext, line_num);printf("%s  %d", yytext, line_num);line_num++;}

%%
int main(){
	yyin = fopen("Output.cpp", "r");
	
	yyout = fopen("output3.cpp", "w");
	fprintf(yyout, "  %d", line_num++);
	yylex();
	

	return 0;
}