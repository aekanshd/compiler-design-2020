%{
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h> 
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
/*Stack*/



/*Data Structure to store quadruples*/
struct quadruple{
    char statement[30];
    char op[5];
    char arg1[20];
    char arg2[20];
    char res[20];
    int lineno;
    struct quadruple *next;
};
typedef struct quadruple quadruple;

struct quad_list{
    quadruple* head;
};
typedef struct quad_list quad_list;
quad_list* q_list1;

quadruple* create_quadruple(char* statement,char* op, char* arg1, char* arg2, char* res, int lineno) {
    quadruple* new_quadruple = (quadruple*)malloc(sizeof(quadruple));
    strcpy(new_quadruple->statement,statement);
    strcpy(new_quadruple->op,op);
    strcpy(new_quadruple->arg1,arg1);
    strcpy(new_quadruple->arg2,arg2);
    strcpy(new_quadruple->res,res);
    new_quadruple->lineno = lineno;
    //printf("Created quadruple record...\n");
    new_quadruple->next=NULL;
    return new_quadruple;
}
void insert_quadruple(quad_list * list, quadruple* q1) {
    quadruple * traverse = list->head;
    if(traverse==NULL) {
        list->head = q1;
    }
    else {
        while (traverse->next !=NULL) {
            traverse = traverse->next;
        }
        traverse->next = q1;
    }
}
char* get_three_add(quadruple* record) {
    char *res = (char *)malloc(sizeof(char)*50);
    if(strcmp(record->statement,"expression") == 0) {
        sprintf(res,"%s = %s %s %s",record->res,record->arg1,record->op,record->arg2);
    }
    else if(strcmp(record->statement,"assignment") == 0){
        sprintf(res,"%s = %s %s",record->res,record->op,record->arg1);   
    }
    else if(strcmp(record->statement,"conditional_goto") == 0){
        sprintf(res,"if %s %s %s goto %s",record->arg1,record->op,record->arg2,record->res);
    }
    else if(strcmp(record->statement,"goto") == 0){
        sprintf(res,"goto %s",record->res);
    }
    else if(strcmp(record->statement,"label") == 0 ){
        sprintf(res,"%s : ",record->res);
    }
    else if(strcmp(record->statement, "unary")==0){
    	sprintf(res, "%s = %s %s", record->res, record->arg1, record->arg2);
    }
    else if(strcmp(record->statement, "condition")==0){
    	sprintf(res, "%s", record->res);
    }
    return res;
}

void display_three_add(quad_list *list) {
    quadruple *traverse = list->head;
    while(traverse!=NULL) {
        printf("%s\n",get_three_add(traverse));
        traverse=traverse->next;
    }
}



int temp_count = 0;
int label_count = 0;
char * create_temp() {
    char *new_temp = (char*)malloc(sizeof(char)*10);
    sprintf(new_temp,"t%d",temp_count);
    temp_count+=1;
    //printf("Created temporary variable : %d",temp_count);
    return new_temp;
}
char * create_label() {
    char *new_label=(char*)malloc(sizeof(char)*10);
    sprintf(new_label,"L%d",label_count);
    label_count+=1;
    return new_label;
}
char * get_previous_temp() {
    //char *new_temp = (char*)malloc(sizeof(char)*10);
    //sprintf(new_temp,"t%d",temp_count-1);
    quadruple * traversal = q_list1->head;
    if(traversal==NULL) return "";
    while(traversal->next!=NULL) {
        traversal=traversal->next;
    }
    return traversal->res;
}
//end of quadruples code
struct node{
    int nl;
    char name[100];
    char dtype[200];
    int scope;
    int value;
    float fvalue;
    char cvalue;
    char rhs[200];
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
    t2 = root->head;
    while(t2!=NULL){
    	if(strcmp(t2->name, name)==0){
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
void insert(list1 *root, int nl, char name[100], char dtype[200], int scope, char rhs[200], char type[100]){
    int out = exists(root, name, scope);
    
    if(out == 0){
    node *temp = (node*)malloc(sizeof(node));
    temp->nl = nl;
    temp->scope = scope;
    strcpy(temp->dtype, dtype);
    strcpy(temp->rhs, rhs);
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

void update(list1 *root, char name[100], int scope,  char rhs[200]){
    node *t2 = root->head;
    if(find(root, name, scope) == NULL){
        return;
    }
    while(strcmp(t2->name, name)!=0){
        t2 = t2->next;
    }
    strcpy(t2->rhs, rhs);
    
    return;
}

void print(node *head){
    // printf("1\n");
    node *temp = head;
    printf("__________________________________________________________________\n");
    printf("|Line      |Name      |Scope     |value     |id_type   |datatype  |\n");
    printf("------------------------------------------------------------------\n");
    while(temp!=NULL){

        printf("|%-10d|%-10s|%-10d|%-10s|%-10s|%-10s|\n", temp->nl, temp->name, temp->scope, temp->rhs, temp->type, temp->dtype);    	
        temp=temp->next;
    }
    printf("------------------------------------------------------------------\n");
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

%token IF ELSE WHILE RETURN VOID INT FLOAT CHAR FOR
%token INC_OP DEC_OP PLUS MINUS STAR SLASH  LT LTEQ GT GTEQ EQ NEQ ASSIGN  
%token SEMI COMMA LPAREN RPAREN LSQUAR RSQUAR LBRACE RBRACE LCOMMENT RCOMMENT 
%token <str> ID NUM FLT
%token LETTER DIGIT
%token NONTOKEN ERROR ENDFILE
%token NL ENDL
%token STR
%token INSERTION EXTRACTION
%token CIN COUT
%token CLASS
%left PLUS MINUS
%left STAR SLASH

%nonassoc THEN
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE


%type<str> atree program external_declaration var_declaration init_declarator_list fun_declaration params_list compound_stmt declarator params block_item_list block_item call factor term additive_expression simple_expression unary_expression postfix_expression assignment_expression return_stmt while_stmt if_stmt expression statement args expression_stmt for_stmt
%type<str> relop declaration_specifiers stream_constructs op

%start atree
%%

atree:program {display_three_add(q_list1);}

program 
    : external_declaration {$$=$1; }
    | program external_declaration { }
    | class_declaration{}
    | program class_declaration{}
    ;

external_declaration
    : var_declaration {$$=$1; }
    | fun_declaration {$$=$1;}
    ;
class_declaration
	: declaration_specifiers ID LBRACE external_declaration RBRACE SEMI {insert(list2, yylineno, $2, "class", peek(stack), " ", "class");}
var_declaration
    : declaration_specifiers init_declarator_list SEMI 
    {}
    | declaration_specifiers array_dec SEMI {}
    | error SEMI{yyerrok;}
    ;
array_dec
	: ID LSQUAR NUM RSQUAR {insert(list2, yylineno, $1, type, peek(stack), " ", "ARRAY");}
	| STAR ID {insert(list2, yylineno, $2, type, peek(stack), " ", "PTR");}

init_declarator_list
    : ID {insert(list2, yylineno, $1, type, peek(stack), " ", "IDENT");}
    | ID ASSIGN expression {
                            char arg1[10];
                            sprintf(arg1,"%s",$3);
    						quadruple * new_record = create_quadruple("assignment","",arg1,"",$1, yylineno);
                            insert_quadruple(q_list1,new_record); 
                            insert(list2, yylineno, $1, type, peek(stack), " ", "IDENT");
                            update(list2, $1, peek(stack), $3);
                            iflag = 0;
                            fflag = 0;
                            cflag = 0; 
                        }
    | init_declarator_list COMMA ID { insert(list2, yylineno, $3, type, peek(stack), " ", "IDENT"); 
    }
    | init_declarator_list COMMA ID ASSIGN expression {
                            char arg1[10];
                            sprintf(arg1,"%s",$5);
    						quadruple * new_record = create_quadruple("assignment","",arg1,"",$3, yylineno);
                            insert_quadruple(q_list1,new_record); 
                            insert(list2, yylineno, $3, type, peek(stack), " ", "IDENT");
                            update(list2, $3, peek(stack), $5);
                            iflag = 0;
                            fflag = 0;
                            cflag = 0; 
                        }
    
    ;

declarator
    : LPAREN RPAREN {}
    | LPAREN params RPAREN {}
    ;

fun_declaration
    : declaration_specifiers ID declarator compound_stmt {insert(list2, yylineno, $2, type, peek(stack), " ", "FUNCT");}
    ;

declaration_specifiers
    : INT {$$=integer; strcpy(type, "int");}
    | VOID {$$="VOID"; strcpy(type, "void");}
    | FLOAT {$$="float"; strcpy(type, "float");}
    | CHAR {$$="char"; strcpy(type, "char");}
    | CLASS {$$="class"; strcpy(type, "class");}
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
    : LBRACE RBRACE {$$ = "$";}
    | LBRACE block_item_list RBRACE {$$ = $2;}
    ;

block_item_list
    : block_item {$$ = $1; }
    | block_item_list block_item {$$ = $2;}
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
    | stream_constructs {$$ = $1;}
    ;
stream_constructs
	: cout_cascade {}
	| cin {}
cout_cascade
	: COUT cascade_out SEMI
cascade_out
	: INSERTION op {if(errors==0) printf("%s", $2);}
	| INSERTION op cascade_out {if(errors==0) printf("%s", $2);}
	| INSERTION op INSERTION ENDL {if(errors==0) printf("%s\n", $2);}

cin
	: CIN EXTRACTION ID SEMI {
					id_ex = find(list2, $3, peek(stack));
					if(id_ex == NULL){
						printf("Error in Line %d : Usage before Declaration\n", yylineno);
						errors++;
					}
					else{
						int a;
						char b;
						float c;
						if(strcmp(id_ex->dtype, "int") == 0){

							scanf("%d", &a);
							id_ex->value = a;
						}
						if(strcmp(id_ex->dtype, "float") == 0){
							scanf("%f", &c);
							id_ex->fvalue = c;
						}
						if(strcmp(id_ex->dtype, "char")==0){
							scanf("%c", &b);
							id_ex->cvalue = b;
						}
					}
					}

op
	:NUM {$<str>$ = yylval.str;}
	|STR {$<str>$ = yylval.str;}
	|ID {
		id_ex = find(list2, $1, peek(stack));
		if(id_ex == NULL){
			printf("Error in Line %d : Usage before Declaration\n", yylineno);
			errors++;
		}
		else{
			if(strcmp(id_ex->dtype, "int") == 0) $<integer>$ = id_ex->value;
			if(strcmp(id_ex->dtype, "float") == 0) $<ft>$ = id_ex->fvalue;
			if(strcmp(id_ex->dtype, "char") == 0) $<chr>$ = id_ex->cvalue;

		}

	}

expression_stmt
    : SEMI {}
    | expression SEMI {$$=$1;}

    ;

if_stmt
    :IF LPAREN expression RPAREN {
    	quadruple* new_record;
        //Insert Condition
        char statement_type[20],arg1[10],arg2[10],arg3[10],temp[10],true_label[10],false_label[10];
        sprintf(statement_type,"conditional_goto");
        strcpy(arg1,$3);
        strcpy(true_label,create_label());
        new_record = create_quadruple(statement_type,arg1,"","",true_label, yylineno);
        insert_quadruple(q_list1,new_record);
        sprintf(statement_type,"goto");
        strcpy(false_label,create_label());
        new_record = create_quadruple(statement_type,"","","",false_label, yylineno); 
        insert_quadruple(q_list1,new_record);
        new_record = create_quadruple("label","","","",true_label, yylineno);
        insert_quadruple(q_list1,new_record);
        $<str>$=false_label;
    } statement {
        quadruple* new_record = create_quadruple("label","","","",$<str>5, yylineno);
        insert_quadruple(q_list1,new_record);
    } else_stmt {}
    ;
else_stmt : 
        %prec LOWER_THAN_ELSE
    | ELSE statement {}
    ;

while_stmt
    : WHILE  {
        quadruple* new_record;
        char while_label[10];
        strcpy(while_label,create_label());
        new_record = create_quadruple("label","","","",while_label, yylineno);
        insert_quadruple(q_list1,new_record);
        $<str>$=while_label;} LPAREN expression RPAREN
        {
        quadruple* new_record;
        char statement_type[20],arg1[10],arg2[10],arg3[10],temp[10],true_label[10],false_label[10];
        sprintf(statement_type,"conditional_goto");
        strcpy(arg1,$4);
        strcpy(true_label,create_label());
        new_record = create_quadruple(statement_type,arg1,"","",true_label, yylineno);
        insert_quadruple(q_list1,new_record);
        sprintf(statement_type,"goto");
        strcpy(false_label,create_label());
        new_record = create_quadruple(statement_type,"","","",false_label, yylineno); 
        insert_quadruple(q_list1,new_record);
        new_record = create_quadruple("label","","","",true_label, yylineno);
        insert_quadruple(q_list1,new_record);
        $<str>$=false_label;
    } statement {
        quadruple* new_record = create_quadruple("goto","","","",$<str>2, yylineno);
        insert_quadruple(q_list1,new_record);
        new_record = create_quadruple("label","","","",$<str>6, yylineno);
        insert_quadruple(q_list1,new_record);
    }
    ;

return_stmt
    : RETURN SEMI {}
    | RETURN expression SEMI {}
    ;
    
expression
    : assignment_expression {$$=$1;}
    | simple_expression {$$=$1;}
    ;

for_stmt
	: FOR {scope++;} LPAREN for_initialiser SEMI {
        quadruple* new_record;
        char for_label[10];
        strcpy(for_label,create_label());
        new_record = create_quadruple("label","","","",for_label, yylineno);
        insert_quadruple(q_list1,new_record);
        $<str>$=for_label;
	} 
	simple_expression SEMI for_update RPAREN { 
        quadruple* new_record;
        char break_label[10],body_label[10];
        strcpy(body_label,create_label());
        strcpy(break_label,create_label());
        new_record = create_quadruple("conditional_goto",$<str>7,"","",body_label, yylineno);
        insert_quadruple(q_list1,new_record);
        new_record = create_quadruple("goto","","","",break_label, yylineno);
        insert_quadruple(q_list1,new_record); 
        new_record = create_quadruple("label","","","",body_label, yylineno);
        insert_quadruple(q_list1,new_record);
        $<str>$=break_label;
        scope--;
    } statement {
        char update_stmt[20],iterable[20],operator[5],update_value[20],for_label[10];
        strcpy(update_stmt,$<str>9);
        strcpy(iterable,strtok(update_stmt, " "));
        strcpy(operator,strtok(NULL," "));
        strcpy(update_value,strtok(NULL," "));
        id_ex = find(list2, iterable, scope+1);
        update(list2, id_ex->name,scope+1,update_stmt);
        quadruple* new_record;
        new_record = create_quadruple("expression",operator,iterable,update_value,iterable, yylineno);
        insert_quadruple(q_list1,new_record);
        strcpy(for_label,$<str>6);
        new_record = create_quadruple("goto","","","",for_label, yylineno);
        insert_quadruple(q_list1,new_record); 
        char break_label[10];
        strcpy(break_label,$<str>11);
        new_record = create_quadruple("label","","","",break_label, yylineno);
        insert_quadruple(q_list1,new_record); 
    }
    ;
for_initialiser 
    : assignment_expression {}
    | declaration_specifiers ID ASSIGN expression {
                            char arg1[10];
                            sprintf(arg1,"%s",$4);
    						quadruple * new_record = create_quadruple("assignment","",arg1,"",$2, yylineno);
                            insert_quadruple(q_list1,new_record); 
                            insert(list2, yylineno, $2, type, scope, " ", "IDENT");
                            update(list2, $2, scope, $4);
                            iflag = 0;
                            fflag = 0;
                            cflag = 0;
                            }
    ;
for_update
    : INC_OP ID { 
                    id_ex = find(list2, $<str>2, scope); 
                    if(id_ex==NULL){
                        printf("Error on Lineno %d : Increment operator cannot be applied to an identifier that's not declared\n", yylineno);
                        errors++;
                        }
                    else {                        
                        char increement[20];
                        strcpy(increement,id_ex->name);
                        strcat(increement," + 1");
                        $<str>$ = increement;
                    }          
                }
    | DEC_OP ID { 
                    id_ex = find(list2, $<str>2, scope); 
                    if(id_ex==NULL){
                        printf("Error on Lineno %d : Increment operator cannot be applied to an identifier that's not declared\n", yylineno);
                        errors++;
                        }
                    else {
                        
                        char decreement[20];
                        strcpy(decreement,id_ex->name);
                        strcat(decreement," - 1");
                        $<str>$ = decreement;
                    }          
                }
    | ID INC_OP { 
                    id_ex = find(list2, $<str>2, scope); 
                    if(id_ex==NULL){
                        printf("Error on Lineno %d : Increment operator cannot be applied to an identifier that's not declared\n", yylineno);
                        errors++;
                        }
                    else {
                        
                        char increement[20];
                        strcpy(increement,id_ex->name);
                        strcat(increement," + 1");
                        $<str>$ = increement;
                    }          
                }
    | ID DEC_OP { 
                    id_ex = find(list2, $<str>2, scope); 
                    if(id_ex==NULL){
                        printf("Error on Lineno %d : Increment operator cannot be applied to an identifier that's not declared\n", yylineno);
                        errors++;
                        }
                    else {
                        char decreement[20];
                        strcpy(decreement,id_ex->name);
                        strcat(decreement," - 1");
                        $<str>$ = decreement;
                    }          
                }
    ;

assignment_expression
    : ID ASSIGN expression {
                            char arg1[10],previous_temp[10];
                            strcpy(previous_temp,get_previous_temp()); 
                            sprintf(arg1,"%s",$3);
    						quadruple * new_record = create_quadruple("assignment","",arg1,"",$1, yylineno);
                            insert_quadruple(q_list1,new_record); 
                            int ex = exists(list2,$1, scope); 
                            if(ex == 0) {printf("Error in Line %d : Assignment before Declaration\n", yylineno); errors++;}
                            id_ex = find(list2, $1, scope);
                            update(list2, $1, scope, $3);
                            iflag = 0;
                            cflag = 0;
                            fflag = 0;
                            

                        }
    | unary_expression  {$$=$1;}    ;

unary_expression 
    : INC_OP ID { 
                 id_ex = find(list2, $2, scope); 
                 if(id_ex==NULL){
                    printf("Error on Lineno %d : Increment operator cannot be applied to an identifier that's not declared\n", yylineno);
                    errors++;
                    }
                else {
                    if(strcmp(id_ex->dtype, "int")!=0){
                        printf("Error on Line %d : Type Mismatch\n", yylineno);
                        errors++;
                        }
                    else{
                    	quadruple* new_record;
                    	char statement_type[20],arg1[10],arg2[10],arg3[10],temp[10];
                    	sprintf(statement_type,"expression");
        
       					//strcpy(temp,create_temp());
        				new_record = create_quadruple(statement_type,"+",$<str>2,"1",$<str>2, yylineno); 
        				insert_quadruple(q_list1,new_record);
        				//char te[20];
        				//strcpy(te, "++");
        				//strcat(te, $2);
        				//insert(list2, yylineno, temp,"TEMP", scope, te, "TEMP");
                        char increement[20];
                        strcpy(increement,id_ex->name);
                        strcat(increement,"+1");
        				update(list2, id_ex->name,scope,increement);
                        $<str>$ = id_ex->rhs;
                        
                    }
                    }
                }
    | DEC_OP ID {
                 id_ex = find(list2, $2, scope); 
                 if(id_ex==NULL){
                    printf("Error on Lineno %d : Increment operator cannot be applied to an identifier that's not declared\n", yylineno);
                    errors++;}
                else {
                    if(strcmp(id_ex->dtype, "int")!=0){
                        printf("Error on Line %d : Type Mismatch\n", yylineno);
                        errors++;
                        }
                    else{
                    	quadruple* new_record;
                    	char statement_type[20],arg1[10],arg2[10],arg3[10],temp[10];
                    	sprintf(statement_type,"expression");
        
       					//strcpy(temp,create_temp());
        				new_record = create_quadruple(statement_type,"-",$<str>2,"1",$<str>2, yylineno); 
        				insert_quadruple(q_list1,new_record);
        				char te[20];
        				strcpy(te, "--");
        				strcat(te, $2);
        				
        				//insert(list2, yylineno, temp,"TEMP", scope, te, "TEMP");
                        char decreement[20];
                        strcpy(decreement,id_ex->name);
                        strcat(decreement,"+1");
        				update(list2, id_ex->name,scope,decreement);
                        $<str>$ = id_ex->rhs;                        
                    }
                    }

                }
    | postfix_expression {$$=$1;}
    ;

postfix_expression
    : ID INC_OP {
                 id_ex = find(list2, $1, scope); 
                 if(id_ex==NULL){
                    printf("Error on Lineno %d : Increment operator cannot be applied to an identifier that's not declared\n", yylineno);
                    errors++;
                    }
                else {
                    if(strcmp(id_ex->dtype, "int")!=0){
                        printf("Error on Line %d : Type Mismatch\n", yylineno);
                        errors++;
                        }
                    else{
                        quadruple* new_record;
                    	char statement_type[20],arg1[10],arg2[10],arg3[10],temp[10];
                    	sprintf(statement_type,"expression");
        
       					//strcpy(temp,create_temp());
        				new_record = create_quadruple(statement_type,"+",$<str>1,"1",$<str>1, yylineno); 
        				insert_quadruple(q_list1,new_record);
        				strcat($1, "++");
        				char increement[20];
                        strcpy(increement,id_ex->name);
                        strcat(increement,"+1");
        				//insert(list2, yylineno, temp,"TEMP", scope, $1, "TEMP");
                        $<str>$ = id_ex->rhs;
        				update(list2, id_ex->name,scope,increement);
                    }
                    }
                }
    | ID DEC_OP {
                 id_ex = find(list2, $1, scope); 
                 if(id_ex==NULL){
                    printf("Error on Lineno %d : Increment operator cannot be applied to an identifier that's not declared\n", yylineno);
                    errors++;

                    }
                else {
                    if(strcmp(id_ex->dtype, "int")!=0){
                        printf("Error on Line %d : Type Mismatch\n", yylineno);
                        errors++;
                        }
                    else{

                    	quadruple* new_record;
                    	char statement_type[20],arg1[10],arg2[10],arg3[10],temp[10];
                    	sprintf(statement_type,"expression");
        
       					//strcpy(temp,create_temp());
        				new_record = create_quadruple(statement_type,"-",$<str>1,"1",$<str>1, yylineno);  
        				insert_quadruple(q_list1,new_record);
        				strcat($1, "--");
        				char decreement[20];
                        strcpy(decreement,id_ex->name);
                        strcat(decreement,"+1");
        				//insert(list2, yylineno, temp,"TEMP", scope, $1, "TEMP");
        				$<str>$ = id_ex->rhs;
        				update(list2, id_ex->name, scope,decreement);
                    }
                        
                    }
                    }

                
    ;

simple_expression
    : additive_expression {$$=$1;}
    | additive_expression relop additive_expression {

				strcat($1, $2);
				strcat($1, $3);
				$$ = $1;                        
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
        }
    | additive_expression PLUS additive_expression {

        quadruple* new_record;
        
        char statement_type[20],arg1[10],arg2[10],arg3[10],temp[10];
        sprintf(statement_type,"expression");
        
        strcpy(temp,create_temp());
        new_record = create_quadruple(statement_type,"+",$1,$3,temp, yylineno); 
        insert_quadruple(q_list1,new_record);
        strcat($1, "+");
        strcat($1, $3);
        insert(list2, yylineno, temp,"TEMP", scope, $1, "TEMP");
        $$ = temp;
    }
    | additive_expression MINUS additive_expression{
    	quadruple* new_record;
        
        char statement_type[20],arg1[10],arg2[10],arg3[10],temp[10];
        sprintf(statement_type,"expression");
        
        strcpy(temp,create_temp());
        new_record = create_quadruple(statement_type,"-",$1,$3,temp, yylineno); 
        insert_quadruple(q_list1,new_record);
        strcat($1, "-");
        strcat($1, $3);
        insert(list2, yylineno, temp,"TEMP", scope, $1, "TEMP");
        $$ = temp;
    	}
    | PLUS additive_expression %prec STAR {$$ = $2;}
    | MINUS additive_expression %prec STAR {char temp[20];strcpy(temp,"-");strcat(temp,$2);$$ = temp;}
    ;

term
    : factor {

              $$ = $1;
            }
    | term STAR factor {
    	quadruple* new_record;
        
        char statement_type[20],arg1[10],arg2[10],arg3[10],temp[10];
        sprintf(statement_type,"expression");
        
        strcpy(temp,create_temp());
        new_record = create_quadruple(statement_type,"*",$1,$3,temp, yylineno); 
        insert_quadruple(q_list1,new_record);
        
    	strcat($1, "*");
    	strcat($1, $3);
    	insert(list2, yylineno, temp,"TEMP", scope, $1, "TEMP");
    	$$ = temp;
		}
    | term SLASH factor {
    	quadruple* new_record;
        
        char statement_type[20],arg1[10],arg2[10],arg3[10],temp[10];
        sprintf(statement_type,"expression");
        
        strcpy(temp,create_temp());
        new_record = create_quadruple(statement_type,"/",$1,$3,temp, yylineno); 
        insert_quadruple(q_list1,new_record);
        
    	strcat($1, "/");
    	strcat($1, $3);
    	insert(list2, yylineno, temp,"TEMP", scope, $1, "TEMP");
    	$$ = temp;
		}
    ;

factor
    : LPAREN expression RPAREN {$$=$2; }
    | ID {

          id_ex = find(list2, $1, scope);
          if(id_ex == NULL){
            printf("Error on %d, Assignment RHS not declared\n", yylineno);
            errors++;
            $$ = "$";}
          else{
          	$$ = $1;
            
            
          }}
    | call {$$=$1;}
    | NUM { 
           $$ = yylval.str;
           
           }
    |FLT{
        $$ = yylval.str;
    	}
    |STR {}
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
int
main(argc, argv)
int argc;
char** argv;
{
//syntree = fopen("syntree.txt", "w");
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
q_list1 = (quad_list*)malloc(sizeof(quad_list));
q_list1->head = NULL;
yyparse();  
print(list2->head);
// fclose(syntree);

if(errors>0){
	printf("%d Errors Found\n", errors);
} else {
    //display_three_add(q_list1);
}

return 0; 
} 

void yyerror(const char *s)
{
	fflush(stdout);
	errors++;
	fprintf(stderr, "Error: %s on line number %d\n", s, yylineno);
}



