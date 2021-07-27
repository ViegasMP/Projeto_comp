/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     STRLIT = 258,
     RESERVED = 259,
     REALLIT = 260,
     INTLIT = 261,
     BOOLLIT = 262,
     AND = 263,
     ASSIGN = 264,
     STAR = 265,
     COMMA = 266,
     DIV = 267,
     EQ = 268,
     GE = 269,
     GT = 270,
     LBRACE = 271,
     LE = 272,
     LPAR = 273,
     LSQ = 274,
     LT = 275,
     MINUS = 276,
     MOD = 277,
     NE = 278,
     NOT = 279,
     OR = 280,
     PLUS = 281,
     RBRACE = 282,
     RPAR = 283,
     RSQ = 284,
     SEMICOLON = 285,
     ARROW = 286,
     LSHIFT = 287,
     RSHIFT = 288,
     XOR = 289,
     BOOL = 290,
     CLASS = 291,
     DOTLENGTH = 292,
     DOUBLE = 293,
     ELSE = 294,
     IF = 295,
     INT = 296,
     PRINT = 297,
     PARSEINT = 298,
     PUBLIC = 299,
     RETURN = 300,
     STATIC = 301,
     STRING = 302,
     VOID = 303,
     WHILE = 304,
     ID = 305
   };
#endif
/* Tokens.  */
#define STRLIT 258
#define RESERVED 259
#define REALLIT 260
#define INTLIT 261
#define BOOLLIT 262
#define AND 263
#define ASSIGN 264
#define STAR 265
#define COMMA 266
#define DIV 267
#define EQ 268
#define GE 269
#define GT 270
#define LBRACE 271
#define LE 272
#define LPAR 273
#define LSQ 274
#define LT 275
#define MINUS 276
#define MOD 277
#define NE 278
#define NOT 279
#define OR 280
#define PLUS 281
#define RBRACE 282
#define RPAR 283
#define RSQ 284
#define SEMICOLON 285
#define ARROW 286
#define LSHIFT 287
#define RSHIFT 288
#define XOR 289
#define BOOL 290
#define CLASS 291
#define DOTLENGTH 292
#define DOUBLE 293
#define ELSE 294
#define IF 295
#define INT 296
#define PRINT 297
#define PARSEINT 298
#define PUBLIC 299
#define RETURN 300
#define STATIC 301
#define STRING 302
#define VOID 303
#define WHILE 304
#define ID 305




/* Copy the first part of user declarations.  */
#line 1 "jucompiler.y"

/*
		Carolina de Castilho Godinho	-	2017247087
		Maria Paula de Alencar Viegas	-	2017125592
		Correr com:
		lex jucompiler.l
		yacc -d jucompiler.y
		cc -o jucompiler y.tab.c lex.yy.c tree_functions.c semantic.c symbol_table.c
		./jucompiler -s < Factorial.java 
*/
#line 12 "jucompiler.y"

