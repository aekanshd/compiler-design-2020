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
int errors = 0;
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
    
    fprintf(syntree, "%s line:%d node: %s ", 
        indent,
        node->lineNo,
        node->nodeType,
        node->string,
        node->value, 
        node->dataType);
    if(strcmp(node->string, "none")!=0){
        fprintf(syntree, "element: %s ", node->string);
    }
    if(strcmp(node->value, "none")!=0){
        fprintf(syntree, "value: %s ", node->value);
    }
    if(strcmp(node->dataType, "none")!=0){
        fprintf(syntree, "dataType: %s\n", node->dataType);
    }
    if(strcmp(node->dataType, "nonde")==0){
        fprintf(syntree, "\n");
    }
    int i;
    if (node->Nchildren > 0){
        fprintf(syntree, "%s\n", indent);
        incIndent();
        for (i=0;i<node->Nchildren;i++){
            printNode(node->child[i]);
        }
        decIndent();
        fprintf(syntree, "%s", indent);
    }
    fprintf(syntree, "%s\n", indent);
}


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

int exists(list1* root, char name[100], int scope){
    if(root == NULL || root->head == NULL){
        return 0;
    }
    node *t2 = root->head;
    while(t2!=NULL){
        if(strcmp(t2->name, name) == 0 && t2->scope == scope){
            
            
            return 1;
        }
        t2 = t2->next;
    }
    return 0;

}
node* find(list1 *root, char name[200], int scope){
    if(root == NULL || root->head == NULL){
        return NULL;
    }
    node *t2 = root->head;
    while(t2!=NULL){
        if(strcmp(t2->name, name)==0 && t2->scope == scope){return t2;}
        t2 = t2->next;
    }
    t2 = root->head;
    while(t2!=NULL){
        if(strcmp(t2->name, name)==0){
            return t2;
        }
        t2 = t2->next;
    }
    return t2;

}
node* id_ex;
void insert(list1 *root, int nl, char name[100], char dtype[200], int scope, int value, float fvalue, char cvalue, char type[100]){
    int out = exists(root, name, scope);
    
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
else{
    errors++;
    printf("Error at line %d: Multiple declarations\n", nl);
}
}

