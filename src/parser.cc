/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "config/parser.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>
#define DEBUG
#include "node.hh"
#include "util.hh"
#include "global.hh"
extern int yylex ();
extern void yyerror (const char *msg);
CompUnitNode     *root;
vector<Node *>    nodelist;
extern bool haserror;

void realse_nodelist(){
    for (int i = 0; i < nodelist.size(); ++i){
        nodelist.pop_back();
    }
}


#line 90 "src/parser.cc" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
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
   by #include "tok.hh".  */
#ifndef YY_YY_INCLUDE_TOK_HH_INCLUDED
# define YY_YY_INCLUDE_TOK_HH_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    eq_tok = 258,
    neq_tok = 259,
    lt_tok = 260,
    le_tok = 261,
    gt_tok = 262,
    ge_tok = 263,
    space_tok = 264,
    while_tok = 265,
    if_tok = 266,
    main_tok = 267,
    void_tok = 268,
    int_tok = 269,
    float_tok = 270,
    const_tok = 271,
    else_tok = 272,
    return_tok = 273,
    intnum_tok = 274,
    floatnum_tok = 275,
    ident_tok = 276,
    eol_tok = 277,
    err_tok = 278,
    extern_tok = 279,
    break_tok = 280,
    continue_tok = 281,
    struct_tok = 282
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 26 "config/parser.y" /* yacc.c:355  */

    int  num;
    float floatnum;
    std::string *ident;
    Node *node;

#line 165 "src/parser.cc" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_INCLUDE_TOK_HH_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 194 "src/parser.cc" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
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
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

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
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   461

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  115
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  317

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   282

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    32,    42,     2,
      40,    41,    30,    29,    39,    28,    43,    31,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    33,
       2,    36,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    37,     2,    38,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    34,     2,    35,     2,     2,     2,     2,
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
      25,    26,    27
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    51,    51,    57,    65,    73,    79,    89,    94,    99,
     107,   111,   115,   119,   125,   130,   138,   144,   153,   159,
     163,   167,   171,   176,   180,   184,   188,   195,   198,   204,
     213,   218,   225,   235,   241,   247,   253,   259,   268,   331,
     337,   356,   363,   368,   375,   382,   389,   394,   401,   410,
     417,   427,   433,   440,   447,   458,   465,   469,   473,   478,
     483,   487,   491,   497,   504,   511,   517,   523,   529,   542,
     552,   557,   567,   572,   580,   585,   593,   599,   606,   614,
     620,   624,   628,   633,   637,   642,   646,   652,   656,   662,
     666,   672,   678,   683,   689,   719,   749,   779,   785,   791,
     797,   803,   807,   813,   819,   825,   831,   837,   843,   849,
     891,   897,   903,   909,   915,   921
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "eq_tok", "neq_tok", "lt_tok", "le_tok",
  "gt_tok", "ge_tok", "space_tok", "while_tok", "if_tok", "main_tok",
  "void_tok", "int_tok", "float_tok", "const_tok", "else_tok",
  "return_tok", "intnum_tok", "floatnum_tok", "ident_tok", "eol_tok",
  "err_tok", "extern_tok", "break_tok", "continue_tok", "struct_tok",
  "'-'", "'+'", "'*'", "'/'", "'%'", "';'", "'{'", "'}'", "'='", "'['",
  "']'", "','", "'('", "')'", "'&'", "'.'", "$accept", "compUnit", "Decl",
  "StructDecl", "ExternDecl", "SimpleDecl", "InnerStructDecl", "Args",
  "Prototype", "FuncDef", "ConstDecl", "ConstDef", "Expp", "VarDecl",
  "VarList", "Ident", "Block", "BlockItemList", "BlockItem", "IdentList",
  "Stmt", "Exp", "Cond", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,    45,    43,
      42,    47,    37,    59,   123,   125,    61,    91,    93,    44,
      40,    41,    38,    46
};
# endif

