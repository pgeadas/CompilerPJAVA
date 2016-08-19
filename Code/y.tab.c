
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
#line 1 "mycalc.y"

#include "structures.h"
#include "functions.h"
#include "symbol_table.h"
#include "semantics.h"
#include "shows.h"
#include "translate.h"
#include <stdio.h>

int ERROS=0;
int showShows=1;	 	//1 - Ligar os Shows | 0 - Desligar os Shows
int checkSemantic=1; 		//1 - Ligar a verificacao da semantica | 0 - Desligar
int showTable=1; 		//1 - Ligar o show Table | 0 - Desligar

table_element *symtab=NULL;


is_program * PJAVAPROGRAM;



/* Line 189 of yacc.c  */
#line 95 "y.tab.c"

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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     MINUSEQUAL = 258,
     PLUSEQUAL = 259,
     EQUAL = 260,
     OR = 261,
     AND = 262,
     EQUALEQUAL = 263,
     NOTEQUAL = 264,
     LESSEQUAL = 265,
     GREATEREQUAL = 266,
     LESS = 267,
     GREATER = 268,
     MINUSMINUS = 269,
     PLUSPLUS = 270,
     MINUS = 271,
     PLUS = 272,
     DIV = 273,
     MULT = 274,
     MOD = 275,
     POT = 276,
     RETURNSYMB = 277,
     FUNCSYMB = 278,
     ELSEIF = 279,
     ELSE = 280,
     WHILE = 281,
     IF = 282,
     NOT = 283,
     CLASSSYMB = 284,
     INTSYMB = 285,
     FLOATSYMB = 286,
     STRINGSYMB = 287,
     DOUBLESYMB = 288,
     VOIDSYMB = 289,
     BOOLSYMB = 290,
     CONCATSYMB = 291,
     INT = 292,
     FLOAT = 293,
     STRING = 294,
     BOOL = 295,
     ID = 296,
     FOR = 297,
     BREAK = 298,
     CONTINUE = 299,
     PRINTLN = 300,
     PRINT = 301,
     READ = 302,
     READLINE = 303
   };
#endif
/* Tokens.  */
#define MINUSEQUAL 258
#define PLUSEQUAL 259
#define EQUAL 260
#define OR 261
#define AND 262
#define EQUALEQUAL 263
#define NOTEQUAL 264
#define LESSEQUAL 265
#define GREATEREQUAL 266
#define LESS 267
#define GREATER 268
#define MINUSMINUS 269
#define PLUSPLUS 270
#define MINUS 271
#define PLUS 272
#define DIV 273
#define MULT 274
#define MOD 275
#define POT 276
#define RETURNSYMB 277
#define FUNCSYMB 278
#define ELSEIF 279
#define ELSE 280
#define WHILE 281
#define IF 282
#define NOT 283
#define CLASSSYMB 284
#define INTSYMB 285
#define FLOATSYMB 286
#define STRINGSYMB 287
#define DOUBLESYMB 288
#define VOIDSYMB 289
#define BOOLSYMB 290
#define CONCATSYMB 291
#define INT 292
#define FLOAT 293
#define STRING 294
#define BOOL 295
#define ID 296
#define FOR 297
#define BREAK 298
#define CONTINUE 299
#define PRINTLN 300
#define PRINT 301
#define READ 302
#define READLINE 303




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 22 "mycalc.y"

	int intValue;
	float floatValue;
	double doubleValue;
	char* string;
	bool boolValue;

	is_statement_list* isl;
	is_instruction* ii;
	is_expression* ie;
	is_relac_exp* ire;
	is_logic_exp_or_and* ileoa;
	is_logic_exp_not* ilen;
	is_aritmetic_exp* iae;
	is_atribution_list* ial;
	is_atribution* ia;
	is_id* id;
	is_statement* is;
	is_type* ity;
	is_program* iprogram;
	is_compound_statement* ics;
	is_if_statement* iifs;
	is_while_statement* iws;
	is_else_statement* ielses;
	is_elseif_statement* ielseifs;
	is_elseif_statement_list* ieisl;
	is_cont_statement* iconts;
	is_println_statement* iprints;
	is_declaration* idecl;
	is_atr* iatr;
	is_dec_list* ideclist;
	is_func_def* ifd;
	is_arg_list* iargl;
	is_cont_func* icf;
	is_symbols* isymb;
	is_func_call* ifcall;
	is_call_list* icall;
	is_for_statement* ifors;
	is_for_args* ifa;
	is_exp_minus_plus* impe;	
	is_return_statement* ireturn;
	is_class* iclass;
	is_func_list* iflist;
	is_plusminus* ipm;
	is_read_statement* irs;
	is_concat* iconcat;
	is_concat_args* icargs;
	is_println_args* ipargs;
	is_break_cont* ibc;



