
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
#line 1 ".\\int_code.y"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h> 
#include "lex.yy.c"
//typedef char* string;
//#define YYSTYPE string
FILE *symtab;
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

FILE *icgout;



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
    	printf("%s\n", get_three_add(traverse));
        fprintf(icgout, "%s\n",get_three_add(traverse));

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
    fprintf(symtab, "__________________________________________________________________\n");
    printf("|Line      |Name      |Scope     |value     |id_type   |datatype  |\n");
    fprintf(symtab, "|Line      |Name      |Scope     |value     |id_type   |datatype  |\n");
    printf("------------------------------------------------------------------\n");
    fprintf(symtab, "------------------------------------------------------------------\n");
    while(temp!=NULL){

        printf("|%-10d|%-10s|%-10d|%-10s|%-10s|%-10s|\n", temp->nl, temp->name, temp->scope, temp->rhs, temp->type, temp->dtype);
        fprintf(symtab, "|%-10d|%-10s|%-10d|%-10s|%-10s|%-10s|\n", temp->nl, temp->name, temp->scope, temp->rhs, temp->type, temp->dtype);      	
        temp=temp->next;
    }

    printf("------------------------------------------------------------------\n");
    fprintf(symtab, "------------------------------------------------------------------\n");
}

void reset_scope(list1 *root, int current_scope) {
    if(root == NULL || root->head == NULL){
        return;
    }
    node *t2 = root->head;
    while (t2!=NULL) {
        if(t2->scope > current_scope) {
            t2->scope=-1;
        }
        t2=t2->next;
    }
}

struct expression_details{
    int value;
    char type[200];
};
typedef struct expression_details exp_det;
exp_det det1;


/* Line 189 of yacc.c  */
#line 369 "int_code.tab.c"

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
#line 295 ".\\int_code.y"





/* Line 209 of yacc.c  */
#line 399 "int_code.tab.c"

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
     PREPROC = 306,
     THEN = 307,
     LOWER_THAN_ELSE = 308
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 298 ".\\int_code.y"

	char chr;
	int integer;
	float ft;
	char *str;