#include <stdio.h>
#include <stdbool.h> 
#include "tree_functions.h"
int yylex(void);
void yyerror (char *s);
int syntax_error = 0;
extern char* yytext;
extern int line_count;
extern int col_count;
extern int ini_line; //guarda linha em que começa comentario ou string
extern int ini_col; //guarda coluna em que começa comentario ou string
extern bool e2;
extern int col_syntax;
struct no* tree;
struct no* aux;
struct no* type;
struct no* dcl;
struct no* body;
struct no* par;
struct no* assign;
struct no* no_void;
struct no* no_id;
struct no* header;
struct no* no_if;
struct no* elseblock;
struct no* no_call;
struct no* no_parse;
struct no* no_block;


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

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 43 "jucompiler.y"
{
	char * str;
	struct no* no;
}
/* Line 193 of yacc.c.  */
#line 243 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 256 "y.tab.c"

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
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
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
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   451

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  88
/* YYNRULES -- Number of states.  */
#define YYNSTATES  178

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   305

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
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     8,    14,    17,    20,    23,    25,    27,
      29,    34,    40,    43,    47,    49,    51,    53,    55,    61,
      66,    72,    77,    81,    84,    89,    94,    98,   102,   105,
     108,   111,   113,   115,   119,   122,   126,   132,   140,   146,
     150,   153,   155,   158,   161,   164,   170,   176,   179,   182,
     184,   190,   195,   199,   204,   208,   211,   215,   223,   228,
     230,   232,   236,   240,   244,   248,   252,   256,   260,   264,
     268,   272,   276,   280,   284,   288,   292,   296,   299,   302,
     305,   309,   311,   313,   316,   318,   320,   322,   324
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      52,     0,    -1,    36,    50,    16,    27,    -1,    36,    50,
      16,    53,    27,    -1,    53,    54,    -1,    53,    55,    -1,
      53,    30,    -1,    55,    -1,    54,    -1,    30,    -1,    44,
      46,    58,    61,    -1,    44,    46,    57,    56,    30,    -1,
       1,    30,    -1,    56,    11,    50,    -1,    50,    -1,    35,
      -1,    41,    -1,    38,    -1,    57,    50,    18,    59,    28,
      -1,    57,    50,    18,    28,    -1,    48,    50,    18,    59,
      28,    -1,    48,    50,    18,    28,    -1,    57,    50,    60,
      -1,    57,    50,    -1,    47,    19,    29,    50,    -1,    11,
      57,    50,    60,    -1,    11,    57,    50,    -1,    16,    62,
      27,    -1,    16,    27,    -1,    62,    64,    -1,    62,    63,
      -1,    64,    -1,    63,    -1,    57,    56,    30,    -1,    16,
      27,    -1,    16,    65,    27,    -1,    40,    18,    70,    28,
      64,    -1,    40,    18,    70,    28,    64,    39,    64,    -1,
      49,    18,    70,    28,    64,    -1,    45,    70,    30,    -1,
      45,    30,    -1,    30,    -1,    66,    30,    -1,    68,    30,
      -1,    69,    30,    -1,    42,    18,    70,    28,    30,    -1,
      42,    18,     3,    28,    30,    -1,     1,    30,    -1,    65,
      64,    -1,    64,    -1,    50,    18,    70,    67,    28,    -1,
      50,    18,    70,    28,    -1,    50,    18,    28,    -1,    50,
      18,     1,    28,    -1,    11,    70,    67,    -1,    11,    70,
      -1,    50,     9,    70,    -1,    43,    18,    50,    19,    70,
      29,    28,    -1,    43,    18,     1,    28,    -1,    71,    -1,
      68,    -1,    71,    26,    71,    -1,    71,    21,    71,    -1,
      71,    10,    71,    -1,    71,    12,    71,    -1,    71,    22,
      71,    -1,    71,     8,    71,    -1,    71,    25,    71,    -1,
      71,    34,    71,    -1,    71,    32,    71,    -1,    71,    33,
      71,    -1,    71,    13,    71,    -1,    71,    14,    71,    -1,
      71,    15,    71,    -1,    71,    17,    71,    -1,    71,    20,
      71,    -1,    71,    23,    71,    -1,    21,    71,    -1,    24,
      71,    -1,    26,    71,    -1,    18,    70,    28,    -1,    66,
      -1,    69,    -1,    50,    37,    -1,    50,    -1,     6,    -1,
       5,    -1,     7,    -1,    18,     1,    28,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   116,   116,   121,   128,   136,   144,   145,   146,   147,
     149,   156,   163,   165,   170,   172,   173,   174,   176,   187,
     198,   209,   220,   228,   235,   243,   250,   257,   262,   264,
     272,   280,   283,   287,   295,   298,   312,   327,   350,   361,
     366,   367,   368,   369,   370,   371,   376,   381,   383,   388,
     392,   400,   407,   413,   415,   420,   422,   430,   437,   439,
     440,   442,   448,   454,   460,   466,   472,   478,   484,   490,
     496,   502,   508,   514,   520,   526,   532,   538,   543,   548,
     553,   554,   555,   556,   561,   562,   563,   564,   565
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "STRLIT", "RESERVED", "REALLIT",
  "INTLIT", "BOOLLIT", "AND", "ASSIGN", "STAR", "COMMA", "DIV", "EQ", "GE",
  "GT", "LBRACE", "LE", "LPAR", "LSQ", "LT", "MINUS", "MOD", "NE", "NOT",
  "OR", "PLUS", "RBRACE", "RPAR", "RSQ", "SEMICOLON", "ARROW", "LSHIFT",
  "RSHIFT", "XOR", "BOOL", "CLASS", "DOTLENGTH", "DOUBLE", "ELSE", "IF",
  "INT", "PRINT", "PARSEINT", "PUBLIC", "RETURN", "STATIC", "STRING",
  "VOID", "WHILE", "ID", "$accept", "Program", "ProgramRepetition",
  "MethodDecl", "FieldDecl", "CommaIDRepetition", "Type", "MethodHeader",
  "FormalParams", "FormalParamsRepetition", "MethodBody",
  "MethodBodyRepetition", "VarDecl", "Statement", "StatementRepetition",
  "MethodInvocation", "CommaExprRepetition", "Assignment", "ParseArgs",
  "Expr", "Expr1", 0
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
     305
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    51,    52,    52,    53,    53,    53,    53,    53,    53,
      54,    55,    55,    56,    56,    57,    57,    57,    58,    58,
      58,    58,    59,    59,    59,    60,    60,    61,    61,    62,
      62,    62,    62,    63,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    65,    65,
      66,    66,    66,    66,    67,    67,    68,    69,    69,    70,
      70,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     5,     2,     2,     2,     1,     1,     1,
       4,     5,     2,     3,     1,     1,     1,     1,     5,     4,
       5,     4,     3,     2,     4,     4,     3,     3,     2,     2,
       2,     1,     1,     3,     2,     3,     5,     7,     5,     3,
       2,     1,     2,     2,     2,     5,     5,     2,     2,     1,
       5,     4,     3,     4,     3,     2,     3,     7,     4,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     2,
       3,     1,     1,     2,     1,     1,     1,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     0,     2,     9,     0,
       0,     8,     7,    12,     0,     3,     6,     4,     5,    15,
      17,    16,     0,     0,     0,     0,    14,     0,     0,    10,
       0,     0,     0,    11,     0,     0,    28,    41,     0,     0,
       0,     0,     0,     0,     0,     0,    32,    31,     0,     0,
       0,    21,     0,     0,     0,    19,     0,    13,    47,    34,
      49,     0,     0,     0,     0,    86,    85,    87,     0,     0,
       0,     0,    40,    84,    81,    60,    82,     0,    59,     0,
       0,     0,    14,     0,    27,    30,    29,    42,    43,    44,
       0,    23,    20,    18,    35,    48,     0,     0,     0,     0,
       0,     0,     0,    84,    77,    78,    79,    83,    39,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    56,     0,    52,     0,
      33,     0,     0,    22,     0,     0,     0,    58,     0,    88,
      80,    66,    63,    64,    71,    72,    73,    74,    75,    62,
      65,    76,    67,    61,    69,    70,    68,     0,    53,     0,
      51,     0,    24,     0,    36,    46,    45,     0,    38,    55,
      50,    26,     0,     0,    54,    25,    37,    57
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,    10,    11,    12,    27,    44,    24,    54,   133,
      29,    45,    46,    47,    61,    74,   161,    75,    76,    77,
      78
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -60
static const yytype_int16 yypact[] =
{
     -31,   -44,    32,     0,   -60,    74,     7,   -60,   -60,    -4,
      94,   -60,   -60,   -60,    62,   -60,   -60,   -60,   -60,   -60,
     -60,   -60,    -6,    -3,    53,    63,    65,    15,   112,   -60,
      58,   156,    30,   -60,    46,   150,   -60,   -60,    67,    73,
      97,   252,   102,    61,    77,   133,   -60,   -60,    82,    93,
      96,   -60,   113,    83,   107,   -60,   108,   -60,   -60,   -60,
     -60,   171,   262,   229,    24,   -60,   -60,   -60,   201,   285,
     285,   285,   -60,     6,   -60,   -60,   -60,   111,   317,   262,
     262,    66,   -60,    16,   -60,   -60,   -60,   -60,   -60,   -60,
     114,   126,   -60,   -60,   -60,   -60,   120,   128,   130,   131,
     145,   137,   139,    12,   -60,   -60,   -60,   -60,   -60,   285,
     285,   285,   285,   285,   285,   285,   285,   285,   285,   285,
     285,   285,   285,   285,   285,   141,   -60,   142,   -60,     3,
     -60,   129,    76,   -60,   188,   151,   155,   -60,   262,   -60,
     -60,   369,   -60,   -60,   418,    56,    56,    56,    56,    26,
     -60,   418,   344,    26,   275,   275,   394,   188,   -60,   262,
     -60,   158,   -60,   138,   157,   -60,   -60,   176,   -60,   198,
     -60,   126,   188,   182,   -60,   -60,   -60,   -60
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -60,   -60,   -60,   202,   205,   173,   -10,   -60,   192,    55,
     -60,   -60,   179,   -32,   -60,   -28,    60,   -27,   -26,   -40,
     -59
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      48,    49,    50,    60,    23,     1,     3,    48,    49,    50,
     104,   105,   106,    86,   159,    80,     5,    48,    49,    50,
      53,    53,    96,    98,    81,    99,    32,    32,   102,    95,
      81,   160,     4,    48,    49,    50,   110,    13,   111,   125,
     126,   129,    14,   107,    25,    33,   130,    26,   118,   107,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   110,   127,   111,    28,
      80,    65,    66,    67,   100,     6,    58,   117,   118,    81,
      57,    30,   121,    31,    68,    62,    51,    69,   122,   123,
      70,    63,    71,    19,   128,     6,    20,    19,   167,    21,
      20,     7,   164,    21,     8,    52,    48,    49,    50,    40,
      22,    19,    87,    34,    20,    64,    73,    21,     9,   169,
      79,    15,   163,    88,    16,   168,    89,    82,    35,    48,
      49,    50,    90,    91,    34,    92,    93,   132,     9,    36,
     176,   108,    37,   131,    48,    49,    50,    19,   134,    35,
      20,    34,    38,    21,    39,    40,   135,    41,   136,   137,
      84,    42,    43,    37,   138,   139,    35,   140,    19,   157,
     158,    20,    34,    38,    21,    39,    40,    59,    41,   162,
      37,   165,    42,    43,    55,   166,   170,    35,   171,    34,
      38,    19,    39,    40,    20,    41,   172,    21,    94,    42,
      43,    37,   101,    52,    35,   173,    65,    66,    67,   159,
     177,    38,    17,    39,    40,    18,    41,    83,    37,    68,
      42,    43,    69,    56,    85,    70,   175,    71,    38,   174,
      39,    40,    97,    41,    65,    66,    67,    42,    43,     0,
       0,     0,     0,     0,    40,     0,     0,    68,     0,     0,
      69,    73,     0,    70,     0,    71,     0,    65,    66,    67,
       0,     0,     0,     0,     0,     0,     0,    65,    66,    67,
      68,     0,    40,    69,     0,     0,    70,     0,    71,    73,
      68,     0,    72,    69,     0,   110,    70,   111,    71,     0,
      65,    66,    67,     0,     0,    40,   117,   118,     0,     0,
       0,   121,    73,    68,     0,    40,    69,     0,     0,    70,
       0,    71,    73,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   109,     0,   110,    40,   111,
     112,   113,   114,     0,   115,   103,     0,   116,   117,   118,
     119,     0,   120,   121,     0,     0,     0,     0,     0,   122,
     123,   124,   109,     0,   110,     0,   111,   112,   113,   114,
       0,   115,     0,     0,   116,   117,   118,   119,     0,     0,
     121,     0,     0,     0,     0,     0,   122,   123,   124,   110,
       0,   111,   112,   113,   114,     0,   115,     0,     0,   116,
     117,   118,   119,     0,     0,   121,     0,     0,     0,     0,
       0,   122,   123,   124,   110,     0,   111,   112,   113,   114,
       0,   115,     0,     0,   116,   117,   118,   119,     0,     0,
     121,     0,     0,     0,     0,     0,   122,   123,   110,     0,
     111,     0,   113,   114,     0,   115,     0,     0,   116,   117,
     118,     0,     0,     0,   121,     0,     0,     0,     0,     0,
     122,   123
};

