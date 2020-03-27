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

char* tab="  ";
char indent[100]="";
char type[200];
char* integer="INT";
char* floating="float";
char* none = "none";
char* assign = "=";
int expval=0;
void incIndent(){
    strcat(indent, tab);
}
void decIndent(){
    int len = strlen(indent);
    indent[len-2]='\0';
}

struct treeNode{
    struct treeNode *child[MAXCHILD];
    char* nodeType;
    char* string;
    char* value;
    char* dataType;
    int lineNo;
    int Nchildren;
};
void printNode(struct treeNode* node){
    fprintf(syntree, "%s lineNo=\"%d\" nodeType=\"%s\" string=\"%s\" value=\"%s\" dataType=\"%s\"\n", 
        indent,
        node->lineNo,
        node->nodeType,
        node->string,
        node->value, 
        node->dataType);
    int i;
    if (node->Nchildren > 0){
        fprintf(syntree, "%sChild\n", indent);
        incIndent();
        for (i=0;i<node->Nchildren;i++){
            printNode(node->child[i]);
        }
        decIndent();
        fprintf(syntree, "%sChild\n", indent);
    }
    fprintf(syntree, "%s\n", indent);
}


struct node{
    int nl;
    char name[100];
    char dtype[200];
    int scope;
    int value;
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
void insert(list1 *root, int nl, char name[100], char dtype[200], int scope, int value, char type[100]){
    int out = exists(root, name);
    
    if(out == 0){
    node *temp = (node*)malloc(sizeof(node));
    temp->nl = nl;
    temp->scope = scope;
    strcpy(temp->dtype, dtype);
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

void update(list1 *root, char name[100], int value){
    node *t2 = root->head;
    if(find(root, name) == NULL){
        return;
    }
    while(strcmp(t2->name, name)!=0){
        t2 = t2->next;
    }
    t2->value = value;
    return;
}
struct treeNode * newnode(int lineNo, char* nodeType, char* string, char* value, char* dataType, int Nchildren, ...){
    struct treeNode * node = (struct treeNode*) malloc(sizeof(struct treeNode));
    node->nodeType = nodeType;
    node->string = string;
    node->value = value;
    node->dataType = dataType;
    node->lineNo = lineNo;
    node->Nchildren = Nchildren;
    va_list ap;
    int i;
    va_start(ap, Nchildren);
    for (i=0;i<Nchildren;i++){
        node->child[i]=va_arg(ap, struct treeNode *);
    }
    va_end(ap);
    return node;
}

void print(node *head){
    // printf("1\n");
    node *temp = head;
    printf("______________________________________\n");
    printf("| Line | Name | Scope | value | type |\n");
    printf("--------------------------------------\n");
    while(temp!=NULL){
        printf("|   %d  |   \"%s\"  |   %d  |  %d  |  %s  |\n", temp->nl, temp->name, temp->scope, temp->value, temp->type);
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

%union {
    char* str;
    struct treeNode * ast;
}

%token IF ELSE WHILE RETURN VOID INT FLOAT CHAR
%token INC_OP DEC_OP PLUS MINUS STAR SLASH  LT LTEQ GT GTEQ EQ NEQ ASSIGN  
%token SEMI COMMA LPAREN RPAREN LSQUAR RSQUAR LBRACE RBRACE LCOMMENT RCOMMENT 
%token <str> ID NUM
%token LETTER DIGIT
%token NONTOKEN ERROR ENDFILE
%token NL

%left PLUS MINUS
%left STAR SLASH
%nonassoc THEN
%nonassoc ELSE
%type<ast> atree program external_declaration var_declaration init_declarator_list fun_declaration params_list compound_stmt declarator params block_item_list block_item factor call term additive_expression simple_expression unary_expression postfix_expression assignment_expression return_stmt while_stmt if_stmt expression statement args expression_stmt 
%type<str> relop declaration_specifiers 

%start atree
%%

atree:program {printNode($1);}

program 
    : external_declaration {$$=$1;}
    | program external_declaration {$$=newnode(yylineno, STR(program), none, none, none,  2, $1, $2); }

    ;

external_declaration
    : var_declaration {$$=$1;}
    | fun_declaration {$$=$1;}

    ;

var_declaration
    : declaration_specifiers init_declarator_list SEMI
    {$$=newnode(yylineno, "var_declaration", none, none, $1, 1, $2);}

    ;

init_declarator_list
    : ID {$$ = newnode(yylineno, "init_declarator_list", $1, none, none, 0);insert(list2, yylineno, $1, type, scope, -1, "IDENT");}
    | ID ASSIGN expression {$$ = newnode(yylineno,"init_declarator_list", $1, none, none,  1, $3);insert(list2, yylineno, $1, type, scope, -1, "IDENT"); }
    | init_declarator_list COMMA ID{$$ = newnode(yylineno,"init_declarator_list", $3, none, none,  1, $1); insert(list2, yylineno, $3, type, scope, -1, "IDENT"); }
    ;

declarator
    : LPAREN RPAREN {$$ = newnode(yylineno,"declarator", none, none, none,  0);}
    | LPAREN params RPAREN {$$ = newnode(yylineno,"declarator", none, none, none,  1, $2);}
    ;

fun_declaration
    : declaration_specifiers ID declarator compound_stmt {$$=newnode(yylineno,STR(fun_declaration), $2, none, $1,  1, $4);}
    ;

declaration_specifiers
    : INT {$$=integer; strcpy(type, "int");}
    | VOID {$$="VOID"; strcpy(type, "void");}
    | FLOAT {$$="float"; strcpy(type, "float");}
    | CHAR {$$="char"; strcpy(type, "char");}
    ;

params_list
    : INT ID {$$ = newnode(yylineno,"params_list", $2, none, integer,  0);}
    | FLOAT ID {$$ = newnode(yylineno,"params_list", $2, none, floating,  0);}
    | params_list COMMA INT ID {$$ = newnode(yylineno,"params_list", $4, none, integer,  1, $1);}
    | params_list COMMA FLOAT ID {$$ = newnode(yylineno,"params_list", $4, none, floating,  1, $1);}

    ;

params
    : params_list {$$=$1;}
    | VOID {$$ = newnode(yylineno,"params", none, none, "VOID",  0);}
    ;
    
compound_stmt
    : LBRACE RBRACE {$$ = newnode(yylineno,"compound_stmt", none, none, none,  0);}
    | LBRACE block_item_list RBRACE {$$ = $2;}
    ;

block_item_list
    : block_item {$$ = $1; }
    | block_item_list block_item {$$ = newnode(yylineno,"block_item_list", none, none, none,  2, $1, $2);}
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
    : SEMI {$$ = newnode(yylineno,"expression_stmt", none, none, none,  0);}
    | expression SEMI {$$=$1;}

    ;

if_stmt
    : IF LPAREN expression RPAREN statement ELSE statement {$$ = newnode(yylineno,"if_stmt", none, none, none,  3, $3, $5, $7);}
    | IF LPAREN expression RPAREN statement %prec THEN {$$ = newnode(yylineno,"if_stmt", none, none, none,  2, $3, $5);}
    ;

while_stmt
    : WHILE LPAREN expression RPAREN statement {$$ = newnode(yylineno,"while_stmt", none, none, none,  2, $3, $5);}
    ;

return_stmt
    : RETURN SEMI {$$ = newnode(yylineno,"return_stmt", none, none, none,  0);}
    | RETURN expression SEMI {$$ = newnode(yylineno,"return_stmt", none, none, none,  1, $2);}
    ;
    
expression
    : assignment_expression {$$=$1;}
    | simple_expression {$$=$1;}
    ;

assignment_expression
    : ID ASSIGN expression {$$ = newnode(yylineno,"assignment_expression", $1, none, none,  1, $3); int ex = exists(list2,$1); if(ex == 0){yyerror("Assignment before Declaration");}}
    | unary_expression  {$$=$1;}    ;

unary_expression 
    : INC_OP ID {$$ = newnode(yylineno,"unary_expression", $2, none, "++",  0); id_ex = find(list2, $2);}
    | DEC_OP ID {$$ = newnode(yylineno,"unary_expression", $2, none, "--",  0);}
    | postfix_expression {$$=$1;}
    ;

postfix_expression
    : ID INC_OP {$$ = newnode(yylineno,"postfix_expression", $1, none, "++",  0);}
    | ID DEC_OP {$$ = newnode(yylineno,"postfix_expression", $1, none, "--",  0);}
    ;

simple_expression
    : additive_expression {$$=$1;}
    | additive_expression relop additive_expression {$$ = newnode(yylineno,"simple_expression", none, none, $2,  2, $1, $3);}
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
    : term {$$=$1;}
    | additive_expression PLUS term {$$ = newnode(yylineno,"additive_expression", none, none, "+",  2, $1, $3);}
    | additive_expression MINUS term {$$ = newnode(yylineno,"additive_expression", none, none, "-",  2, $1, $3);}
    | PLUS additive_expression %prec STAR {$$ = newnode(yylineno,"additive_expression", none, none, "+",  1, $2);}
    | MINUS additive_expression %prec STAR {$$ = newnode(yylineno,"additive_expression", none, none, "-",  1, $2);}
    ;

term
    : factor {$$=$1;}
    | term STAR factor {$$ = newnode(yylineno,"term", none, none, "*",  2, $1, $3);}
    | term SLASH factor {$$ = newnode(yylineno,"term", none, none, "/",  2, $1, $3);}
    ;

factor
    : LPAREN expression RPAREN {$$=$2;}
    | ID {$$ = newnode(yylineno,"factor", $1, none, none,  0);}
    | call {$$=$1;}
    | NUM {$$ = newnode(yylineno,"factor", none, $1, none,  0); }
    ;
    
call
    : ID LPAREN RPAREN {$$ = newnode(yylineno,"call", $1, none, none,  0);}
    | ID LPAREN args RPAREN {$$ = newnode(yylineno,"call", $1, none, none,  1, $3);}
    ;

args
    : expression {$$=$1;}
    | expression COMMA args {$$ = newnode(yylineno,"args", none, none, none,  2, $1, $3);}
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
return 0; 
} 

void yyerror(const char *s)
{
	fflush(stdout);

	fprintf(stderr, "Error: %s on line number %d\n", s, yylineno);
}