/* Line 214 of yacc.c  */
#line 478 "int_code.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 490 "int_code.tab.c"

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
#define YYFINAL  17
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   274

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  48
/* YYNRULES -- Number of rules.  */
#define YYNRULES  114
/* YYNRULES -- Number of states.  */
#define YYNSTATES  199

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   308

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
      45,    46,    47,    48,    49,    50,    51,    52,    53
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    16,    21,    23,    26,
      28,    30,    37,    41,    45,    48,    53,    56,    58,    62,
      66,    72,    75,    79,    84,    86,    88,    90,    92,    94,
      97,   100,   105,   110,   112,   114,   117,   121,   123,   126,
     128,   130,   132,   134,   136,   138,   140,   142,   144,   146,
     148,   152,   155,   159,   164,   169,   171,   173,   175,   177,
     180,   181,   182,   191,   192,   195,   196,   197,   205,   208,
     212,   214,   216,   217,   218,   219,   232,   234,   239,   242,
     245,   248,   251,   255,   257,   260,   263,   265,   268,   271,
     273,   277,   279,   281,   283,   285,   287,   289,   291,   295,
     299,   302,   305,   307,   311,   315,   319,   321,   323,   325,
     327,   329,   333,   338,   340
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      55,     0,    -1,    56,    -1,    57,    -1,    56,    57,    -1,
      56,    51,    18,    35,    20,    -1,    51,    18,    35,    20,
      -1,    58,    -1,    56,    58,    -1,    59,    -1,    63,    -1,
      64,    35,    31,    57,    32,    25,    -1,    64,    61,    25,
      -1,    64,    60,    25,    -1,     1,    25,    -1,    35,    29,
      36,    30,    -1,    16,    35,    -1,    35,    -1,    35,    24,
      85,    -1,    61,    26,    35,    -1,    61,    26,    35,    24,
      85,    -1,    27,    28,    -1,    27,    66,    28,    -1,    64,
      35,    62,    67,    -1,     8,    -1,     7,    -1,     9,    -1,
      10,    -1,    50,    -1,     8,    35,    -1,     9,    35,    -1,
      65,    26,     8,    35,    -1,    65,    26,     9,    35,    -1,
      65,    -1,     7,    -1,    31,    32,    -1,    31,    68,    32,
      -1,    69,    -1,    68,    69,    -1,    59,    -1,    70,    -1,
      76,    -1,    67,    -1,    77,    -1,    81,    -1,    84,    -1,
      86,    -1,    71,    -1,    72,    -1,    74,    -1,    49,    73,
      25,    -1,    46,    75,    -1,    46,    75,    73,    -1,    46,
      75,    46,    44,    -1,    48,    47,    35,    25,    -1,    36,
      -1,    45,    -1,    35,    -1,    25,    -1,    85,    25,    -1,
      -1,    -1,     3,    27,    85,    28,    78,    70,    79,    80,
      -1,    -1,     4,    70,    -1,    -1,    -1,     5,    82,    27,
      85,    28,    83,    70,    -1,     6,    25,    -1,     6,    85,
      25,    -1,    92,    -1,    95,    -1,    -1,    -1,    -1,    11,
      87,    27,    90,    25,    88,    95,    25,    91,    28,    89,
      70,    -1,    92,    -1,    64,    35,    24,    85,    -1,    12,
      35,    -1,    13,    35,    -1,    35,    12,    -1,    35,    13,
      -1,    35,    24,    85,    -1,    93,    -1,    12,    35,    -1,
      13,    35,    -1,    94,    -1,    35,    12,    -1,    35,    13,
      -1,    97,    -1,    97,    96,    97,    -1,    18,    -1,    19,
      -1,    20,    -1,    21,    -1,    22,    -1,    23,    -1,    98,
      -1,    97,    14,    97,    -1,    97,    15,    97,    -1,    14,
      97,    -1,    15,    97,    -1,    99,    -1,    98,    16,    98,
      -1,    98,    17,    98,    -1,    27,    85,    28,    -1,    35,
      -1,   100,    -1,    36,    -1,    37,    -1,    45,    -1,    35,
      27,    28,    -1,    35,    27,   101,    28,    -1,    85,    -1,
      85,    26,   101,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   331,   331,   334,   335,   336,   337,   338,   339,   343,
     344,   347,   349,   351,   352,   355,   356,   359,   360,   371,
     373,   388,   389,   393,   397,   398,   399,   400,   401,   405,
     406,   407,   408,   413,   414,   418,   419,   423,   424,   428,
     429,   433,   434,   435,   436,   437,   438,   439,   442,   443,
     445,   447,   448,   449,   452,   479,   480,   481,   497,   498,
     503,   519,   503,   526,   527,   531,   538,   531,   562,   563,
     567,   568,   572,   572,   580,   572,   614,   615,   628,   641,
     655,   669,   685,   701,   704,   736,   768,   772,   801,   838,
     839,   848,   849,   850,   851,   852,   853,   857,   859,   874,
     888,   889,   893,   896,   911,   929,   930,   945,   946,   950,
     953,   957,   958,   962,   963
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
  "EXTRACTION", "CIN", "COUT", "CLASS", "PREPROC", "THEN",
  "LOWER_THAN_ELSE", "$accept", "atree", "program", "external_declaration",
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
     305,   306,   307,   308
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    54,    55,    56,    56,    56,    56,    56,    56,    57,
      57,    58,    59,    59,    59,    60,    60,    61,    61,    61,
      61,    62,    62,    63,    64,    64,    64,    64,    64,    65,
      65,    65,    65,    66,    66,    67,    67,    68,    68,    69,
      69,    70,    70,    70,    70,    70,    70,    70,    71,    71,
      72,    73,    73,    73,    74,    75,    75,    75,    76,    76,
      78,    79,    77,    80,    80,    82,    83,    81,    84,    84,
      85,    85,    87,    88,    89,    86,    90,    90,    91,    91,
      91,    91,    92,    92,    93,    93,    93,    94,    94,    95,
      95,    96,    96,    96,    96,    96,    96,    97,    97,    97,
      97,    97,    98,    98,    98,    99,    99,    99,    99,    99,
      99,   100,   100,   101,   101
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     5,     4,     1,     2,     1,
       1,     6,     3,     3,     2,     4,     2,     1,     3,     3,
       5,     2,     3,     4,     1,     1,     1,     1,     1,     2,
       2,     4,     4,     1,     1,     2,     3,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     3,     4,     4,     1,     1,     1,     1,     2,
       0,     0,     8,     0,     2,     0,     0,     7,     2,     3,
       1,     1,     0,     0,     0,    12,     1,     4,     2,     2,
       2,     2,     3,     1,     2,     2,     1,     2,     2,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       2,     2,     1,     3,     3,     3,     1,     1,     1,     1,
       1,     3,     4,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    25,    24,    26,    27,    28,     0,     0,     0,
       3,     7,     9,    10,     0,    14,     0,     1,     0,     4,
       8,     0,    17,     0,     0,     0,     0,    16,     0,     0,
       0,     0,     0,    13,    12,     0,     6,     0,     0,     0,
       0,     0,     0,   106,   108,   109,   110,    18,    70,    83,
      86,    71,    89,    97,   102,   107,    34,     0,     0,    21,
      33,     0,     0,     0,     0,     0,    23,    19,     5,    84,
      85,   106,   100,   101,     0,    87,    88,     0,     0,     0,
       0,    91,    92,    93,    94,    95,    96,     0,     0,     0,
      29,    30,     0,    22,    15,     0,    17,     0,    65,     0,
      72,    58,    35,     0,     0,    39,     0,    42,     0,    37,
      40,    47,    48,    49,    41,    43,    44,    45,     0,    46,
       0,   105,    82,   111,   113,     0,    98,    99,    90,   103,
     104,     0,     0,    11,     0,     0,    68,     0,     0,     0,
       0,     0,    17,    36,    38,    59,    20,     0,   112,    31,
      32,     0,     0,    69,     0,     0,    57,    55,    56,    51,
      50,   114,    60,     0,     0,     0,     0,    76,    54,     0,
      52,     0,    66,     0,    73,    53,    61,     0,     0,     0,
      63,    67,    77,     0,     0,    62,     0,    64,     0,     0,
       0,     0,    78,    79,    80,    81,    74,     0,    75
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     8,     9,    10,    11,    12,    23,    24,    32,    13,
      14,    60,    61,   107,   108,   109,   110,   111,   112,   141,
     113,   159,   114,   115,   171,   180,   185,   116,   135,   177,
     117,   118,   119,   138,   179,   197,   166,   191,    48,    49,
      50,    51,    87,    52,    53,    54,    55,   125
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -81
static const yytype_int16 yypact[] =
{
       8,    23,   -81,   -81,   -81,   -81,   -81,     4,    61,     3,
     -81,   -81,   -81,   -81,    27,   -81,    43,   -81,    49,   -81,
     -81,    66,   164,    80,   -20,    87,    83,   -81,   132,    32,
      86,    65,    95,   -81,   -81,    93,   -81,   110,   125,   131,
     186,   186,   132,   212,   -81,   -81,   -81,   -81,   -81,   -81,
     -81,   -81,   223,    -9,   -81,   -81,   -81,   148,   161,   -81,
     185,   124,   184,   194,    78,    20,   -81,   203,   -81,   -81,
     -81,   202,   -81,   -81,   204,   -81,   -81,   132,    75,   186,
     186,   -81,   -81,   -81,   -81,   -81,   -81,   186,   183,   183,
     -81,   -81,    55,   -81,   -81,   205,    69,   206,   -81,   172,
     -81,   -81,   -81,   187,   189,   -81,    79,   -81,   126,   -81,
     -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,   215,   -81,
     132,   -81,   -81,   -81,   221,   220,   -81,   -81,   134,   -81,
     -81,   214,   216,   -81,   132,   225,   -81,   228,   227,   222,
      64,   230,    92,   -81,   -81,   -81,   -81,   132,   -81,   -81,
     -81,   231,   132,   -81,    73,   233,   -81,   -81,   -81,   210,
     -81,   -81,   -81,   232,   130,   226,   237,   -81,   -81,   120,
     -81,   167,   -81,   239,   -81,   -81,   -81,   167,   132,   186,
     246,   -81,   -81,   240,   167,   -81,     7,   -81,   229,   234,
     177,   238,   -81,   -81,   -81,   -81,   -81,   167,   -81
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -81,   -81,   -81,    15,   258,   -64,   -81,   -81,   -81,   -81,
     -29,   -81,   -81,   236,   -81,   162,   -80,   -81,   -81,   112,
     -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,
     -81,   -28,   -81,   -81,   -81,   -81,   -81,   -81,   118,   -81,
     -81,    94,   -81,    -3,   117,   -81,   -81,   127
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -3
static const yytype_int16 yytable[] =
{
      47,   105,    64,    -2,     1,    34,    35,    88,    89,     1,
       2,     3,     4,     5,    74,     2,     3,     4,     5,   188,
     189,     1,    16,    97,    19,    98,    99,     2,     3,     4,
       5,   100,    38,    39,    40,    41,   106,    72,    73,    56,
      57,    58,   190,    21,   105,   101,    63,    42,    15,   122,
     124,    65,   102,     6,    18,    43,    44,    45,     6,     7,
      59,    17,    22,   131,   132,    46,     1,    26,   103,   104,
       6,   137,     2,     3,     4,     5,   126,   127,    25,   106,
       2,     3,     4,     5,   128,    38,    39,    38,    39,    40,
      41,   176,   146,    28,    21,    21,    29,   181,    30,   156,
     157,    27,    42,   123,   187,    33,   151,    36,   164,   158,
      43,    44,    45,    96,   142,     6,    28,   198,    37,   124,
      46,    30,    62,     6,   163,   165,    65,     1,    67,    97,
      68,    98,    99,     2,     3,     4,     5,   100,    38,    39,
      40,    41,    75,    76,    38,    39,    40,    41,    79,    80,
     182,   101,    93,    42,    77,   156,   157,    65,   143,    42,
      69,    43,    44,    45,   175,   158,    70,    43,    44,    45,
      97,    46,    98,    99,   103,   104,     6,    46,   100,    38,
      39,    40,    41,    90,    38,    39,    40,    41,    28,   194,
     195,    29,   101,    30,    42,    31,    91,   136,    65,    42,
      40,    41,    43,    44,    45,   129,   130,    43,    44,    45,
      42,    92,    46,    42,    94,   103,   104,    46,    71,    44,
      45,    71,    44,    45,    75,    76,    95,   120,    46,    78,
     133,    46,   121,   134,   139,   140,    77,    79,    80,    78,
     145,    81,    82,    83,    84,    85,    86,   147,   148,   149,
     184,   150,   152,   153,   154,   160,   169,   155,   168,   162,
     172,   173,   174,   178,   192,   186,   196,    20,    66,   193,
     144,   170,   167,   183,   161
};

static const yytype_uint8 yycheck[] =
{
      28,    65,    31,     0,     1,    25,    26,    16,    17,     1,
       7,     8,     9,    10,    42,     7,     8,     9,    10,    12,
      13,     1,    18,     3,     9,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    65,    40,    41,     7,
       8,     9,    35,    16,   108,    25,    31,    27,    25,    77,
      78,    31,    32,    50,    51,    35,    36,    37,    50,    51,
      28,     0,    35,     8,     9,    45,     1,    18,    48,    49,
      50,    99,     7,     8,     9,    10,    79,    80,    35,   108,
       7,     8,     9,    10,    87,    12,    13,    12,    13,    14,
      15,   171,   120,    24,    16,    16,    27,   177,    29,    35,
      36,    35,    27,    28,   184,    25,   134,    20,    35,    45,
      35,    36,    37,    35,    35,    50,    24,   197,    35,   147,
      45,    29,    36,    50,   152,   154,    31,     1,    35,     3,
      20,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    12,    13,    12,    13,    14,    15,    14,    15,
     178,    25,    28,    27,    24,    35,    36,    31,    32,    27,
      35,    35,    36,    37,    44,    45,    35,    35,    36,    37,
       3,    45,     5,     6,    48,    49,    50,    45,    11,    12,
      13,    14,    15,    35,    12,    13,    14,    15,    24,    12,
      13,    27,    25,    29,    27,    31,    35,    25,    31,    27,
      14,    15,    35,    36,    37,    88,    89,    35,    36,    37,
      27,    26,    45,    27,    30,    48,    49,    45,    35,    36,
      37,    35,    36,    37,    12,    13,    32,    24,    45,    27,
      25,    45,    28,    27,    47,    46,    24,    14,    15,    27,
      25,    18,    19,    20,    21,    22,    23,    26,    28,    35,
       4,    35,    27,    25,    27,    25,    46,    35,    25,    28,
      28,    35,    25,    24,    35,    25,    28,     9,    32,    35,
     108,   159,   154,   179,   147
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     7,     8,     9,    10,    50,    51,    55,    56,
      57,    58,    59,    63,    64,    25,    18,     0,    51,    57,
      58,    16,    35,    60,    61,    35,    18,    35,    24,    27,
      29,    31,    62,    25,    25,    26,    20,    35,    12,    13,
      14,    15,    27,    35,    36,    37,    45,    85,    92,    93,
      94,    95,    97,    98,    99,   100,     7,     8,     9,    28,
      65,    66,    36,    57,    64,    31,    67,    35,    20,    35,
      35,    35,    97,    97,    85,    12,    13,    24,    27,    14,
      15,    18,    19,    20,    21,    22,    23,    96,    16,    17,
      35,    35,    26,    28,    30,    32,    35,     3,     5,     6,
      11,    25,    32,    48,    49,    59,    64,    67,    68,    69,
      70,    71,    72,    74,    76,    77,    81,    84,    85,    86,
      24,    28,    85,    28,    85,   101,    97,    97,    97,    98,
      98,     8,     9,    25,    27,    82,    25,    85,    87,    47,
      46,    73,    35,    32,    69,    25,    85,    26,    28,    35,
      35,    85,    27,    25,    27,    35,    35,    36,    45,    75,
      25,   101,    28,    85,    35,    64,    90,    92,    25,    46,
      73,    78,    28,    35,    25,    44,    70,    83,    24,    88,
      79,    70,    85,    95,     4,    80,    25,    70,    12,    13,
      35,    91,    35,    35,    12,    13,    28,    89,    70
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
#line 331 ".\\int_code.y"
    {display_three_add(q_list1);;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 334 ".\\int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 335 ".\\int_code.y"
    {;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 336 ".\\int_code.y"
    {printf("%s\n", (yyvsp[(4) - (5)].str));;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 337 ".\\int_code.y"
    {printf("%s\n", (yyvsp[(3) - (4)].str));;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 338 ".\\int_code.y"
    {;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 339 ".\\int_code.y"
    {;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 343 ".\\int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str); ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 344 ".\\int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 347 ".\\int_code.y"
    {insert(list2, yylineno, (yyvsp[(2) - (6)].str), "class", scope, " ", "class");;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 350 ".\\int_code.y"
    {;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 351 ".\\int_code.y"
    {;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 352 ".\\int_code.y"
    {yyerrok;;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 355 ".\\int_code.y"
    {insert(list2, yylineno, (yyvsp[(1) - (4)].str), type, scope, " ", "ARRAY");;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 356 ".\\int_code.y"
    {insert(list2, yylineno, (yyvsp[(2) - (2)].str), type, scope, " ", "PTR");;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 359 ".\\int_code.y"
    {insert(list2, yylineno, (yyvsp[(1) - (1)].str), type, scope, " ", "IDENT");;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 360 ".\\int_code.y"
    {
                            char arg1[10];
                            sprintf(arg1,"%s",(yyvsp[(3) - (3)].str));
    						quadruple * new_record = create_quadruple("assignment","",arg1,"",(yyvsp[(1) - (3)].str), yylineno);
                            insert_quadruple(q_list1,new_record); 
                            insert(list2, yylineno, (yyvsp[(1) - (3)].str), type, scope, " ", "IDENT");
                            update(list2, (yyvsp[(1) - (3)].str), scope, (yyvsp[(3) - (3)].str));
                            iflag = 0;
                            fflag = 0;
                            cflag = 0; 
                        ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 371 ".\\int_code.y"
    { insert(list2, yylineno, (yyvsp[(3) - (3)].str), type, scope, " ", "IDENT"); 
    ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 373 ".\\int_code.y"
    {
                            char arg1[10];
                            sprintf(arg1,"%s",(yyvsp[(5) - (5)].str));
    						quadruple * new_record = create_quadruple("assignment","",arg1,"",(yyvsp[(3) - (5)].str), yylineno);
                            insert_quadruple(q_list1,new_record); 
                            insert(list2, yylineno, (yyvsp[(3) - (5)].str), type, scope, " ", "IDENT");
                            update(list2, (yyvsp[(3) - (5)].str), scope, (yyvsp[(5) - (5)].str));
                            iflag = 0;
                            fflag = 0;
                            cflag = 0; 
                        ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 388 ".\\int_code.y"
    {;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 389 ".\\int_code.y"
    {;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 393 ".\\int_code.y"
    {insert(list2, yylineno, (yyvsp[(2) - (4)].str), type, scope, " ", "FUNCT");;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 397 ".\\int_code.y"
    {(yyval.str)=integer; strcpy(type, "int");;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 398 ".\\int_code.y"
    {(yyval.str)="VOID"; strcpy(type, "void");;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 399 ".\\int_code.y"
    {(yyval.str)="float"; strcpy(type, "float");;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 400 ".\\int_code.y"
    {(yyval.str)="char"; strcpy(type, "char");;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 401 ".\\int_code.y"
    {(yyval.str)="class"; strcpy(type, "class");;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 405 ".\\int_code.y"
    {;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 406 ".\\int_code.y"
    {;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 407 ".\\int_code.y"
    {;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 408 ".\\int_code.y"
    {;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 413 ".\\int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 414 ".\\int_code.y"
    {;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 418 ".\\int_code.y"
    {(yyval.str) = "$";;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 419 ".\\int_code.y"
    {(yyval.str) = (yyvsp[(2) - (3)].str); reset_scope(list2,scope);;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 423 ".\\int_code.y"
    {(yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 424 ".\\int_code.y"
    {(yyval.str) = (yyvsp[(2) - (2)].str);;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 428 ".\\int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str); ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 429 ".\\int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 433 ".\\int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 434 ".\\int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 435 ".\\int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 436 ".\\int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 437 ".\\int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 438 ".\\int_code.y"
    {(yyval.str) = (yyvsp[(1) - (1)].str);;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 439 ".\\int_code.y"
    {(yyval.str) = (yyvsp[(1) - (1)].str);;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 442 ".\\int_code.y"
    {;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 443 ".\\int_code.y"
    {;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 447 ".\\int_code.y"
    {if(errors==0) printf("%s", (yyvsp[(2) - (2)].str));;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 448 ".\\int_code.y"
    {if(errors==0) printf("%s", (yyvsp[(2) - (3)].str));;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 449 ".\\int_code.y"
    {if(errors==0) printf("%s\n", (yyvsp[(2) - (4)].str));;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 452 ".\\int_code.y"
    {
					id_ex = find(list2, (yyvsp[(3) - (4)].str), scope);
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

  case 55:

/* Line 1455 of yacc.c  */
#line 479 ".\\int_code.y"
    {(yyval.str) = yylval.str;;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 480 ".\\int_code.y"
    {(yyval.str) = yylval.str;;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 481 ".\\int_code.y"
    {
		id_ex = find(list2, (yyvsp[(1) - (1)].str), scope);
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

  case 58:

/* Line 1455 of yacc.c  */
#line 497 ".\\int_code.y"
    {;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 498 ".\\int_code.y"
    {(yyval.str)=(yyvsp[(1) - (2)].str);;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 503 ".\\int_code.y"
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

  case 61:

/* Line 1455 of yacc.c  */
#line 519 ".\\int_code.y"
    {
        quadruple* new_record = create_quadruple("label","","","",(yyvsp[(5) - (6)].str), yylineno);
        insert_quadruple(q_list1,new_record);
        
    ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 523 ".\\int_code.y"
    {;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 527 ".\\int_code.y"
    {;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 531 ".\\int_code.y"
    {
        quadruple* new_record;
        char while_label[10];
        strcpy(while_label,create_label());
        new_record = create_quadruple("label","","","",while_label, yylineno);
        insert_quadruple(q_list1,new_record);
        (yyval.str)=while_label;;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 538 ".\\int_code.y"
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

  case 67:

/* Line 1455 of yacc.c  */
#line 553 ".\\int_code.y"
    {
        quadruple* new_record = create_quadruple("goto","","","",(yyvsp[(2) - (7)].str), yylineno);
        insert_quadruple(q_list1,new_record);
        new_record = create_quadruple("label","","","",(yyvsp[(6) - (7)].str), yylineno);
        insert_quadruple(q_list1,new_record);
    ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 562 ".\\int_code.y"
    {;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 563 ".\\int_code.y"
    {;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 567 ".\\int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 568 ".\\int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 572 ".\\int_code.y"
    {scope++;;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 572 ".\\int_code.y"
    {
        quadruple* new_record;
        char for_label[10];
        strcpy(for_label,create_label());
        new_record = create_quadruple("label","","","",for_label, yylineno);
        insert_quadruple(q_list1,new_record);
        (yyval.str)=for_label;
	;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 580 ".\\int_code.y"
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

  case 75:

/* Line 1455 of yacc.c  */
#line 593 ".\\int_code.y"
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

  case 76:

/* Line 1455 of yacc.c  */
#line 614 ".\\int_code.y"
    {;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 615 ".\\int_code.y"
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

  case 78:

/* Line 1455 of yacc.c  */
#line 628 ".\\int_code.y"
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
#line 641 ".\\int_code.y"
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
#line 655 ".\\int_code.y"
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

  case 81:

/* Line 1455 of yacc.c  */
#line 669 ".\\int_code.y"
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

  case 82:

/* Line 1455 of yacc.c  */
#line 685 ".\\int_code.y"
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

  case 83:

/* Line 1455 of yacc.c  */
#line 701 ".\\int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 704 ".\\int_code.y"
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

  case 85:

/* Line 1455 of yacc.c  */
#line 736 ".\\int_code.y"
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

  case 86:

/* Line 1455 of yacc.c  */
#line 768 ".\\int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 772 ".\\int_code.y"
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

  case 88:

/* Line 1455 of yacc.c  */
#line 801 ".\\int_code.y"
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

  case 89:

/* Line 1455 of yacc.c  */
#line 838 ".\\int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 839 ".\\int_code.y"
    {

				strcat((yyvsp[(1) - (3)].str), (yyvsp[(2) - (3)].str));
				strcat((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str));
				(yyval.str) = (yyvsp[(1) - (3)].str);                        
    		;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 848 ".\\int_code.y"
    {(yyval.str) = "<";;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 849 ".\\int_code.y"
    {(yyval.str) = "<=";;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 850 ".\\int_code.y"
    {(yyval.str) = ">";;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 851 ".\\int_code.y"
    {(yyval.str) = ">=";;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 852 ".\\int_code.y"
    {(yyval.str) = "==";;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 853 ".\\int_code.y"
    {(yyval.str) = "!=";;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 857 ".\\int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);
        ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 859 ".\\int_code.y"
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

  case 99:

/* Line 1455 of yacc.c  */
#line 874 ".\\int_code.y"
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

  case 100:

/* Line 1455 of yacc.c  */
#line 888 ".\\int_code.y"
    {(yyval.str) = (yyvsp[(2) - (2)].str);;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 889 ".\\int_code.y"
    {char temp[20];strcpy(temp,"-");strcat(temp,(yyvsp[(2) - (2)].str));(yyval.str) = temp;;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 893 ".\\int_code.y"
    {
              (yyval.str) = (yyvsp[(1) - (1)].str);
            ;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 896 ".\\int_code.y"
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

  case 104:

/* Line 1455 of yacc.c  */
#line 911 ".\\int_code.y"
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

  case 105:

/* Line 1455 of yacc.c  */
#line 929 ".\\int_code.y"
    {(yyval.str)=(yyvsp[(2) - (3)].str); ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 930 ".\\int_code.y"
    {
    	  if(yylineno == 1){
    	  	(yyval.str) = (yyvsp[(1) - (1)].str);
    	  }	
    	  else{
          id_ex = find(list2, (yyvsp[(1) - (1)].str), scope);
          if(id_ex == NULL){
            printf("Error on %d, Assignment RHS not declared\n", yylineno);
            errors++;
            (yyval.str) = "$";}
          else{
          	(yyval.str) = (yyvsp[(1) - (1)].str);
            
            
          }};}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 945 ".\\int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 946 ".\\int_code.y"
    { 
           (yyval.str) = yylval.str;
           
           ;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 950 ".\\int_code.y"
    {
        (yyval.str) = yylval.str;
    	;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 953 ".\\int_code.y"
    {(yyval.str) = yylval.str;;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 957 ".\\int_code.y"
    {;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 958 ".\\int_code.y"
    {;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 962 ".\\int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 963 ".\\int_code.y"
    {;}
    break;



/* Line 1455 of yacc.c  */
#line 3087 "int_code.tab.c"
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
#line 966 ".\\int_code.y"

#include <stdio.h>
int
main(argc, argv)
int argc;
char** argv;
{
//syntree = fopen("syntree.txt", "w");
FILE *fp = fopen("tokens.txt", "w");
icgout = fopen("icg.txt", "w");
symtab = fopen("symtab.txt", "w");
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
fclose(icgout);
fclose(symtab);
return 0; 
} 

void yyerror(const char *s)
{
	fflush(stdout);
	errors++;
	fprintf(stderr, "Error: %s on line number %d\n", s, yylineno);
}