static const yytype_int16 yycheck[] =
{
      28,    28,    28,    35,    14,    36,    50,    35,    35,    35,
      69,    70,    71,    45,    11,     9,    16,    45,    45,    45,
      30,    31,    62,    63,    18,     1,    11,    11,    68,    61,
      18,    28,     0,    61,    61,    61,    10,    30,    12,    79,
      80,    81,    46,    37,    50,    30,    30,    50,    22,    37,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,    10,     1,    12,    16,
       9,     5,     6,     7,    50,     1,    30,    21,    22,    18,
      50,    18,    26,    18,    18,    18,    28,    21,    32,    33,
      24,    18,    26,    35,    28,     1,    38,    35,   138,    41,
      38,    27,   134,    41,    30,    47,   134,   134,   134,    43,
      48,    35,    30,     1,    38,    18,    50,    41,    44,   159,
      18,    27,   132,    30,    30,   157,    30,    50,    16,   157,
     157,   157,    19,    50,     1,    28,    28,    11,    44,    27,
     172,    30,    30,    29,   172,   172,   172,    35,    28,    16,
      38,     1,    40,    41,    42,    43,    28,    45,    28,    28,
      27,    49,    50,    30,    19,    28,    16,    28,    35,    28,
      28,    38,     1,    40,    41,    42,    43,    27,    45,    50,
      30,    30,    49,    50,    28,    30,    28,    16,    50,     1,
      40,    35,    42,    43,    38,    45,    39,    41,    27,    49,
      50,    30,     1,    47,    16,    29,     5,     6,     7,    11,
      28,    40,    10,    42,    43,    10,    45,    44,    30,    18,
      49,    50,    21,    31,    45,    24,   171,    26,    40,   169,
      42,    43,     3,    45,     5,     6,     7,    49,    50,    -1,
      -1,    -1,    -1,    -1,    43,    -1,    -1,    18,    -1,    -1,
      21,    50,    -1,    24,    -1,    26,    -1,     5,     6,     7,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,     6,     7,
      18,    -1,    43,    21,    -1,    -1,    24,    -1,    26,    50,
      18,    -1,    30,    21,    -1,    10,    24,    12,    26,    -1,
       5,     6,     7,    -1,    -1,    43,    21,    22,    -1,    -1,
      -1,    26,    50,    18,    -1,    43,    21,    -1,    -1,    24,
      -1,    26,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     8,    -1,    10,    43,    12,
      13,    14,    15,    -1,    17,    50,    -1,    20,    21,    22,
      23,    -1,    25,    26,    -1,    -1,    -1,    -1,    -1,    32,
      33,    34,     8,    -1,    10,    -1,    12,    13,    14,    15,
      -1,    17,    -1,    -1,    20,    21,    22,    23,    -1,    -1,
      26,    -1,    -1,    -1,    -1,    -1,    32,    33,    34,    10,
      -1,    12,    13,    14,    15,    -1,    17,    -1,    -1,    20,
      21,    22,    23,    -1,    -1,    26,    -1,    -1,    -1,    -1,
      -1,    32,    33,    34,    10,    -1,    12,    13,    14,    15,
      -1,    17,    -1,    -1,    20,    21,    22,    23,    -1,    -1,
      26,    -1,    -1,    -1,    -1,    -1,    32,    33,    10,    -1,
      12,    -1,    14,    15,    -1,    17,    -1,    -1,    20,    21,
      22,    -1,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,
      32,    33
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    36,    52,    50,     0,    16,     1,    27,    30,    44,
      53,    54,    55,    30,    46,    27,    30,    54,    55,    35,
      38,    41,    48,    57,    58,    50,    50,    56,    16,    61,
      18,    18,    11,    30,     1,    16,    27,    30,    40,    42,
      43,    45,    49,    50,    57,    62,    63,    64,    66,    68,
      69,    28,    47,    57,    59,    28,    59,    50,    30,    27,
      64,    65,    18,    18,    18,     5,     6,     7,    18,    21,
      24,    26,    30,    50,    66,    68,    69,    70,    71,    18,
       9,    18,    50,    56,    27,    63,    64,    30,    30,    30,
      19,    50,    28,    28,    27,    64,    70,     3,    70,     1,
      50,     1,    70,    50,    71,    71,    71,    37,    30,     8,
      10,    12,    13,    14,    15,    17,    20,    21,    22,    23,
      25,    26,    32,    33,    34,    70,    70,     1,    28,    70,
      30,    29,    11,    60,    28,    28,    28,    28,    19,    28,
      28,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    28,    28,    11,
      28,    67,    50,    57,    64,    30,    30,    70,    64,    70,
      28,    50,    39,    29,    67,    60,    64,    28
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
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
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
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
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



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

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
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
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
#line 116 "jucompiler.y"
    {	
																					tree = cria_no("Program", NULL);
																					no_id = cria_no("Id",(yyvsp[(2) - (4)].str));
																					add_filho(tree, no_id);
																				}
    break;

  case 3:
#line 121 "jucompiler.y"
    {	
																					tree = cria_no("Program", NULL);
																					no_id = cria_no("Id",(yyvsp[(2) - (5)].str));
																					add_filho(tree, no_id);
																					add_irmao(no_id, (yyvsp[(4) - (5)].no));
																				}
    break;

  case 4:
#line 128 "jucompiler.y"
    {
																					aux = (yyvsp[(1) - (2)].no);
																					if(aux!=NULL){
																						add_irmao(aux,(yyvsp[(2) - (2)].no));
																						(yyval.no) = aux;
																					}else
																						(yyval.no) = (yyvsp[(2) - (2)].no);
																				}
    break;

  case 5:
#line 136 "jucompiler.y"
    {
																					aux = (yyvsp[(1) - (2)].no);
																					if(aux!=NULL){
																						add_irmao(aux,(yyvsp[(2) - (2)].no));
																						(yyval.no) = aux;
																					}else
																						(yyval.no) = (yyvsp[(2) - (2)].no);
																				}
    break;

  case 6:
#line 144 "jucompiler.y"
    {(yyval.no) = (yyvsp[(1) - (2)].no);}
    break;

  case 7:
#line 145 "jucompiler.y"
    {(yyval.no) = (yyvsp[(1) - (1)].no);}
    break;

  case 8:
#line 146 "jucompiler.y"
    {(yyval.no) = (yyvsp[(1) - (1)].no);}
    break;

  case 9:
#line 147 "jucompiler.y"
    {(yyval.no) = NULL;}
    break;

  case 10:
#line 149 "jucompiler.y"
    {	
																					aux = cria_no("MethodDecl", NULL);
																					add_filho(aux, (yyvsp[(3) - (4)].no));
																					add_irmao((yyvsp[(3) - (4)].no), (yyvsp[(4) - (4)].no));
																					(yyval.no)=aux;
																				}
    break;

  case 11:
#line 156 "jucompiler.y"
    {	
																					aux = cria_no("FieldDecl", NULL);
																					add_filho(aux, (yyvsp[(3) - (5)].no));
																					add_irmao((yyvsp[(3) - (5)].no), (yyvsp[(4) - (5)].no));
																					tratamentoIDRep(aux, (yyvsp[(3) - (5)].no));
																					(yyval.no) = aux;
																				}
    break;

  case 12:
#line 163 "jucompiler.y"
    {(yyval.no) = NULL;}
    break;

  case 13:
#line 165 "jucompiler.y"
    {
																					aux = (yyvsp[(1) - (3)].no);
																					add_irmao(aux, cria_no("Id",(yyvsp[(3) - (3)].str)));
																					(yyval.no)=aux;
																				}
    break;

  case 14:
#line 170 "jucompiler.y"
    {(yyval.no) = cria_no("Id",(yyvsp[(1) - (1)].str));}
    break;

  case 15:
#line 172 "jucompiler.y"
    {(yyval.no) = cria_no("Bool", NULL);}
    break;

  case 16:
#line 173 "jucompiler.y"
    {(yyval.no) = cria_no("Int", NULL);}
    break;

  case 17:
#line 174 "jucompiler.y"
    {(yyval.no) = cria_no("Double", NULL);}
    break;

  case 18:
#line 176 "jucompiler.y"
    {
																					header = cria_no("MethodHeader", NULL);
																					par = cria_no("MethodParams", NULL);
																					type = (yyvsp[(1) - (5)].no);
																					no_id = cria_no("Id", (yyvsp[(2) - (5)].str));
																					add_filho(header, type);
																					add_irmao(type, no_id);
																					add_irmao(no_id, par);
																					add_filho(par, (yyvsp[(4) - (5)].no));
																					(yyval.no) = header;
																				}
    break;

  case 19:
#line 187 "jucompiler.y"
    {
																					header = cria_no("MethodHeader", NULL);
																					par = cria_no("MethodParams", NULL);
																					type = (yyvsp[(1) - (4)].no);
																					no_id = cria_no("Id", (yyvsp[(2) - (4)].str));
																					add_filho(header, type);
																					add_irmao(type, no_id);
																					add_irmao(no_id, par);
																					(yyval.no) = header;
																				}
    break;

  case 20:
#line 198 "jucompiler.y"
    {
																					header = cria_no("MethodHeader", NULL);
																					no_void = cria_no("Void", NULL);
																					par = cria_no("MethodParams", NULL);
																					no_id = cria_no("Id",(yyvsp[(2) - (5)].str));
																					add_filho(header, no_void);
																					add_irmao(no_void, no_id);
																					add_irmao(no_id, par);
																					add_filho(par, (yyvsp[(4) - (5)].no));
																					(yyval.no) = header;
																				}
    break;

  case 21:
#line 209 "jucompiler.y"
    {
																					header = cria_no("MethodHeader", NULL);
																					par = cria_no("MethodParams", NULL);
																					no_void =  cria_no("Void", NULL);
																					no_id = cria_no("Id",(yyvsp[(2) - (4)].str));
																					add_filho(header, no_void);
																					add_irmao(no_void, no_id);
																					add_irmao(no_id, par);
																					(yyval.no) = header;
																				}
    break;

  case 22:
#line 220 "jucompiler.y"
    {
																					par = cria_no("ParamDecl", NULL);
																					add_filho(par, (yyvsp[(1) - (3)].no));
																					aux = cria_no("Id", (yyvsp[(2) - (3)].str));
																					add_irmao((yyvsp[(1) - (3)].no), aux);
																					add_irmao(par, (yyvsp[(3) - (3)].no));
																					(yyval.no) = par;
																				}
    break;

  case 23:
#line 228 "jucompiler.y"
    {
																					par = cria_no("ParamDecl", NULL);
																					add_filho(par, (yyvsp[(1) - (2)].no));
																					aux = cria_no("Id", (yyvsp[(2) - (2)].str));
																					add_irmao((yyvsp[(1) - (2)].no), aux);
																					(yyval.no) = par;
																				}
    break;

  case 24:
#line 235 "jucompiler.y"
    {
																					par = cria_no("ParamDecl", NULL);
																					aux = cria_no("StringArray", NULL);
																					add_filho(par, aux);
																					add_irmao(aux, cria_no("Id",(yyvsp[(4) - (4)].str)));
																					(yyval.no) = par;
																				}
    break;

  case 25:
#line 243 "jucompiler.y"
    {	
																					par = cria_no("ParamDecl", NULL);
																					add_filho(par, (yyvsp[(2) - (4)].no));
																					add_irmao((yyvsp[(2) - (4)].no), cria_no("Id", (yyvsp[(3) - (4)].str)));
																					add_irmao(par, (yyvsp[(4) - (4)].no));
																					(yyval.no) = par;
																				}
    break;

  case 26:
#line 250 "jucompiler.y"
    {	
																					par = cria_no("ParamDecl", NULL);
																					add_filho(par, (yyvsp[(2) - (3)].no));
																					add_irmao((yyvsp[(2) - (3)].no), cria_no("Id", (yyvsp[(3) - (3)].str)));
																					(yyval.no) = par;
																				}
    break;

  case 27:
#line 257 "jucompiler.y"
    {	
																					body = cria_no("MethodBody", NULL);
																					add_filho(body, (yyvsp[(2) - (3)].no));
																					(yyval.no) = body;
																				}
    break;

  case 28:
#line 262 "jucompiler.y"
    {(yyval.no) = cria_no("MethodBody", NULL);}
    break;

  case 29:
#line 264 "jucompiler.y"
    {
																					aux = (yyvsp[(1) - (2)].no);
																					if(aux!=NULL){
																						add_irmao(aux,(yyvsp[(2) - (2)].no));
																						(yyval.no) = aux;
																					}else
																						(yyval.no) = (yyvsp[(2) - (2)].no);
																				}
    break;

  case 30:
#line 272 "jucompiler.y"
    {
																					aux = (yyvsp[(1) - (2)].no);
																					if(aux!=NULL){
																						add_irmao(aux,(yyvsp[(2) - (2)].no));
																						(yyval.no) = aux;
																					}else
																						(yyval.no) = (yyvsp[(2) - (2)].no);
																				}
    break;

  case 31:
#line 280 "jucompiler.y"
    {
																					(yyval.no) = (yyvsp[(1) - (1)].no);
																				}
    break;

  case 32:
#line 283 "jucompiler.y"
    {
																					(yyval.no) = (yyvsp[(1) - (1)].no);
																				}
    break;

  case 33:
#line 287 "jucompiler.y"
    {
																					dcl = cria_no("VarDecl", NULL);
																					add_filho(dcl, (yyvsp[(1) - (3)].no));
																					add_irmao((yyvsp[(1) - (3)].no), (yyvsp[(2) - (3)].no));
																					tratamentoIDRep(dcl, (yyvsp[(1) - (3)].no));
																					(yyval.no)=dcl;
																				}
    break;

  case 34:
#line 295 "jucompiler.y"
    {
																					(yyval.no) = NULL;
																				}
    break;

  case 35:
#line 298 "jucompiler.y"
    {
																					aux = (yyvsp[(2) - (3)].no);
																					if(aux!=NULL){
																						if(check_irmao(aux)){
																							no_block = cria_no("Block", NULL);
																							add_filho(no_block, aux);
																							(yyval.no) = no_block;
																						} else{
																							(yyval.no) = aux;
																						}
																					} else {
																						(yyval.no)=NULL;
																					}
																				}
    break;

  case 36:
#line 312 "jucompiler.y"
    {
																					no_if = cria_no("If", NULL);
																					aux = (yyvsp[(3) - (5)].no);
                                                            						add_filho(no_if, aux);
																					no_block = cria_no("Block", NULL);
																					elseblock = cria_no("Block", NULL); 
																					if((yyvsp[(5) - (5)].no)==NULL){
																						add_irmao(aux, no_block);
																						add_irmao(no_block, elseblock);
																					}else{
                                                            							add_irmao(aux, (yyvsp[(5) - (5)].no));
																						add_irmao((yyvsp[(5) - (5)].no), no_block);
																					}
																					(yyval.no) = no_if;
																				}
    break;

  case 37:
#line 327 "jucompiler.y"
    {
																					no_if = cria_no("If", NULL);
																					aux = (yyvsp[(3) - (7)].no);
                                                            						add_filho(no_if, aux);
																					no_block = cria_no("Block", NULL);
																					elseblock = cria_no("Block", NULL); 
																					if((yyvsp[(5) - (7)].no)==NULL && (yyvsp[(7) - (7)].no)==NULL){
																						add_irmao(aux,no_block);
																						add_irmao(no_block,elseblock);
																					}else if((yyvsp[(5) - (7)].no)!=NULL && (yyvsp[(7) - (7)].no)==NULL){
																						add_irmao(aux,(yyvsp[(5) - (7)].no));
																						add_irmao((yyvsp[(5) - (7)].no),no_block);
																					}else if((yyvsp[(5) - (7)].no)==NULL && (yyvsp[(7) - (7)].no)!=NULL){
																						add_irmao(aux,elseblock);
																						add_irmao(elseblock,(yyvsp[(7) - (7)].no));
																					}else if((yyvsp[(5) - (7)].no)!=NULL && (yyvsp[(7) - (7)].no)!=NULL){
																						add_irmao(aux,(yyvsp[(5) - (7)].no));
																						add_irmao((yyvsp[(5) - (7)].no),(yyvsp[(7) - (7)].no));
																					}


																					(yyval.no)=no_if;
																				}
    break;

  case 38:
#line 350 "jucompiler.y"
    {
																					aux = cria_no("While", NULL);
                                                            						add_filho(aux, (yyvsp[(3) - (5)].no));
																					no_block = cria_no("Block", NULL);
																					if((yyvsp[(5) - (5)].no)==NULL){
																						add_irmao((yyvsp[(3) - (5)].no), no_block);
																					}else{
																						add_irmao((yyvsp[(3) - (5)].no), (yyvsp[(5) - (5)].no));
																					}
																					(yyval.no) = aux;
																				}
    break;

  case 39:
#line 361 "jucompiler.y"
    {
																					aux = cria_no("Return", NULL);
                                                            						add_filho(aux, (yyvsp[(2) - (3)].no));
																					(yyval.no) = aux;
																				}
    break;

  case 40:
#line 366 "jucompiler.y"
    {(yyval.no) = cria_no("Return", NULL);}
    break;

  case 41:
#line 367 "jucompiler.y"
    {(yyval.no) = NULL;}
    break;

  case 42:
#line 368 "jucompiler.y"
    {(yyval.no) = (yyvsp[(1) - (2)].no);}
    break;

  case 43:
#line 369 "jucompiler.y"
    {(yyval.no) = (yyvsp[(1) - (2)].no);}
    break;

  case 44:
#line 370 "jucompiler.y"
    {(yyval.no) = (yyvsp[(1) - (2)].no);}
    break;

  case 45:
#line 371 "jucompiler.y"
    {
																					aux = cria_no("Print", NULL);
                                                            						add_filho(aux, (yyvsp[(3) - (5)].no));
																					(yyval.no) = aux;
																				}
    break;

  case 46:
#line 376 "jucompiler.y"
    {
																					aux = cria_no("Print", NULL);
                                                            						add_filho(aux, cria_no("StrLit", (yyvsp[(3) - (5)].str)));
																					(yyval.no) = aux;
																				}
    break;

  case 47:
#line 381 "jucompiler.y"
    {(yyval.no) = NULL;}
    break;

  case 48:
#line 383 "jucompiler.y"
    {
																					aux = (yyvsp[(1) - (2)].no);
																					add_irmao(aux,(yyvsp[(2) - (2)].no));
																					(yyval.no) = aux;
																				}
    break;

  case 49:
#line 388 "jucompiler.y"
    {
																					(yyval.no) = (yyvsp[(1) - (1)].no);
																				}
    break;

  case 50:
#line 392 "jucompiler.y"
    {
																					no_call = cria_no("Call", NULL);
																					aux = cria_no("Id", (yyvsp[(1) - (5)].str));
																					add_filho(no_call, aux);
																					add_irmao(aux, (yyvsp[(3) - (5)].no));
																					add_irmao((yyvsp[(3) - (5)].no), (yyvsp[(4) - (5)].no));
																					(yyval.no) = no_call;
																				}
    break;

  case 51:
#line 400 "jucompiler.y"
    {
																					no_call = cria_no("Call", NULL);
																					aux = cria_no("Id", (yyvsp[(1) - (4)].str));
																					add_filho(no_call, aux);
																					add_irmao(aux, (yyvsp[(3) - (4)].no));
																					(yyval.no) = no_call;
																				}
    break;

  case 52:
#line 407 "jucompiler.y"
    {
                                                                        			no_call = cria_no("Call", NULL);
																					aux = cria_no("Id", (yyvsp[(1) - (3)].str));
                                                                        			add_filho(no_call, aux);
																					(yyval.no) = no_call;
                                                                    			}
    break;

  case 53:
#line 413 "jucompiler.y"
    {(yyval.no) = NULL;}
    break;

  case 54:
#line 415 "jucompiler.y"
    {
																				aux = (yyvsp[(2) - (3)].no);
																				add_irmao(aux, (yyvsp[(3) - (3)].no));
																				(yyval.no) = aux;
																			}
    break;

  case 55:
#line 420 "jucompiler.y"
    {(yyval.no) = (yyvsp[(2) - (2)].no);}
    break;

  case 56:
#line 422 "jucompiler.y"
    {
																					assign = cria_no("Assign", NULL);
																					aux = cria_no("Id", (yyvsp[(1) - (3)].str));
																					add_filho(assign, aux);
																					add_irmao(aux, (yyvsp[(3) - (3)].no));
																					(yyval.no) = assign;
																				}
    break;

  case 57:
#line 430 "jucompiler.y"
    {
																					no_parse = cria_no("ParseArgs", NULL);
																					aux = cria_no("Id", (yyvsp[(3) - (7)].str));
																					add_filho(no_parse, aux);
																					add_irmao(aux, (yyvsp[(5) - (7)].no));
																					(yyval.no) = no_parse;
																				}
    break;

  case 58:
#line 437 "jucompiler.y"
    {(yyval.no) = NULL;}
    break;

  case 59:
#line 439 "jucompiler.y"
    {(yyval.no) = (yyvsp[(1) - (1)].no);}
    break;

  case 60:
#line 440 "jucompiler.y"
    {(yyval.no) = (yyvsp[(1) - (1)].no);}
    break;

  case 61:
#line 442 "jucompiler.y"
    {
																					aux = cria_no("Add", NULL);
																					add_filho(aux, (yyvsp[(1) - (3)].no));
																					add_irmao((yyvsp[(1) - (3)].no), (yyvsp[(3) - (3)].no));
																					(yyval.no) = aux;
																				}
    break;

  case 62:
#line 448 "jucompiler.y"
    {
																					aux = cria_no("Sub", NULL);
																					add_filho(aux, (yyvsp[(1) - (3)].no));
																					add_irmao((yyvsp[(1) - (3)].no), (yyvsp[(3) - (3)].no));
																					(yyval.no) = aux;
																				}
    break;

  case 63:
#line 454 "jucompiler.y"
    {
																					aux = cria_no("Mul", NULL);
																					add_filho(aux, (yyvsp[(1) - (3)].no));
																					add_irmao((yyvsp[(1) - (3)].no), (yyvsp[(3) - (3)].no));
																					(yyval.no) = aux;
																				}
    break;

  case 64:
#line 460 "jucompiler.y"
    {
																					aux = cria_no("Div", NULL);
																					add_filho(aux, (yyvsp[(1) - (3)].no));
																					add_irmao((yyvsp[(1) - (3)].no), (yyvsp[(3) - (3)].no));
																					(yyval.no) = aux;
																				}
    break;

  case 65:
#line 466 "jucompiler.y"
    {
																					aux = cria_no("Mod", NULL);
																					add_filho(aux, (yyvsp[(1) - (3)].no));
																					add_irmao((yyvsp[(1) - (3)].no), (yyvsp[(3) - (3)].no));
																					(yyval.no) = aux;
																				}
    break;

  case 66:
#line 472 "jucompiler.y"
    {
																					aux = cria_no("And", NULL);
																					add_filho(aux, (yyvsp[(1) - (3)].no));
																					add_irmao((yyvsp[(1) - (3)].no), (yyvsp[(3) - (3)].no));
																					(yyval.no) = aux;
																				}
    break;

  case 67:
#line 478 "jucompiler.y"
    {
																					aux = cria_no("Or", NULL);
																					add_filho(aux, (yyvsp[(1) - (3)].no));
																					add_irmao((yyvsp[(1) - (3)].no), (yyvsp[(3) - (3)].no));
																					(yyval.no) = aux;
																				}
    break;

  case 68:
#line 484 "jucompiler.y"
    {
																					aux = cria_no("Xor", NULL);
																					add_filho(aux, (yyvsp[(1) - (3)].no));
																					add_irmao((yyvsp[(1) - (3)].no), (yyvsp[(3) - (3)].no));
																					(yyval.no) = aux;
																				}
    break;

  case 69:
#line 490 "jucompiler.y"
    {
																					aux = cria_no("Lshift", NULL);
																					add_filho(aux, (yyvsp[(1) - (3)].no));
																					add_irmao((yyvsp[(1) - (3)].no), (yyvsp[(3) - (3)].no));
																					(yyval.no) = aux;
																				}
    break;

  case 70:
#line 496 "jucompiler.y"
    {
																					aux = cria_no("Rshift", NULL);
																					add_filho(aux, (yyvsp[(1) - (3)].no));
																					add_irmao((yyvsp[(1) - (3)].no), (yyvsp[(3) - (3)].no));
																					(yyval.no) = aux;
																				}
    break;

  case 71:
#line 502 "jucompiler.y"
    {
																					aux = cria_no("Eq", NULL);
																					add_filho(aux, (yyvsp[(1) - (3)].no));
																					add_irmao((yyvsp[(1) - (3)].no), (yyvsp[(3) - (3)].no));
																					(yyval.no) = aux;
																				}
    break;

  case 72:
#line 508 "jucompiler.y"
    {
																					aux = cria_no("Ge", NULL);
																					add_filho(aux, (yyvsp[(1) - (3)].no));
																					add_irmao((yyvsp[(1) - (3)].no), (yyvsp[(3) - (3)].no));
																					(yyval.no) = aux;
																				}
    break;

  case 73:
#line 514 "jucompiler.y"
    {
																					aux = cria_no("Gt", NULL);
																					add_filho(aux, (yyvsp[(1) - (3)].no));
																					add_irmao((yyvsp[(1) - (3)].no), (yyvsp[(3) - (3)].no));
																					(yyval.no) = aux;
																				}
    break;

  case 74:
#line 520 "jucompiler.y"
    {
																					aux = cria_no("Le", NULL);
																					add_filho(aux, (yyvsp[(1) - (3)].no));
																					add_irmao((yyvsp[(1) - (3)].no), (yyvsp[(3) - (3)].no));
																					(yyval.no) = aux;
																				}
    break;

  case 75:
#line 526 "jucompiler.y"
    {
																					aux = cria_no("Lt", NULL);
																					add_filho(aux, (yyvsp[(1) - (3)].no));
																					add_irmao((yyvsp[(1) - (3)].no), (yyvsp[(3) - (3)].no));
																					(yyval.no) = aux;
																				}
    break;

  case 76:
#line 532 "jucompiler.y"
    {
																					aux = cria_no("Ne", NULL);
																					add_filho(aux, (yyvsp[(1) - (3)].no));
																					add_irmao((yyvsp[(1) - (3)].no), (yyvsp[(3) - (3)].no));
																					(yyval.no) = aux;
																				}
    break;

  case 77:
#line 538 "jucompiler.y"
    {
																					aux = cria_no("Minus", NULL);
                            														add_filho(aux, (yyvsp[(2) - (2)].no));
																					(yyval.no) = aux;
																				}
    break;

  case 78:
#line 543 "jucompiler.y"
    {
																					aux = cria_no("Not", NULL);
                            														add_filho(aux, (yyvsp[(2) - (2)].no));
																					(yyval.no) = aux;
																				}
    break;

  case 79:
#line 548 "jucompiler.y"
    {
																					aux = cria_no("Plus", NULL);
                            														add_filho(aux, (yyvsp[(2) - (2)].no));
																					(yyval.no) = aux;
																				}
    break;

  case 80:
#line 553 "jucompiler.y"
    {(yyval.no)=(yyvsp[(2) - (3)].no);}
    break;

  case 81:
#line 554 "jucompiler.y"
    {(yyval.no) = (yyvsp[(1) - (1)].no);}
    break;

  case 82:
#line 555 "jucompiler.y"
    {(yyval.no) = (yyvsp[(1) - (1)].no);}
    break;

  case 83:
#line 556 "jucompiler.y"
    {
																					aux = cria_no("Length", NULL);
																					add_filho(aux,cria_no("Id",(yyvsp[(1) - (2)].str)));
																					(yyval.no)=aux;
																				}
    break;

  case 84:
#line 561 "jucompiler.y"
    {(yyval.no) = cria_no("Id",(yyvsp[(1) - (1)].str));}
    break;

  case 85:
#line 562 "jucompiler.y"
    {(yyval.no) = cria_no("DecLit",(yyvsp[(1) - (1)].str));}
    break;

  case 86:
#line 563 "jucompiler.y"
    {(yyval.no) = cria_no("RealLit",(yyvsp[(1) - (1)].str));}
    break;

  case 87:
#line 564 "jucompiler.y"
    {(yyval.no) = cria_no("BoolLit",(yyvsp[(1) - (1)].str));}
    break;

  case 88:
#line 565 "jucompiler.y"
    {(yyval.no) = NULL;}
    break;


/* Line 1267 of yacc.c.  */
#line 2442 "y.tab.c"
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
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  if (yyn == YYFINAL)
    YYACCEPT;

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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
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


#line 569 "jucompiler.y"


void yyerror ( char *s) {
	syntax_error = 1;
	if(e2){
		if(yychar==STRLIT){
			printf("Line %d, col %d: %s: \"%s\n",ini_line,ini_col,s,yylval.str);

		}
		else{
			printf("Line %d, col %d: %s: %s\n",line_count,col_syntax,s,yytext);
		}
	}
}

