
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
#line 1 ".\\syntax_tree.y"


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





/* Line 189 of yacc.c  */
#line 320 "syntax_tree.tab.c"

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
#line 246 ".\\syntax_tree.y"





/* Line 209 of yacc.c  */
#line 350 "syntax_tree.tab.c"

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
     STR = 293,
     LETTER = 294,
     DIGIT = 295,
     NONTOKEN = 296,
     ERROR = 297,
     ENDFILE = 298,
     NL = 299,
     ENDL = 300,
     INSERTION = 301,
     EXTRACTION = 302,
     CIN = 303,
     COUT = 304,
     CLASS = 305,
     THEN = 306
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 250 ".\\syntax_tree.y"

    char* str;
    struct treeNode * ast;



/* Line 214 of yacc.c  */
#line 425 "syntax_tree.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 437 "syntax_tree.tab.c"

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
#define YYLAST   248

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  97
/* YYNRULES -- Number of states.  */
#define YYNSTATES  170

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   306

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
      45,    46,    47,    48,    49,    50,    51
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    12,    15,    17,    19,
      26,    30,    34,    37,    42,    45,    47,    51,    55,    58,
      62,    67,    69,    71,    73,    75,    77,    80,    83,    88,
      93,    95,    97,   100,   104,   106,   109,   111,   113,   115,
     117,   119,   121,   123,   125,   127,   129,   131,   135,   138,
     142,   147,   152,   154,   156,   158,   160,   163,   171,   177,
     183,   186,   190,   192,   194,   204,   208,   210,   213,   216,
     218,   221,   224,   226,   230,   232,   234,   236,   238,   240,
     242,   244,   248,   252,   255,   258,   260,   264,   268,   272,
     274,   276,   278,   280,   282,   286,   291,   293
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      53,     0,    -1,    54,    -1,    55,    -1,    54,    55,    -1,
      56,    -1,    54,    56,    -1,    57,    -1,    61,    -1,    62,
      35,    31,    55,    32,    25,    -1,    62,    59,    25,    -1,
      62,    58,    25,    -1,     1,    25,    -1,    35,    29,    36,
      30,    -1,    16,    35,    -1,    35,    -1,    35,    24,    78,
      -1,    59,    26,    35,    -1,    27,    28,    -1,    27,    64,
      28,    -1,    62,    35,    60,    65,    -1,     8,    -1,     7,
      -1,     9,    -1,    10,    -1,    50,    -1,     8,    35,    -1,
       9,    35,    -1,    63,    26,     8,    35,    -1,    63,    26,
       9,    35,    -1,    63,    -1,     7,    -1,    31,    32,    -1,
      31,    66,    32,    -1,    67,    -1,    66,    67,    -1,    57,
      -1,    68,    -1,    74,    -1,    65,    -1,    75,    -1,    76,
      -1,    77,    -1,    79,    -1,    69,    -1,    70,    -1,    72,
      -1,    49,    71,    25,    -1,    46,    73,    -1,    46,    73,
      71,    -1,    46,    73,    46,    45,    -1,    48,    47,    35,
      25,    -1,    36,    -1,    38,    -1,    35,    -1,    25,    -1,
      78,    25,    -1,     3,    27,    78,    28,    68,     4,    68,
      -1,     3,    27,    78,    28,    68,    -1,     5,    27,    78,
      28,    68,    -1,     6,    25,    -1,     6,    78,    25,    -1,
      80,    -1,    83,    -1,    11,    27,    80,    25,    83,    25,
      81,    28,    65,    -1,    35,    24,    78,    -1,    81,    -1,
      12,    35,    -1,    13,    35,    -1,    82,    -1,    35,    12,
      -1,    35,    13,    -1,    85,    -1,    85,    84,    85,    -1,
      18,    -1,    19,    -1,    20,    -1,    21,    -1,    22,    -1,
      23,    -1,    86,    -1,    85,    14,    86,    -1,    85,    15,
      86,    -1,    14,    85,    -1,    15,    85,    -1,    87,    -1,
      86,    16,    87,    -1,    86,    17,    87,    -1,    27,    78,
      28,    -1,    35,    -1,    88,    -1,    36,    -1,    37,    -1,
      38,    -1,    35,    27,    28,    -1,    35,    27,    89,    28,
      -1,    78,    -1,    78,    26,    89,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   275,   275,   278,   279,   280,   281,   285,   286,   290,
     292,   294,   295,   299,   300,   304,   305,   312,   316,   317,
     321,   325,   326,   327,   328,   329,   333,   334,   335,   336,
     341,   342,   346,   347,   351,   352,   356,   357,   361,   362,
     363,   364,   365,   366,   367,   370,   371,   373,   376,   377,
     378,   380,   382,   383,   384,   386,   387,   392,   393,   397,
     401,   402,   406,   407,   410,   412,   422,   425,   438,   452,
     456,   469,   486,   487,   491,   492,   493,   494,   495,   496,
     500,   508,   509,   510,   511,   515,   523,   524,   528,   529,
     555,   556,   559,   560,   564,   565,   569,   570
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
  "RBRACE", "LCOMMENT", "RCOMMENT", "ID", "NUM", "FLT", "STR", "LETTER",
  "DIGIT", "NONTOKEN", "ERROR", "ENDFILE", "NL", "ENDL", "INSERTION",
  "EXTRACTION", "CIN", "COUT", "CLASS", "THEN", "$accept", "atree",
  "program", "external_declaration", "class_declaration",
  "var_declaration", "array_dec", "init_declarator_list", "declarator",
  "fun_declaration", "declaration_specifiers", "params_list", "params",
  "compound_stmt", "block_item_list", "block_item", "statement",
  "stream_constructs", "cout_cascade", "cascade_out", "cin", "op",
  "expression_stmt", "if_stmt", "while_stmt", "return_stmt", "expression",
  "for_stmt", "assignment_expression", "unary_expression",
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
     305,   306
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    52,    53,    54,    54,    54,    54,    55,    55,    56,
      57,    57,    57,    58,    58,    59,    59,    59,    60,    60,
      61,    62,    62,    62,    62,    62,    63,    63,    63,    63,
      64,    64,    65,    65,    66,    66,    67,    67,    68,    68,
      68,    68,    68,    68,    68,    69,    69,    70,    71,    71,
      71,    72,    73,    73,    73,    74,    74,    75,    75,    76,
      77,    77,    78,    78,    79,    80,    80,    81,    81,    81,
      82,    82,    83,    83,    84,    84,    84,    84,    84,    84,
      85,    85,    85,    85,    85,    86,    86,    86,    87,    87,
      87,    87,    87,    87,    88,    88,    89,    89
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     2,     1,     1,     6,
       3,     3,     2,     4,     2,     1,     3,     3,     2,     3,
       4,     1,     1,     1,     1,     1,     2,     2,     4,     4,
       1,     1,     2,     3,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     2,     3,
       4,     4,     1,     1,     1,     1,     2,     7,     5,     5,
       2,     3,     1,     1,     9,     3,     1,     2,     2,     1,
       2,     2,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     2,     2,     1,     3,     3,     3,     1,
       1,     1,     1,     1,     3,     4,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    22,    21,    23,    24,    25,     0,     0,     3,
       5,     7,     8,     0,    12,     1,     4,     6,     0,    15,
       0,     0,    14,     0,     0,     0,     0,     0,    11,    10,
       0,     0,     0,     0,     0,     0,    89,    91,    92,    93,
      16,    62,    66,    69,    63,    72,    80,    85,    90,    31,
       0,     0,    18,    30,     0,     0,     0,     0,     0,    20,
      17,    67,    68,    89,    83,    84,     0,    70,    71,     0,
       0,     0,     0,    74,    75,    76,    77,    78,    79,     0,
       0,     0,    26,    27,     0,    19,    13,     0,    15,     0,
       0,     0,     0,    55,    32,     0,     0,    36,     0,    39,
       0,    34,    37,    44,    45,    46,    38,    40,    41,    42,
       0,    43,    88,    65,    94,    96,     0,    81,    82,    73,
      86,    87,     0,     0,     9,     0,     0,    60,     0,     0,
       0,     0,     0,    15,    33,    35,    56,     0,    95,    28,
      29,     0,     0,    61,     0,     0,     0,    54,    52,    53,
      48,    47,    97,     0,     0,     0,    51,     0,    49,    58,
      59,     0,    50,     0,     0,    57,     0,     0,     0,    64
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     7,     8,     9,    10,    11,    20,    21,    27,    12,
      13,    53,    54,    99,   100,   101,   102,   103,   104,   132,
     105,   150,   106,   107,   108,   109,   110,   111,    41,    42,
      43,    44,    79,    45,    46,    47,    48,   116
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -90
static const yytype_int16 yypact[] =
{
       2,    -7,   -90,   -90,   -90,   -90,   -90,    22,     7,   -90,
     -90,   -90,   -90,     4,   -90,   -90,   -90,   -90,    27,   146,
      94,    66,   -90,   153,    33,    58,     2,    77,   -90,   -90,
      90,    96,   110,   172,   172,   153,   188,   -90,   -90,   -90,
     -90,   -90,   -90,   -90,   -90,   206,    97,   -90,   -90,   -90,
     114,   119,   -90,   143,   148,   141,   149,    28,    18,   -90,
     -90,   -90,   -90,   165,   -90,   -90,   168,   -90,   -90,   153,
     120,   167,   167,   -90,   -90,   -90,   -90,   -90,   -90,   172,
     167,   167,   -90,   -90,   108,   -90,   -90,   170,    73,   166,
     171,   147,   179,   -90,   -90,   150,   173,   -90,    43,   -90,
      74,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,
     186,   -90,   -90,   -90,   -90,   191,   190,    97,    97,   122,
     -90,   -90,   187,   195,   -90,   153,   153,   -90,   207,    23,
     196,    35,   208,    69,   -90,   -90,   -90,   153,   -90,   -90,
     -90,   209,   210,   -90,    83,   211,   214,   -90,   -90,   -90,
     189,   -90,   -90,   115,   115,   172,   -90,   178,   -90,   230,
     -90,   215,   -90,   115,    25,   -90,   126,   213,    77,   -90
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -90,   -90,   -90,    64,   234,   -54,   -90,   -90,   -90,   -90,
     -24,   -90,   -90,   -27,   -90,   144,   -89,   -90,   -90,    93,
     -90,   -90,   -90,   -90,   -90,   -90,   -22,   -90,   116,    82,
     -90,    92,   -90,   -28,    72,    98,   -90,   111
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -3
static const yytype_int16 yytable[] =
{
      59,    40,    57,     1,    97,    64,    65,    -2,     1,     2,
       3,     4,     5,    66,     2,     3,     4,     5,    14,     1,
      18,    89,    15,    90,    91,     2,     3,     4,     5,    92,
      31,    32,    33,    34,    98,    31,    32,    31,    32,    19,
      49,    50,    51,    93,    18,    35,    97,   113,   115,    58,
      94,   119,     6,    36,    37,    38,    39,     6,   144,    18,
     166,    52,    22,    88,   159,   160,    95,    96,     6,   128,
     147,   148,    16,   149,   165,     1,    98,    89,   133,    90,
      91,     2,     3,     4,     5,    92,    31,    32,    33,    34,
      56,    29,    30,    23,    55,    67,    68,    23,    25,    93,
      24,    35,    25,   141,   142,    58,   134,    69,    58,    36,
      37,    38,    39,    80,    81,   115,   122,   123,    89,    28,
      90,    91,    95,    96,     6,    60,    92,    31,    32,    33,
      34,    61,    31,    32,    33,    34,    71,    72,    67,    68,
      93,   169,    35,   117,   118,    62,    58,    35,   114,    82,
      36,    37,    38,    39,    83,    36,    37,    38,    39,    31,
      32,    33,    34,    95,    96,    31,    32,    33,    34,    84,
      23,    86,   127,    24,    35,    25,    85,    26,   120,   121,
      35,    87,    36,    37,    38,    39,    33,    34,    36,    37,
      38,    39,    70,   125,    35,   124,   112,   130,   126,    35,
      67,    68,    63,    37,    38,    39,   129,    63,    37,    38,
      39,   136,    69,   147,   148,    70,   149,   137,   138,   131,
      71,    72,   139,   162,    73,    74,    75,    76,    77,    78,
     140,   146,   143,   151,   163,   157,   155,   153,   154,   156,
     164,   168,    17,   158,   135,   145,   167,   161,   152
};

static const yytype_uint8 yycheck[] =
{
      27,    23,    26,     1,    58,    33,    34,     0,     1,     7,
       8,     9,    10,    35,     7,     8,     9,    10,    25,     1,
      16,     3,     0,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    58,    12,    13,    12,    13,    35,
       7,     8,     9,    25,    16,    27,   100,    69,    70,    31,
      32,    79,    50,    35,    36,    37,    38,    50,    35,    16,
      35,    28,    35,    35,   153,   154,    48,    49,    50,    91,
      35,    36,     8,    38,   163,     1,   100,     3,    35,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      26,    25,    26,    24,    36,    12,    13,    24,    29,    25,
      27,    27,    29,   125,   126,    31,    32,    24,    31,    35,
      36,    37,    38,    16,    17,   137,     8,     9,     3,    25,
       5,     6,    48,    49,    50,    35,    11,    12,    13,    14,
      15,    35,    12,    13,    14,    15,    14,    15,    12,    13,
      25,   168,    27,    71,    72,    35,    31,    27,    28,    35,
      35,    36,    37,    38,    35,    35,    36,    37,    38,    12,
      13,    14,    15,    48,    49,    12,    13,    14,    15,    26,
      24,    30,    25,    27,    27,    29,    28,    31,    80,    81,
      27,    32,    35,    36,    37,    38,    14,    15,    35,    36,
      37,    38,    27,    27,    27,    25,    28,    47,    27,    27,
      12,    13,    35,    36,    37,    38,    27,    35,    36,    37,
      38,    25,    24,    35,    36,    27,    38,    26,    28,    46,
      14,    15,    35,    45,    18,    19,    20,    21,    22,    23,
      35,    35,    25,    25,     4,    46,    25,    28,    28,    25,
      25,    28,     8,   150,   100,   129,   164,   155,   137
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     7,     8,     9,    10,    50,    53,    54,    55,
      56,    57,    61,    62,    25,     0,    55,    56,    16,    35,
      58,    59,    35,    24,    27,    29,    31,    60,    25,    25,
      26,    12,    13,    14,    15,    27,    35,    36,    37,    38,
      78,    80,    81,    82,    83,    85,    86,    87,    88,     7,
       8,     9,    28,    63,    64,    36,    55,    62,    31,    65,
      35,    35,    35,    35,    85,    85,    78,    12,    13,    24,
      27,    14,    15,    18,    19,    20,    21,    22,    23,    84,
      16,    17,    35,    35,    26,    28,    30,    32,    35,     3,
       5,     6,    11,    25,    32,    48,    49,    57,    62,    65,
      66,    67,    68,    69,    70,    72,    74,    75,    76,    77,
      78,    79,    28,    78,    28,    78,    89,    86,    86,    85,
      87,    87,     8,     9,    25,    27,    27,    25,    78,    27,
      47,    46,    71,    35,    32,    67,    25,    26,    28,    35,
      35,    78,    78,    25,    35,    80,    35,    35,    36,    38,
      73,    25,    89,    28,    28,    25,    25,    46,    71,    68,
      68,    83,    45,     4,    25,    68,    35,    81,    28,    65
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
#line 275 ".\\syntax_tree.y"
    {printNode((yyvsp[(1) - (1)].ast));;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 278 ".\\syntax_tree.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 279 ".\\syntax_tree.y"
    {(yyval.ast)=newnode(yylineno, STR(program), none, none, none,  2, (yyvsp[(1) - (2)].ast), (yyvsp[(2) - (2)].ast)); ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 280 ".\\syntax_tree.y"
    {(yyval.ast) = (yyvsp[(1) - (1)].ast);;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 281 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno, "program", none, none, none, 2, (yyvsp[(1) - (2)].ast), (yyvsp[(2) - (2)].ast));printf("Here\n");;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 285 ".\\syntax_tree.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 286 ".\\syntax_tree.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 290 ".\\syntax_tree.y"
    {insert(list2, yylineno, (yyvsp[(2) - (6)].str), "class", scope, -1, 0.0, '\0', "class"); (yyval.ast) = newnode(yylineno, "class_declaration", (yyvsp[(2) - (6)].str), none, "class", 1, (yyvsp[(4) - (6)].ast));;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 293 ".\\syntax_tree.y"
    {(yyval.ast)=newnode(yylineno, "var_declaration", none, none, (yyvsp[(1) - (3)].str), 1, (yyvsp[(2) - (3)].ast));;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 294 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno, "var_declaration", none, none, (yyvsp[(1) - (3)].str), 1, (yyvsp[(2) - (3)].ast));;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 295 ".\\syntax_tree.y"
    {yyerrok; printf("Here\n");;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 299 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno, "array_dec", (yyvsp[(1) - (4)].str), none, none, 0);insert(list2, yylineno, (yyvsp[(1) - (4)].str), type, scope, -1, 0.0, '\0', "ARRAY");;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 300 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno, "array_dec", (yyvsp[(2) - (2)].str), none, none, 0);insert(list2, yylineno, (yyvsp[(2) - (2)].str), type, scope, -1, 0.0, '\0', "PTR");;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 304 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno, "init_declarator_list", (yyvsp[(1) - (1)].str), none, none, 0);insert(list2, yylineno, (yyvsp[(1) - (1)].str), type, scope, -1, 0.0, '\0',"IDENT");;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 305 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno,"init_declarator_list", (yyvsp[(1) - (3)].str), none, none,  1, (yyvsp[(3) - (3)].ast));
                            insert(list2, yylineno, (yyvsp[(1) - (3)].str), type, scope, -1,0.0,'\0', "IDENT");
                            update(list2, (yyvsp[(1) - (3)].str), scope, iexpval, fexpval, cexpval);
                            iflag = 0;
                            fflag = 0;
                            cflag = 0; 
                        ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 312 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno,"init_declarator_list", (yyvsp[(3) - (3)].str), none, none,  1, (yyvsp[(1) - (3)].ast)); insert(list2, yylineno, (yyvsp[(3) - (3)].str), type, scope, -1,0.0,'\0', "IDENT"); ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 316 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno,"declarator", none, none, none,  0);;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 317 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno,"declarator", none, none, none,  1, (yyvsp[(2) - (3)].ast));;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 321 ".\\syntax_tree.y"
    {(yyval.ast)=newnode(yylineno,STR(fun_declaration), (yyvsp[(2) - (4)].str), none, (yyvsp[(1) - (4)].str),  1, (yyvsp[(4) - (4)].ast));;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 325 ".\\syntax_tree.y"
    {(yyval.str)=integer; strcpy(type, "int");;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 326 ".\\syntax_tree.y"
    {(yyval.str)="VOID"; strcpy(type, "void");;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 327 ".\\syntax_tree.y"
    {(yyval.str)="float"; strcpy(type, "float");;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 328 ".\\syntax_tree.y"
    {(yyval.str)="char"; strcpy(type, "char");;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 329 ".\\syntax_tree.y"
    {(yyval.str)="class"; strcpy(type, "class");;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 333 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno,"params_list", (yyvsp[(2) - (2)].str), none, integer,  0);;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 334 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno,"params_list", (yyvsp[(2) - (2)].str), none, floating,  0);;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 335 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno,"params_list", (yyvsp[(4) - (4)].str), none, integer,  1, (yyvsp[(1) - (4)].ast));;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 336 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno,"params_list", (yyvsp[(4) - (4)].str), none, floating,  1, (yyvsp[(1) - (4)].ast));;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 341 ".\\syntax_tree.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 342 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno,"params", none, none, "VOID",  0);;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 346 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno,"compound_stmt", none, none, none,  0);;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 347 ".\\syntax_tree.y"
    {(yyval.ast) = (yyvsp[(2) - (3)].ast);;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 351 ".\\syntax_tree.y"
    {(yyval.ast) = (yyvsp[(1) - (1)].ast); ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 352 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno,"block_item_list", none, none, none,  2, (yyvsp[(1) - (2)].ast), (yyvsp[(2) - (2)].ast));;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 356 ".\\syntax_tree.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast); ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 357 ".\\syntax_tree.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 361 ".\\syntax_tree.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 362 ".\\syntax_tree.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 363 ".\\syntax_tree.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 364 ".\\syntax_tree.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 365 ".\\syntax_tree.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 366 ".\\syntax_tree.y"
    {(yyval.ast) = (yyvsp[(1) - (1)].ast);;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 367 ".\\syntax_tree.y"
    {(yyval.ast)= (yyvsp[(1) - (1)].ast);;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 370 ".\\syntax_tree.y"
    {(yyval.ast) = (yyvsp[(1) - (1)].ast);;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 371 ".\\syntax_tree.y"
    {(yyval.ast) = (yyvsp[(1) - (1)].ast);;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 373 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno, "cout_cascade", none, none, none, 1, (yyvsp[(2) - (3)].ast));;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 376 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno, "cascade_out", none, none, none, 1, (yyvsp[(2) - (2)].ast));;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 377 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno, "cascade_out", none, none, none, 2, (yyvsp[(2) - (3)].ast), (yyvsp[(3) - (3)].ast));;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 378 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno, "cascade_out", none,none, none, 1, (yyvsp[(2) - (4)].ast));;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 380 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno, "cin", none, none, none, 1,  (yyvsp[(3) - (4)].str));;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 382 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno, "op", none, (yyvsp[(1) - (1)].str), none, 0);;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 383 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno, "op", none, (yyvsp[(1) - (1)].str), none, 0);;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 384 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno, "op", (yyvsp[(1) - (1)].str), none, none, 0);;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 386 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno,"expression_stmt", none, none, none,  0);;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 387 ".\\syntax_tree.y"
    {(yyval.ast)=(yyvsp[(1) - (2)].ast);;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 392 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno,"if_stmt", none, none, none,  3, (yyvsp[(3) - (7)].ast), (yyvsp[(5) - (7)].ast), (yyvsp[(7) - (7)].ast)); ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 393 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno,"if_stmt", none, none, none,  2, (yyvsp[(3) - (5)].ast), (yyvsp[(5) - (5)].ast));;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 397 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno,"while_stmt", none, none, none,  2, (yyvsp[(3) - (5)].ast), (yyvsp[(5) - (5)].ast));;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 401 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno,"return_stmt", none, none, none,  0);;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 402 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno,"return_stmt", none, none, none,  1, (yyvsp[(2) - (3)].ast));;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 406 ".\\syntax_tree.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 407 ".\\syntax_tree.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 410 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno, "for_stmt", none, none, none, 4, (yyvsp[(3) - (9)].ast), (yyvsp[(5) - (9)].ast),(yyvsp[(7) - (9)].ast), (yyvsp[(9) - (9)].ast));;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 412 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno,"assignment_expression", (yyvsp[(1) - (3)].str), none, none,  1, (yyvsp[(3) - (3)].ast)); 
                            int ex = exists(list2,(yyvsp[(1) - (3)].str), scope); 
                            if(ex == 0) {printf("Error on Lineno %d: Assignment before Declaration\n",yylineno);errors++;}
                            id_ex = find(list2, (yyvsp[(1) - (3)].str),scope);
                            iflag = 0;
                            cflag = 0;
                            fflag = 0;
                            update(list2, (yyvsp[(1) - (3)].str),scope, iexpval, fexpval, cexpval);

                        ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 422 ".\\syntax_tree.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 425 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno,"unary_expression", (yyvsp[(2) - (2)].str), none, "++",  0); 
                 id_ex = find(list2, (yyvsp[(2) - (2)].str), scope); 
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
                ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 438 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno,"unary_expression", (yyvsp[(2) - (2)].str), none, "--",  0);
                 id_ex = find(list2, (yyvsp[(2) - (2)].str), scope); 
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

                ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 452 ".\\syntax_tree.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 456 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno,"postfix_expression", (yyvsp[(1) - (2)].str), none, "++",  0);
                 id_ex = find(list2, (yyvsp[(1) - (2)].str), scope); 
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
                ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 469 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno,"postfix_expression", (yyvsp[(1) - (2)].str), none, "--",  0);
                 id_ex = find(list2, (yyvsp[(1) - (2)].str), scope); 
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

                ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 486 ".\\syntax_tree.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 487 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno,"simple_expression", none, none, (yyvsp[(2) - (3)].str),  2, (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast));;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 491 ".\\syntax_tree.y"
    {(yyval.str) = "<";;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 492 ".\\syntax_tree.y"
    {(yyval.str) = "<=";;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 493 ".\\syntax_tree.y"
    {(yyval.str) = ">";;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 494 ".\\syntax_tree.y"
    {(yyval.str) = ">=";;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 495 ".\\syntax_tree.y"
    {(yyval.str) = "==";;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 496 ".\\syntax_tree.y"
    {(yyval.str) = "!=";;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 500 ".\\syntax_tree.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast); 
            if(iflag == 1)
                iexpval = itermval;
            if(fflag == 1)
                fexpval = ftermval;
            if(cflag == 1)
                cexpval = ctermval;
        ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 508 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno,"additive_expression", none, none, "+",  2, (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast)); ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 509 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno,"additive_expression", none, none, "-",  2, (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast));;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 510 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno,"additive_expression", none, none, "+",  1, (yyvsp[(2) - (2)].ast));;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 511 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno,"additive_expression", none, none, "-",  1, (yyvsp[(2) - (2)].ast));;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 515 ".\\syntax_tree.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast); 
              if(iflag == 1)
                itermval = iasval;
              if(fflag == 1)
                ftermval = fasval;
              if(cflag == 1)
                ctermval = casval;
            ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 523 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno,"term", none, none, "*",  2, (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast));;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 524 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno,"term", none, none, "/",  2, (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast));;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 528 ".\\syntax_tree.y"
    {(yyval.ast)=(yyvsp[(2) - (3)].ast);;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 529 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno,"factor", (yyvsp[(1) - (1)].str), none, none,  0);
          id_ex = find(list2, (yyvsp[(1) - (1)].str), scope);
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
          };}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 555 ".\\syntax_tree.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 556 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno,"factor", none, (yyvsp[(1) - (1)].str), none,  0); 
           iasval = atoi(yylval.str); iflag = 1; cflag=0; fflag=0;
           ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 559 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno, "factor", none, (yyvsp[(1) - (1)].str), none, 0);iasval = atof(yylval.str); iflag=0; cflag=0; fflag=1;;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 560 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno, "factor", none, (yyvsp[(1) - (1)].str), none, 0); ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 564 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno,"call", (yyvsp[(1) - (3)].str), none, none,  0);;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 565 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno,"call", (yyvsp[(1) - (4)].str), none, none,  1, (yyvsp[(3) - (4)].ast));;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 569 ".\\syntax_tree.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 570 ".\\syntax_tree.y"
    {(yyval.ast) = newnode(yylineno,"args", none, none, none,  2, (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast));;}
    break;



/* Line 1455 of yacc.c  */
#line 2583 "syntax_tree.tab.c"
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
#line 573 ".\\syntax_tree.y"

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




