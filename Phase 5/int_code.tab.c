/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "int_code.y"

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
char if_stmt_skip_label[10];
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
    else if(strcmp(record->statement, "ARR")==0){
    	sprintf(res, "ARR %s = %s", record->res, record->arg1);
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

char * get_dtype(char * str) {
    int i=0;
    char* type = (char*)malloc(sizeof(char)*10);
    if(str[0]=='\"') {
        strcpy(type,"STRING");
        return type;
    }
    else if(str[0]=='\'') {
        strcpy(type,"CHAR");
        return type;
    }
    strcpy(type,"INT");
    while(str[i]!='\0' && str[i]>=0 && str[i]<=9) {
        i++;
    }
    if (str[i]=='\0') {
        return type;
    }
    else if (str[i]=='.') {
        strcpy(type,"FLOAT");
        i++;
        while(str[i]!='\0' && str[i]>=0 && str[i]<=9) {
            i++;
        }
        if (str[i]=='\0') {
        return type;
    }
    else {
        strcpy(type,"INVALID");
        return type;
    }
    }
    
}
//end of quadruples code
// Implementation of break and continue
struct construct {
    char start_label[10];
    char stop_label[10];
};

typedef struct construct construct;
construct current_construct;

//end
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
    printf("___________________________________________________________________\n");
    fprintf(symtab, "___________________________________________________________________\n");
    printf("|Line      |Name      |Scope     |value     |id_type   |datatype  |\n");
    fprintf(symtab, "|Line      |Name      |Scope     |value     |id_type   |datatype  |\n");
    printf("-------------------------------------------------------------------\n");
    fprintf(symtab, "-------------------------------------------------------------------\n");
    while(temp!=NULL){

        printf("|%-10d|%-10s|%-10d|%-10s|%-10s|%-10s|\n", temp->nl, temp->name, temp->scope, temp->rhs, temp->type, temp->dtype);
        fprintf(symtab, "|%-10d|%-10s|%-10d|%-10s|%-10s|%-10s|\n", temp->nl, temp->name, temp->scope, temp->rhs, temp->type, temp->dtype);      	
        temp=temp->next;
    }

    printf("-------------------------------------------------------------------\n");
    fprintf(symtab, "-------------------------------------------------------------------\n");
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
    //int value;
    char type[200];
};
typedef struct expression_details exp_det;
exp_det det1;

/* Line 371 of yacc.c  */
#line 412 "int_code.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "int_code.tab.h".  */
#ifndef YY_YY_INT_CODE_TAB_H_INCLUDED
# define YY_YY_INT_CODE_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
/* Line 387 of yacc.c  */
#line 344 "int_code.y"




/* Line 387 of yacc.c  */
#line 449 "int_code.tab.c"

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
     BREAK = 267,
     CONTINUE = 268,
     INC_OP = 269,
     DEC_OP = 270,
     PLUS = 271,
     MINUS = 272,
     STAR = 273,
     SLASH = 274,
     LT = 275,
     LTEQ = 276,
     GT = 277,
     GTEQ = 278,
     EQ = 279,
     NEQ = 280,
     ASSIGN = 281,
     SEMI = 282,
     COMMA = 283,
     LPAREN = 284,
     RPAREN = 285,
     LSQUAR = 286,
     RSQUAR = 287,
     LBRACE = 288,
     RBRACE = 289,
     LCOMMENT = 290,
     RCOMMENT = 291,
     ID = 292,
     NUM = 293,
     FLT = 294,
     CHR = 295,
     LETTER = 296,
     DIGIT = 297,
     NONTOKEN = 298,
     ERROR = 299,
     ENDFILE = 300,
     NL = 301,
     ENDL = 302,
     STR = 303,
     INSERTION = 304,
     EXTRACTION = 305,
     CIN = 306,
     COUT = 307,
     CLASS = 308,
     PREPROC = 309,
     THEN = 310,
     LOWER_THAN_IF = 311
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 347 "int_code.y"

	char chr;
	int integer;
	float ft;
	char *str;


/* Line 387 of yacc.c  */
#line 528 "int_code.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

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

#endif /* !YY_YY_INT_CODE_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 556 "int_code.tab.c"

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
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
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

