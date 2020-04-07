
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 ".\\int_code2.y"

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
struct Stack {
	int top;
	unsigned capacity;
	int* data;
};

struct Stack* createStack(unsigned capacity)
{
	struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
	stack->capacity = capacity;
	stack->top = -1;
	stack->data = (int*)malloc(stack->capacity * sizeof(int));
	return stack;
}

int isFull(struct Stack* stack)
{
	return stack->top == stack->capacity - 1;
}

int isEmpty(struct Stack* stack)
{
	return stack->top == -1;
}

void push(struct Stack* stack, int item)
{
    if(stack == NULL) {
        stack = createStack(100);
        push(stack, 0);
    }
	if (isFull(stack))
		return;
	stack->data[++stack->top] = item;
}

int pop(struct Stack* stack)
{
    if(stack == NULL) {
        stack = createStack(100);
        push(stack, 0);
    }
	if (isEmpty(stack))
		return -32767;
	return stack->data[stack->top--];
}

int peek(struct Stack* stack)
{
    if(stack == NULL) {
        stack = createStack(100);
        push(stack, 0);
    }
	if (isEmpty(stack))
		return -32767;
	return stack->data[stack->top];
}

struct Stack* stack;



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





/* Line 189 of yacc.c  */
#line 408 "int_code2.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

/* "%code requires" blocks.  */

/* Line 209 of yacc.c  */
#line 334 ".\\int_code2.y"





/* Line 209 of yacc.c  */
#line 438 "int_code2.tab.c"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IF = 258,
     ELSE = 259,
     WHILE = 260,
     RETURN = 261,
     VOID = 262,
     INT = 263,
     FLOAT = 264,
     CHAR = 265,
     FOR = 266,
     INC_OP = 267,
     DEC_OP = 268,
     PLUS = 269,
     MINUS = 270,
     STAR = 271,
     SLASH = 272,
     LT = 273,
     LTEQ = 274,
     GT = 275,
     GTEQ = 276,
     EQ = 277,
     NEQ = 278,
     ASSIGN = 279,
     SEMI = 280,
     COMMA = 281,
     LPAREN = 282,
     RPAREN = 283,
     LSQUAR = 284,
     RSQUAR = 285,
     LBRACE = 286,
     RBRACE = 287,
     LCOMMENT = 288,
     RCOMMENT = 289,
     ID = 290,
     NUM = 291,
     FLT = 292,
     LETTER = 293,
     DIGIT = 294,
     NONTOKEN = 295,
     ERROR = 296,
     ENDFILE = 297,
     NL = 298,
     ENDL = 299,
     STR = 300,
     INSERTION = 301,
     EXTRACTION = 302,
     CIN = 303,
     COUT = 304,
     CLASS = 305,
     THEN = 306,
     LOWER_THAN_ELSE = 307
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 337 ".\\int_code2.y"

	char chr;
	int integer;
	float ft;
	char *str;