#define YYPACT_NINF -235

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-235)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -235,    71,  -235,     7,   -10,    -4,     4,     0,    12,  -235,
    -235,    39,    55,  -235,  -235,  -235,    62,    77,    97,    13,
    -235,   156,   122,    68,    20,    20,    43,    76,   144,  -235,
    -235,    35,  -235,  -235,  -235,    53,   148,   186,    53,     8,
    -235,   111,    53,    34,  -235,   238,   176,    98,   138,    63,
     195,   236,   220,   203,   212,   225,    53,    94,   133,   134,
    -235,   331,  -235,  -235,    93,   119,   295,   119,   333,   318,
     218,   221,   151,   332,   -17,    53,   254,   354,  -235,   335,
      53,   119,     2,   317,  -235,   154,  -235,   189,   352,   192,
     353,   369,  -235,   360,   119,   137,   362,    -5,   356,   357,
     111,   111,   119,   182,   365,   366,   379,  -235,  -235,  -235,
    -235,  -235,  -235,   364,   381,   367,   382,    53,  -235,   119,
     202,   384,   336,  -235,    47,  -235,   119,   119,   119,   119,
     119,   372,   371,  -235,   249,   387,   338,   373,  -235,   339,
     318,   374,   375,   368,   270,   392,  -235,   222,  -235,   234,
    -235,   119,   239,  -235,   393,  -235,   383,   385,   119,   119,
     294,   132,   119,   202,   394,  -235,  -235,   164,  -235,  -235,
    -235,   250,  -235,  -235,   342,  -235,  -235,   336,   336,  -235,
    -235,  -235,   119,   386,   202,   396,   388,  -235,  -235,   390,
     389,   398,   119,     5,   391,  -235,  -235,   109,   318,   395,
     319,  -235,  -235,    31,   380,   397,  -235,   278,   401,   119,
     403,   300,   255,   343,   399,  -235,   298,  -235,   152,   119,
     346,  -235,   119,   400,   119,  -235,   318,   402,   405,   404,
     406,   119,  -235,  -235,   119,   119,   119,   119,   119,   119,
     119,   124,   124,   202,   408,   409,   316,   407,  -235,   411,
     410,   216,  -235,  -235,  -235,   322,  -235,   266,   119,   323,
     412,   415,   416,  -235,   318,   271,   318,   318,   318,   318,
     318,   318,  -235,   413,   347,   417,  -235,   418,   119,   219,
    -235,   424,   306,  -235,  -235,   324,  -235,   419,   119,  -235,
     421,   124,   422,  -235,  -235,   282,   268,   312,   423,  -235,
    -235,   119,   325,  -235,  -235,  -235,   425,   202,  -235,  -235,
     330,  -235,  -235,   350,  -235,   426,  -235
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     4,
       9,     0,     0,     6,     7,     8,     0,    55,     0,     0,
      54,    55,     0,     0,     0,     0,     0,     0,     0,    17,
      16,     0,     3,    70,    38,    30,     0,     0,    30,    56,
      51,     0,    30,    56,    52,     0,     0,     0,     0,    18,
       0,    19,     0,     0,     0,     0,    27,     0,     0,     0,
      31,     0,    98,    99,   100,     0,     0,     0,     0,    66,
     100,     0,     0,     0,     0,    30,    55,     0,    53,     0,
      30,     0,     0,     0,    39,     0,    40,     0,    20,     0,
      21,     0,    10,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    97,    69,    72,
      92,    71,    73,    18,     0,    19,     0,     0,    33,     0,
      74,     0,   108,    61,     0,   101,     0,     0,     0,     0,
       0,     0,    65,    34,    57,     0,     0,    56,    35,     0,
      41,     0,     0,     0,     0,     0,    24,     0,    25,     0,
      26,     0,     0,    13,     0,    28,     0,     0,     0,     0,
       0,     0,     0,    74,     0,    90,    91,     0,    20,    21,
      32,     0,    76,    75,     0,    62,   109,   104,   103,   105,
     106,   107,     0,     0,    74,     0,    59,    36,    37,     0,
       0,     0,     0,     0,     0,    22,    23,     0,    49,     0,
       0,     5,    29,     0,     0,     0,    93,   100,     0,     0,
       0,     0,     0,     0,     0,   102,     0,    63,     0,     0,
       0,    58,     0,     0,     0,    42,    45,     0,     0,     0,
       0,     0,    12,    14,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    74,     0,     0,     0,   101,    79,     0,
       0,     0,    78,    77,    67,     0,    64,     0,     0,     0,
       0,     0,     0,    11,    50,     0,   110,   111,   112,   113,
     114,   115,    96,    94,     0,     0,    80,     0,     0,     0,
      87,     0,     0,    68,    60,     0,    43,     0,     0,    46,
       0,     0,     0,    82,    81,     0,   100,     0,   101,    83,
      44,     0,     0,    15,    95,    88,     0,    74,    86,    84,
       0,    47,    85,     0,    48,     0,    89
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -235,  -235,   376,  -235,  -235,    -1,  -235,   -26,   429,  -235,
    -235,   427,  -177,  -235,    -2,   420,   445,  -235,  -235,  -161,
    -234,   -36,   272
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     9,    10,    11,    60,    97,    61,    12,    13,
      14,    47,   197,    15,    19,    20,   110,    57,   111,   174,
     112,   198,   204
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
      69,    72,   213,    23,   134,   218,    29,   272,   273,    58,
      59,    17,    73,     3,    26,    27,    79,    21,    24,    25,
      18,   141,    28,   220,   227,   135,    22,    28,    16,   122,
     156,   124,   246,    31,   235,   236,   237,   238,   239,   240,
     142,    45,   255,   228,    74,   140,    40,   259,    75,   136,
      46,   147,    41,   149,   139,    96,    54,   304,   152,   126,
     127,   128,   129,   130,    49,    55,   160,    58,    59,    56,
      74,     2,    32,    50,    80,   126,   127,   128,   129,   130,
      28,   285,   274,   171,     3,     4,     5,     6,   176,    33,
     177,   178,   179,   180,   181,     7,   157,    51,     8,    23,
      87,    44,    35,    38,    98,    99,    52,    41,   100,   101,
       6,   302,   102,    36,    37,   103,   170,    38,    39,   104,
     105,   106,   203,   203,   310,   211,   212,   107,    33,   108,
     119,    84,    76,   120,    98,    99,   121,    85,    62,    63,
      70,    77,   102,    43,   230,   103,   313,    65,   231,   104,
     105,    62,    63,   207,   113,   115,   226,   107,    33,    67,
      65,    68,   208,   114,   116,    53,   209,    62,    63,    64,
     153,    86,    67,   154,   210,   144,    65,    85,    66,   126,
     127,   128,   129,   130,   145,    54,   257,   254,    67,   132,
      68,   231,    36,    37,    55,   264,    42,    83,   265,   266,
     267,   268,   269,   270,   271,    62,    63,    70,    62,    63,
      70,    62,    63,    70,    65,   282,    88,    65,   161,   162,
      65,   172,   163,   173,    71,   164,    67,   146,    68,    67,
     148,    68,    67,    91,    68,    62,    63,    70,    62,    63,
     296,    90,   295,   297,    65,    92,    95,    65,    93,    94,
     126,   127,   128,   129,   130,   119,    67,   131,   281,    67,
     195,    68,   126,   127,   128,   129,   130,   126,   127,   128,
     129,   130,   196,    89,    81,    82,    42,   199,   126,   127,
     128,   129,   130,   126,   127,   128,   129,   130,   215,   184,
      36,    37,   185,   249,   126,   127,   128,   129,   130,   126,
     127,   128,   129,   130,   284,   119,   192,   193,   307,   290,
     126,   127,   128,   129,   130,   119,   123,   252,   243,   253,
     306,   244,   126,   127,   128,   129,   130,   206,   126,   127,
     128,   129,   130,   248,   126,   127,   128,   129,   130,   299,
     126,   127,   128,   129,   130,   308,   126,   127,   128,   129,
     130,   277,   233,   143,   125,   231,   234,   283,   286,   300,
     311,   231,   231,   231,   231,   314,   128,   129,   130,   231,
     117,   117,   118,   133,   117,   137,   138,   117,   117,   187,
     188,   216,   216,   217,   250,   216,   216,   256,   292,   216,
     150,   315,    75,    80,   151,   155,   158,   159,   165,   166,
     167,    87,   168,   169,    89,   175,   182,   183,   186,    74,
     191,   190,   189,   194,   200,   214,   201,   221,   202,   225,
     219,   241,   245,   224,   247,   222,   223,   229,   232,   275,
     291,   205,     0,   109,   258,   251,    30,   289,   242,   263,
     260,   261,   276,   280,   278,   298,   262,   279,   287,   288,
     293,   294,    48,   301,   303,   305,   309,    34,   312,   316,
       0,    78
};