# define YYCOPY_NEEDED 1

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

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  17
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   318

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  57
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  55
/* YYNRULES -- Number of rules.  */
#define YYNRULES  133
/* YYNRULES -- Number of states.  */
#define YYNSTATES  228

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   311

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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    16,    21,    23,    26,
      28,    30,    37,    41,    45,    48,    52,    56,    58,    63,
      66,    72,    74,    78,    82,    88,    91,    95,   100,   102,
     104,   106,   108,   110,   113,   116,   121,   126,   128,   130,
     133,   137,   139,   142,   144,   146,   148,   150,   152,   154,
     156,   158,   160,   162,   164,   166,   168,   170,   172,   176,
     179,   183,   188,   193,   195,   197,   199,   201,   204,   205,
     206,   215,   216,   217,   227,   230,   231,   233,   235,   237,
     239,   241,   243,   245,   247,   248,   249,   257,   260,   264,
     266,   268,   269,   270,   271,   284,   286,   291,   294,   297,
     300,   303,   307,   309,   312,   315,   317,   320,   323,   325,
     329,   331,   333,   335,   337,   339,   341,   343,   347,   351,
     354,   357,   359,   363,   367,   371,   373,   375,   377,   379,
     381,   385,   390,   392
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      58,     0,    -1,    59,    -1,    60,    -1,    59,    60,    -1,
      59,    54,    20,    37,    22,    -1,    54,    20,    37,    22,
      -1,    61,    -1,    59,    61,    -1,    62,    -1,    68,    -1,
      69,    37,    33,    60,    34,    27,    -1,    69,    66,    27,
      -1,    69,    65,    27,    -1,     1,    27,    -1,    33,    64,
      34,    -1,    38,    28,    64,    -1,    38,    -1,    37,    31,
      38,    32,    -1,    18,    37,    -1,    37,    31,    32,    26,
      63,    -1,    37,    -1,    37,    26,    95,    -1,    66,    28,
      37,    -1,    66,    28,    37,    26,    95,    -1,    29,    30,
      -1,    29,    71,    30,    -1,    69,    37,    67,    72,    -1,
       8,    -1,     7,    -1,     9,    -1,    10,    -1,    53,    -1,
       8,    37,    -1,     9,    37,    -1,    70,    28,     8,    37,
      -1,    70,    28,     9,    37,    -1,    70,    -1,     7,    -1,
      33,    34,    -1,    33,    73,    34,    -1,    74,    -1,    73,
      74,    -1,    62,    -1,    75,    -1,    83,    -1,    72,    -1,
      84,    -1,    91,    -1,    94,    -1,    96,    -1,    78,    -1,
      76,    -1,    77,    -1,    12,    -1,    13,    -1,    79,    -1,
      81,    -1,    52,    80,    27,    -1,    49,    82,    -1,    49,
      82,    80,    -1,    49,    82,    49,    47,    -1,    51,    50,
      37,    27,    -1,    38,    -1,    48,    -1,    37,    -1,    27,
      -1,    95,    27,    -1,    -1,    -1,     3,    29,    95,    30,
      85,    75,    86,    87,    -1,    -1,    -1,     4,     3,    29,
      95,    30,    88,    75,    89,    87,    -1,     4,    90,    -1,
      -1,    83,    -1,    72,    -1,    91,    -1,    94,    -1,    96,
      -1,    78,    -1,    76,    -1,    77,    -1,    -1,    -1,     5,
      92,    29,    95,    30,    93,    75,    -1,     6,    27,    -1,
       6,    95,    27,    -1,   102,    -1,   105,    -1,    -1,    -1,
      -1,    11,    97,    29,   100,    27,    98,   105,    27,   101,
      30,    99,    75,    -1,   102,    -1,    69,    37,    26,    95,
      -1,    14,    37,    -1,    15,    37,    -1,    37,    14,    -1,
      37,    15,    -1,    37,    26,    95,    -1,   103,    -1,    14,
      37,    -1,    15,    37,    -1,   104,    -1,    37,    14,    -1,
      37,    15,    -1,   107,    -1,   107,   106,   107,    -1,    20,
      -1,    21,    -1,    22,    -1,    23,    -1,    24,    -1,    25,
      -1,   108,    -1,   107,    16,   107,    -1,   107,    17,   107,
      -1,    16,   107,    -1,    17,   107,    -1,   109,    -1,   108,
      18,   108,    -1,   108,    19,   108,    -1,    29,    95,    30,
      -1,    37,    -1,   110,    -1,    38,    -1,    39,    -1,    48,
      -1,    37,    29,    30,    -1,    37,    29,   111,    30,    -1,
      95,    -1,    95,    28,   111,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   380,   380,   383,   384,   385,   386,   387,   388,   392,
     393,   396,   398,   400,   401,   404,   407,   408,   411,   412,
     413,   418,   419,   430,   432,   447,   448,   452,   456,   457,
     458,   459,   460,   464,   465,   466,   467,   472,   473,   477,
     478,   482,   483,   487,   488,   492,   493,   494,   495,   496,
     497,   498,   499,   500,   504,   516,   528,   529,   531,   533,
     534,   535,   538,   565,   566,   567,   583,   584,   589,   605,
     589,   620,   637,   620,   644,   647,   651,   652,   653,   654,
     655,   656,   657,   658,   662,   670,   662,   697,   698,   702,
     703,   707,   707,   716,   707,   753,   754,   767,   780,   794,
     808,   824,   840,   843,   875,   907,   911,   940,   977,   978,
     987,   988,   989,   990,   991,   992,   996,   998,  1012,  1026,
    1027,  1031,  1034,  1049,  1067,  1068,  1082,  1085,  1089,  1093,
    1097,  1098,  1102,  1103
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "WHILE", "RETURN", "VOID",
  "INT", "FLOAT", "CHAR", "FOR", "BREAK", "CONTINUE", "INC_OP", "DEC_OP",
  "PLUS", "MINUS", "STAR", "SLASH", "LT", "LTEQ", "GT", "GTEQ", "EQ",
  "NEQ", "ASSIGN", "SEMI", "COMMA", "LPAREN", "RPAREN", "LSQUAR", "RSQUAR",
  "LBRACE", "RBRACE", "LCOMMENT", "RCOMMENT", "ID", "NUM", "FLT", "CHR",
  "LETTER", "DIGIT", "NONTOKEN", "ERROR", "ENDFILE", "NL", "ENDL", "STR",
  "INSERTION", "EXTRACTION", "CIN", "COUT", "CLASS", "PREPROC", "THEN",
  "LOWER_THAN_IF", "$accept", "atree", "program", "external_declaration",
  "class_declaration", "var_declaration", "array_init", "comma_list",
  "array_dec", "init_declarator_list", "declarator", "fun_declaration",
  "declaration_specifiers", "params_list", "params", "compound_stmt",
  "block_item_list", "block_item", "statement", "break_stmt",
  "continue_stmt", "stream_constructs", "cout_cascade", "cascade_out",
  "cin", "op", "expression_stmt", "if_stmt", "@1", "$@2", "else_if", "@3",
  "$@4", "else_body", "while_stmt", "@5", "@6", "return_stmt",
  "expression", "for_stmt", "$@7", "@8", "@9", "for_initialiser",
  "for_update", "assignment_expression", "unary_expression",
  "postfix_expression", "simple_expression", "relop",
  "additive_expression", "term", "factor", "call", "args", YY_NULL
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
     305,   306,   307,   308,   309,   310,   311
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    57,    58,    59,    59,    59,    59,    59,    59,    60,
      60,    61,    62,    62,    62,    63,    64,    64,    65,    65,
      65,    66,    66,    66,    66,    67,    67,    68,    69,    69,
      69,    69,    69,    70,    70,    70,    70,    71,    71,    72,
      72,    73,    73,    74,    74,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    76,    77,    78,    78,    79,    80,
      80,    80,    81,    82,    82,    82,    83,    83,    85,    86,
      84,    88,    89,    87,    87,    87,    90,    90,    90,    90,
      90,    90,    90,    90,    92,    93,    91,    94,    94,    95,
      95,    97,    98,    99,    96,   100,   100,   101,   101,   101,
     101,   102,   102,   103,   103,   103,   104,   104,   105,   105,
     106,   106,   106,   106,   106,   106,   107,   107,   107,   107,
     107,   108,   108,   108,   109,   109,   109,   109,   109,   109,
     110,   110,   111,   111
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     5,     4,     1,     2,     1,
       1,     6,     3,     3,     2,     3,     3,     1,     4,     2,
       5,     1,     3,     3,     5,     2,     3,     4,     1,     1,
       1,     1,     1,     2,     2,     4,     4,     1,     1,     2,
       3,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     2,
       3,     4,     4,     1,     1,     1,     1,     2,     0,     0,
       8,     0,     0,     9,     2,     0,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     0,     7,     2,     3,     1,
       1,     0,     0,     0,    12,     1,     4,     2,     2,     2,
       2,     3,     1,     2,     2,     1,     2,     2,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     2,
       2,     1,     3,     3,     3,     1,     1,     1,     1,     1,
       3,     4,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    29,    28,    30,    31,    32,     0,     0,     0,
       3,     7,     9,    10,     0,    14,     0,     1,     0,     4,
       8,     0,    21,     0,     0,     0,     0,    19,     0,     0,
       0,     0,     0,    13,    12,     0,     6,     0,     0,     0,
       0,     0,     0,   125,   127,   128,   129,    22,    89,   102,
     105,    90,   108,   116,   121,   126,    38,     0,     0,    25,
      37,     0,     0,     0,     0,     0,     0,    27,    23,     5,
     103,   104,   125,   119,   120,     0,   106,   107,     0,     0,
       0,     0,   110,   111,   112,   113,   114,   115,     0,     0,
       0,    33,    34,     0,    26,     0,    18,     0,    21,     0,
      84,     0,    91,    54,    55,    66,    39,     0,     0,    43,
       0,    46,     0,    41,    44,    52,    53,    51,    56,    57,
      45,    47,    48,    49,     0,    50,     0,   124,   101,   130,
     132,     0,   117,   118,   109,   122,   123,     0,     0,     0,
      20,    11,     0,     0,    87,     0,     0,     0,     0,     0,
      21,    40,    42,    67,    24,     0,   131,    35,    36,    17,
       0,     0,     0,    88,     0,     0,    65,    63,    64,    59,
      58,   133,     0,    15,    68,     0,     0,     0,     0,    95,
      62,     0,    60,    16,     0,    85,     0,    92,    61,    69,
       0,     0,     0,    75,    86,    96,     0,     0,    70,     0,
       0,    77,    82,    83,    81,    76,    74,    78,    79,    80,
       0,     0,     0,     0,     0,    97,    98,    99,   100,    93,
       0,     0,    71,    94,     0,    72,    75,    73
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     8,     9,    10,    11,    12,   140,   160,    23,    24,
      32,    13,    14,    60,    61,   111,   112,   113,   114,   115,
     116,   117,   118,   149,   119,   169,   120,   121,   184,   193,
     198,   224,   226,   206,   122,   143,   190,   123,   124,   125,
     146,   192,   221,   178,   213,    48,    49,    50,    51,    88,
      52,    53,    54,    55,   131
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -162
static const yytype_int16 yypact[] =
{
       8,   -20,  -162,  -162,  -162,  -162,  -162,    14,    24,     3,
    -162,  -162,  -162,  -162,    29,  -162,    11,  -162,    52,  -162,
    -162,    31,   154,    55,    72,    70,    67,  -162,   199,   102,
      81,    18,    85,  -162,  -162,    87,  -162,   109,    99,   101,
       4,     4,   199,   111,  -162,  -162,  -162,  -162,  -162,  -162,
    -162,  -162,   275,   104,  -162,  -162,  -162,   105,   107,  -162,
     132,   138,   158,   157,   156,    37,   140,  -162,   169,  -162,
    -162,  -162,   168,  -162,  -162,   181,  -162,  -162,   199,    91,
       4,     4,  -162,  -162,  -162,  -162,  -162,  -162,     4,     1,
       1,  -162,  -162,    23,  -162,   179,  -162,   190,   192,   195,
    -162,   242,  -162,  -162,  -162,  -162,  -162,   175,   170,  -162,
      47,  -162,   193,  -162,  -162,  -162,  -162,  -162,  -162,  -162,
    -162,  -162,  -162,  -162,   202,  -162,   199,  -162,  -162,  -162,
     205,   204,  -162,  -162,   148,  -162,  -162,   198,   218,   201,
    -162,  -162,   199,   231,  -162,   234,   233,   226,    48,   238,
      33,  -162,  -162,  -162,  -162,   199,  -162,  -162,  -162,   239,
     243,   248,   199,  -162,    80,   241,  -162,  -162,  -162,   223,
    -162,  -162,   201,  -162,  -162,   252,   144,   236,   256,  -162,
    -162,   124,  -162,  -162,    64,  -162,   258,  -162,  -162,  -162,
      64,   199,     4,   282,  -162,  -162,   260,   237,  -162,    21,
     264,  -162,  -162,  -162,  -162,  -162,  -162,  -162,  -162,  -162,
     257,   265,   161,   271,   199,  -162,  -162,  -162,  -162,  -162,
     273,    64,  -162,  -162,    64,  -162,   282,  -162
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -162,  -162,  -162,    13,   295,   -58,  -162,   133,  -162,  -162,
    -162,  -162,   -29,  -162,  -162,   -31,  -162,   194,  -161,   110,
     112,   113,  -162,   139,  -162,  -162,   114,  -162,  -162,  -162,
      86,  -162,  -162,  -162,   116,  -162,  -162,   117,   -28,   118,
    -162,  -162,  -162,  -162,  -162,   152,  -162,  -162,   125,  -162,
     -35,    92,  -162,  -162,   163
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -3
static const yytype_int16 yytable[] =
{
      47,    67,    65,    -2,     1,    73,    74,    15,   109,     1,
       2,     3,     4,     5,    75,     2,     3,     4,     5,     1,
      40,    41,    19,   189,    17,     2,     3,     4,     5,   194,
      42,   137,   138,    42,    16,   210,   211,   110,    72,    44,
      45,    72,    44,    45,    64,   132,   133,    21,    25,    46,
     128,   130,    46,   134,   109,    21,     6,    18,   212,    28,
     223,     6,     7,   225,    30,    21,    22,    99,    27,   100,
     101,     6,    26,   145,    98,   102,   103,   104,    38,    39,
      40,    41,    33,   110,   150,   166,   167,     2,     3,     4,
       5,   105,    36,    42,    38,    39,   168,    66,   154,    34,
      35,    43,    44,    45,    37,    38,    39,    40,    41,    56,
      57,    58,    46,    62,   161,   107,   108,   176,    66,    63,
      42,   129,    89,    90,    68,    76,    77,   130,    43,    44,
      45,    69,    59,     6,   175,   177,    70,    78,    71,    46,
      79,     1,    91,    99,    92,   100,   101,     2,     3,     4,
       5,   102,   103,   104,    38,    39,    40,    41,    76,    77,
      93,   166,   167,   195,    80,    81,   201,   105,    94,    42,
      78,   188,   168,    66,   106,   217,   218,    43,    44,    45,
      28,   135,   136,    29,    95,    30,   220,    31,    46,    96,
      97,   107,   108,     6,     1,   126,    99,    79,   100,   101,
       2,     3,     4,     5,   102,   103,   104,    38,    39,    40,
      41,   127,   139,    38,    39,    40,    41,   141,    28,   148,
     105,    29,    42,    30,   142,   147,    66,   151,    42,   153,
      43,    44,    45,   155,   156,   157,    43,    44,    45,   159,
     200,    46,   100,   101,   107,   108,     6,    46,   102,   103,
     104,    38,    39,    40,    41,   158,    38,    39,    40,    41,
     162,   163,   164,   165,   105,   170,    42,   172,   180,   144,
      66,    42,   181,   186,    43,    44,    45,   173,   174,    43,
      44,    45,   185,   187,   191,    46,   197,   199,   107,   108,
      46,    80,    81,   214,   215,    82,    83,    84,    85,    86,
      87,   219,   216,   222,    20,   183,   152,   202,   182,   203,
     204,   205,   227,   207,   208,   209,   179,   196,   171
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-162)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_uint8 yycheck[] =
{
      28,    32,    31,     0,     1,    40,    41,    27,    66,     1,
       7,     8,     9,    10,    42,     7,     8,     9,    10,     1,
      16,    17,     9,   184,     0,     7,     8,     9,    10,   190,
      29,     8,     9,    29,    20,    14,    15,    66,    37,    38,
      39,    37,    38,    39,    31,    80,    81,    18,    37,    48,
      78,    79,    48,    88,   112,    18,    53,    54,    37,    26,
     221,    53,    54,   224,    31,    18,    37,     3,    37,     5,
       6,    53,    20,   101,    37,    11,    12,    13,    14,    15,
      16,    17,    27,   112,    37,    37,    38,     7,     8,     9,
      10,    27,    22,    29,    14,    15,    48,    33,   126,    27,
      28,    37,    38,    39,    37,    14,    15,    16,    17,     7,
       8,     9,    48,    32,   142,    51,    52,    37,    33,    38,
      29,    30,    18,    19,    37,    14,    15,   155,    37,    38,
      39,    22,    30,    53,   162,   164,    37,    26,    37,    48,
      29,     1,    37,     3,    37,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    14,    15,
      28,    37,    38,   191,    16,    17,   197,    27,    30,    29,
      26,    47,    48,    33,    34,    14,    15,    37,    38,    39,
      26,    89,    90,    29,    26,    31,   214,    33,    48,    32,
      34,    51,    52,    53,     1,    26,     3,    29,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    30,    33,    14,    15,    16,    17,    27,    26,    49,
      27,    29,    29,    31,    29,    50,    33,    34,    29,    27,
      37,    38,    39,    28,    30,    37,    37,    38,    39,    38,
       3,    48,     5,     6,    51,    52,    53,    48,    11,    12,
      13,    14,    15,    16,    17,    37,    14,    15,    16,    17,
      29,    27,    29,    37,    27,    27,    29,    28,    27,    27,
      33,    29,    49,    37,    37,    38,    39,    34,    30,    37,
      38,    39,    30,    27,    26,    48,     4,    27,    51,    52,
      48,    16,    17,    29,    37,    20,    21,    22,    23,    24,
      25,    30,    37,    30,     9,   172,   112,   197,   169,   197,
     197,   197,   226,   197,   197,   197,   164,   192,   155
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     7,     8,     9,    10,    53,    54,    58,    59,
      60,    61,    62,    68,    69,    27,    20,     0,    54,    60,
      61,    18,    37,    65,    66,    37,    20,    37,    26,    29,
      31,    33,    67,    27,    27,    28,    22,    37,    14,    15,
      16,    17,    29,    37,    38,    39,    48,    95,   102,   103,
     104,   105,   107,   108,   109,   110,     7,     8,     9,    30,
      70,    71,    32,    38,    60,    69,    33,    72,    37,    22,
      37,    37,    37,   107,   107,    95,    14,    15,    26,    29,
      16,    17,    20,    21,    22,    23,    24,    25,   106,    18,
      19,    37,    37,    28,    30,    26,    32,    34,    37,     3,
       5,     6,    11,    12,    13,    27,    34,    51,    52,    62,
      69,    72,    73,    74,    75,    76,    77,    78,    79,    81,
      83,    84,    91,    94,    95,    96,    26,    30,    95,    30,
      95,   111,   107,   107,   107,   108,   108,     8,     9,    33,
      63,    27,    29,    92,    27,    95,    97,    50,    49,    80,
      37,    34,    74,    27,    95,    28,    30,    37,    37,    38,
      64,    95,    29,    27,    29,    37,    37,    38,    48,    82,
      27,   111,    28,    34,    30,    95,    37,    69,   100,   102,
      27,    49,    80,    64,    85,    30,    37,    27,    47,    75,
      93,    26,    98,    86,    75,    95,   105,     4,    87,    27,
       3,    72,    76,    77,    78,    83,    90,    91,    94,    96,
      14,    15,    37,   101,    29,    37,    37,    14,    15,    30,
      95,    99,    30,    75,    88,    75,    89,    87
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
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
  FILE *yyo = yyoutput;
  YYUSE (yyo);
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
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




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

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

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
  if (yypact_value_is_default (yyn))
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
      if (yytable_value_is_error (yyn))
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
/* Line 1792 of yacc.c  */
#line 380 "int_code.y"
    {display_three_add(q_list1);}
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 383 "int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);}
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 384 "int_code.y"
    {}
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 385 "int_code.y"
    {printf("%s\n", (yyvsp[(4) - (5)].str));}
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 386 "int_code.y"
    {printf("%s\n", (yyvsp[(3) - (4)].str));}
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 387 "int_code.y"
    {}
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 388 "int_code.y"
    {}
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 392 "int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str); }
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 393 "int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);}
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 396 "int_code.y"
    {insert(list2, yylineno, (yyvsp[(2) - (6)].str), "class", scope, " ", "class");}
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 399 "int_code.y"
    {}
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 400 "int_code.y"
    {}
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 401 "int_code.y"
    {yyerrok;}
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 404 "int_code.y"
    {(yyval.str)=(yyvsp[(2) - (3)].str);}
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 407 "int_code.y"
    {(yyval.str)=(yyvsp[(1) - (3)].str);strcat((yyval.str),",");strcat((yyval.str),(yyvsp[(3) - (3)].str));}
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 408 "int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);}
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 411 "int_code.y"
    {insert(list2, yylineno, (yyvsp[(1) - (4)].str), type, scope, " ", "ARRAY");}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 412 "int_code.y"
    {insert(list2, yylineno, (yyvsp[(2) - (2)].str), type, scope, " ", "PTR");}
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 413 "int_code.y"
    { insert(list2, yylineno, (yyvsp[(1) - (5)].str), "int" , scope, (yyvsp[(5) - (5)].str), "ARRAY");
    									   quadruple * new_record = create_quadruple("ARR","",(yyvsp[(5) - (5)].str),"",(yyvsp[(1) - (5)].str), yylineno);
                            			   insert_quadruple(q_list1,new_record);  }
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 418 "int_code.y"
    {insert(list2, yylineno, (yyvsp[(1) - (1)].str), type, scope, " ", "IDENT");}
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 419 "int_code.y"
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
                        }
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 430 "int_code.y"
    { insert(list2, yylineno, (yyvsp[(3) - (3)].str), type, scope, " ", "IDENT"); 
    }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 432 "int_code.y"
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
                        }
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 447 "int_code.y"
    {}
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 448 "int_code.y"
    {}
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 452 "int_code.y"
    {insert(list2, yylineno, (yyvsp[(2) - (4)].str), type, scope, " ", "FUNCT");}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 456 "int_code.y"
    {(yyval.str)=integer; strcpy(type, "int");}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 457 "int_code.y"
    {(yyval.str)="VOID"; strcpy(type, "void");}
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 458 "int_code.y"
    {(yyval.str)="float"; strcpy(type, "float");}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 459 "int_code.y"
    {(yyval.str)="char"; strcpy(type, "char");}
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 460 "int_code.y"
    {(yyval.str)="class"; strcpy(type, "class");}
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 464 "int_code.y"
    {}
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 465 "int_code.y"
    {}
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 466 "int_code.y"
    {}
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 467 "int_code.y"
    {}
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 472 "int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);}
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 473 "int_code.y"
    {}
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 477 "int_code.y"
    {(yyval.str) = "$";}
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 478 "int_code.y"
    {(yyval.str) = (yyvsp[(2) - (3)].str); reset_scope(list2,scope);}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 482 "int_code.y"
    {(yyval.str) = (yyvsp[(1) - (1)].str); }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 483 "int_code.y"
    {(yyval.str) = (yyvsp[(2) - (2)].str);}
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 487 "int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str); }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 488 "int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);}
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 492 "int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);}
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 493 "int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);}
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 494 "int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);}
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 495 "int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);}
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 496 "int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);}
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 497 "int_code.y"
    {(yyval.str) = (yyvsp[(1) - (1)].str);}
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 498 "int_code.y"
    {(yyval.str) = (yyvsp[(1) - (1)].str);}
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 499 "int_code.y"
    {}
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 500 "int_code.y"
    {}
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 504 "int_code.y"
    {
        if (strcmp(current_construct.stop_label,"") !=0) {
            quadruple* new_record;
            new_record = create_quadruple("goto","","","",current_construct.stop_label, yylineno);
            insert_quadruple(q_list1,new_record);
        } else {
            errors++;
            printf("Error in Line %d : Wrong Usage of statement \"break\"...\n", yylineno);
        }
    }
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 516 "int_code.y"
    {
        if (strcmp(current_construct.start_label,"") !=0) {
            quadruple* new_record;
            new_record = create_quadruple("goto","","","",current_construct.start_label, yylineno);
            insert_quadruple(q_list1,new_record);
        } else {
            errors++;
            printf("Error in Line %d : Wrong Usage of statement \"continue\"...\n", yylineno);
        }
    }
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 528 "int_code.y"
    {}
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 529 "int_code.y"
    {}
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 533 "int_code.y"
    {if(errors==0) printf("%s", (yyvsp[(2) - (2)].str));}
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 534 "int_code.y"
    {if(errors==0) printf("%s", (yyvsp[(2) - (3)].str));}
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 535 "int_code.y"
    {if(errors==0) printf("%s\n", (yyvsp[(2) - (4)].str));}
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 538 "int_code.y"
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
					}
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 565 "int_code.y"
    {(yyval.str) = yylval.str;}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 566 "int_code.y"
    {(yyval.str) = yylval.str;}
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 567 "int_code.y"
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

	}
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 583 "int_code.y"
    {}
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 584 "int_code.y"
    {(yyval.str)=(yyvsp[(1) - (2)].str);}
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 589 "int_code.y"
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
    }
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 605 "int_code.y"
    {
        quadruple* new_record;
        strcpy(if_stmt_skip_label,create_label());
        new_record = create_quadruple("goto","","","",if_stmt_skip_label, yylineno); 
        insert_quadruple(q_list1,new_record);
        new_record = create_quadruple("label","","","",(yyvsp[(5) - (6)].str), yylineno);
        insert_quadruple(q_list1,new_record);   
    }
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 612 "int_code.y"
    {
        quadruple* new_record;
        new_record = create_quadruple("label","","","",if_stmt_skip_label, yylineno);
        insert_quadruple(q_list1,new_record);
    }
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 620 "int_code.y"
    {
        //printf("else if\n");
        quadruple* new_record;
        //Insert Condition
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
    }
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 637 "int_code.y"
    {
        quadruple* new_record;
        new_record = create_quadruple("goto","","","",if_stmt_skip_label, yylineno); 
        insert_quadruple(q_list1,new_record);
        new_record = create_quadruple("label","","","",(yyvsp[(6) - (7)].str), yylineno);
        insert_quadruple(q_list1,new_record);   
    }
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 643 "int_code.y"
    {}
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 644 "int_code.y"
    {
        //printf("else\n");
    }
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 647 "int_code.y"
    {}
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 651 "int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);}
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 652 "int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);}
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 653 "int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);}
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 654 "int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);}
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 655 "int_code.y"
    {(yyval.str) = (yyvsp[(1) - (1)].str);}
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 656 "int_code.y"
    {(yyval.str) = (yyvsp[(1) - (1)].str);}
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 657 "int_code.y"
    {}
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 658 "int_code.y"
    {}
    break;

  case 84:
/* Line 1792 of yacc.c  */
#line 662 "int_code.y"
    {
        quadruple* new_record;
        char while_label[10];
        strcpy(while_label,create_label());
        new_record = create_quadruple("label","","","",while_label, yylineno);
        insert_quadruple(q_list1,new_record);
        strcpy(current_construct.start_label,while_label);
        (yyval.str)=while_label;}
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 670 "int_code.y"
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
        strcpy(current_construct.stop_label,false_label);
        new_record = create_quadruple("label","","","",true_label, yylineno);
        insert_quadruple(q_list1,new_record);
        (yyval.str)=false_label;
    }
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 686 "int_code.y"
    {
        quadruple* new_record = create_quadruple("goto","","","",(yyvsp[(2) - (7)].str), yylineno);
        insert_quadruple(q_list1,new_record);
        new_record = create_quadruple("label","","","",(yyvsp[(6) - (7)].str), yylineno);
        insert_quadruple(q_list1,new_record);
        strcpy(current_construct.start_label,"");
        strcpy(current_construct.stop_label,"");
    }
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 697 "int_code.y"
    {}
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 698 "int_code.y"
    {}
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 702 "int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);}
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 703 "int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);}
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 707 "int_code.y"
    {scope++;}
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 707 "int_code.y"
    {
        quadruple* new_record;
        char for_label[10];
        strcpy(for_label,create_label());
        new_record = create_quadruple("label","","","",for_label, yylineno);
        insert_quadruple(q_list1,new_record);
        strcpy(current_construct.start_label,for_label);
        (yyval.str)=for_label;
	}
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 716 "int_code.y"
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
        strcpy(current_construct.stop_label,break_label);
        (yyval.str)=break_label;
        scope--;
    }
    break;

  case 94:
/* Line 1792 of yacc.c  */
#line 730 "int_code.y"
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
        strcpy(current_construct.start_label,"");
        strcpy(current_construct.stop_label,"");
    }
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 753 "int_code.y"
    {}
    break;

  case 96:
/* Line 1792 of yacc.c  */
#line 754 "int_code.y"
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
                            }
    break;

  case 97:
/* Line 1792 of yacc.c  */
#line 767 "int_code.y"
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
                }
    break;

  case 98:
/* Line 1792 of yacc.c  */
#line 780 "int_code.y"
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
                }
    break;

  case 99:
/* Line 1792 of yacc.c  */
#line 794 "int_code.y"
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
                }
    break;

  case 100:
/* Line 1792 of yacc.c  */
#line 808 "int_code.y"
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
                }
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 824 "int_code.y"
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
                            

                        }
    break;

  case 102:
/* Line 1792 of yacc.c  */
#line 840 "int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);}
    break;

  case 103:
/* Line 1792 of yacc.c  */
#line 843 "int_code.y"
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
                }
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 875 "int_code.y"
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

                }
    break;

  case 105:
/* Line 1792 of yacc.c  */
#line 907 "int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);}
    break;

  case 106:
/* Line 1792 of yacc.c  */
#line 911 "int_code.y"
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
                }
    break;

  case 107:
/* Line 1792 of yacc.c  */
#line 940 "int_code.y"
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
                    }
    break;

  case 108:
/* Line 1792 of yacc.c  */
#line 977 "int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);}
    break;

  case 109:
/* Line 1792 of yacc.c  */
#line 978 "int_code.y"
    {

				strcat((yyvsp[(1) - (3)].str), (yyvsp[(2) - (3)].str));
				strcat((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str));
				(yyval.str) = (yyvsp[(1) - (3)].str);                        
    		}
    break;

  case 110:
/* Line 1792 of yacc.c  */
#line 987 "int_code.y"
    {(yyval.str) = "<";}
    break;

  case 111:
/* Line 1792 of yacc.c  */
#line 988 "int_code.y"
    {(yyval.str) = "<=";}
    break;

  case 112:
/* Line 1792 of yacc.c  */
#line 989 "int_code.y"
    {(yyval.str) = ">";}
    break;

  case 113:
/* Line 1792 of yacc.c  */
#line 990 "int_code.y"
    {(yyval.str) = ">=";}
    break;

  case 114:
/* Line 1792 of yacc.c  */
#line 991 "int_code.y"
    {(yyval.str) = "==";}
    break;

  case 115:
/* Line 1792 of yacc.c  */
#line 992 "int_code.y"
    {(yyval.str) = "!=";}
    break;

  case 116:
/* Line 1792 of yacc.c  */
#line 996 "int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);
        }
    break;

  case 117:
/* Line 1792 of yacc.c  */
#line 998 "int_code.y"
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
    }
    break;

  case 118:
/* Line 1792 of yacc.c  */
#line 1012 "int_code.y"
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
    	}
    break;

  case 119:
/* Line 1792 of yacc.c  */
#line 1026 "int_code.y"
    {(yyval.str) = (yyvsp[(2) - (2)].str);}
    break;

  case 120:
/* Line 1792 of yacc.c  */
#line 1027 "int_code.y"
    {char temp[20];strcpy(temp,"-");strcat(temp,(yyvsp[(2) - (2)].str));(yyval.str) = temp;}
    break;

  case 121:
/* Line 1792 of yacc.c  */
#line 1031 "int_code.y"
    {
              (yyval.str) = (yyvsp[(1) - (1)].str);
            }
    break;

  case 122:
/* Line 1792 of yacc.c  */
#line 1034 "int_code.y"
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
		}
    break;

  case 123:
/* Line 1792 of yacc.c  */
#line 1049 "int_code.y"
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
		}
    break;

  case 124:
/* Line 1792 of yacc.c  */
#line 1067 "int_code.y"
    {(yyval.str)=(yyvsp[(2) - (3)].str); }
    break;

  case 125:
/* Line 1792 of yacc.c  */
#line 1068 "int_code.y"
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
            strcpy(det1.type,id_ex->dtype);            
          }}}
    break;

  case 126:
/* Line 1792 of yacc.c  */
#line 1082 "int_code.y"
    {
        (yyval.str)=(yyvsp[(1) - (1)].str);
        }
    break;

  case 127:
/* Line 1792 of yacc.c  */
#line 1085 "int_code.y"
    { 
           (yyval.str) = yylval.str;
           strcpy(det1.type,"int");
           }
    break;

  case 128:
/* Line 1792 of yacc.c  */
#line 1089 "int_code.y"
    {
        (yyval.str) = yylval.str;
        strcpy(det1.type,"float");
    	}
    break;

  case 129:
/* Line 1792 of yacc.c  */
#line 1093 "int_code.y"
    {(yyval.str) = yylval.str;strcpy(det1.type,"string");}
    break;

  case 130:
/* Line 1792 of yacc.c  */
#line 1097 "int_code.y"
    {}
    break;

  case 131:
/* Line 1792 of yacc.c  */
#line 1098 "int_code.y"
    {}
    break;

  case 132:
/* Line 1792 of yacc.c  */
#line 1102 "int_code.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str);}
    break;

  case 133:
/* Line 1792 of yacc.c  */
#line 1103 "int_code.y"
    {}
    break;


/* Line 1792 of yacc.c  */
#line 3255 "int_code.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
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
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
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
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
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
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
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


/* Line 2055 of yacc.c  */
#line 1106 "int_code.y"

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