/* Line 214 of yacc.c  */
#line 516 "int_code2.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 528 "int_code2.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  15
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   260

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  48
/* YYNRULES -- Number of rules.  */
#define YYNRULES  112
/* YYNRULES -- Number of states.  */
#define YYNSTATES  191

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   307

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    12,    15,    17,    19,
      26,    30,    34,    37,    42,    45,    47,    51,    55,    61,
      64,    68,    73,    75,    77,    79,    81,    83,    86,    89,
      94,    99,   101,   103,   106,   110,   112,   115,   117,   119,
     121,   123,   125,   127,   129,   131,   133,   135,   137,   141,
     144,   148,   153,   158,   160,   162,   164,   166,   169,   170,
     171,   180,   181,   184,   185,   186,   194,   197,   201,   203,
     205,   206,   207,   208,   221,   223,   228,   231,   234,   237,
     240,   244,   246,   249,   252,   254,   257,   260,   262,   266,
     268,   270,   272,   274,   276,   278,   280,   284,   288,   291,
     294,   296,   300,   304,   308,   310,   312,   314,   316,   318,
     322,   327,   329
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      54,     0,    -1,    55,    -1,    56,    -1,    55,    56,    -1,
      57,    -1,    55,    57,    -1,    58,    -1,    62,    -1,    63,
      35,    31,    56,    32,    25,    -1,    63,    60,    25,    -1,
      63,    59,    25,    -1,     1,    25,    -1,    35,    29,    36,
      30,    -1,    16,    35,    -1,    35,    -1,    35,    24,    84,
      -1,    60,    26,    35,    -1,    60,    26,    35,    24,    84,
      -1,    27,    28,    -1,    27,    65,    28,    -1,    63,    35,
      61,    66,    -1,     8,    -1,     7,    -1,     9,    -1,    10,
      -1,    50,    -1,     8,    35,    -1,     9,    35,    -1,    64,
      26,     8,    35,    -1,    64,    26,     9,    35,    -1,    64,
      -1,     7,    -1,    31,    32,    -1,    31,    67,    32,    -1,
      68,    -1,    67,    68,    -1,    58,    -1,    69,    -1,    75,
      -1,    66,    -1,    76,    -1,    80,    -1,    83,    -1,    85,
      -1,    70,    -1,    71,    -1,    73,    -1,    49,    72,    25,
      -1,    46,    74,    -1,    46,    74,    72,    -1,    46,    74,
      46,    44,    -1,    48,    47,    35,    25,    -1,    36,    -1,
      45,    -1,    35,    -1,    25,    -1,    84,    25,    -1,    -1,
      -1,     3,    27,    84,    28,    77,    69,    78,    79,    -1,
      -1,     4,    69,    -1,    -1,    -1,     5,    81,    27,    84,
      28,    82,    69,    -1,     6,    25,    -1,     6,    84,    25,
      -1,    91,    -1,    94,    -1,    -1,    -1,    -1,    11,    86,
      27,    89,    25,    87,    94,    25,    90,    28,    88,    69,
      -1,    91,    -1,    63,    35,    24,    84,    -1,    12,    35,
      -1,    13,    35,    -1,    35,    12,    -1,    35,    13,    -1,
      35,    24,    84,    -1,    92,    -1,    12,    35,    -1,    13,
      35,    -1,    93,    -1,    35,    12,    -1,    35,    13,    -1,
      96,    -1,    96,    95,    96,    -1,    18,    -1,    19,    -1,
      20,    -1,    21,    -1,    22,    -1,    23,    -1,    97,    -1,
      96,    14,    96,    -1,    96,    15,    96,    -1,    14,    96,
      -1,    15,    96,    -1,    98,    -1,    97,    16,    98,    -1,
      97,    17,    98,    -1,    27,    84,    28,    -1,    35,    -1,
      99,    -1,    36,    -1,    37,    -1,    45,    -1,    35,    27,
      28,    -1,    35,    27,   100,    28,    -1,    84,    -1,    84,
      26,   100,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   369,   369,   372,   373,   374,   375,   379,   380,   383,
     385,   387,   388,   391,   392,   395,   396,   407,   409,   424,
     425,   429,   433,   434,   435,   436,   437,   441,   442,   443,
     444,   449,   450,   454,   455,   459,   460,   464,   465,   469,
     470,   471,   472,   473,   474,   475,   478,   479,   481,   483,
     484,   485,   488,   515,   516,   517,   533,   534,   539,   555,
     539,   561,   562,   566,   573,   566,   597,   598,   602,   603,
     607,   607,   615,   607,   649,   650,   663,   676,   690,   704,
     720,   736,   739,   771,   803,   807,   836,   873,   874,   883,
     884,   885,   886,   887,   888,   892,   894,   909,   923,   924,
     928,   932,   947,   965,   966,   978,   979,   983,   986,   990,
     991,   995,   996
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "WHILE", "RETURN", "VOID",
  "INT", "FLOAT", "CHAR", "FOR", "INC_OP", "DEC_OP", "PLUS", "MINUS",
  "STAR", "SLASH", "LT", "LTEQ", "GT", "GTEQ", "EQ", "NEQ", "ASSIGN",
  "SEMI", "COMMA", "LPAREN", "RPAREN", "LSQUAR", "RSQUAR", "LBRACE",
  "RBRACE", "LCOMMENT", "RCOMMENT", "ID", "NUM", "FLT", "LETTER", "DIGIT",
  "NONTOKEN", "ERROR", "ENDFILE", "NL", "ENDL", "STR", "INSERTION",
  "EXTRACTION", "CIN", "COUT", "CLASS", "THEN", "LOWER_THAN_ELSE",
  "$accept", "atree", "program", "external_declaration",
  "class_declaration", "var_declaration", "array_dec",
  "init_declarator_list", "declarator", "fun_declaration",
  "declaration_specifiers", "params_list", "params", "compound_stmt",
  "block_item_list", "block_item", "statement", "stream_constructs",
  "cout_cascade", "cascade_out", "cin", "op", "expression_stmt", "if_stmt",
  "@1", "$@2", "else_stmt", "while_stmt", "@3", "@4", "return_stmt",
  "expression", "for_stmt", "$@5", "@6", "@7", "for_initialiser",
  "for_update", "assignment_expression", "unary_expression",
  "postfix_expression", "simple_expression", "relop",
  "additive_expression", "term", "factor", "call", "args", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    53,    54,    55,    55,    55,    55,    56,    56,    57,
      58,    58,    58,    59,    59,    60,    60,    60,    60,    61,
      61,    62,    63,    63,    63,    63,    63,    64,    64,    64,
      64,    65,    65,    66,    66,    67,    67,    68,    68,    69,
      69,    69,    69,    69,    69,    69,    70,    70,    71,    72,
      72,    72,    73,    74,    74,    74,    75,    75,    77,    78,
      76,    79,    79,    81,    82,    80,    83,    83,    84,    84,
      86,    87,    88,    85,    89,    89,    90,    90,    90,    90,
      91,    91,    92,    92,    92,    93,    93,    94,    94,    95,
      95,    95,    95,    95,    95,    96,    96,    96,    96,    96,
      97,    97,    97,    98,    98,    98,    98,    98,    98,    99,
      99,   100,   100
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     2,     1,     1,     6,
       3,     3,     2,     4,     2,     1,     3,     3,     5,     2,
       3,     4,     1,     1,     1,     1,     1,     2,     2,     4,
       4,     1,     1,     2,     3,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     2,
       3,     4,     4,     1,     1,     1,     1,     2,     0,     0,
       8,     0,     2,     0,     0,     7,     2,     3,     1,     1,
       0,     0,     0,    12,     1,     4,     2,     2,     2,     2,
       3,     1,     2,     2,     1,     2,     2,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     2,     2,
       1,     3,     3,     3,     1,     1,     1,     1,     1,     3,
       4,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    23,    22,    24,    25,    26,     0,     0,     3,
       5,     7,     8,     0,    12,     1,     4,     6,     0,    15,
       0,     0,    14,     0,     0,     0,     0,     0,    11,    10,
       0,     0,     0,     0,     0,     0,   104,   106,   107,   108,
      16,    68,    81,    84,    69,    87,    95,   100,   105,    32,
       0,     0,    19,    31,     0,     0,     0,     0,     0,    21,
      17,    82,    83,   104,    98,    99,     0,    85,    86,     0,
       0,     0,     0,    89,    90,    91,    92,    93,    94,     0,
       0,     0,    27,    28,     0,    20,    13,     0,    15,     0,
      63,     0,    70,    56,    33,     0,     0,    37,     0,    40,
       0,    35,    38,    45,    46,    47,    39,    41,    42,    43,
       0,    44,     0,   103,    80,   109,   111,     0,    96,    97,
      88,   101,   102,     0,     0,     9,     0,     0,    66,     0,
       0,     0,     0,     0,    15,    34,    36,    57,    18,     0,
     110,    29,    30,     0,     0,    67,     0,     0,    55,    53,
      54,    49,    48,   112,    58,     0,     0,     0,     0,    74,
      52,     0,    50,     0,    64,     0,    71,    51,    59,     0,
       0,     0,    61,    65,    75,     0,     0,    60,     0,    62,
       0,     0,     0,     0,    76,    77,    78,    79,    72,     0,
      73
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     7,     8,     9,    10,    11,    20,    21,    27,    12,
      13,    53,    54,    99,   100,   101,   102,   103,   104,   133,
     105,   151,   106,   107,   163,   172,   177,   108,   127,   169,
     109,   110,   111,   130,   171,   189,   158,   183,    41,    42,
      43,    44,    79,    45,    46,    47,    48,   117
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -58
static const yytype_int16 yypact[] =
{
      50,   -16,   -58,   -58,   -58,   -58,   -58,    37,     6,   -58,
     -58,   -58,   -58,     3,   -58,   -58,   -58,   -58,   -18,   193,
      14,    65,   -58,   129,   179,    19,    50,    10,   -58,   -58,
      15,    26,    28,    72,    72,   129,   203,   -58,   -58,   -58,
     -58,   -58,   -58,   -58,   -58,   214,   -12,   -58,   -58,   -58,
      40,    66,   -58,    78,    82,    95,   119,     5,    17,   -58,
     103,   -58,   -58,   130,   -58,   -58,   135,   -58,   -58,   129,
      57,    72,    72,   -58,   -58,   -58,   -58,   -58,   -58,    72,
      61,    61,   -58,   -58,   106,   -58,   -58,   155,   215,   158,
     -58,   169,   -58,   -58,   -58,   143,   152,   -58,    29,   -58,
     123,   -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,
     177,   -58,   129,   -58,   -58,   -58,   182,   183,   -58,   -58,
     131,   -58,   -58,   184,   186,   -58,   129,   191,   -58,   200,
     199,   196,   104,   213,   -21,   -58,   -58,   -58,   -58,   129,
     -58,   -58,   -58,   212,   129,   -58,    70,   216,   -58,   -58,
     -58,   197,   -58,   -58,   -58,   217,    99,   211,   222,   -58,
     -58,   117,   -58,   164,   -58,   224,   -58,   -58,   -58,   164,
     129,    72,   245,   -58,   -58,   225,   164,   -58,    -2,   -58,
     218,   219,   180,   223,   -58,   -58,   -58,   -58,   -58,   164,
     -58
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -58,   -58,   -58,    87,   244,   -57,   -58,   -58,   -58,   -58,
     -24,   -58,   -58,   228,   -58,   156,    34,   -58,   -58,   107,
     -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,
     -58,   -23,   -58,   -58,   -58,   -58,   -58,   -58,   111,   -58,
     -58,    88,   -58,     2,   -58,    38,   -58,   121
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -3
static const yytype_int16 yytable[] =
{
      40,    97,    57,    23,    80,    81,    -2,     1,    25,    14,
     180,   181,    66,     2,     3,     4,     5,    22,     1,    18,
      89,    18,    90,    91,     2,     3,     4,     5,    92,    31,
      32,    33,    34,   182,    98,    64,    65,    15,    19,    28,
      88,    58,    93,    97,    35,    18,   114,   116,    58,    94,
      60,     1,    36,    37,    38,    55,     6,     2,     3,     4,
       5,    61,    39,    62,   134,    95,    96,     6,   129,    31,
      32,    33,    34,   118,   119,    82,    98,     2,     3,     4,
       5,   120,    31,    32,    35,   115,    33,    34,    35,   138,
      29,    30,    36,    37,    38,    16,    63,    37,    38,    35,
       6,    83,    39,   143,    84,   156,    39,    63,    37,    38,
      85,    67,    68,    56,   123,   124,   116,    39,   121,   122,
       6,   155,   157,    69,     1,    86,    89,   112,    90,    91,
       2,     3,     4,     5,    92,    31,    32,    33,    34,   148,
     149,    31,    32,    33,    34,    71,    72,   174,    93,   150,
      35,    87,   148,   149,    58,   135,    35,    70,    36,    37,
      38,   167,   150,   113,    36,    37,    38,    89,    39,    90,
      91,    95,    96,     6,    39,    92,    31,    32,    33,    34,
     125,    31,    32,    33,    34,   126,    49,    50,    51,    93,
     131,    35,   186,   187,   128,    58,    35,   168,   132,    36,
      37,    38,   137,   173,    36,    37,    38,    52,   139,    39,
     179,   140,    95,    96,    39,    67,    68,    23,   144,   141,
      24,   142,    25,   190,    26,   145,   146,    69,    71,    72,
      70,   147,    73,    74,    75,    76,    77,    78,   152,    23,
     154,   160,    24,   161,    25,   164,   165,   166,   170,   176,
     178,   188,    17,   184,   185,    59,   136,   159,   162,   175,
     153
};

static const yytype_uint8 yycheck[] =
{
      23,    58,    26,    24,    16,    17,     0,     1,    29,    25,
      12,    13,    35,     7,     8,     9,    10,    35,     1,    16,
       3,    16,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    35,    58,    33,    34,     0,    35,    25,
      35,    31,    25,   100,    27,    16,    69,    70,    31,    32,
      35,     1,    35,    36,    37,    36,    50,     7,     8,     9,
      10,    35,    45,    35,    35,    48,    49,    50,    91,    12,
      13,    14,    15,    71,    72,    35,   100,     7,     8,     9,
      10,    79,    12,    13,    27,    28,    14,    15,    27,   112,
      25,    26,    35,    36,    37,     8,    35,    36,    37,    27,
      50,    35,    45,   126,    26,    35,    45,    35,    36,    37,
      28,    12,    13,    26,     8,     9,   139,    45,    80,    81,
      50,   144,   146,    24,     1,    30,     3,    24,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    35,
      36,    12,    13,    14,    15,    14,    15,   170,    25,    45,
      27,    32,    35,    36,    31,    32,    27,    27,    35,    36,
      37,    44,    45,    28,    35,    36,    37,     3,    45,     5,
       6,    48,    49,    50,    45,    11,    12,    13,    14,    15,
      25,    12,    13,    14,    15,    27,     7,     8,     9,    25,
      47,    27,    12,    13,    25,    31,    27,   163,    46,    35,
      36,    37,    25,   169,    35,    36,    37,    28,    26,    45,
     176,    28,    48,    49,    45,    12,    13,    24,    27,    35,
      27,    35,    29,   189,    31,    25,    27,    24,    14,    15,
      27,    35,    18,    19,    20,    21,    22,    23,    25,    24,
      28,    25,    27,    46,    29,    28,    35,    25,    24,     4,
      25,    28,     8,    35,    35,    27,   100,   146,   151,   171,
     139
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     7,     8,     9,    10,    50,    54,    55,    56,
      57,    58,    62,    63,    25,     0,    56,    57,    16,    35,
      59,    60,    35,    24,    27,    29,    31,    61,    25,    25,
      26,    12,    13,    14,    15,    27,    35,    36,    37,    45,
      84,    91,    92,    93,    94,    96,    97,    98,    99,     7,
       8,     9,    28,    64,    65,    36,    56,    63,    31,    66,
      35,    35,    35,    35,    96,    96,    84,    12,    13,    24,
      27,    14,    15,    18,    19,    20,    21,    22,    23,    95,
      16,    17,    35,    35,    26,    28,    30,    32,    35,     3,
       5,     6,    11,    25,    32,    48,    49,    58,    63,    66,
      67,    68,    69,    70,    71,    73,    75,    76,    80,    83,
      84,    85,    24,    28,    84,    28,    84,   100,    96,    96,
      96,    98,    98,     8,     9,    25,    27,    81,    25,    84,
      86,    47,    46,    72,    35,    32,    68,    25,    84,    26,
      28,    35,    35,    84,    27,    25,    27,    35,    35,    36,
      45,    74,    25,   100,    28,    84,    35,    63,    89,    91,
      25,    46,    72,    77,    28,    35,    25,    44,    69,    82,
      24,    87,    78,    69,    84,    94,     4,    79,    25,    69,
      12,    13,    35,    90,    35,    35,    12,    13,    28,    88,
      69
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 369 ".\\int_code2.y"
    {display_three_add(q_list1);;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 372 ".\\int_code2.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str); ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 373 ".\\int_code2.y"
    { ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 374 ".\\int_code2.y"
    {;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 375 ".\\int_code2.y"
    {;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 379 ".\\int_code2.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str); ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 380 ".\\int_code2.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 383 ".\\int_code2.y"
    {insert(list2, yylineno, (yyvsp[(2) - (6)].str), "class", peek(stack), " ", "class");;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 386 ".\\int_code2.y"
    {;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 387 ".\\int_code2.y"
    {;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 388 ".\\int_code2.y"
    {yyerrok;;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 391 ".\\int_code2.y"
    {insert(list2, yylineno, (yyvsp[(1) - (4)].str), type, peek(stack), " ", "ARRAY");;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 392 ".\\int_code2.y"
    {insert(list2, yylineno, (yyvsp[(2) - (2)].str), type, peek(stack), " ", "PTR");;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 395 ".\\int_code2.y"
    {insert(list2, yylineno, (yyvsp[(1) - (1)].str), type, peek(stack), " ", "IDENT");;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 396 ".\\int_code2.y"
    {
                            char arg1[10];
                            sprintf(arg1,"%s",(yyvsp[(3) - (3)].str));
    						quadruple * new_record = create_quadruple("assignment","",arg1,"",(yyvsp[(1) - (3)].str), yylineno);
                            insert_quadruple(q_list1,new_record); 
                            insert(list2, yylineno, (yyvsp[(1) - (3)].str), type, peek(stack), " ", "IDENT");
                            update(list2, (yyvsp[(1) - (3)].str), peek(stack), (yyvsp[(3) - (3)].str));
                            iflag = 0;
                            fflag = 0;
                            cflag = 0; 
                        ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 407 ".\\int_code2.y"
    { insert(list2, yylineno, (yyvsp[(3) - (3)].str), type, peek(stack), " ", "IDENT"); 
    ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 409 ".\\int_code2.y"
    {
                            char arg1[10];
                            sprintf(arg1,"%s",(yyvsp[(5) - (5)].str));
    						quadruple * new_record = create_quadruple("assignment","",arg1,"",(yyvsp[(3) - (5)].str), yylineno);
                            insert_quadruple(q_list1,new_record); 
                            insert(list2, yylineno, (yyvsp[(3) - (5)].str), type, peek(stack), " ", "IDENT");
                            update(list2, (yyvsp[(3) - (5)].str), peek(stack), (yyvsp[(5) - (5)].str));
                            iflag = 0;
                            fflag = 0;
                            cflag = 0; 
                        ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 424 ".\\int_code2.y"
    {;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 425 ".\\int_code2.y"
    {;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 429 ".\\int_code2.y"
    {insert(list2, yylineno, (yyvsp[(2) - (4)].str), type, peek(stack), " ", "FUNCT");;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 433 ".\\int_code2.y"
    {(yyval.str)=integer; strcpy(type, "int");;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 434 ".\\int_code2.y"
    {(yyval.str)="VOID"; strcpy(type, "void");;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 435 ".\\int_code2.y"
    {(yyval.str)="float"; strcpy(type, "float");;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 436 ".\\int_code2.y"
    {(yyval.str)="char"; strcpy(type, "char");;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 437 ".\\int_code2.y"
    {(yyval.str)="class"; strcpy(type, "class");;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 441 ".\\int_code2.y"
    {;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 442 ".\\int_code2.y"
    {;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 443 ".\\int_code2.y"
    {;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 444 ".\\int_code2.y"
    {;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 449 ".\\int_code2.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 450 ".\\int_code2.y"
    {;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 454 ".\\int_code2.y"
    {(yyval.str) = "$";;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 455 ".\\int_code2.y"
    {(yyval.str) = (yyvsp[(2) - (3)].str);;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 459 ".\\int_code2.y"
    {(yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 460 ".\\int_code2.y"
    {(yyval.str) = (yyvsp[(2) - (2)].str);;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 464 ".\\int_code2.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str); ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 465 ".\\int_code2.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 469 ".\\int_code2.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 470 ".\\int_code2.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 471 ".\\int_code2.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 472 ".\\int_code2.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 473 ".\\int_code2.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 474 ".\\int_code2.y"
    {(yyval.str) = (yyvsp[(1) - (1)].str);;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 475 ".\\int_code2.y"
    {(yyval.str) = (yyvsp[(1) - (1)].str);;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 478 ".\\int_code2.y"
    {;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 479 ".\\int_code2.y"
    {;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 483 ".\\int_code2.y"
    {if(errors==0) printf("%s", (yyvsp[(2) - (2)].str));;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 484 ".\\int_code2.y"
    {if(errors==0) printf("%s", (yyvsp[(2) - (3)].str));;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 485 ".\\int_code2.y"
    {if(errors==0) printf("%s\n", (yyvsp[(2) - (4)].str));;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 488 ".\\int_code2.y"
    {
					id_ex = find(list2, (yyvsp[(3) - (4)].str), peek(stack));
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
					;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 515 ".\\int_code2.y"
    {(yyval.str) = yylval.str;;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 516 ".\\int_code2.y"
    {(yyval.str) = yylval.str;;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 517 ".\\int_code2.y"
    {
		id_ex = find(list2, (yyvsp[(1) - (1)].str), peek(stack));
		if(id_ex == NULL){
			printf("Error in Line %d : Usage before Declaration\n", yylineno);
			errors++;
		}
		else{
			if(strcmp(id_ex->dtype, "int") == 0) (yyval.integer) = id_ex->value;
			if(strcmp(id_ex->dtype, "float") == 0) (yyval.ft) = id_ex->fvalue;
			if(strcmp(id_ex->dtype, "char") == 0) (yyval.chr) = id_ex->cvalue;

		}

	;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 533 ".\\int_code2.y"
    {;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 534 ".\\int_code2.y"
    {(yyval.str)=(yyvsp[(1) - (2)].str);;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 539 ".\\int_code2.y"
    {
    	quadruple* new_record;
        //Insert Condition
        char statement_type[20],arg1[10],arg2[10],arg3[10],temp[10],true_label[10],false_label[10];
        sprintf(statement_type,"conditional_goto");
        strcpy(arg1,(yyvsp[(3) - (4)].str));
        strcpy(true_label,create_label());
        new_record = create_quadruple(statement_type,arg1,"","",true_label, yylineno);
        insert_quadruple(q_list1,new_record);
        sprintf(statement_type,"goto");
        strcpy(false_label,create_label());
        new_record = create_quadruple(statement_type,"","","",false_label, yylineno); 
        insert_quadruple(q_list1,new_record);
        new_record = create_quadruple("label","","","",true_label, yylineno);
        insert_quadruple(q_list1,new_record);
        (yyval.str)=false_label;
    ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 555 ".\\int_code2.y"
    {
        quadruple* new_record = create_quadruple("label","","","",(yyvsp[(5) - (6)].str), yylineno);
        insert_quadruple(q_list1,new_record);
    ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 558 ".\\int_code2.y"
    {;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 562 ".\\int_code2.y"
    {;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 566 ".\\int_code2.y"
    {
        quadruple* new_record;
        char while_label[10];
        strcpy(while_label,create_label());
        new_record = create_quadruple("label","","","",while_label, yylineno);
        insert_quadruple(q_list1,new_record);
        (yyval.str)=while_label;;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 573 ".\\int_code2.y"
    {
        quadruple* new_record;
        char statement_type[20],arg1[10],arg2[10],arg3[10],temp[10],true_label[10],false_label[10];
        sprintf(statement_type,"conditional_goto");
        strcpy(arg1,(yyvsp[(4) - (5)].str));
        strcpy(true_label,create_label());
        new_record = create_quadruple(statement_type,arg1,"","",true_label, yylineno);
        insert_quadruple(q_list1,new_record);
        sprintf(statement_type,"goto");
        strcpy(false_label,create_label());
        new_record = create_quadruple(statement_type,"","","",false_label, yylineno); 
        insert_quadruple(q_list1,new_record);
        new_record = create_quadruple("label","","","",true_label, yylineno);
        insert_quadruple(q_list1,new_record);
        (yyval.str)=false_label;
    ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 588 ".\\int_code2.y"
    {
        quadruple* new_record = create_quadruple("goto","","","",(yyvsp[(2) - (7)].str), yylineno);
        insert_quadruple(q_list1,new_record);
        new_record = create_quadruple("label","","","",(yyvsp[(6) - (7)].str), yylineno);
        insert_quadruple(q_list1,new_record);
    ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 597 ".\\int_code2.y"
    {;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 598 ".\\int_code2.y"
    {;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 602 ".\\int_code2.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 603 ".\\int_code2.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 607 ".\\int_code2.y"
    {scope++;;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 607 ".\\int_code2.y"
    {
        quadruple* new_record;
        char for_label[10];
        strcpy(for_label,create_label());
        new_record = create_quadruple("label","","","",for_label, yylineno);
        insert_quadruple(q_list1,new_record);
        (yyval.str)=for_label;
	;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 615 ".\\int_code2.y"
    { 
        quadruple* new_record;
        char break_label[10],body_label[10];
        strcpy(body_label,create_label());
        strcpy(break_label,create_label());
        new_record = create_quadruple("conditional_goto",(yyvsp[(7) - (10)].str),"","",body_label, yylineno);
        insert_quadruple(q_list1,new_record);
        new_record = create_quadruple("goto","","","",break_label, yylineno);
        insert_quadruple(q_list1,new_record); 
        new_record = create_quadruple("label","","","",body_label, yylineno);
        insert_quadruple(q_list1,new_record);
        (yyval.str)=break_label;
        scope--;
    ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 628 ".\\int_code2.y"
    {
        char update_stmt[20],iterable[20],operator[5],update_value[20],for_label[10];
        strcpy(update_stmt,(yyvsp[(9) - (12)].str));
        strcpy(iterable,strtok(update_stmt, " "));
        strcpy(operator,strtok(NULL," "));
        strcpy(update_value,strtok(NULL," "));
        id_ex = find(list2, iterable, scope+1);
        update(list2, id_ex->name,scope+1,update_stmt);
        quadruple* new_record;
        new_record = create_quadruple("expression",operator,iterable,update_value,iterable, yylineno);
        insert_quadruple(q_list1,new_record);
        strcpy(for_label,(yyvsp[(6) - (12)].str));
        new_record = create_quadruple("goto","","","",for_label, yylineno);
        insert_quadruple(q_list1,new_record); 
        char break_label[10];
        strcpy(break_label,(yyvsp[(11) - (12)].str));
        new_record = create_quadruple("label","","","",break_label, yylineno);
        insert_quadruple(q_list1,new_record); 
    ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 649 ".\\int_code2.y"
    {;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 650 ".\\int_code2.y"
    {
                            char arg1[10];
                            sprintf(arg1,"%s",(yyvsp[(4) - (4)].str));
    						quadruple * new_record = create_quadruple("assignment","",arg1,"",(yyvsp[(2) - (4)].str), yylineno);
                            insert_quadruple(q_list1,new_record); 
                            insert(list2, yylineno, (yyvsp[(2) - (4)].str), type, scope, " ", "IDENT");
                            update(list2, (yyvsp[(2) - (4)].str), scope, (yyvsp[(4) - (4)].str));
                            iflag = 0;
                            fflag = 0;
                            cflag = 0;
                            ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 663 ".\\int_code2.y"
    { 
                    id_ex = find(list2, (yyvsp[(2) - (2)].str), scope); 
                    if(id_ex==NULL){
                        printf("Error on Lineno %d : Increment operator cannot be applied to an identifier that's not declared\n", yylineno);
                        errors++;
                        }
                    else {                        
                        char increement[20];
                        strcpy(increement,id_ex->name);
                        strcat(increement," + 1");
                        (yyval.str) = increement;
                    }          
                ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 676 ".\\int_code2.y"
    { 
                    id_ex = find(list2, (yyvsp[(2) - (2)].str), scope); 
                    if(id_ex==NULL){
                        printf("Error on Lineno %d : Increment operator cannot be applied to an identifier that's not declared\n", yylineno);
                        errors++;
                        }
                    else {
                        
                        char decreement[20];
                        strcpy(decreement,id_ex->name);
                        strcat(decreement," - 1");
                        (yyval.str) = decreement;
                    }          
                ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 690 ".\\int_code2.y"
    { 
                    id_ex = find(list2, (yyvsp[(2) - (2)].str), scope); 
                    if(id_ex==NULL){
                        printf("Error on Lineno %d : Increment operator cannot be applied to an identifier that's not declared\n", yylineno);
                        errors++;
                        }
                    else {
                        
                        char increement[20];
                        strcpy(increement,id_ex->name);
                        strcat(increement," + 1");
                        (yyval.str) = increement;
                    }          
                ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 704 ".\\int_code2.y"
    { 
                    id_ex = find(list2, (yyvsp[(2) - (2)].str), scope); 
                    if(id_ex==NULL){
                        printf("Error on Lineno %d : Increment operator cannot be applied to an identifier that's not declared\n", yylineno);
                        errors++;
                        }
                    else {
                        char decreement[20];
                        strcpy(decreement,id_ex->name);
                        strcat(decreement," - 1");
                        (yyval.str) = decreement;
                    }          
                ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 720 ".\\int_code2.y"
    {
                            char arg1[10],previous_temp[10];
                            strcpy(previous_temp,get_previous_temp()); 
                            sprintf(arg1,"%s",(yyvsp[(3) - (3)].str));
    						quadruple * new_record = create_quadruple("assignment","",arg1,"",(yyvsp[(1) - (3)].str), yylineno);
                            insert_quadruple(q_list1,new_record); 
                            int ex = exists(list2,(yyvsp[(1) - (3)].str), scope); 
                            if(ex == 0) {printf("Error in Line %d : Assignment before Declaration\n", yylineno); errors++;}
                            id_ex = find(list2, (yyvsp[(1) - (3)].str), scope);
                            update(list2, (yyvsp[(1) - (3)].str), scope, (yyvsp[(3) - (3)].str));
                            iflag = 0;
                            cflag = 0;
                            fflag = 0;
                            

                        ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 736 ".\\int_code2.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 739 ".\\int_code2.y"
    { 
                 id_ex = find(list2, (yyvsp[(2) - (2)].str), scope); 
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
        				new_record = create_quadruple(statement_type,"+",(yyvsp[(2) - (2)].str),"1",(yyvsp[(2) - (2)].str), yylineno); 
        				insert_quadruple(q_list1,new_record);
        				//char te[20];
        				//strcpy(te, "++");
        				//strcat(te, $2);
        				//insert(list2, yylineno, temp,"TEMP", scope, te, "TEMP");
                        char increement[20];
                        strcpy(increement,id_ex->name);
                        strcat(increement,"+1");
        				update(list2, id_ex->name,scope,increement);
                        (yyval.str) = id_ex->rhs;
                        
                    }
                    }
                ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 771 ".\\int_code2.y"
    {
                 id_ex = find(list2, (yyvsp[(2) - (2)].str), scope); 
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
        				new_record = create_quadruple(statement_type,"-",(yyvsp[(2) - (2)].str),"1",(yyvsp[(2) - (2)].str), yylineno); 
        				insert_quadruple(q_list1,new_record);
        				char te[20];
        				strcpy(te, "--");
        				strcat(te, (yyvsp[(2) - (2)].str));
        				
        				//insert(list2, yylineno, temp,"TEMP", scope, te, "TEMP");
                        char decreement[20];
                        strcpy(decreement,id_ex->name);
                        strcat(decreement,"+1");
        				update(list2, id_ex->name,scope,decreement);
                        (yyval.str) = id_ex->rhs;                        
                    }
                    }

                ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 803 ".\\int_code2.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 807 ".\\int_code2.y"
    {
                 id_ex = find(list2, (yyvsp[(1) - (2)].str), scope); 
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
        				new_record = create_quadruple(statement_type,"+",(yyvsp[(1) - (2)].str),"1",(yyvsp[(1) - (2)].str), yylineno); 
        				insert_quadruple(q_list1,new_record);
        				strcat((yyvsp[(1) - (2)].str), "++");
        				char increement[20];
                        strcpy(increement,id_ex->name);
                        strcat(increement,"+1");
        				//insert(list2, yylineno, temp,"TEMP", scope, $1, "TEMP");
                        (yyval.str) = id_ex->rhs;
        				update(list2, id_ex->name,scope,increement);
                    }
                    }
                ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 836 ".\\int_code2.y"
    {
                 id_ex = find(list2, (yyvsp[(1) - (2)].str), scope); 
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
        				new_record = create_quadruple(statement_type,"-",(yyvsp[(1) - (2)].str),"1",(yyvsp[(1) - (2)].str), yylineno);  
        				insert_quadruple(q_list1,new_record);
        				strcat((yyvsp[(1) - (2)].str), "--");
        				char decreement[20];
                        strcpy(decreement,id_ex->name);
                        strcat(decreement,"+1");
        				//insert(list2, yylineno, temp,"TEMP", scope, $1, "TEMP");
        				(yyval.str) = id_ex->rhs;
        				update(list2, id_ex->name, scope,decreement);
                    }
                        
                    }
                    ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 873 ".\\int_code2.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 874 ".\\int_code2.y"
    {

				strcat((yyvsp[(1) - (3)].str), (yyvsp[(2) - (3)].str));
				strcat((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str));
				(yyval.str) = (yyvsp[(1) - (3)].str);                        
    		;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 883 ".\\int_code2.y"
    {(yyval.str) = "<";;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 884 ".\\int_code2.y"
    {(yyval.str) = "<=";;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 885 ".\\int_code2.y"
    {(yyval.str) = ">";;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 886 ".\\int_code2.y"
    {(yyval.str) = ">=";;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 887 ".\\int_code2.y"
    {(yyval.str) = "==";;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 888 ".\\int_code2.y"
    {(yyval.str) = "!=";;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 892 ".\\int_code2.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);
        ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 894 ".\\int_code2.y"
    {

        quadruple* new_record;
        
        char statement_type[20],arg1[10],arg2[10],arg3[10],temp[10];
        sprintf(statement_type,"expression");
        
        strcpy(temp,create_temp());
        new_record = create_quadruple(statement_type,"+",(yyvsp[(1) - (3)].str),(yyvsp[(3) - (3)].str),temp, yylineno); 
        insert_quadruple(q_list1,new_record);
        strcat((yyvsp[(1) - (3)].str), "+");
        strcat((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str));
        insert(list2, yylineno, temp,"TEMP", scope, (yyvsp[(1) - (3)].str), "TEMP");
        (yyval.str) = temp;
    ;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 909 ".\\int_code2.y"
    {
    	quadruple* new_record;
        
        char statement_type[20],arg1[10],arg2[10],arg3[10],temp[10];
        sprintf(statement_type,"expression");
        
        strcpy(temp,create_temp());
        new_record = create_quadruple(statement_type,"-",(yyvsp[(1) - (3)].str),(yyvsp[(3) - (3)].str),temp, yylineno); 
        insert_quadruple(q_list1,new_record);
        strcat((yyvsp[(1) - (3)].str), "-");
        strcat((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str));
        insert(list2, yylineno, temp,"TEMP", scope, (yyvsp[(1) - (3)].str), "TEMP");
        (yyval.str) = temp;
    	;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 923 ".\\int_code2.y"
    {(yyval.str) = (yyvsp[(2) - (2)].str);;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 924 ".\\int_code2.y"
    {char temp[20];strcpy(temp,"-");strcat(temp,(yyvsp[(2) - (2)].str));(yyval.str) = temp;;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 928 ".\\int_code2.y"
    {

              (yyval.str) = (yyvsp[(1) - (1)].str);
            ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 932 ".\\int_code2.y"
    {
    	quadruple* new_record;
        
        char statement_type[20],arg1[10],arg2[10],arg3[10],temp[10];
        sprintf(statement_type,"expression");
        
        strcpy(temp,create_temp());
        new_record = create_quadruple(statement_type,"*",(yyvsp[(1) - (3)].str),(yyvsp[(3) - (3)].str),temp, yylineno); 
        insert_quadruple(q_list1,new_record);
        
    	strcat((yyvsp[(1) - (3)].str), "*");
    	strcat((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str));
    	insert(list2, yylineno, temp,"TEMP", scope, (yyvsp[(1) - (3)].str), "TEMP");
    	(yyval.str) = temp;
		;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 947 ".\\int_code2.y"
    {
    	quadruple* new_record;
        
        char statement_type[20],arg1[10],arg2[10],arg3[10],temp[10];
        sprintf(statement_type,"expression");
        
        strcpy(temp,create_temp());
        new_record = create_quadruple(statement_type,"/",(yyvsp[(1) - (3)].str),(yyvsp[(3) - (3)].str),temp, yylineno); 
        insert_quadruple(q_list1,new_record);
        
    	strcat((yyvsp[(1) - (3)].str), "/");
    	strcat((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str));
    	insert(list2, yylineno, temp,"TEMP", scope, (yyvsp[(1) - (3)].str), "TEMP");
    	(yyval.str) = temp;
		;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 965 ".\\int_code2.y"
    {(yyval.str)=(yyvsp[(2) - (3)].str); ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 966 ".\\int_code2.y"
    {

          id_ex = find(list2, (yyvsp[(1) - (1)].str), scope);
          if(id_ex == NULL){
            printf("Error on %d, Assignment RHS not declared\n", yylineno);
            errors++;
            (yyval.str) = "$";}
          else{
          	(yyval.str) = (yyvsp[(1) - (1)].str);
            
            
          };}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 978 ".\\int_code2.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 979 ".\\int_code2.y"
    { 
           (yyval.str) = yylval.str;
           
           ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 983 ".\\int_code2.y"
    {
        (yyval.str) = yylval.str;
    	;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 986 ".\\int_code2.y"
    {;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 990 ".\\int_code2.y"
    {;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 991 ".\\int_code2.y"
    {;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 995 ".\\int_code2.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 996 ".\\int_code2.y"
    {;}
    break;



/* Line 1455 of yacc.c  */
#line 3105 "int_code2.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 999 ".\\int_code2.y"

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