static const yytype_int16 yycheck[] =
{
      36,    37,   163,     5,    21,   182,     7,   241,   242,    14,
      15,    21,    38,    13,    14,    15,    42,    21,    14,    15,
      30,    19,    27,   184,    19,    42,    30,    27,    21,    65,
      35,    67,   209,    21,     3,     4,     5,     6,     7,     8,
      38,    21,   219,    38,    36,    81,    33,   224,    40,    75,
      30,    87,    39,    89,    80,    56,    21,   291,    94,    28,
      29,    30,    31,    32,    21,    30,   102,    14,    15,    34,
      36,     0,    33,    30,    40,    28,    29,    30,    31,    32,
      27,   258,   243,   119,    13,    14,    15,    16,    41,    34,
     126,   127,   128,   129,   130,    24,    97,    21,    27,   101,
      37,    33,    40,    40,    10,    11,    30,    39,    14,    15,
      16,   288,    18,    36,    37,    21,   117,    40,    21,    25,
      26,    27,   158,   159,   301,   161,   162,    33,    34,    35,
      37,    33,    21,    40,    10,    11,    43,    39,    19,    20,
      21,    30,    18,    21,    35,    21,   307,    28,    39,    25,
      26,    19,    20,    21,    21,    21,   192,    33,    34,    40,
      28,    42,    30,    30,    30,    21,    34,    19,    20,    21,
      33,    33,    40,    36,    42,    21,    28,    39,    30,    28,
      29,    30,    31,    32,    30,    21,   222,    35,    40,    38,
      42,    39,    36,    37,    30,   231,    40,    21,   234,   235,
     236,   237,   238,   239,   240,    19,    20,    21,    19,    20,
      21,    19,    20,    21,    28,   251,    21,    28,    36,    37,
      28,    19,    40,    21,    38,    43,    40,    38,    42,    40,
      38,    42,    40,    30,    42,    19,    20,    21,    19,    20,
      21,    21,   278,   279,    28,    33,    21,    28,    36,    37,
      28,    29,    30,    31,    32,    37,    40,    36,    42,    40,
      38,    42,    28,    29,    30,    31,    32,    28,    29,    30,
      31,    32,    38,    37,    36,    37,    40,    38,    28,    29,
      30,    31,    32,    28,    29,    30,    31,    32,    38,    40,
      36,    37,    43,    38,    28,    29,    30,    31,    32,    28,
      29,    30,    31,    32,    38,    37,    36,    37,    40,    38,
      28,    29,    30,    31,    32,    37,    21,    19,    40,    21,
      38,    43,    28,    29,    30,    31,    32,    33,    28,    29,
      30,    31,    32,    33,    28,    29,    30,    31,    32,    33,
      28,    29,    30,    31,    32,    33,    28,    29,    30,    31,
      32,    35,    33,    36,    21,    39,    37,    35,    35,    35,
      35,    39,    39,    39,    39,    35,    30,    31,    32,    39,
      39,    39,    41,    41,    39,    21,    41,    39,    39,    41,
      41,    39,    39,    41,    41,    39,    39,    41,    41,    39,
      21,    41,    40,    40,    34,    33,    40,    40,    33,    33,
      21,    37,    21,    21,    37,    21,    34,    36,    21,    36,
      42,    36,    38,    21,    21,    21,    33,    21,    33,    21,
      34,    41,    21,    34,    21,    37,    36,    36,    33,    21,
      17,   159,    -1,    57,    34,    36,     7,    21,    41,    33,
      38,    36,    33,    33,    37,    21,    42,    36,    36,    34,
      33,    33,    25,    34,    33,    33,    33,    12,    33,    33,
      -1,    41
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    45,     0,    13,    14,    15,    16,    24,    27,    46,
      47,    48,    52,    53,    54,    57,    21,    21,    30,    58,
      59,    21,    30,    58,    14,    15,    14,    15,    27,    49,
      52,    21,    33,    34,    60,    40,    36,    37,    40,    21,
      33,    39,    40,    21,    33,    21,    30,    55,    55,    21,
      30,    21,    30,    21,    21,    30,    34,    61,    14,    15,
      49,    51,    19,    20,    21,    28,    30,    40,    42,    65,
      21,    38,    65,    51,    36,    40,    21,    30,    59,    51,
      40,    36,    37,    21,    33,    39,    33,    37,    21,    37,
      21,    30,    33,    36,    37,    21,    49,    50,    10,    11,
      14,    15,    18,    21,    25,    26,    27,    33,    35,    46,
      60,    62,    64,    21,    30,    21,    30,    39,    41,    37,
      40,    43,    65,    21,    65,    21,    28,    29,    30,    31,
      32,    36,    38,    41,    21,    42,    51,    21,    41,    51,
      65,    19,    38,    36,    21,    30,    38,    65,    38,    65,
      21,    34,    65,    33,    36,    33,    35,    49,    40,    40,
      65,    36,    37,    40,    43,    33,    33,    21,    21,    21,
      49,    65,    19,    21,    63,    21,    41,    65,    65,    65,
      65,    65,    34,    36,    40,    43,    21,    41,    41,    38,
      36,    42,    36,    37,    21,    38,    38,    56,    65,    38,
      21,    33,    33,    65,    66,    66,    33,    21,    30,    34,
      42,    65,    65,    63,    21,    38,    39,    41,    56,    34,
      63,    21,    37,    36,    34,    21,    65,    19,    38,    36,
      35,    39,    33,    33,    37,     3,     4,     5,     6,     7,
       8,    41,    41,    40,    43,    21,    56,    21,    33,    38,
      41,    36,    19,    21,    35,    56,    41,    65,    34,    56,
      38,    36,    42,    33,    65,    65,    65,    65,    65,    65,
      65,    65,    64,    64,    63,    21,    33,    35,    37,    36,
      33,    42,    65,    35,    38,    56,    35,    36,    34,    21,
      38,    17,    41,    33,    33,    65,    21,    65,    21,    33,
      35,    34,    56,    33,    64,    33,    38,    40,    33,    33,
      56,    35,    33,    63,    35,    41,    33
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    44,    45,    45,    45,    45,    45,    46,    46,    46,
      47,    47,    47,    47,    47,    47,    48,    48,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    50,    50,    50,
      51,    51,    51,    52,    52,    52,    52,    52,    53,    54,
      54,    55,    55,    55,    55,    55,    55,    55,    55,    56,
      56,    57,    57,    58,    58,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    60,
      61,    61,    62,    62,    63,    63,    63,    63,    63,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      66,    66,    66,    66,    66,    66
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     3,     2,     7,     2,     1,     1,     1,
       4,     8,     7,     5,     7,    10,     2,     2,     2,     2,
       3,     3,     5,     5,     4,     4,     4,     0,     2,     3,
       0,     1,     3,     5,     5,     5,     6,     6,     2,     4,
       4,     3,     5,     7,     8,     5,     7,     9,    10,     1,
       3,     3,     3,     3,     1,     1,     2,     4,     6,     5,
       8,     4,     5,     6,     7,     4,     3,     7,     8,     3,
       0,     2,     1,     1,     0,     1,     1,     3,     3,     4,
       5,     6,     6,     6,     7,     8,     7,     5,     7,    10,
       2,     2,     1,     3,     5,     7,     5,     1,     1,     1,
       1,     2,     4,     3,     3,     3,     3,     3,     2,     3,
       3,     3,     3,     3,     3,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

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

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yychar = yylex ();
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
  *++yylsp = yylloc;
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
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 51 "config/parser.y" /* yacc.c:1646  */
    {
                // debug("compUnit ::= empty \n");
                (yyval.node) = new CompUnitNode();
                root = (CompUnitNode *)(yyval.node);
                // nodelist.push_back((Node *)$$);
            }
#line 1597 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 3:
#line 58 "config/parser.y" /* yacc.c:1646  */
    {
                // debug("compUnit ::= compUnit , ExternDecl \n");
                (yyval.node) = (CompUnitNode *)(yyvsp[-2].node);
                ((CompUnitNode *)(yyval.node))->append((Node *)(yyvsp[-1].node));
                root = (CompUnitNode *)(yyval.node);
                // nodelist.push_back((Node *)$$);
            }
#line 1609 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 4:
#line 66 "config/parser.y" /* yacc.c:1646  */
    {
                // debug("compUnit ::= compUnit , Decl \n");
                (yyval.node) = (CompUnitNode *)(yyvsp[-1].node);
                ((CompUnitNode *)(yyval.node))->append((Node *)(yyvsp[0].node));
                root = (CompUnitNode *)(yyval.node);
                // nodelist.push_back((Node *)$$);
            }
#line 1621 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 5:
#line 74 "config/parser.y" /* yacc.c:1646  */
    {
                (yyval.node) = (CompUnitNode *)(yyvsp[-6].node);
                ((CompUnitNode *)(yyval.node))->append(new StructNode(new VarNode((std::string *)(yyvsp[-4].ident)), (InnerStructDeclNode *)(yyvsp[-2].node)));
                root = (CompUnitNode *)(yyval.node);
            }
#line 1631 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 6:
#line 80 "config/parser.y" /* yacc.c:1646  */
    {
                // debug("compUnit ::= compUnit , FuncDef \n");
                (yyval.node) = (CompUnitNode *)(yyvsp[-1].node);
                ((CompUnitNode *)(yyval.node))->append((Node *)(yyvsp[0].node));
                root = (CompUnitNode *)(yyval.node);
                // nodelist.push_back((Node *)$$);
            }
#line 1643 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 7:
#line 90 "config/parser.y" /* yacc.c:1646  */
    {
                // debug("Decl ::= ConstDecl \n");
                (yyval.node) = (yyvsp[0].node);
             }
#line 1652 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 8:
#line 95 "config/parser.y" /* yacc.c:1646  */
    {
                // debug("Decl ::= VarDecl \n");
                (yyval.node) = (yyvsp[0].node);
             }
#line 1661 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 9:
#line 100 "config/parser.y" /* yacc.c:1646  */
    {
                (yyval.node) = (yyvsp[0].node);
            }
#line 1669 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 10:
#line 108 "config/parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = new StructAssignNode(new VarNode((std::string *)(yyvsp[-2].ident)), new VarNode((std::string *)(yyvsp[-1].ident)), 0,DECLASSIGN);
            }