/* Line 214 of yacc.c  */
#line 280 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 292 "y.tab.c"

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   401

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  116
/* YYNRULES -- Number of states.  */
#define YYNSTATES  214

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   303

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      29,    30,     2,     2,    54,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    53,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    51,     2,    52,     2,     2,     2,     2,
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
      25,    26,    27,    28,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     9,    13,    15,    18,    20,    23,    25,
      28,    30,    33,    36,    39,    42,    45,    48,    51,    53,
      55,    60,    64,    68,    73,    78,    80,    82,    84,    87,
      90,    92,    94,    96,   101,   106,   110,   112,   114,   117,
     127,   129,   131,   133,   134,   142,   148,   151,   152,   155,
     156,   162,   164,   168,   171,   173,   181,   186,   190,   192,
     193,   197,   200,   205,   208,   209,   211,   213,   215,   217,
     219,   221,   224,   227,   230,   233,   236,   238,   242,   244,
     246,   249,   253,   257,   261,   264,   267,   270,   272,   276,
     278,   280,   282,   284,   286,   289,   292,   295,   299,   303,
     307,   311,   315,   319,   323,   327,   331,   335,   339,   343,
     347,   351,   353,   355,   357,   359,   361
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      56,     0,    -1,    31,    43,    51,    57,    52,    -1,    85,
      53,    57,    -1,    58,    -1,    58,    79,    -1,    79,    -1,
      59,    60,    -1,    60,    -1,    65,    53,    -1,    67,    -1,
      68,    53,    -1,    85,    53,    -1,    80,    53,    -1,    70,
      53,    -1,    64,    53,    -1,    62,    53,    -1,    61,    53,
      -1,    45,    -1,    46,    -1,    38,    29,    63,    30,    -1,
      96,    54,    63,    -1,    96,    54,    96,    -1,    49,    29,
      43,    30,    -1,    50,    29,    43,    30,    -1,    90,    -1,
      88,    -1,    66,    -1,    43,    15,    -1,    43,    14,    -1,
      73,    -1,    74,    -1,    71,    -1,    47,    29,    69,    30,
      -1,    48,    29,    69,    30,    -1,    96,    17,    69,    -1,
      96,    -1,    22,    -1,    22,    65,    -1,    44,    29,    72,
      53,    94,    53,    72,    30,    78,    -1,    86,    -1,    85,
      -1,    66,    -1,    -1,    27,    29,    65,    30,    78,    76,
      75,    -1,    26,    29,    65,    30,    78,    -1,    25,    78,
      -1,    -1,    76,    77,    -1,    -1,    24,    29,    65,    30,
      78,    -1,    60,    -1,    51,    59,    52,    -1,    51,    52,
      -1,    53,    -1,    23,    84,    43,    29,    83,    30,    82,
      -1,    43,    29,    81,    30,    -1,    81,    54,    96,    -1,
      96,    -1,    -1,    51,    59,    52,    -1,    51,    52,    -1,
      83,    54,    84,    43,    -1,    84,    43,    -1,    -1,    32,
      -1,    35,    -1,    33,    -1,    34,    -1,    36,    -1,    37,
      -1,    32,    86,    -1,    35,    86,    -1,    33,    86,    -1,
      34,    86,    -1,    37,    86,    -1,    87,    -1,    86,    54,
      87,    -1,    43,    -1,    88,    -1,    89,    90,    -1,    89,
      43,     5,    -1,    89,    43,     4,    -1,    89,    43,     3,
      -1,    43,     5,    -1,    43,     3,    -1,    43,     4,    -1,
      91,    -1,    29,    90,    30,    -1,    93,    -1,    94,    -1,
      95,    -1,    92,    -1,    96,    -1,    16,    90,    -1,    17,
      90,    -1,    28,    90,    -1,    90,     7,    90,    -1,    90,
       6,    90,    -1,    90,     8,    90,    -1,    90,     9,    90,
      -1,    90,    11,    90,    -1,    90,    10,    90,    -1,    90,
      12,    90,    -1,    90,    13,    90,    -1,    90,    17,    90,
      -1,    90,    16,    90,    -1,    90,    19,    90,    -1,    90,
      18,    90,    -1,    90,    20,    90,    -1,    90,    21,    90,
      -1,    39,    -1,    40,    -1,    41,    -1,    43,    -1,    80,
      -1,    42,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   144,   144,   148,   149,   153,   154,   158,   159,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   173,   174,
     177,   180,   181,   184,   185,   189,   190,   191,   194,   195,
     198,   199,   200,   203,   204,   207,   208,   211,   212,   215,
     218,   219,   220,   221,   224,   227,   230,   231,   234,   235,
     238,   240,   241,   242,   243,   246,   248,   251,   252,   253,
     256,   257,   260,   261,   262,   266,   267,   268,   269,   270,
     271,   275,   276,   277,   278,   279,   282,   283,   286,   287,
     290,   293,   294,   295,   296,   297,   298,   301,   302,   303,
     304,   305,   306,   307,   310,   311,   314,   317,   318,   321,
     322,   323,   324,   325,   326,   329,   330,   331,   332,   333,
     334,   337,   338,   339,   340,   341,   342
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "MINUSEQUAL", "PLUSEQUAL", "EQUAL", "OR",
  "AND", "EQUALEQUAL", "NOTEQUAL", "LESSEQUAL", "GREATEREQUAL", "LESS",
  "GREATER", "MINUSMINUS", "PLUSPLUS", "MINUS", "PLUS", "DIV", "MULT",
  "MOD", "POT", "RETURNSYMB", "FUNCSYMB", "ELSEIF", "ELSE", "WHILE", "IF",
  "NOT", "'('", "')'", "CLASSSYMB", "INTSYMB", "FLOATSYMB", "STRINGSYMB",
  "DOUBLESYMB", "VOIDSYMB", "BOOLSYMB", "CONCATSYMB", "INT", "FLOAT",
  "STRING", "BOOL", "ID", "FOR", "BREAK", "CONTINUE", "PRINTLN", "PRINT",
  "READ", "READLINE", "'{'", "'}'", "';'", "','", "$accept", "program",
  "class", "func_list", "statement_list", "statement", "break_cont",
  "concat", "concat_args", "read_statement", "instruction", "plusminus",
  "compound_statement", "println_statement", "println_args",
  "return_statement", "for_statement", "for_args", "if_statement",
  "while_statement", "else_statement", "elseif_statement_list",
  "elseif_statement", "cont_statement", "func_def", "func_call",
  "call_list", "cont_func", "arg_list", "symbols", "declaration",
  "dec_list", "atr", "atribution", "atribution_list", "expression",
  "exp_minus_plus", "logic_exp_not", "logic_exp_or_and", "relac_exp",
  "aritmetic_exp", "type", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,    40,
      41,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   123,   125,    59,    44
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    55,    56,    57,    57,    58,    58,    59,    59,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    61,    61,
      62,    63,    63,    64,    64,    65,    65,    65,    66,    66,
      67,    67,    67,    68,    68,    69,    69,    70,    70,    71,
      72,    72,    72,    72,    73,    74,    75,    75,    76,    76,
      77,    78,    78,    78,    78,    79,    80,    81,    81,    81,
      82,    82,    83,    83,    83,    84,    84,    84,    84,    84,
      84,    85,    85,    85,    85,    85,    86,    86,    87,    87,
      88,    89,    89,    89,    89,    89,    89,    90,    90,    90,
      90,    90,    90,    90,    91,    91,    92,    93,    93,    94,
      94,    94,    94,    94,    94,    95,    95,    95,    95,    95,
      95,    96,    96,    96,    96,    96,    96
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     3,     1,     2,     1,     2,     1,     2,
       1,     2,     2,     2,     2,     2,     2,     2,     1,     1,
       4,     3,     3,     4,     4,     1,     1,     1,     2,     2,
       1,     1,     1,     4,     4,     3,     1,     1,     2,     9,
       1,     1,     1,     0,     7,     5,     2,     0,     2,     0,
       5,     1,     3,     2,     1,     7,     4,     3,     1,     0,
       3,     2,     4,     2,     0,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     1,     3,     1,     1,
       2,     3,     3,     3,     2,     2,     2,     1,     3,     1,
       1,     1,     1,     1,     2,     2,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     0,     0,     0,     0,
       0,     0,     0,     4,     6,     0,    65,    67,    68,    66,
      69,    70,     0,    78,    71,    76,    79,     0,    73,    74,
      72,    75,     2,     5,     0,     0,    85,    86,    84,     0,
       0,     0,     0,     0,   111,   112,   113,   116,   114,   115,
      80,    87,    92,    89,    90,    91,    93,     3,    64,    77,
     114,    94,    95,    96,     0,    83,    82,    81,    59,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    88,     0,    58,    98,    97,
      99,   100,   102,   101,   103,   104,   106,   105,   108,   107,
     109,   110,     0,     0,    63,    56,     0,     0,    55,     0,
      57,    37,     0,     0,     0,   114,     0,    18,    19,     0,
       0,     0,     0,    61,     0,     8,     0,     0,     0,     0,
      27,    10,     0,     0,    32,    30,    31,   115,     0,    26,
      25,    62,    38,     0,     0,     0,    29,    28,    43,     0,
       0,     0,     0,    60,     7,    17,    16,    15,     9,    11,
      14,    13,    12,     0,     0,     0,     0,    78,    42,     0,
      41,    40,     0,    36,     0,     0,     0,     0,     0,    20,
       0,     0,    33,     0,    34,    23,    24,     0,    54,    51,
      45,    49,    21,    22,     0,    90,    35,    53,     0,    47,
      43,    52,     0,     0,    44,    48,     0,     0,    46,     0,
       0,    39,     0,    50
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,    12,    13,   124,   189,   126,   127,   165,   128,
     129,   130,   131,   132,   172,   133,   134,   169,   135,   136,
     204,   199,   205,   190,    14,    49,    86,   108,    83,    22,
     138,   171,    25,   139,    27,   140,    51,    52,    53,    54,
      55,    56
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -166
static const yytype_int16 yypact[] =
{
     -17,   -27,    18,   -25,  -166,    91,   353,     0,     0,     0,
       0,     0,    13,    23,  -166,    26,  -166,  -166,  -166,  -166,
    -166,  -166,    42,    27,    15,  -166,  -166,    54,    15,    15,
      15,    15,  -166,  -166,    91,    57,  -166,  -166,  -166,     0,
      92,    92,    92,    92,  -166,  -166,  -166,  -166,    69,  -166,
     351,  -166,  -166,  -166,  -166,  -166,  -166,  -166,   353,  -166,
      70,   118,   118,  -166,   326,  -166,  -166,  -166,   340,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,   -15,    60,  -166,    33,  -166,   375,   375,
     375,   375,   375,   375,   375,   375,   118,   118,    16,    16,
    -166,  -166,    49,   353,  -166,  -166,   340,   164,  -166,    62,
    -166,   312,    78,    81,    82,    63,    84,  -166,  -166,    87,
      88,    89,    98,  -166,   201,  -166,    76,    77,    94,    95,
    -166,  -166,    96,   101,  -166,  -166,  -166,   102,   123,  -166,
     351,  -166,  -166,   312,   312,   340,  -166,  -166,   341,   340,
     340,   135,   136,  -166,  -166,  -166,  -166,  -166,  -166,  -166,
    -166,  -166,  -166,   114,   115,   152,   129,    20,  -166,   131,
    -166,    15,   155,   170,   158,   159,   185,   124,   124,  -166,
     340,    92,  -166,   340,  -166,  -166,  -166,   238,  -166,  -166,
    -166,  -166,  -166,   129,   351,   147,  -166,  -166,   275,    51,
     341,  -166,   190,   124,  -166,  -166,   191,   312,  -166,   124,
     192,  -166,   124,  -166
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -166,  -166,   186,  -166,    37,   -96,  -166,  -166,    45,  -166,
    -103,  -136,  -166,  -166,  -141,  -166,  -166,    31,  -166,  -166,
    -166,  -166,  -166,  -165,   213,   -97,  -166,  -166,  -166,   -41,
      -5,   390,   193,    -6,  -166,   -21,  -166,  -166,  -166,    56,
    -166,   -61
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      15,    26,    26,    26,    26,    26,    50,    87,   142,   174,
     137,   125,   168,   191,     1,   102,     3,    84,     4,    61,
      62,    63,    64,    36,    37,    38,     5,   137,   154,    15,
      36,    37,    38,    26,   146,   147,    81,    82,   208,   103,
     163,   164,   196,    23,   211,   110,     6,   213,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   109,   105,   168,    32,    36,    37,    38,    39,
      40,    41,    65,    66,    67,   202,   203,   146,   147,    34,
     137,   137,    42,    43,   166,    35,    58,   106,   173,   173,
     137,   125,    68,    44,    45,    46,    47,    48,    68,    68,
     107,   137,   154,   104,   210,   141,   137,   143,    40,    41,
     144,   145,   137,   148,     6,   137,   149,   150,   151,   193,
      42,    43,   173,     7,     8,     9,    10,   152,    11,   155,
     156,    44,    45,    46,    47,    60,    79,    80,    81,    82,
      40,    41,    26,   170,   177,   178,   111,   157,   158,   159,
     112,   113,    42,    43,   160,   161,     7,     8,     9,    10,
     194,    11,   114,    44,    45,    46,    47,   115,   116,   117,
     118,   119,   120,   121,   122,   187,   162,   188,   175,   176,
      40,    41,   179,   180,   181,   182,   111,   183,   184,   185,
     112,   113,    42,    43,    26,   170,     7,     8,     9,    10,
     200,    11,   114,    44,    45,    46,    47,   115,   116,   117,
     118,   119,   120,   121,   122,   186,   123,    40,    41,   207,
      57,   209,   212,   111,   198,   192,    33,   112,   113,    42,
      43,   206,    59,     7,     8,     9,    10,   195,    11,   114,
      44,    45,    46,    47,   115,   116,   117,   118,   119,   120,
     121,   122,     0,   153,    40,    41,     0,     0,     0,     0,
     111,     0,     0,     0,   112,   113,    42,    43,     0,     0,
       7,     8,     9,    10,     0,    11,   114,    44,    45,    46,
      47,   115,   116,   117,   118,   119,   120,   121,   122,     0,
     197,    40,    41,     0,     0,     0,     0,   111,     0,     0,
       0,   112,   113,    42,    43,     0,     0,     7,     8,     9,
      10,     0,    11,   114,    44,    45,    46,    47,   115,   116,
     117,   118,   119,   120,   121,   122,     0,   201,    40,    41,
       0,     0,    69,    70,    71,    72,    73,    74,    75,    76,
      42,    43,    77,    78,    79,    80,    81,    82,     0,     0,
       0,    44,    45,    46,    47,   115,    85,    69,    70,    71,
      72,    73,    74,    75,    76,     0,     0,    77,    78,    79,
      80,    81,    82,     7,     8,     9,    10,     0,    11,    44,
      45,    46,    47,    60,   167,    16,    17,    18,    19,    20,
      21,    77,    78,    79,    80,    81,    82,    24,    28,    29,
      30,    31
};

