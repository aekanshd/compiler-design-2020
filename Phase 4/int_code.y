%{

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "lex.yy.c"
//typedef char* string;
//#define YYSTYPE string
#define STR(VAR) (#VAR)
#define release 1
#define MAXCHILD 10
FILE *syntree;
extern void yyerror(const char *);  /* prints grammar violation message */
extern int yylex(void);
extern FILE *yyin;
extern FILE *yyout;
extern int yylineno;

int iasval, itermval, iexpval;
char casval, ctermval, cexpval;
float fasval, ftermval, fexpval;
int cflag=0, iflag=0, fflag=0;
char* tab="  ";
char indent[100]="";
char type[200];
char* integer="INT";
char* floating="float";
char* none = "none";
char* assign = "=";
int expval=0;
int errors = 0;

struct node{
    int nl;
    char name[100];
    char dtype[200];
    int scope;
    int value;
    float fvalue;
    char cvalue;
    char type[100];
    struct node *next;

};
typedef struct node node;
struct list{
    node* head;
};

typedef struct list list1;
struct list* list2 = NULL;

int exists(list1* root, char name[100]){
    if(root == NULL || root->head == NULL){
        return 0;
    }
    node *t2 = root->head;
    while(t2!=NULL){
        if(strcmp(t2->name, name) == 0){
            
            
            return 1;
        }
        t2 = t2->next;
    }
    return 0;

}
node* find(list1 *root, char name[200]){
    if(root == NULL || root->head == NULL){
        return NULL;
    }
    node *t2 = root->head;
    while(t2!=NULL){
        if(strcmp(t2->name, name)==0){return t2;}
        t2 = t2->next;
    }
    return t2;

}
node* id_ex;
void insert(list1 *root, int nl, char name[100], char dtype[200], int scope, int value, float fvalue, char cvalue, char type[100]){
    int out = exists(root, name);
    
    if(out == 0){
    node *temp = (node*)malloc(sizeof(node));
    temp->nl = nl;
    temp->scope = scope;
    strcpy(temp->dtype, dtype);
    if(strcmp(type, "int") == 0)
        
        temp->value = value;
    else if(strcmp(type, "float")==0)
        
        temp->fvalue = fvalue;
    else if(strcmp(type, "char")==0)
        
        temp->cvalue = cvalue;
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

void update(list1 *root, char name[100], int value, float fvalue, char cvalue){
    node *t2 = root->head;
    if(find(root, name) == NULL){
        return;
    }
    while(strcmp(t2->name, name)!=0){
        t2 = t2->next;
    }
    if(strcmp(t2->dtype, "int") == 0)
        t2->value = value;
    else if(strcmp(t2->dtype, "float")==0)
        t2->fvalue = fvalue;
    else if(strcmp(t2->dtype, "char")==0)
        t2->cvalue = cvalue;
    
    return;
}

void print(node *head){
    // printf("1\n");
    node *temp = head;
    printf("____________________________________________________\n");
    printf("| Line | Name | Scope | value | id_type | datatype |\n");
    printf("----------------------------------------------------\n");
    while(temp!=NULL){

        if(strcmp(temp->dtype, "int")==0)

            printf("|   %d  |   \"%s\"  |   %d  |  %d  |  %s  |  %s  |\n", temp->nl, temp->name, temp->scope, temp->value, temp->type, temp->dtype);
        if(strcmp(temp->dtype, "float")==0)
            printf("|   %d  |   \"%s\"  |   %d  |  %.1f  |  %s  |  %s  |\n", temp->nl, temp->name, temp->scope, temp->fvalue, temp->type, temp->dtype);
        if(strcmp(temp->dtype, "char")==0)
            printf("|   %d  |   \"%s\"  |   %d  |  %c  |  %s  |  %s  |\n", temp->nl, temp->name, temp->scope, temp->cvalue, temp->type, temp->dtype);

        temp=temp->next;
    }
}

struct expression_details{
    int value;
    char type[200];
};
typedef struct expression_details exp_det;
exp_det det1;



%}
%code requires {

}
%union{
	char chr;
	int integer;
	float ft;
	char *str;
}

%token IF ELSE WHILE RETURN VOID INT FLOAT CHAR
%token INC_OP DEC_OP PLUS MINUS STAR SLASH  LT LTEQ GT GTEQ EQ NEQ ASSIGN  
%token SEMI COMMA LPAREN RPAREN LSQUAR RSQUAR LBRACE RBRACE LCOMMENT RCOMMENT 
%token <str> ID NUM FLT
%token LETTER DIGIT
%token NONTOKEN ERROR ENDFILE
%token NL

%left PLUS MINUS
%left STAR SLASH
%nonassoc THEN
%nonassoc ELSE

%type<integer> atree program external_declaration var_declaration init_declarator_list fun_declaration params_list compound_stmt declarator params block_item_list block_item call factor term additive_expression simple_expression unary_expression postfix_expression assignment_expression return_stmt while_stmt if_stmt expression statement args expression_stmt 
%type<str> relop declaration_specifiers 


%start atree
%%

atree:program {}


program 
    : external_declaration {$$=$1; }
    | program external_declaration { }

    ;

external_declaration
    : var_declaration {$$=$1;}
    | fun_declaration {$$=$1;}

    ;

var_declaration
    : declaration_specifiers init_declarator_list SEMI 
    {}
    | error SEMI{yyerrok;}

    ;

init_declarator_list
    : ID {insert(list2, yylineno, $1, type, scope, -1,0.0,'\0', "IDENT");}
    | ID ASSIGN expression {
                            insert(list2, yylineno, $1, type, scope, -1,0.0,'\0', "IDENT");
                            update(list2, $1, iexpval, fexpval, cexpval);
                            iflag = 0;
                            fflag = 0;
                            cflag = 0; 
                        }
    | init_declarator_list COMMA ID{ insert(list2, yylineno, $3, type, scope, -1,0.0,'\0', "IDENT"); }
    ;

declarator
    : LPAREN RPAREN {}
    | LPAREN params RPAREN {}
    ;

fun_declaration
    : declaration_specifiers ID declarator compound_stmt {}
    ;

declaration_specifiers
    : INT {$$=integer; strcpy(type, "int");}
    | VOID {$$="VOID"; strcpy(type, "void");}
    | FLOAT {$$="float"; strcpy(type, "float");}
    | CHAR {$$="char"; strcpy(type, "char");}
    ;

params_list
    : INT ID {}
    | FLOAT ID {}
    | params_list COMMA INT ID {}
    | params_list COMMA FLOAT ID {}

    ;

params
    : params_list {$$=$1;}
    | VOID {}
    ;
    
compound_stmt
    : LBRACE RBRACE {}
    | LBRACE block_item_list RBRACE {$$ = $2;}
    ;

block_item_list
    : block_item {$$ = $1; }
    | block_item_list block_item {}
    ;

block_item
    : var_declaration {$$=$1; }
    | statement {$$=$1;}
    ;

statement
    : expression_stmt {$$=$1;}
    | compound_stmt {$$=$1;}
    | if_stmt {$$=$1;}
    | while_stmt {$$=$1;}
    | return_stmt {$$=$1;}
    ;

expression_stmt
    : SEMI {}
    | expression SEMI {$$=$1;}

    ;

if_stmt
    : IF LPAREN expression RPAREN statement ELSE statement { }
    | IF LPAREN expression RPAREN statement %prec THEN {}
    ;

while_stmt
    : WHILE LPAREN expression RPAREN statement {}
    ;

return_stmt
    : RETURN SEMI {}
    | RETURN expression SEMI {}
    ;
    
expression
    : assignment_expression {$$=$1;}
    | simple_expression {$$=$1;}
    ;

assignment_expression
    : ID ASSIGN expression {
    						 
                            int ex = exists(list2,$1); 
                            if(ex == 0) {printf("Error in Line %d: Assignment before Declaration\n", yylineno); errors++;}
                            id_ex = find(list2, $1);
                            if(iflag == 1){
                            	update(list2, $1, $3, fexpval, cexpval);
                            }
                            if(fflag == 1){
                            	update(list2, $1, iexpval, $3, cexpval);
                            }
                            if(cflag == 1){
                            	update(list2, $1, iexpval, fexpval, $3);
                            }
                            iflag = 0;
                            cflag = 0;
                            fflag = 0;
                            

                        }
    | unary_expression  {$$=$1;}    ;

unary_expression 
    : INC_OP ID { 
                 id_ex = find(list2, $2); 
                 if(id_ex==NULL){
                    printf("Error on Lineno %d: Increment operator cannot be applied to an identifier that's not declared\n", yylineno);
                    errors++;
                    }
                else {
                    if(strcmp(id_ex->dtype, "int")!=0){
                        printf("Error on Line %d: Type Mismatch\n", yylineno);
                        errors++;
                        }
                    else
                        ++id_ex->value;
                    }
                }
    | DEC_OP ID {
                 id_ex = find(list2, $2); 
                 if(id_ex==NULL){
                    printf("Error on Lineno %d: Increment operator cannot be applied to an identifier that's not declared\n", yylineno);
                    errors++;}
                else {
                    if(strcmp(id_ex->dtype, "int")!=0){
                        printf("Error on Line %d: Type Mismatch\n", yylineno);
                        errors++;
                        }
                    else
                        --id_ex->value;
                    }

                }
    | postfix_expression {$$=$1;}
    ;

postfix_expression
    : ID INC_OP {
                 id_ex = find(list2, $1); 
                 if(id_ex==NULL){
                    printf("Error on Lineno %d: Increment operator cannot be applied to an identifier that's not declared\n", yylineno);
                    errors++;
                    }
                else {
                    if(strcmp(id_ex->dtype, "int")!=0){
                        printf("Error on Line %d: Type Mismatch\n", yylineno);
                        errors++;
                        }
                    else
                        id_ex->value++;
                    }
                }
    | ID DEC_OP {
                 id_ex = find(list2, $1); 
                 if(id_ex==NULL){
                    printf("Error on Lineno %d: Increment operator cannot be applied to an identifier that's not declared\n", yylineno);
                    errors++;
                    }
                else {
                    if(strcmp(id_ex->dtype, "int")!=0){
                        printf("Error on Line %d: Type Mismatch\n", yylineno);
                        errors++;
                        }
                    else
                        id_ex->value--;
                    }

                }
    ;

simple_expression
    : additive_expression {$$=$1;}
    | additive_expression relop additive_expression {
				if(strcmp($2, "<")==0)
					$<integer>$ = $1<$3;
				if(strcmp($2, "<=")==0)
					$<integer>$ = $1<=$3;
				if(strcmp($2, ">")==0)
					$<integer>$ = $1>$3;
				if(strcmp($2, ">=")==0)
					$<integer>$ = $1>=$3;
				if(strcmp($2, "==")==0)
					$<integer>$ = $1==$3;
				if(strcmp($2, "!=")==0)
					$<integer>$ = $1!=$3;

    		}
    ;

relop 
    : LT {$$ = "<";}
    | LTEQ  {$$ = "<=";}
    | GT    {$$ = ">";}
    | GTEQ  {$$ = ">=";}
    | EQ    {$$ = "==";}
    | NEQ   {$$ = "!=";}
    ;

additive_expression
    : term {$$=$1; 
            if(iflag == 1)
                iexpval = itermval;
            if(fflag == 1)
                fexpval = ftermval;
            if(cflag == 1)
                cexpval = ctermval;

        }
    | additive_expression PLUS term {$$ = $1 + $3;}
    | additive_expression MINUS term {$$ = $1 - $3;}
    | PLUS additive_expression %prec STAR {}
    | MINUS additive_expression %prec STAR {}
    ;

term
    : factor {
              if(iflag == 1)
              	$<integer>$ = iasval;
                itermval = iasval;
              if(fflag == 1)
              	$<ft>$ = fasval;
                ftermval = fasval;
              if(cflag == 1)
              	$<chr>$ = casval;
                ctermval = casval;
            }
    | term STAR factor {$$ = $1*$3;}
    | term SLASH factor {$$ = $1/$3;}
    ;

factor
    : LPAREN expression RPAREN {$$=$2;}
    | ID {
          id_ex = find(list2, $1);
          if(id_ex == NULL){
            printf("Error on %d, Assignment RHS not declared\n", yylineno);
            errors++;
            $$ = 0;}
          else{
          	//$$ = $1;

            if(strcmp(id_ex->dtype, "int")==0) 
            {
            	$<integer>$ = id_ex->value;
                iasval = id_ex->value;
                iflag = 1;
                cflag = 0;
                fflag = 0;
            }
            if(strcmp(id_ex->dtype, "float")==0){
            	$<ft>$ = id_ex->fvalue;
            	
                fasval = id_ex->fvalue;
                iflag = 0;
                fflag = 1;
                cflag = 0;
            }
            if(strcmp(id_ex->dtype, "char")==0){
            	$<chr>$ = id_ex->cvalue;
                casval = id_ex->cvalue;
                iflag = 0;
                fflag = 0;
                cflag = 1;
            }
          }}
    | call {$$=$1;}
    | NUM { 
           iasval = atoi(yylval.str); iflag = 1; cflag=0; fflag=0;
           $<integer>$ = iasval;
           
           }
    |FLT{
    	fasval = atof(yylval.str); fflag = 1; cflag = 0; iflag = 0;
    	$<ft>$ = fasval;
    	}
    ;
    
call
    : ID LPAREN RPAREN {}
    | ID LPAREN args RPAREN {}
    ;

args
    : expression {$$=$1;}
    | expression COMMA args {}
    ;

%%
#include <stdio.h>
main(argc, argv)
int argc;
char** argv;
{
syntree = fopen("syntree.txt", "w");
FILE *fp = fopen("tokens.txt", "w");
fclose(fp);
if (argc > 1)
{
    FILE *file;
    file = fopen(argv[1], "r");
    if (!file)
    {
        fprintf(stderr, "failed open");
        exit(1);
    }
    yyin=file;
    //printf("success open %s\n", argv[1]);
}
else
{
    printf("no input file\n");
    exit(1);
}
list2 = (struct list*)malloc(sizeof(struct list));
list2->head = NULL;

yyparse();  
print(list2->head);
fclose(syntree);
if(errors>0){
	printf("%d Errors Found\n", errors);
}
return 0; 
} 

void yyerror(const char *s)
{
	fflush(stdout);
	errors++;
	fprintf(stderr, "Error: %s on line number %d\n", s, yylineno);
}