#line 1677 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 11:
#line 112 "config/parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = new StructAssignNode(new VarNode((std::string *)(yyvsp[-6].ident)), new VarNode((std::string *)(yyvsp[-5].ident)), (ExppNode *)(yyvsp[-2].node),DECLASSIGN);
           }
#line 1685 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 12:
#line 116 "config/parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = new StructArrayNode(new VarNode((std::string *)(yyvsp[-5].ident)), new VarNode((std::string *)(yyvsp[-4].ident)), (ExpNode *)(yyvsp[-2].node));
           }
#line 1693 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 13:
#line 120 "config/parser.y" /* yacc.c:1646  */
    {
                    // printf("this one\n");
                     (yyval.node) = new PointerAssignNode(new VarNode((std::string *)(yyvsp[-3].ident)), new VarNode((std::string *)(yyvsp[-1].ident)), 0, 0, DECLASSIGN);
                     dynamic_cast<PointerAssignNode *>((yyval.node))->VarType = 7;
            }
#line 1703 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 14:
#line 126 "config/parser.y" /* yacc.c:1646  */
    {
                     (yyval.node) = new PointerAssignNode(new VarNode((std::string *)(yyvsp[-5].ident)), new VarNode((std::string *)(yyvsp[-3].ident)), new VarNode((std::string *)(yyvsp[-3].ident)), 0, DECLASSIGN);
                     dynamic_cast<PointerAssignNode *>((yyval.node))->VarType = 7;
            }
#line 1712 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 15:
#line 131 "config/parser.y" /* yacc.c:1646  */
    {
                     (yyval.node) = new PointerAssignNode(new VarNode((std::string *)(yyvsp[-8].ident)), new VarNode((std::string *)(yyvsp[-6].ident)), new VarNode((std::string *)(yyvsp[-6].ident)), (ExpNode *)(yyvsp[-2].node), DECLASSIGN);
                     dynamic_cast<PointerAssignNode *>((yyval.node))->VarType = 7;
            }
#line 1721 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 16:
#line 139 "config/parser.y" /* yacc.c:1646  */
    {
                // debug("ExternDecl ::= extern Prototype \n");
                (yyval.node) = new ExternNode((ProtoNode *)(yyvsp[0].node));
                // nodelist.push_back((Node *)$$);
           }
#line 1731 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 17:
#line 145 "config/parser.y" /* yacc.c:1646  */
    {
                // debug("ExternDecl ::= extern SimpleDecl \n");
                (yyval.node) = new ExternNode((SimpleDeclNode *)(yyvsp[0].node));
                // nodelist.push_back((Node *)$$);
           }
#line 1741 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 18:
#line 154 "config/parser.y" /* yacc.c:1646  */
    {
                // debug("SimpleDecl ::= int ident \n");
                (yyval.node) = new SimpleDeclNode(new VarNode((std::string *)(yyvsp[0].ident)), 0);
                // nodelist.push_back((Node *)$$);
            }
#line 1751 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 19:
#line 160 "config/parser.y" /* yacc.c:1646  */
    {
                (yyval.node) = new SimpleDeclNode(new VarNode((std::string *)(yyvsp[0].ident)), 1);
            }
#line 1759 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 20:
#line 164 "config/parser.y" /* yacc.c:1646  */
    {
                (yyval.node) = new SimpleDeclNode(new VarNode((std::string *)(yyvsp[0].ident)), 3);
            }
#line 1767 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 21:
#line 168 "config/parser.y" /* yacc.c:1646  */
    {
                (yyval.node) = new SimpleDeclNode(new VarNode((std::string *)(yyvsp[0].ident)), 4);
            }
#line 1775 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 22:
#line 172 "config/parser.y" /* yacc.c:1646  */
    {
                // debug("SimpleDecl ::= int ident [ Exp ] \n");
                (yyval.node) = new SimpleDeclNode(new VarNode((std::string *)(yyvsp[-3].ident)), (ExpNode *)(yyvsp[-1].node), 3);
            }
#line 1784 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 23:
#line 177 "config/parser.y" /* yacc.c:1646  */
    {
                (yyval.node) = new SimpleDeclNode(new VarNode((std::string *)(yyvsp[-3].ident)), (ExpNode *)(yyvsp[-1].node), 4);
            }
#line 1792 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 24:
#line 181 "config/parser.y" /* yacc.c:1646  */
    {
                (yyval.node) = new SimpleDeclNode(new VarNode((std::string *)(yyvsp[-2].ident)), (ExpNode *)0, 3);
            }
#line 1800 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 25:
#line 185 "config/parser.y" /* yacc.c:1646  */
    {
                (yyval.node) = new SimpleDeclNode(new VarNode((std::string *)(yyvsp[-2].ident)), (ExpNode *)0, 4);
            }
#line 1808 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 26:
#line 189 "config/parser.y" /* yacc.c:1646  */
    {
                (yyval.node) = new SimpleDeclNode(new VarNode((std::string *)(yyvsp[-2].ident)), new VarNode((std::string *)(yyvsp[0].ident)), 5);
            }
#line 1816 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 27:
#line 195 "config/parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = new InnerStructDeclNode();
            }
#line 1824 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 28:
#line 199 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("InnerStructDecl ::= Args \n");
                    (yyval.node) = new InnerStructDeclNode();
                    (yyval.node)->append((SimpleDeclNode *)(yyvsp[-1].node));
            }