static const yytype_int16 yycheck[] =
{
       5,     7,     8,     9,    10,    11,    27,    68,   111,   150,
     107,   107,   148,   178,    31,    30,    43,    58,     0,    40,
      41,    42,    43,     3,     4,     5,    51,   124,   124,    34,
       3,     4,     5,    39,    14,    15,    20,    21,   203,    54,
     143,   144,   183,    43,   209,   106,    23,   212,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,   103,    30,   200,    52,     3,     4,     5,    54,
      16,    17,     3,     4,     5,    24,    25,    14,    15,    53,
     177,   178,    28,    29,   145,    43,    29,    54,   149,   150,
     187,   187,    29,    39,    40,    41,    42,    43,    29,    29,
      51,   198,   198,    43,   207,    43,   203,    29,    16,    17,
      29,    29,   209,    29,    23,   212,    29,    29,    29,   180,
      28,    29,   183,    32,    33,    34,    35,    29,    37,    53,
      53,    39,    40,    41,    42,    43,    18,    19,    20,    21,
      16,    17,   148,   148,    30,    30,    22,    53,    53,    53,
      26,    27,    28,    29,    53,    53,    32,    33,    34,    35,
     181,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    53,    53,    43,    43,
      16,    17,    30,    54,    53,    30,    22,    17,    30,    30,
      26,    27,    28,    29,   200,   200,    32,    33,    34,    35,
      53,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    30,    52,    16,    17,    29,
      34,    30,    30,    22,   187,   180,    13,    26,    27,    28,
      29,   200,    39,    32,    33,    34,    35,   181,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    -1,    52,    16,    17,    -1,    -1,    -1,    -1,
      22,    -1,    -1,    -1,    26,    27,    28,    29,    -1,    -1,
      32,    33,    34,    35,    -1,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    -1,
      52,    16,    17,    -1,    -1,    -1,    -1,    22,    -1,    -1,
      -1,    26,    27,    28,    29,    -1,    -1,    32,    33,    34,
      35,    -1,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    -1,    52,    16,    17,
      -1,    -1,     6,     7,     8,     9,    10,    11,    12,    13,
      28,    29,    16,    17,    18,    19,    20,    21,    -1,    -1,
      -1,    39,    40,    41,    42,    43,    30,     6,     7,     8,
       9,    10,    11,    12,    13,    -1,    -1,    16,    17,    18,
      19,    20,    21,    32,    33,    34,    35,    -1,    37,    39,
      40,    41,    42,    43,    43,    32,    33,    34,    35,    36,
      37,    16,    17,    18,    19,    20,    21,     7,     8,     9,
      10,    11
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    31,    56,    43,     0,    51,    23,    32,    33,    34,
      35,    37,    57,    58,    79,    85,    32,    33,    34,    35,
      36,    37,    84,    43,    86,    87,    88,    89,    86,    86,
      86,    86,    52,    79,    53,    43,     3,     4,     5,    54,
      16,    17,    28,    29,    39,    40,    41,    42,    43,    80,
      90,    91,    92,    93,    94,    95,    96,    57,    29,    87,
      43,    90,    90,    90,    90,     3,     4,     5,    29,     6,
       7,     8,     9,    10,    11,    12,    13,    16,    17,    18,
      19,    20,    21,    83,    84,    30,    81,    96,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    30,    54,    43,    30,    54,    51,    82,    84,
      96,    22,    26,    27,    38,    43,    44,    45,    46,    47,
      48,    49,    50,    52,    59,    60,    61,    62,    64,    65,
      66,    67,    68,    70,    71,    73,    74,    80,    85,    88,
      90,    43,    65,    29,    29,    29,    14,    15,    29,    29,
      29,    29,    29,    52,    60,    53,    53,    53,    53,    53,
      53,    53,    53,    65,    65,    63,    96,    43,    66,    72,
      85,    86,    69,    96,    69,    43,    43,    30,    30,    30,
      54,    53,    30,    17,    30,    30,    30,    51,    53,    60,
      78,    78,    63,    96,    90,    94,    69,    52,    59,    76,
      53,    52,    24,    25,    75,    77,    72,    29,    78,    30,
      65,    78,    30,    78
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
#line 144 "mycalc.y"
    {(yyval.iprogram) = PJAVAPROGRAM = insert_program((yyvsp[(2) - (5)].id), (yyvsp[(4) - (5)].iclass)); return 0;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 148 "mycalc.y"
    {(yyval.iclass)=insert_class((yyvsp[(1) - (3)].idecl), (yyvsp[(3) - (3)].iclass), NULL);}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 149 "mycalc.y"
    {(yyval.iclass)=insert_class(NULL, NULL, (yyvsp[(1) - (1)].iflist));}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 153 "mycalc.y"
    {(yyval.iflist)=insert_func_list((yyvsp[(1) - (2)].iflist), (yyvsp[(2) - (2)].ifd));}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 154 "mycalc.y"
    {(yyval.iflist)=insert_func_list(NULL, (yyvsp[(1) - (1)].ifd));}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 158 "mycalc.y"
    {(yyval.isl)=insert_statement_list((yyvsp[(1) - (2)].isl), (yyvsp[(2) - (2)].is));}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 159 "mycalc.y"
    {(yyval.isl)=insert_statement_list(NULL, (yyvsp[(1) - (1)].is));}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 162 "mycalc.y"
    {(yyval.is)=insert_statement(d_instruction, (yyvsp[(1) - (2)].ii));}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 163 "mycalc.y"
    {(yyval.is)=insert_statement(d_compound_statement, (yyvsp[(1) - (1)].ics));}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 164 "mycalc.y"
    {(yyval.is)=insert_statement(d_println_statement, (yyvsp[(1) - (2)].iprints));}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 165 "mycalc.y"
    {(yyval.is)=insert_statement(d_declaration, (yyvsp[(1) - (2)].idecl));}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 166 "mycalc.y"
    {(yyval.is)=insert_statement(d_func_call, (yyvsp[(1) - (2)].ifcall));}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 167 "mycalc.y"
    {(yyval.is)=insert_statement(d_return_statement, (yyvsp[(1) - (2)].ireturn));}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 168 "mycalc.y"
    {(yyval.is)=insert_statement(d_read_statement, (yyvsp[(1) - (2)].irs));}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 169 "mycalc.y"
    {(yyval.is)=insert_statement(d_concat, (yyvsp[(1) - (2)].iconcat));}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 170 "mycalc.y"
    {(yyval.is)=insert_statement(d_break_cont, (yyvsp[(1) - (2)].ibc));}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 173 "mycalc.y"
    {(yyval.ibc)=insert_break_cont(is_BREAK);}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 174 "mycalc.y"
    {(yyval.ibc)=insert_break_cont(is_CONTINUE);}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 177 "mycalc.y"
    {(yyval.iconcat)=insert_concat((yyvsp[(3) - (4)].icargs));}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 180 "mycalc.y"
    {(yyval.icargs)=insert_concat_args((yyvsp[(1) - (3)].ity), NULL, (yyvsp[(3) - (3)].icargs));}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 181 "mycalc.y"
    {(yyval.icargs)=insert_concat_args((yyvsp[(1) - (3)].ity),(yyvsp[(3) - (3)].ity), NULL);}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 184 "mycalc.y"
    {(yyval.irs)=insert_read_statement(d_READ, (yyvsp[(3) - (4)].id));}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 185 "mycalc.y"
    {(yyval.irs)=insert_read_statement(d_READLINE, (yyvsp[(3) - (4)].id));}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 189 "mycalc.y"
    {(yyval.ii)=insert_instruction(d_expression, (yyvsp[(1) - (1)].ie));}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 190 "mycalc.y"
    {(yyval.ii)=insert_instruction(d_atribution, (yyvsp[(1) - (1)].ia));}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 191 "mycalc.y"
    {(yyval.ii)=insert_instruction(d_plusminus, (yyvsp[(1) - (1)].ipm));}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 194 "mycalc.y"
    {(yyval.ipm)=insert_plusminus(d_PLUSPLUS, (yyvsp[(1) - (2)].id));}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 195 "mycalc.y"
    {(yyval.ipm)=insert_plusminus(d_MINUSMINUS, (yyvsp[(1) - (2)].id));}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 198 "mycalc.y"
    {(yyval.ics)=insert_compound_statement(d_if_statement,(yyvsp[(1) - (1)].iifs));}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 199 "mycalc.y"
    {(yyval.ics)=insert_compound_statement(d_while_statement,(yyvsp[(1) - (1)].iws));}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 200 "mycalc.y"
    {(yyval.ics)=insert_compound_statement(d_for_statement,(yyvsp[(1) - (1)].ifors));}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 203 "mycalc.y"
    {(yyval.iprints)=insert_println_statement(d_PRINTLN, (yyvsp[(3) - (4)].ipargs));}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 204 "mycalc.y"
    {(yyval.iprints)=insert_println_statement(d_PRINT, (yyvsp[(3) - (4)].ipargs));}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 207 "mycalc.y"
    {(yyval.ipargs)=insert_println_args((yyvsp[(1) - (3)].ity), (yyvsp[(3) - (3)].ipargs));}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 208 "mycalc.y"
    {(yyval.ipargs)=insert_println_args((yyvsp[(1) - (1)].ity), NULL);}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 211 "mycalc.y"
    {(yyval.ireturn)=insert_return_statement(NULL);}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 212 "mycalc.y"
    {(yyval.ireturn)=insert_return_statement((yyvsp[(2) - (2)].ii));}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 215 "mycalc.y"
    {(yyval.ifors)=insert_for_statement((yyvsp[(3) - (9)].ifa),(yyvsp[(5) - (9)].ire),(yyvsp[(7) - (9)].ifa), (yyvsp[(9) - (9)].iconts));}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 218 "mycalc.y"
    {(yyval.ifa)=insert_for_args(d_for_dec_list,(yyvsp[(1) - (1)].ideclist));}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 219 "mycalc.y"
    {(yyval.ifa)=insert_for_args(d_for_declaration,(yyvsp[(1) - (1)].idecl));}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 220 "mycalc.y"
    {(yyval.ifa)=insert_for_args(d_for_plusminus,(yyvsp[(1) - (1)].ipm));}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 221 "mycalc.y"
    {(yyval.ifa)=NULL;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 224 "mycalc.y"
    {(yyval.iifs)=insert_if_statement((yyvsp[(3) - (7)].ii), (yyvsp[(5) - (7)].iconts), (yyvsp[(6) - (7)].ieisl), (yyvsp[(7) - (7)].ielses));}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 227 "mycalc.y"
    {(yyval.iws)=insert_while_statement((yyvsp[(3) - (5)].ii), (yyvsp[(5) - (5)].iconts));}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 230 "mycalc.y"
    {(yyval.ielses)=insert_else_statement((yyvsp[(2) - (2)].iconts));}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 231 "mycalc.y"
    {(yyval.ielses)=NULL;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 234 "mycalc.y"
    {(yyval.ieisl)=insert_elseif_statement_list((yyvsp[(1) - (2)].ieisl),(yyvsp[(2) - (2)].ielseifs));}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 235 "mycalc.y"
    {(yyval.ieisl)=NULL;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 238 "mycalc.y"
    {(yyval.ielseifs)=insert_elseif_statement((yyvsp[(3) - (5)].ii),(yyvsp[(5) - (5)].iconts));}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 240 "mycalc.y"
    {(yyval.iconts)=insert_cont_statement(d_statement,(yyvsp[(1) - (1)].is));}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 241 "mycalc.y"
    {(yyval.iconts)=insert_cont_statement(d_statement_list,(yyvsp[(2) - (3)].isl));}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 242 "mycalc.y"
    {(yyval.iconts)=NULL;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 243 "mycalc.y"
    {(yyval.iconts)=NULL;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 246 "mycalc.y"
    {(yyval.ifd)=insert_func_def((yyvsp[(2) - (7)].isymb), (yyvsp[(3) - (7)].id), (yyvsp[(5) - (7)].iargl), (yyvsp[(7) - (7)].icf));}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 248 "mycalc.y"
    {(yyval.ifcall)=insert_func_call((yyvsp[(1) - (4)].id), (yyvsp[(3) - (4)].icall));}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 251 "mycalc.y"
    {(yyval.icall)=insert_call_list((yyvsp[(1) - (3)].icall), (yyvsp[(3) - (3)].ity));}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 252 "mycalc.y"
    {(yyval.icall)=insert_call_list(NULL, (yyvsp[(1) - (1)].ity));}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 253 "mycalc.y"
    {(yyval.icall)=NULL;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 256 "mycalc.y"
    {(yyval.icf)=insert_cont_func((yyvsp[(2) - (3)].isl));}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 257 "mycalc.y"
    {(yyval.icf)=NULL;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 260 "mycalc.y"
    {(yyval.iargl)=insert_arg_list((yyvsp[(1) - (4)].iargl), (yyvsp[(3) - (4)].isymb), (yyvsp[(4) - (4)].id));}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 261 "mycalc.y"
    {(yyval.iargl)=insert_arg_list(NULL, (yyvsp[(1) - (2)].isymb), (yyvsp[(2) - (2)].id));}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 262 "mycalc.y"
    {(yyval.iargl)=NULL;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 266 "mycalc.y"
    {(yyval.isymb)=insert_symbols(d_INTEGER);}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 267 "mycalc.y"
    {(yyval.isymb)=insert_symbols(d_DOUBLE);}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 268 "mycalc.y"
    {(yyval.isymb)=insert_symbols(d_FLOAT);}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 269 "mycalc.y"
    {(yyval.isymb)=insert_symbols(d_STRING);}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 270 "mycalc.y"
    {(yyval.isymb)=insert_symbols(d_VOID);}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 271 "mycalc.y"
    {(yyval.isymb)=insert_symbols(d_BOOL);}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 275 "mycalc.y"
    {(yyval.idecl)=insert_declaration(d_INTEGER, (yyvsp[(2) - (2)].ideclist));}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 276 "mycalc.y"
    {(yyval.idecl)=insert_declaration(d_DOUBLE, (yyvsp[(2) - (2)].ideclist));}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 277 "mycalc.y"
    {(yyval.idecl)=insert_declaration(d_FLOAT, (yyvsp[(2) - (2)].ideclist));}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 278 "mycalc.y"
    {(yyval.idecl)=insert_declaration(d_STRING, (yyvsp[(2) - (2)].ideclist));}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 279 "mycalc.y"
    {(yyval.idecl)=insert_declaration(d_BOOL, (yyvsp[(2) - (2)].ideclist));}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 282 "mycalc.y"
    {(yyval.ideclist)=insert_dec_list(NULL, (yyvsp[(1) - (1)].iatr));}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 283 "mycalc.y"
    {(yyval.ideclist)=insert_dec_list((yyvsp[(1) - (3)].ideclist), (yyvsp[(3) - (3)].iatr));}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 286 "mycalc.y"
    {(yyval.iatr)=insert_atr(d_ID, (yyvsp[(1) - (1)].id));}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 287 "mycalc.y"
    {(yyval.iatr)=insert_atr(d_atribution_atr, (yyvsp[(1) - (1)].ia));}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 290 "mycalc.y"
    {(yyval.ia)=insert_atribution((yyvsp[(1) - (2)].ial),(yyvsp[(2) - (2)].ie));}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 293 "mycalc.y"
    {(yyval.ial)= insert_atribution_list(d_EQUAL, (yyvsp[(1) - (3)].ial),(yyvsp[(2) - (3)].id));}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 294 "mycalc.y"
    {(yyval.ial)= insert_atribution_list(d_PLUSEQUAL, (yyvsp[(1) - (3)].ial),(yyvsp[(2) - (3)].id));}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 295 "mycalc.y"
    {(yyval.ial)= insert_atribution_list(d_MINUSEQUAL, (yyvsp[(1) - (3)].ial),(yyvsp[(2) - (3)].id));}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 296 "mycalc.y"
    {(yyval.ial)= insert_atribution_list(d_EQUAL, NULL,(yyvsp[(1) - (2)].id));}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 297 "mycalc.y"
    {(yyval.ial)= insert_atribution_list(d_MINUSEQUAL, NULL,(yyvsp[(1) - (2)].id));}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 298 "mycalc.y"
    {(yyval.ial)= insert_atribution_list(d_PLUSEQUAL, NULL,(yyvsp[(1) - (2)].id));}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 301 "mycalc.y"
    {(yyval.ie)=insert_expression(d_exp_minus_plus, (yyvsp[(1) - (1)].impe));}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 302 "mycalc.y"
    {(yyval.ie)=insert_expression(d_expression_exp, (yyvsp[(2) - (3)].ie));}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 303 "mycalc.y"
    {(yyval.ie)=insert_expression(d_logic_exp_or_and, (yyvsp[(1) - (1)].ileoa));}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 304 "mycalc.y"
    {(yyval.ie)=insert_expression(d_relac_exp, (yyvsp[(1) - (1)].ire));}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 305 "mycalc.y"
    {(yyval.ie)=insert_expression(d_aritmetic_exp, (yyvsp[(1) - (1)].iae));}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 306 "mycalc.y"
    {(yyval.ie)=insert_expression(d_logic_exp_not, (yyvsp[(1) - (1)].ilen));}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 307 "mycalc.y"
    {(yyval.ie)=insert_expression(d_type, (yyvsp[(1) - (1)].ity));}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 310 "mycalc.y"
    {(yyval.impe)=insert_exp_minus_plus((yyvsp[(2) - (2)].ie),is_MINUS);}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 311 "mycalc.y"
    {(yyval.impe)=insert_exp_minus_plus((yyvsp[(2) - (2)].ie),is_PLUS);}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 314 "mycalc.y"
    {(yyval.ilen)=insert_logic_exp_not((yyvsp[(2) - (2)].ie));}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 317 "mycalc.y"
    {(yyval.ileoa)=insert_logic_exp_or_and((yyvsp[(1) - (3)].ie), is_AND, (yyvsp[(3) - (3)].ie));}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 318 "mycalc.y"
    {(yyval.ileoa)=insert_logic_exp_or_and((yyvsp[(1) - (3)].ie), is_OR, (yyvsp[(3) - (3)].ie));}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 321 "mycalc.y"
    {(yyval.ire)=insert_relac_exp((yyvsp[(1) - (3)].ie), is_EQUAL, (yyvsp[(3) - (3)].ie));}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 322 "mycalc.y"
    {(yyval.ire)=insert_relac_exp((yyvsp[(1) - (3)].ie), is_NOTEQUAL, (yyvsp[(3) - (3)].ie));}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 323 "mycalc.y"
    {(yyval.ire)=insert_relac_exp((yyvsp[(1) - (3)].ie), is_GREATEREQUAL, (yyvsp[(3) - (3)].ie));}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 324 "mycalc.y"
    {(yyval.ire)=insert_relac_exp((yyvsp[(1) - (3)].ie), is_LESSEQUAL, (yyvsp[(3) - (3)].ie));}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 325 "mycalc.y"
    {(yyval.ire)=insert_relac_exp((yyvsp[(1) - (3)].ie), is_LESS, (yyvsp[(3) - (3)].ie));}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 326 "mycalc.y"
    {(yyval.ire)=insert_relac_exp((yyvsp[(1) - (3)].ie), is_GREATER, (yyvsp[(3) - (3)].ie));}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 329 "mycalc.y"
    {(yyval.iae)=insert_aritmetic_exp((yyvsp[(1) - (3)].ie), is_PLUS, (yyvsp[(3) - (3)].ie));}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 330 "mycalc.y"
    {(yyval.iae)=insert_aritmetic_exp((yyvsp[(1) - (3)].ie), is_MINUS, (yyvsp[(3) - (3)].ie));}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 331 "mycalc.y"
    {(yyval.iae)=insert_aritmetic_exp((yyvsp[(1) - (3)].ie), is_MULT, (yyvsp[(3) - (3)].ie));}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 332 "mycalc.y"
    {(yyval.iae)=insert_aritmetic_exp((yyvsp[(1) - (3)].ie), is_DIV, (yyvsp[(3) - (3)].ie));}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 333 "mycalc.y"
    {(yyval.iae)=insert_aritmetic_exp((yyvsp[(1) - (3)].ie), is_MOD, (yyvsp[(3) - (3)].ie));}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 334 "mycalc.y"
    {(yyval.iae)=insert_aritmetic_exp((yyvsp[(1) - (3)].ie), is_POT, (yyvsp[(3) - (3)].ie));}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 337 "mycalc.y"
    {(yyval.ity)=insert_type(d_INTEGER, &(yyvsp[(1) - (1)].intValue));}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 338 "mycalc.y"
    {(yyval.ity)=insert_type(d_FLOAT, &(yyvsp[(1) - (1)].floatValue));}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 339 "mycalc.y"
    {(yyval.ity)=insert_type(d_STRING, (yyvsp[(1) - (1)].string));}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 340 "mycalc.y"
    {(yyval.ity)=insert_type(d_type_ID, (yyvsp[(1) - (1)].id));}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 341 "mycalc.y"
    {(yyval.ity)=insert_type(d_type_func_call, (yyvsp[(1) - (1)].ifcall));}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 342 "mycalc.y"
    {(yyval.ity)=insert_type(d_BOOL, &(yyvsp[(1) - (1)].boolValue));}
    break;



/* Line 1455 of yacc.c  */
#line 2531 "y.tab.c"
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
#line 347 "mycalc.y"

int main()
{
	int parsingOK=0;
	
	linha=1;

	parsingOK=yyparse();

	if(parsingOK==0){
		
		if(showShows==1){
			printf("\n\nSTRUCTURES SHOW:\n\n");
			show_program(PJAVAPROGRAM);
			printf("-------------------\n");
		}

		if(checkSemantic==1){
			printf("\n\nSEMANTIC CHECK:\n\n");
			ERROS=semantic_analysis(PJAVAPROGRAM);
			if(ERROS>0){
				printf("-------------------\n");
				printf("\nTOTAL DE ERROS DE SEMANTICA:\n%d\n", ERROS);
				printf("-------------------\n");
			}
			else{
				printf("-->!SEMANTIC IS CORRECT!<--\n\n");
				printf("-------------------\n");
			}
		}

		
		if(showTable==1 && checkSemantic==1){
			printf("\n\nTABELAS:\n");
			show_table();
			printf("-------------------\n");
		}


		if(checkSemantic==1 && ERROS==0){
			printf("\n\nVAI FAZER O TRANSLATE\n\n");
			translate(PJAVAPROGRAM);
			printf("\n\nTRANSLATE FINALIZADO COM SUCESSO!\n\n");

		}
	}
	else
	{
		printf("linha %d: Erro de Sintaxe!\n", linha);
		
		return -1;
	}

	return 0;
}


int yyerror(char* s)
{
	printf("%s\n", s);
	return 1;
}

