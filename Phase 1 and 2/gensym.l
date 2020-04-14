%option noyywrap
%{

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "y.tab.h"
extern int yylval;
int x = 0;
int scope = 0;
int nl =1;
struct node{
	int nl;
	char name[100];
	int scope;
	int value;
	char type[100];
	struct node *next;

};
char *token;
typedef struct node node;
struct list{
	node* head;
};

typedef struct list list1;
struct list* list2;
int exists(list1* root, char name[100], int value){
	if(root == NULL || root->head == NULL){
		return 0;
	}
	node *t2 = root->head;
	while(t2!=NULL){
		if(strcmp(t2->name, name) == 0){
			
			t2->value = value;
			return 1;
		}
		t2 = t2->next;
	}
	return 0;

}
void removespaces(char name[100]){
	const char *d = name;
	do{
		while(*d == ' '){
			++d;
		}

	}while (*name++ = *d++);
}
void insert(list1 *root, int nl, char name[100], int scope, int value, char type[100]){
	removespaces(name);

	int out = exists(root, name, value);
	if(out == 0){
	node *temp = (node*)malloc(sizeof(node));
	temp->nl = nl;
	temp->scope = scope;
	temp->value = value;
	strcpy(temp->name, name);
	strcpy(temp->type, type);
	temp->next = NULL;
	if(root->head == NULL){
		root->head = temp;
		return;
	}
	node *t2 = root->head;
	while(t2->next!=NULL){
		t2 = t2->next;
	}
	t2->next = temp;
	return;
}
}
void print(node *head){
	node *temp = head;
	printf("______________________________________\n");
	printf("| Line | Name | Scope | value | type |\n");
	printf("--------------------------------------\n");
	while(temp!=NULL){
		printf("|   %d  |   %s  |   %d  |  %d  |  %s  |\n", temp->nl, temp->name, temp->scope, temp->value, temp->type);
		temp=temp->next;
	}
}

%}
datatype "int"|"float"|"char"
identifier [_a-zA-Z][_a-zA-Z0-9]*
%%
"int" { fprintf(yyout, ">KEYWORD INT\n");}
"float" {fprintf(yyout, ">KEYWORD float\n");}
"char" {fprintf(yyout, ">KEYWORD char\n");}
"while" return WHILE; 
"do" return DO;
"if" return IF;
"for" return FOR;
"else" return ELSE;
"#include"(.)*"\n" fprintf(yyout, "> PRE_PROC_DIR %s\n", yytext);
\"[_a-zA-Z0-9$#@!%^&*]*\" fprintf(yyout, ">STRING LITERAL %s", yytext);
"(" fprintf(yyout, "> OPEN_PAR (\n");
")" fprintf(yyout, "> CLOSED_PAR )\n");
";" fprintf(yyout, "> SEMI_COLON ;\n");
"." fprintf(yyout, "> DOT_OPER .\n");
"{" {scope++; fprintf(yyout, "> OPEN_SCOPE {\n");}
"}" {scope--; fprintf(yyout, "> CLOSE_SCOPE }\n");}
"," fprintf(yyout, "> COMMA ,\n");
"[" fprintf(yyout, "> ARR_SUB_ST [\n");
"]" fprintf(yyout, "> ARR_SUB_END ]\n");
"\n" nl++;
[_a-zA-Z][_a-zA-Z0-9]* {fprintf(yyout, "> IDENTIFIER %s\n", yytext); insert(list2, nl,yytext, scope, -1, "VAR");}
[_a-zA-Z][_a-zA-Z0-9]*" "*"="" "*[0-9]+"."*[0-9]* {token = strtok(yytext, "="); fprintf(yyout, "> IDENT %s\n", token); token = strtok(NULL, "="); int val = atoi(token);fprintf(yyout, ">LITERAL %d\n", val);insert(list2, nl,yytext, scope, val, "VAR");}
[_a-zA-Z][_a-zA-Z0-9]*"(" {token = strtok(yytext, "("); fprintf(yyout, "> IDENT %s\n", token); insert(list2, nl, token, scope, -1, "FUNCT");}


%%

int main(){
	list2 = (struct list*)malloc(sizeof(struct list));
	list2->head = NULL;
	yyin = fopen("Output.cpp", "r");
	yyout = fopen("tokens.txt", "w"); 
	yylex();
	print(list2->head);
	
}