#line 1834 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 29:
#line 205 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("InnerStructDecl ::= InnerStructDecl Args ; \n");
                    (yyval.node) = (InnerStructDeclNode *)(yyvsp[-2].node);
                    (yyval.node)->append((SimpleDeclNode *)(yyvsp[-1].node));
            }
#line 1844 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 30:
#line 213 "config/parser.y" /* yacc.c:1646  */
    {
                // debug("Args ::= empty \n");
                (yyval.node) = new ArgsNode();
                // nodelist.push_back((Node *)$$);
            }
#line 1854 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 31:
#line 219 "config/parser.y" /* yacc.c:1646  */
    {
                // debug("Args ::= SimpleDecl \n");
                (yyval.node) = new ArgsNode();
                (yyval.node)->append((SimpleDeclNode *)(yyvsp[0].node));
                // nodelist.push_back((Node *)$$);
            }
#line 1865 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 32:
#line 226 "config/parser.y" /* yacc.c:1646  */
    {
                // debug("Args ::= Args , SimpleDecl \n");
                (yyval.node) = (ArgsNode *)(yyvsp[-2].node) ;
                (yyval.node)->append((SimpleDeclNode *)(yyvsp[0].node));
                // nodelist.push_back((Node *)$$);
            }
#line 1876 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 33:
#line 236 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("Prototype := void ident( Args ) \n ");
                    (yyval.node) = new ProtoNode("void" , new VarNode((std::string *)(yyvsp[-3].ident)), (ArgsNode *)(yyvsp[-1].node));
                    // nodelist.push_back((Node *)$$);
            }
#line 1886 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 34:
#line 242 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("Prototype := int ident( Args ) \n ");
                    (yyval.node) = new ProtoNode("int", new VarNode((std::string *)(yyvsp[-3].ident)), (ArgsNode *)(yyvsp[-1].node));
                    // nodelist.push_back((Node *)$$);
            }
#line 1896 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 35:
#line 248 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("Prototype := int ident( Args ) \n ");
                    (yyval.node) = new ProtoNode("float", new VarNode((std::string *)(yyvsp[-3].ident)), (ArgsNode *)(yyvsp[-1].node));
                    // nodelist.push_back((Node *)$$);
            }
#line 1906 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 36:
#line 254 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("Prototype := int ident( Args ) \n ");
                    (yyval.node) = new ProtoNode("int *", new VarNode((std::string *)(yyvsp[-3].ident)), (ArgsNode *)(yyvsp[-1].node));
                    // nodelist.push_back((Node *)$$);
            }
#line 1916 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 37:
#line 260 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("Prototype := int ident( Args ) \n ");
                    (yyval.node) = new ProtoNode("float *", new VarNode((std::string *)(yyvsp[-3].ident)), (ArgsNode *)(yyvsp[-1].node));
                    // nodelist.push_back((Node *)$$);
            }
#line 1926 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 38:
#line 269 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("FuncDef ::= Prototype Block \n");
                    (yyval.node) = new FuncDefNode((ProtoNode *)(yyvsp[-1].node), (BlockNode *)(yyvsp[0].node));
                    // nodelist.push_back((Node *)$$);
             }
#line 1936 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 39:
#line 332 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("ConstDecl ::= const int ConstDef ;\n");
                    (yyval.node) = new ConstDeclNode((ConstDefNode *)(yyvsp[-1].node), 0);
                    // nodelist.push_back((Node *)$$);
            }
#line 1946 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 40:
#line 338 "config/parser.y" /* yacc.c:1646  */
    {
                   (yyval.node) = new ConstDeclNode((ConstDefNode *)(yyvsp[-1].node), 1);
            }
#line 1954 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 41:
#line 357 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("ConstDef ::= id assign exp \n");
                    (yyval.node) = new ConstDefNode();
                    (yyval.node)->append((Node *)new AssignNode(new VarNode((std::string *)(yyvsp[-2].ident)), (ExpNode *)(yyvsp[0].node), DECLASSIGN, 0));
                    // nodelist.push_back((Node *)$$);
            }
#line 1965 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 42:
#line 364 "config/parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = new ConstDefNode();
                    (yyval.node)->append((Node *)(new AssignNode(new VarNode((std::string *)(yyvsp[-3].ident)),  (ExpNode *)(new VarNode((std::string *)(yyvsp[0].ident))), DECLASSIGN, 1)));
            }
#line 1974 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 43:
#line 369 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("ConstDef ::= id [] assign { Exp {, Exp} } \n");
                    (yyval.node) = new ConstDefNode();
                    (yyval.node)->append((Node *)new ArrayAssignExppNode(new VarNode((std::string *)(yyvsp[-6].ident)), new IntNumNode(-1), (ExppNode *)(yyvsp[-1].node)));
                    // nodelist.push_back((Node *)$$);
             }
#line 1985 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 44:
#line 376 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("ConstDef ::= id [num] assign { Exp {, Exp} } \n");
                    (yyval.node) = new ConstDefNode();
                    (yyval.node)->append((Node *)new ArrayAssignExppNode(new VarNode((std::string *)(yyvsp[-7].ident)), new IntNumNode((int)(yyvsp[-5].num)), (ExppNode *)(yyvsp[-1].node)));
                    // nodelist.push_back((Node *)$$);
             }
#line 1996 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 45:
#line 383 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("ConstDef ::= ConstDef , id assign exp \n");
                    (yyval.node) = (ConstDefNode *)(yyvsp[-4].node);
                    (yyval.node)->append((Node *)new AssignNode(new VarNode((std::string *)(yyvsp[-2].ident)), (ExpNode *)(yyvsp[0].node), DECLASSIGN, 0));
                    // nodelist.push_back((Node *)$$);
             }
#line 2007 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 46:
#line 390 "config/parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (ConstDefNode *)(yyvsp[-6].node);
                    (yyval.node)->append((Node *)(new AssignNode(new VarNode((std::string *)(yyvsp[-3].ident)),  (ExpNode *)(new VarNode((std::string *)(yyvsp[0].ident))), DECLASSIGN, 1)));
            }
#line 2016 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 47:
#line 395 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("ConstDef ::= id [] assign { Exp {, Exp} } \n");
                    (yyval.node) = (ConstDefNode *)(yyvsp[-8].node);
                    (yyval.node)->append((Node *)new ArrayAssignExppNode(new VarNode((std::string *)(yyvsp[-6].ident)), new IntNumNode(-1), (ExppNode *)(yyvsp[-1].node)));
                    // nodelist.push_back((Node *)$$);
             }
#line 2027 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 48:
#line 402 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("ConstDef ::= ConstDef , id [Exp] assign { Expp } \n");
                    (yyval.node) = (ConstDefNode *)(yyvsp[-9].node);
                    (yyval.node)->append((Node *)new ArrayAssignExppNode(new VarNode((std::string *)(yyvsp[-7].ident)), new IntNumNode((int)(yyvsp[-5].num)), (ExppNode *)(yyvsp[-1].node)));
                    // nodelist.push_back((Node *)$$);
             }