void update(list1 *root, char name[100], int scope,  int value, float fvalue, char cvalue){
    node *t2 = root->head;
    if(find(root, name, scope) == NULL){
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
    printf("____________________________________________________\n");
    printf("| Line | Name | Scope | value | id_type | datatype |\n");
    printf("----------------------------------------------------\n");
    while(temp!=NULL){

        if(strcmp(temp->dtype, "int")==0)

            printf("|   %d  |   %s  |   %d  |  %d  |  %s  |  %s  |\n", temp->nl, temp->name, temp->scope, temp->value, temp->type, temp->dtype);
        else if(strcmp(temp->dtype, "float")==0)
            printf("|   %d  |   %s  |   %d  |  %.1f  |  %s  |  %s  |\n", temp->nl, temp->name, temp->scope, temp->fvalue, temp->type, temp->dtype);
        else if(strcmp(temp->dtype, "char")==0)
            printf("|   %d  |   %s  |   %d  |  %c  |  %s  |  %s  |\n", temp->nl, temp->name, temp->scope, temp->cvalue, temp->type, temp->dtype);
        else
            printf("|   %d  |   %s  |   %d  |  --  |  %s  |  %s  |\n", temp->nl, temp->name, temp->scope, temp->type, temp->dtype);         
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

%token IF ELSE WHILE RETURN VOID INT FLOAT CHAR FOR
%token INC_OP DEC_OP PLUS MINUS STAR SLASH  LT LTEQ GT GTEQ EQ NEQ ASSIGN  
%token SEMI COMMA LPAREN RPAREN LSQUAR RSQUAR LBRACE RBRACE LCOMMENT RCOMMENT 
%token <str> ID NUM FLT STR
%token LETTER DIGIT
%token NONTOKEN ERROR ENDFILE
%token NL ENDL
%token INSERTION EXTRACTION
%token CIN COUT
%token CLASS
%left PLUS MINUS
%left STAR SLASH
%nonassoc THEN
%nonassoc ELSE
%type<ast> atree program external_declaration var_declaration init_declarator_list fun_declaration params_list compound_stmt declarator params block_item_list block_item factor call term additive_expression simple_expression unary_expression postfix_expression assignment_expression return_stmt while_stmt if_stmt expression statement args expression_stmt stream_constructs op for_stmt class_declaration array_dec cout_cascade cascade_out cin
%type<str> relop declaration_specifiers 

%start atree
%%

atree:program {printNode($1);}

program 
    : external_declaration {$$=$1;}
    | program external_declaration {$$=newnode(yylineno, STR(program), none, none, none,  2, $1, $2); }
    | class_declaration{$$ = $1;}
    | program class_declaration{$$ = newnode(yylineno, "program", none, none, none, 2, $1, $2);printf("Here\n");}
    ;

external_declaration
    : var_declaration {$$=$1;}
    | fun_declaration {$$=$1;}

    ;
class_declaration
    : declaration_specifiers ID LBRACE external_declaration RBRACE SEMI {insert(list2, yylineno, $2, "class", scope, -1, 0.0, '\0', "class"); $$ = newnode(yylineno, "class_declaration", $2, none, "class", 1, $4);}
var_declaration
    : declaration_specifiers init_declarator_list SEMI
    {$$=newnode(yylineno, "var_declaration", none, none, $1, 1, $2);}
    | declaration_specifiers array_dec SEMI {$$ = newnode(yylineno, "var_declaration", none, none, $1, 1, $2);}
    | error SEMI{yyerrok; printf("Here\n");}

    ;
array_dec
    : ID LSQUAR NUM RSQUAR {$$ = newnode(yylineno, "array_dec", $1, none, none, 0);insert(list2, yylineno, $1, type, scope, -1, 0.0, '\0', "ARRAY");}
    | STAR ID {$$ = newnode(yylineno, "array_dec", $2, none, none, 0);insert(list2, yylineno, $2, type, scope, -1, 0.0, '\0', "PTR");}


init_declarator_list
    : ID {$$ = newnode(yylineno, "init_declarator_list", $1, none, none, 0);insert(list2, yylineno, $1, type, scope, -1, 0.0, '\0',"IDENT");}
    | ID ASSIGN expression {$$ = newnode(yylineno,"init_declarator_list", $1, none, none,  1, $3);
                            insert(list2, yylineno, $1, type, scope, -1,0.0,'\0', "IDENT");
                            update(list2, $1, scope, iexpval, fexpval, cexpval);
                            iflag = 0;
                            fflag = 0;
                            cflag = 0; 
                        }
    | init_declarator_list COMMA ID{$$ = newnode(yylineno,"init_declarator_list", $3, none, none,  1, $1); insert(list2, yylineno, $3, type, scope, -1,0.0,'\0', "IDENT"); }
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
    | CLASS {$$="class"; strcpy(type, "class");}
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
    | for_stmt {$$ = $1;}
    | stream_constructs {$$= $1;}
    ;
stream_constructs
    : cout_cascade {$$ = $1;}
    | cin {$$ = $1;}
cout_cascade
    : COUT cascade_out SEMI {$$ = newnode(yylineno, "cout_cascade", none, none, none, 1, $2);}

cascade_out
    : INSERTION op {$$ = newnode(yylineno, "cascade_out", none, none, none, 1, $2);}
    | INSERTION op cascade_out {$$ = newnode(yylineno, "cascade_out", none, none, none, 2, $2, $3);}
    | INSERTION op INSERTION ENDL {$$ = newnode(yylineno, "cascade_out", none,none, none, 1, $2);}
cin
    : CIN EXTRACTION ID SEMI {$$ = newnode(yylineno, "cin", none, none, none, 1,  $3);}
op
    :NUM {$$ = newnode(yylineno, "op", none, $1, none, 0);}
    |STR {$$ = newnode(yylineno, "op", none, $1, none, 0);}
    |ID {$$ = newnode(yylineno, "op", $1, none, none, 0);}
expression_stmt
    : SEMI {$$ = newnode(yylineno,"expression_stmt", none, none, none,  0);}
    | expression SEMI {$$=$1;}

    ;

if_stmt
    : IF LPAREN expression RPAREN statement ELSE statement {$$ = newnode(yylineno,"if_stmt", none, none, none,  3, $3, $5, $7); }
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
for_stmt
    : FOR LPAREN assignment_expression SEMI simple_expression SEMI unary_expression RPAREN compound_stmt{$$ = newnode(yylineno, "for_stmt", none, none, none, 4, $3, $5,$7, $9);}
assignment_expression
    : ID ASSIGN expression {$$ = newnode(yylineno,"assignment_expression", $1, none, none,  1, $3); 
                            int ex = exists(list2,$1, scope); 
                            if(ex == 0) {printf("Error on Lineno %d: Assignment before Declaration\n",yylineno);errors++;}
                            id_ex = find(list2, $1,scope);
                            iflag = 0;
                            cflag = 0;
                            fflag = 0;
                            update(list2, $1,scope, iexpval, fexpval, cexpval);

                        }
    | unary_expression  {$$=$1;}    ;

unary_expression 
    : INC_OP ID {$$ = newnode(yylineno,"unary_expression", $2, none, "++",  0); 
                 id_ex = find(list2, $2, scope); 
                 if(id_ex==NULL){
                    printf("Error on Lineno %d: Increment operator cannot be applied to an identifier that's not declared\n", yylineno);
                    errors++;}
                else {
                    if(strcmp(id_ex->dtype, "int")!=0){
                        printf("Error on Line %d: Type Mismatch\n", yylineno);
                        errors++;}
                    else
                        ++id_ex->value;
                    }
                }
    | DEC_OP ID {$$ = newnode(yylineno,"unary_expression", $2, none, "--",  0);
                 id_ex = find(list2, $2, scope); 
                 if(id_ex==NULL){
                    printf("Error on Lineno %d: Increment operator cannot be applied to an identifier that's not declared\n", yylineno);
                    errors++;}
                else {
                    if(strcmp(id_ex->dtype, "int")!=0){
                        printf("Error on Line %d: Type Mismatch\n", yylineno);
                        errors++;}
                    else
                        --id_ex->value;
                    }

                }
    | postfix_expression {$$=$1;}
    ;

postfix_expression
    : ID INC_OP {$$ = newnode(yylineno,"postfix_expression", $1, none, "++",  0);
                 id_ex = find(list2, $1, scope); 
                 if(id_ex==NULL){
                    printf("Error on Lineno %d: Increment operator cannot be applied to an identifier that's not declared\n", yylineno);
                    errors++;}
                else {
                    if(strcmp(id_ex->dtype, "int")!=0){
                        printf("Error on Line %d: Type Mismatch\n", yylineno);
                        errors++;}
                    else
                        id_ex->value++;
                    }
                }
    | ID DEC_OP {$$ = newnode(yylineno,"postfix_expression", $1, none, "--",  0);
                 id_ex = find(list2, $1, scope); 
                 if(id_ex==NULL){
                    printf("Error on Lineno %d: Increment operator cannot be applied to an identifier that's not declared\n", yylineno);
                    errors++;}
                else {
                    if(strcmp(id_ex->dtype, "int")!=0){
                        printf("Error on Line %d: Type Mismatch\n", yylineno);
                        errors++;}
                    else
                        id_ex->value--;
                    }

                }
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
    : term {$$=$1; 
            if(iflag == 1)
                iexpval = itermval;
            if(fflag == 1)
                fexpval = ftermval;
            if(cflag == 1)
                cexpval = ctermval;
        }
    | additive_expression PLUS term {$$ = newnode(yylineno,"additive_expression", none, none, "+",  2, $1, $3); }
    | additive_expression MINUS term {$$ = newnode(yylineno,"additive_expression", none, none, "-",  2, $1, $3);}
    | PLUS additive_expression %prec STAR {$$ = newnode(yylineno,"additive_expression", none, none, "+",  1, $2);}
    | MINUS additive_expression %prec STAR {$$ = newnode(yylineno,"additive_expression", none, none, "-",  1, $2);}
    ;

term
    : factor {$$=$1; 
              if(iflag == 1)
                itermval = iasval;
              if(fflag == 1)
                ftermval = fasval;
              if(cflag == 1)
                ctermval = casval;
            }
    | term STAR factor {$$ = newnode(yylineno,"term", none, none, "*",  2, $1, $3);}
    | term SLASH factor {$$ = newnode(yylineno,"term", none, none, "/",  2, $1, $3);}
    ;

factor
    : LPAREN expression RPAREN {$$=$2;}
    | ID {$$ = newnode(yylineno,"factor", $1, none, none,  0);
          id_ex = find(list2, $1, scope);
          if(id_ex == NULL){
            printf("Error on %d, Assignment RHS not declared\n", yylineno);
            errors++;}
          else{
            if(strcmp(id_ex->dtype, "int")==0) 
            {
                iasval = id_ex->value;
                iflag = 1;
                cflag = 0;
                fflag = 0;
            }
            if(strcmp(id_ex->dtype, "float")==0){
                fasval = id_ex->fvalue;
                iflag = 0;
                fflag = 1;
                cflag = 0;
            }
            if(strcmp(id_ex->dtype, "char")==0){
                casval = id_ex->cvalue;
                iflag = 0;
                fflag = 0;
                cflag = 1;
            }
          }}
    | call {$$=$1;}
    | NUM {$$ = newnode(yylineno,"factor", none, $1, none,  0); 
           iasval = atoi(yylval.str); iflag = 1; cflag=0; fflag=0;
           }
    | FLT{$$ = newnode(yylineno, "factor", none, $1, none, 0);iasval = atof(yylval.str); iflag=0; cflag=0; fflag=1;}
    | STR{$$ = newnode(yylineno, "factor", none, $1, none, 0); }
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

if(errors>0){
    printf("%d Errors Found\n", errors);
}  
print(list2->head);
fclose(syntree);
return 0; 
} 

void yyerror(const char *s)
{
	fflush(stdout);
    errors++;
	fprintf(stderr, "Error: %s on line number %d\n", s, yylineno);
}