#line 2038 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 49:
#line 411 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("Expp ::= Exp \n");
                    (yyval.node) = new ExppNode();
                    (yyval.node)->append((Node *)(yyvsp[0].node));
                    // nodelist.push_back((Node *)$$);
            }
#line 2049 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 50:
#line 418 "config/parser.y" /* yacc.c:1646  */
    {
                     // debug("Expp ::= Expp, Exp \n");
                     (yyval.node) = (ExppNode *)(yyvsp[-2].node);
                     (yyval.node)->append((Node *)(yyvsp[0].node));
                     // nodelist.push_back((Node *)$$);
            }
#line 2060 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 51:
#line 428 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("IdentDecl ::= int VarList ; \n");
                    (yyval.node) = new VarDeclNode((VarListNode *)(yyvsp[-1].node), 0);
                    // nodelist.push_back((Node *)$$);
             }
#line 2070 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 52:
#line 434 "config/parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = new VarDeclNode((VarListNode *)(yyvsp[-1].node), 1);
             }
#line 2078 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 53:
#line 441 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("VarList ::= VarList, Ident \n");
                    (yyval.node) = (VarListNode *)(yyvsp[-2].node);
                    (yyval.node)->append((Node *)(yyvsp[0].node));
                    // nodelist.push_back((Node *)$$);
            }
#line 2089 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 54:
#line 448 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("VarList ::= Ident \n");
                    // printf("identlist\n");
                    (yyval.node) = new VarListNode();
                    (yyval.node)->append((Node *)(yyvsp[0].node));
                    // nodelist.push_back((Node *)$$);
            }
#line 2101 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 55:
#line 459 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("Ident ::= id \n");
                    (yyval.node) = new AssignNode(new VarNode((std::string *)(yyvsp[0].ident)), new IntNumNode(65535), DECLASSIGN, 0);
                    // printf("ident got\n");
                    // nodelist.push_back((Node *)$$);
             }
#line 2112 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 56:
#line 466 "config/parser.y" /* yacc.c:1646  */
    {
                     (yyval.node) = new PointerAssignNode(new VarNode((std::string *)(yyvsp[0].ident)), 0, DECLASSIGN);
            }
#line 2120 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 57:
#line 470 "config/parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = new PointerAssignNode(new VarNode((std::string *)(yyvsp[-2].ident)), new VarNode((std::string *)(yyvsp[0].ident)), PTOP);
            }
#line 2128 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 58:
#line 474 "config/parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = new SEToVarNode(new VarNode((std::string *)(yyvsp[-4].ident)), new VarNode((std::string *)(yyvsp[-2].ident)), new VarNode((std::string *)(yyvsp[0].ident)), DECLASSIGN);
                    dynamic_cast<SEToVarNode *>((yyval.node))->isPointer = 1;
            }
#line 2137 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 59:
#line 479 "config/parser.y" /* yacc.c:1646  */
    {
                     (yyval.node) = new PointerAssignNode(new VarNode((std::string *)(yyvsp[-3].ident)), new VarNode((std::string *)(yyvsp[0].ident)), DECLASSIGN);
                     // printf("%d\n", ((ExpNode *)$5)->type);
            }
#line 2146 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 60:
#line 484 "config/parser.y" /* yacc.c:1646  */
    {
                     (yyval.node) = new PointerAssignNode(new VarNode((std::string *)(yyvsp[-6].ident)), new VarNode((std::string *)(yyvsp[-3].ident)), (ExpNode *)(yyvsp[-1].node), DECLASSIGN);
            }
#line 2154 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 61:
#line 488 "config/parser.y" /* yacc.c:1646  */
    {
                     (yyval.node) = new PointeeAssignNode(new VarNode((std::string *)(yyvsp[-3].ident)), new VarNode((std::string *)(yyvsp[0].ident)), DECLASSIGN);
            }
#line 2162 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 62:
#line 492 "config/parser.y" /* yacc.c:1646  */
    {
                  // printf("done\n");
                  (yyval.node) = new SEToVarNode(new VarNode((std::string *)(yyvsp[-4].ident)), new VarNode((std::string *)(yyvsp[-2].ident)), new VarNode((std::string *)(yyvsp[0].ident)), DECLASSIGN);
                  dynamic_cast<SEToVarNode *>((yyval.node))->isPointer = 0;
            }
#line 2172 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 63:
#line 498 "config/parser.y" /* yacc.c:1646  */
    {
                        // printf("a  = f()\n");
                        (yyval.node) = new RetAssignNode(new VarNode((std::string *)(yyvsp[-5].ident)), new FuncCallNode(new VarNode((std::string *)(yyvsp[-3].ident)), (IdentListNode *)(yyvsp[-1].node)));
                       dynamic_cast<RetAssignNode *>((yyval.node))->Ty= DECLASSIGN;
                       dynamic_cast<RetAssignNode *>((yyval.node))->isPointer= 0;
            }
#line 2183 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 64:
#line 505 "config/parser.y" /* yacc.c:1646  */
    {
                        // printf("a  = f()\n");
                        (yyval.node) = new RetAssignNode(new VarNode((std::string *)(yyvsp[-5].ident)), new FuncCallNode(new VarNode((std::string *)(yyvsp[-3].ident)), (IdentListNode *)(yyvsp[-1].node)));
                       dynamic_cast<RetAssignNode *>((yyval.node))->Ty= DECLASSIGN;
                       dynamic_cast<RetAssignNode *>((yyval.node))->isPointer= 1;
            }
#line 2194 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 65:
#line 512 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("Ident ::= id [ Exp ] \n");
                    (yyval.node) = new ArrayAssignExppNode(new VarNode((std::string *)(yyvsp[-3].ident)), (ExpNode *)(yyvsp[-1].node), new ExppNode());
                    // nodelist.push_back((Node *)$$);
             }
#line 2204 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 66:
#line 518 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("Ident ::= id assign Exp \n");
                    (yyval.node) = new AssignNode(new VarNode((std::string *)(yyvsp[-2].ident)), (ExpNode *)(yyvsp[0].node), DECLASSIGN, 0);
                    // nodelist.push_back((Node *)$$);
            }
#line 2214 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 67:
#line 524 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("Ident ::= id [ ] assign { Expp } \n");
                    (yyval.node) = new ArrayAssignExppNode(new VarNode((std::string *)(yyvsp[-6].ident)), 0, (ExppNode *)(yyvsp[-1].node));
                    // nodelist.push_back((Node *)$$);
            }
#line 2224 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 68:
#line 530 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("Ident ::= id [ num ] assign { Expp } \n");
                    (yyval.node) = new ArrayAssignExppNode(new VarNode((std::string *)(yyvsp[-7].ident)), (ExpNode *)(yyvsp[-5].node), (ExppNode *)(yyvsp[-1].node));
                    // nodelist.push_back((Node *)$$);
            }
#line 2234 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 69:
#line 543 "config/parser.y" /* yacc.c:1646  */
    {
                // debug("Block ::= BlockItemList \n");
                (yyval.node) = new BlockNode((BlockItemListNode *)(yyvsp[-1].node));
                // nodelist.push_back((Node *)$$);
                (yyval.node) = (yyvsp[-1].node);
            }
#line 2245 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 70:
#line 552 "config/parser.y" /* yacc.c:1646  */
    {
                 // debug("BlockItemList ::= empty \n ");
                 (yyval.node) = new BlockItemListNode();
                 // nodelist.push_back((Node *)$$);
            }
#line 2255 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 71:
#line 558 "config/parser.y" /* yacc.c:1646  */
    {
                // debug("BlockItemList ::= BlockItemList , BlockItem \n");
                (yyval.node) = (BlockItemListNode *)(yyvsp[-1].node);
                (yyval.node)->append((Node *)(yyvsp[0].node));
                // nodelist.push_back((Node *)$$);
            }
#line 2266 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 72:
#line 568 "config/parser.y" /* yacc.c:1646  */
    {
                // debug("BlockItem ::= Decl \n");
                (yyval.node) = (yyvsp[0].node);
            }
#line 2275 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 73:
#line 573 "config/parser.y" /* yacc.c:1646  */
    {
                // debug("BlockItem ::= Stmt \n");
                (yyval.node) = (yyvsp[0].node);
            }
#line 2284 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 74:
#line 580 "config/parser.y" /* yacc.c:1646  */
    {
                // debug("Ident_List ::= empty \n");
                (yyval.node) = new IdentListNode();
                // nodelist.push_back((Node *)$$);
            }
#line 2294 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 75:
#line 586 "config/parser.y" /* yacc.c:1646  */
    {
                // debug("Ident_List ::= ident \n");
                (yyval.node) = new IdentListNode();
                // printf("%s\n", (std::string *)$1->c_str());
                (yyval.node)->append(new VarNode((std::string *)(yyvsp[0].ident)));
                // nodelist.push_back((Node *)$$);
            }
#line 2306 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 76:
#line 594 "config/parser.y" /* yacc.c:1646  */
    {
                (yyval.node) = new IdentListNode();
                // printf("%s\n", (std::string *)$1->c_str());
                (yyval.node)->append(new IntNumNode((int)(yyvsp[0].num)));
            }
#line 2316 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 77:
#line 600 "config/parser.y" /* yacc.c:1646  */
    {
                // debug("Ident_List ::= IdentList , ident \n");
                (yyval.node) = (IdentListNode *)(yyvsp[-2].node) ;
                (yyval.node)->append(new VarNode((std::string *)(yyvsp[0].ident)));
                // nodelist.push_back((Node *)$$);
            }
#line 2327 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 78:
#line 607 "config/parser.y" /* yacc.c:1646  */
    {
                (yyval.node) = (IdentListNode *)(yyvsp[-2].node) ;
                (yyval.node)->append(new IntNumNode((int)(yyvsp[0].num)));
           }
#line 2336 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 79:
#line 615 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("Stmt ::= Ident = Exp \n");
                    (yyval.node) = new AssignNode(new VarNode((std::string *)(yyvsp[-3].ident)), (ExpNode *)(yyvsp[-1].node), STMTASSIGN, 0);
                    // nodelist.push_back((Node *)$$);
             }
#line 2346 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 80:
#line 621 "config/parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = new PointeeAssignNode(new VarNode((std::string *)(yyvsp[-4].ident)), new VarNode((std::string *)(yyvsp[-1].ident)), STMTASSIGN);
            }
#line 2354 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 81:
#line 625 "config/parser.y" /* yacc.c:1646  */
    {
                   (yyval.node) = new StructAssignNode(0, new VarNode((std::string *)(yyvsp[-5].ident)), (ExppNode *)(yyvsp[-2].node), STMTASSIGN);
            }
#line 2362 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 82:
#line 629 "config/parser.y" /* yacc.c:1646  */
    {
                  // printf("done\n");
                  (yyval.node) = new SEToVarNode(new VarNode((std::string *)(yyvsp[-5].ident)), new VarNode((std::string *)(yyvsp[-3].ident)), new VarNode((std::string *)(yyvsp[-1].ident)), STMTASSIGN);
            }
#line 2371 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 83:
#line 634 "config/parser.y" /* yacc.c:1646  */
    {
                  (yyval.node) = new VarToSENode(new VarNode((std::string *)(yyvsp[-5].ident)), new VarNode((std::string *)(yyvsp[-3].ident)), (ExpNode *)(yyvsp[-1].node));
            }
#line 2379 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 84:
#line 638 "config/parser.y" /* yacc.c:1646  */
    {
                  (yyval.node) = new VarToSENode(new VarNode((std::string *)(yyvsp[-6].ident)), new VarNode((std::string *)(yyvsp[-4].ident)), (ExpNode *)(new VarNode((std::string *)(yyvsp[-1].ident))));
                  dynamic_cast<VarToSENode *>((yyval.node))->rightPointer = 1;
            }
#line 2388 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 85:
#line 643 "config/parser.y" /* yacc.c:1646  */
    {
                     (yyval.node) = new PointerAssignNode(new VarNode((std::string *)(yyvsp[-7].ident)), new VarNode((std::string *)(yyvsp[-4].ident)), (ExpNode *)(yyvsp[-2].node), STMTASSIGN);
            }
#line 2396 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 86:
#line 647 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("Stmt ::= Ident[Exp] = Exp \n");
                    (yyval.node) = new ArrayAssignExpNode(new VarNode((std::string *)(yyvsp[-6].ident)), (ExpNode *)(yyvsp[-4].node), (ExpNode *)(yyvsp[-1].node));
                    // nodelist.push_back((Node *)$$);
            }
#line 2406 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 87:
#line 653 "config/parser.y" /* yacc.c:1646  */
    {
            	     (yyval.node) = new FuncCallNode(new VarNode((std::string *)(yyvsp[-4].ident)), (IdentListNode *)(yyvsp[-2].node));
            }
#line 2414 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 88:
#line 657 "config/parser.y" /* yacc.c:1646  */
    {
            		// printf("a = f()\n");
            	    	(yyval.node) = new RetAssignNode(new VarNode((std::string *)(yyvsp[-6].ident)), new FuncCallNode(new VarNode((std::string *)(yyvsp[-4].ident)), (IdentListNode *)(yyvsp[-2].node)));
                            dynamic_cast<RetAssignNode *>((yyval.node))->Ty= STMTASSIGN;
            }
#line 2424 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 89:
#line 663 "config/parser.y" /* yacc.c:1646  */
    {
            	    	(yyval.node) = new ArrayRetAssignNode(new VarNode((std::string *)(yyvsp[-9].ident)), (ExpNode *)(yyvsp[-7].node), new FuncCallNode(new VarNode((std::string *)(yyvsp[-4].ident)), (IdentListNode *)(yyvsp[-2].node)));
            }
#line 2432 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 90:
#line 667 "config/parser.y" /* yacc.c:1646  */
    {
                        // debug(" Stmt ::= break ");
                        (yyval.node) = new BreakNode();
                        // // nodelist.push_back((Node *)$$);
            }
#line 2442 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 91:
#line 673 "config/parser.y" /* yacc.c:1646  */
    {
                        // debug(" Stmt ::= break ");
                        (yyval.node) = new ContinueNode();
                        // // nodelist.push_back((Node *)$$);
            }
#line 2452 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 92:
#line 679 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("Stmt ::= Block \n");
                    (yyval.node) = (yyvsp[0].node);
             }
#line 2461 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 93:
#line 684 "config/parser.y" /* yacc.c:1646  */
    {
                // debug("FUNCRET := return Exp \n");
                (yyval.node) = new RetNode((ExpNode *)(yyvsp[-1].node));
                // // nodelist.push_back((Node *)$$);
            }
#line 2471 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 94:
#line 690 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("Stmt ::= if( Cond ) Stmt \n");
                    (yyval.node) = new IfElseNode((CondNode *)(yyvsp[-2].node), (StmtNode * )(yyvsp[0].node),0);
                    // // nodelist.push_back((Node *)$$);
             }
#line 2481 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 95:
#line 720 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("Stmt ::= if( Cond ) Stmt else Stmt \n");
                    (yyval.node) = new IfElseNode((CondNode *)(yyvsp[-4].node), (StmtNode *)(yyvsp[-2].node), (StmtNode *)(yyvsp[0].node));
                    // // nodelist.push_back((Node *)$$);
             }
#line 2491 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 96:
#line 750 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("Stmt ::= while ( Cond ) Stmt \n");
                    (yyval.node) = new WhileNode((CondNode *)(yyvsp[-2].node), (StmtNode *)(yyvsp[0].node));
                    // nodelist.push_back((Node *)$$);
            }
#line 2501 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 97:
#line 780 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("Stmt ::= ; \n");
            }
#line 2509 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 98:
#line 786 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug ("Exp ::= num \n");
                    (yyval.node) = new IntNumNode((int)(yyvsp[0].num));
                    // nodelist.push_back((Node *)$$);
             }
#line 2519 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 99:
#line 792 "config/parser.y" /* yacc.c:1646  */
    {
                    // printf("%f\n", $1);
                    (yyval.node) = new FloatNumNode((float)(yyvsp[0].floatnum));
                    // printf("%f\n",(float)$1);
            }
#line 2529 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 100:
#line 798 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug ("Exp ::= Ident \n");
                    (yyval.node) = new VarNode((std::string *)(yyvsp[0].ident));
                    // nodelist.push_back((Node *)$$);
             }
#line 2539 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 101:
#line 804 "config/parser.y" /* yacc.c:1646  */
    {
                   (yyval.node) = new PointNode(new VarNode((std::string *)(yyvsp[0].ident)));
            }
#line 2547 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 102:
#line 808 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("Exp ::= Ident [ Exp ] \n");
                    (yyval.node) = new ArrayNode(new VarNode((std::string *)(yyvsp[-3].ident)), (ExpNode *)(yyvsp[-1].node));
                    // nodelist.push_back((Node *)$$);
            }
#line 2557 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 103:
#line 814 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("Exp ::= Exp add Exp \n");
                    (yyval.node) = new BinaryExpNode('+', (ExpNode *)(yyvsp[-2].node), (ExpNode *)(yyvsp[0].node));
                    // nodelist.push_back((Node *)$$);
             }
#line 2567 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 104:
#line 820 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("Exp ::= Exp minus Exp \n");
                    (yyval.node) = new BinaryExpNode('-', (ExpNode *)(yyvsp[-2].node), (ExpNode *)(yyvsp[0].node));
                    // nodelist.push_back((Node *)$$);
            }
#line 2577 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 105:
#line 826 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("Exp ::= Exp mul Exp \n");
                    (yyval.node) = new BinaryExpNode('*', (ExpNode *)(yyvsp[-2].node), (ExpNode *)(yyvsp[0].node));
                    // nodelist.push_back((Node *)$$);
             }
#line 2587 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 106:
#line 832 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("Exp ::= Exp div Exp \n");
                    (yyval.node) = new BinaryExpNode('/', (ExpNode *)(yyvsp[-2].node), (ExpNode *)(yyvsp[0].node));
                    // nodelist.push_back((Node *)$$);
             }
#line 2597 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 107:
#line 838 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("Exp ::= Exp mod Exp \n");
                    (yyval.node) = new BinaryExpNode('%', (ExpNode *)(yyvsp[-2].node), (ExpNode *)(yyvsp[0].node));
                    // nodelist.push_back((Node *)$$);
             }
#line 2607 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 108:
#line 844 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("Exp ::= - Exp \n");
                    (yyval.node) = new UnaryExpNode('-', (ExpNode *)(yyvsp[0].node));
                    // nodelist.push_back((Node *)$$);
            }
#line 2617 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 109:
#line 850 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug ("Exp ::= ( Exp ) \n");
                    (yyval.node) = (yyvsp[-1].node);
             }
#line 2626 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 110:
#line 892 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("Cond ::= Exp eq Exp \n");
                    (yyval.node) = new CondNode(eq_tok, (ExpNode *)(yyvsp[-2].node), (ExpNode *)(yyvsp[0].node));
                    // nodelist.push_back((Node *)$$);
            }
#line 2636 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 111:
#line 898 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("Cond ::= Exp neq Exp \n");
                    (yyval.node) = new CondNode(neq_tok, (ExpNode *)(yyvsp[-2].node), (ExpNode *)(yyvsp[0].node));
                    // nodelist.push_back((Node *)$$);
            }
#line 2646 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 112:
#line 904 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("Cond ::= Exp lt Exp \n");
                    (yyval.node) = new CondNode(lt_tok, (ExpNode *)(yyvsp[-2].node), (ExpNode *)(yyvsp[0].node));
                    // nodelist.push_back((Node *)$$);
            }
#line 2656 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 113:
#line 910 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("Cond ::= Exp le Exp \n");
                    (yyval.node) = new CondNode(le_tok, (ExpNode *)(yyvsp[-2].node), (ExpNode *)(yyvsp[0].node));
                    // nodelist.push_back((Node *)$$);
            }
#line 2666 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 114:
#line 916 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("Cond ::= Exp gt Exp \n");
                    (yyval.node) = new CondNode(gt_tok, (ExpNode *)(yyvsp[-2].node), (ExpNode *)(yyvsp[0].node));
                    // nodelist.push_back((Node *)$$);
            }
#line 2676 "src/parser.cc" /* yacc.c:1646  */
    break;

  case 115:
#line 922 "config/parser.y" /* yacc.c:1646  */
    {
                    // debug("Cond ::= Exp ge Exp \n");
                    (yyval.node) = new CondNode(ge_tok, (ExpNode *)(yyvsp[-2].node), (ExpNode *)(yyvsp[0].node));
                    // nodelist.push_back((Node *)$$);
            }
#line 2686 "src/parser.cc" /* yacc.c:1646  */
    break;


#line 2690 "src/parser.cc" /* yacc.c:1646  */
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
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
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

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc);
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

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
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
  return yyresult;
}
#line 929 "config/parser.y" /* yacc.c:1906  */


void yyerror (const char *msg)
{
    error ("%s\n", msg);
}
