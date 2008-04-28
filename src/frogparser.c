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

/* Substitute the variable and function names.  */
#define yyparse frogparse
#define yylex   froglex
#define yyerror frogerror
#define yylval  froglval
#define yychar  frogchar
#define yydebug frogdebug
#define yynerrs frognerrs


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     STAFFNAME = 258,
     TIE = 259,
     END = 260,
     FLOAT = 261,
     NOTENAME = 262,
     DURATION = 263,
     RESTTYPE = 264,
     DIRECTION = 265,
     SLURPOSITION = 266,
     NUMPOSITION = 267,
     KEYTYPE = 268,
     NUM = 269,
     BRACKET = 270,
     CLEFTYPE = 271,
     ORNAMENT = 272,
     FULL = 273,
     PARTIAL_ = 274,
     MODE = 275,
     BARTYPE = 276,
     TEMPOTERM = 277,
     TRANSTEMPO = 278,
     DYN = 279,
     ACCIDENTAL = 280,
     ACCENT = 281,
     NOTEHEAD = 282,
     STYLE = 283,
     CURVESHAPE = 284,
     SYSTEM = 285,
     STAFFGROUP = 286,
     STAFF = 287,
     ENDSTAFFGROUP = 288,
     TUPLET = 289,
     TUP_END = 290,
     SLURTYPE = 291,
     HAIRPINTYPE = 292
   };
#endif
/* Tokens.  */
#define STAFFNAME 258
#define TIE 259
#define END 260
#define FLOAT 261
#define NOTENAME 262
#define DURATION 263
#define RESTTYPE 264
#define DIRECTION 265
#define SLURPOSITION 266
#define NUMPOSITION 267
#define KEYTYPE 268
#define NUM 269
#define BRACKET 270
#define CLEFTYPE 271
#define ORNAMENT 272
#define FULL 273
#define PARTIAL_ 274
#define MODE 275
#define BARTYPE 276
#define TEMPOTERM 277
#define TRANSTEMPO 278
#define DYN 279
#define ACCIDENTAL 280
#define ACCENT 281
#define NOTEHEAD 282
#define STYLE 283
#define CURVESHAPE 284
#define SYSTEM 285
#define STAFFGROUP 286
#define STAFF 287
#define ENDSTAFFGROUP 288
#define TUPLET 289
#define TUP_END 290
#define SLURTYPE 291
#define HAIRPINTYPE 292




/* Copy the first part of user declarations.  */
#line 1 "./frogparser.y"

/*
	(c) 2000  Adam Tee  <eenajt@electeng.leeds.ac.uk>
	(c) 2000  University of Leeds 
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "frogdefs.h"
#include "redefs.h"
#include "contexts.h"
#include "file.h"
#include "frogio.h"
#include "draw.h"
#include "keyresponses.h"
#include "chordops.h"
#include "scoreops.h"
#include "staffops.h"
#include "dialogs.h"
#include "measureops.h"
#include "calculatepositions.h"
#include "objops.h"
#include "processstaffname.h"
#include "tupletops.h"
#include "dynamic.h"
#include "articulations.h"

#define yyin frogin
#define yytext frogtext
#define YYDEBUG 0
#define YYMAXDEPTH 100000
#define YYINITDEPTH 500
  objnode *currentobject;
  extern int errcount;

  static DenemoScore *frogsi;

  extern int yylex (void);
  int yyerror (char *);

  static void
    newnoteobj (struct p_note *thenote, gfloat length, DenemoScore *si);

  static void newclef (char *clefname);

  static void newkeysigobj (char *keyname);

  static void newtimesig (int upper, int lower);

 // static void newdynamic (gchar * type);

  static enum headtype setnoteheadtype (gchar * type);
  optionlist *createoption(struct p_modifier option);
  void emptylist(optionlist *head) ;
  void insertoption(optionlist **header, optionlist *newitem);


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
#line 61 "./frogparser.y"
{
  gfloat f;
  char string[FROG_MAX_TOKEN_STRING];
  int number;
  char character;
  struct p_pitch t_pitch;
  optionlist *t_option;
  struct p_note t_note;
  struct p_modifier t_modifier;
  struct p_position t_position;
  struct p_grace t_grace;
  struct p_beam t_beamd;
  struct p_beam_type t_beamtype;
  struct p_gracenoteoption t_graceoption;
  struct p_staff t_staff;
  struct p_rest t_rest;
  struct p_tupops t_tupops;
  struct p_slur t_slur;
  struct p_hairpin t_hairpin;
}
/* Line 187 of yacc.c.  */
#line 258 "frogparser.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */
#line 150 "./frogparser.y"

  DenemoStaff *thestaffstruct = NULL;
  

  measurenode *themeasures = NULL;
  gint cleftype;
  static int counter = 0;
  static int n = 1;
  static int currentbar=1;
  static gfloat beatnum = 0;
  static gfloat totaldurs = 0;
  static gint staffnum = 0;
  gboolean is_tup = FALSE;
  static gfloat currentbeat = 0;
  gint no_of_options = 0;


/* Line 216 of yacc.c.  */
#line 287 "frogparser.tab.c"

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
#define YYLAST   103

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  95
/* YYNRULES -- Number of states.  */
#define YYNSTATES  144

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    40,    38,     2,     2,    41,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    39,     2,     2,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     6,     8,    10,    11,    16,    18,    22,
      24,    26,    30,    32,    37,    41,    42,    46,    48,    50,
      52,    54,    56,    58,    60,    62,    64,    66,    68,    72,
      75,    78,    80,    83,    85,    90,    93,    95,    97,    99,
     101,   103,   104,   108,   110,   112,   114,   116,   118,   120,
     122,   124,   126,   128,   135,   138,   141,   144,   147,   150,
     153,   155,   157,   159,   162,   165,   167,   169,   171,   174,
     177,   180,   184,   186,   191,   193,   195,   197,   199,   202,
     204,   207,   209,   211,   213,   215,   219,   221,   223,   225,
     227,   231,   233,   237,   243,   245
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      43,     0,    -1,    44,    46,    -1,    30,    -1,    15,    -1,
      -1,    45,    47,    46,    48,    -1,    49,    -1,    49,    46,
      48,    -1,    31,    -1,    33,    -1,    50,    51,    52,    -1,
      32,    -1,     3,    89,    94,    90,    -1,    53,    56,    52,
      -1,    -1,    54,    55,    57,    -1,    14,    -1,     6,    -1,
      58,    -1,    78,    -1,    16,    -1,    92,    -1,    21,    -1,
      24,    -1,    85,    -1,    80,    -1,    79,    -1,     6,    38,
       6,    -1,    60,     6,    -1,    59,     6,    -1,    76,    -1,
       9,    68,    -1,     9,    -1,    61,    63,    65,    71,    -1,
       7,    62,    -1,    93,    -1,    14,    -1,    64,    -1,     5,
      -1,    10,    -1,    -1,    65,    66,    57,    -1,    25,    -1,
      26,    -1,    28,    -1,    14,    -1,    17,    -1,    69,    -1,
       4,    -1,    27,    -1,     4,    -1,    14,    -1,    61,    63,
      70,    71,     6,    57,    -1,    25,    57,    -1,    26,    57,
      -1,    28,    57,    -1,    68,    57,    -1,    17,    57,    -1,
      67,    57,    -1,    72,    -1,    73,    -1,     5,    -1,    74,
      10,    -1,    75,    10,    -1,    10,    -1,    18,    -1,    19,
      -1,    34,    77,    -1,    34,    35,    -1,    14,    14,    -1,
      36,    57,    29,    -1,    37,    -1,    81,    82,    83,    84,
      -1,    20,    -1,    13,    -1,    14,    -1,    14,    -1,     7,
      83,    -1,     5,    -1,     7,    84,    -1,     5,    -1,    86,
      -1,    88,    -1,    87,    -1,     6,    39,    14,    -1,    22,
      -1,    23,    -1,    14,    -1,    14,    -1,    14,    40,    91,
      -1,    14,    -1,    91,    41,    14,    -1,    91,    41,    14,
      40,    92,    -1,    14,    -1,    14,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   168,   168,   170,   177,   182,   184,   185,   185,   187,
     194,   201,   211,   229,   244,   244,   246,   280,   287,   294,
     294,   320,   324,   325,   326,   337,   338,   339,   366,   375,
     396,   431,   433,   441,   449,   462,   469,   476,   483,   488,
     494,   501,   510,   521,   522,   523,   524,   528,   529,   530,
     531,   535,   541,   549,   562,   569,   576,   583,   589,   596,
     604,   609,   614,   621,   628,   637,   644,   651,   658,   679,
     702,   712,   721,   726,   727,   728,   731,   734,   737,   738,
     741,   742,   745,   745,   747,   747,   754,   761,   768,   775,
     782,   787,   794,   799,   806,   813
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "STAFFNAME", "TIE", "END", "FLOAT",
  "NOTENAME", "DURATION", "RESTTYPE", "DIRECTION", "SLURPOSITION",
  "NUMPOSITION", "KEYTYPE", "NUM", "BRACKET", "CLEFTYPE", "ORNAMENT",
  "FULL", "PARTIAL_", "MODE", "BARTYPE", "TEMPOTERM", "TRANSTEMPO", "DYN",
  "ACCIDENTAL", "ACCENT", "NOTEHEAD", "STYLE", "CURVESHAPE", "SYSTEM",
  "STAFFGROUP", "STAFF", "ENDSTAFFGROUP", "TUPLET", "TUP_END", "SLURTYPE",
  "HAIRPINTYPE", "','", "'='", "'+'", "'/'", "$accept", "system", "symbol",
  "brace", "staffgroup", "staffgroupsym", "endstaffsym", "staffspec",
  "staffsym", "staffparams", "musicalobject", "characteristics",
  "barnumber", "beatnumber", "musicalobjects", "position",
  "durationobject", "rest", "note", "pitch", "octave", "stem_dir",
  "directions", "note_option", "modifier_note_type", "tie", "dot",
  "grace_notes", "grace_note_option", "beam", "beam_type", "flag",
  "primary", "secondary", "tuplet", "tuplet_option", "slur", "hairpin",
  "keysignature", "no_of_sharps", "no_of_flats", "name_of_sharps",
  "name_of_flats", "tempo", "stationary", "tempo_term", "transitional",
  "no_of_lines", "transposition", "additive", "timesignature",
  "number_of_half_lines", "position_in_half_lines", 0
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
     285,   286,   287,   288,   289,   290,   291,   292,    44,    61,
      43,    47
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    42,    43,    44,    45,    45,    46,    46,    46,    47,
      48,    49,    50,    51,    52,    52,    53,    54,    55,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    57,    58,
      58,    58,    59,    59,    60,    61,    61,    62,    63,    63,
      64,    65,    65,    66,    66,    66,    66,    66,    66,    66,
      66,    67,    68,    69,    70,    70,    70,    70,    70,    70,
      71,    71,    71,    72,    72,    73,    74,    75,    76,    76,
      77,    78,    79,    80,    80,    80,    81,    82,    83,    83,
      84,    84,    85,    85,    86,    86,    87,    88,    89,    90,
      91,    91,    92,    92,    93,    94
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     1,     0,     4,     1,     3,     1,
       1,     3,     1,     4,     3,     0,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     2,
       2,     1,     2,     1,     4,     2,     1,     1,     1,     1,
       1,     0,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     6,     2,     2,     2,     2,     2,     2,
       1,     1,     1,     2,     2,     1,     1,     1,     2,     2,
       2,     3,     1,     4,     1,     1,     1,     1,     2,     1,
       2,     1,     1,     1,     1,     3,     1,     1,     1,     1,
       3,     1,     3,     5,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     3,     0,     5,     1,     4,    12,     0,     2,     7,
       0,     9,     5,     0,     0,    15,     0,    10,     8,    88,
       0,    17,    11,     0,     0,     6,    95,     0,     0,     0,
      33,    75,    94,    21,    74,    23,    86,    87,    24,     0,
       0,    72,    15,    19,     0,     0,     0,    31,    20,    27,
      26,     0,    25,    82,    84,    83,     0,    22,    36,    18,
       0,    89,    13,     0,    37,    35,    52,    32,     0,     0,
      69,    68,     0,     0,    14,    30,    29,    39,    40,    41,
      38,    77,     0,     0,    16,    85,    91,    90,    70,     0,
      71,     0,    79,     0,     0,    92,    28,    49,    62,    65,
      94,    47,    66,    67,    43,    44,    50,    45,     0,     0,
      48,    34,    60,    61,     0,     0,    78,    81,     0,    73,
       0,     0,    42,    63,    64,    80,    93,    51,     0,     0,
       0,     0,     0,     0,     0,    58,    54,    55,    56,    59,
      57,     0,     0,    53
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     7,     8,    12,    18,     9,    10,    15,
      22,    23,    24,    60,    42,    73,    43,    44,    45,    46,
      65,    79,    80,    91,   109,   132,    67,   110,   134,   111,
     112,   113,   114,   115,    47,    71,    48,    49,    50,    51,
      82,    94,   119,    52,    53,    54,    55,    20,    62,    56,
      57,    58,    27
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -61
static const yytype_int8 yypact[] =
{
      -3,   -61,    30,    -9,   -61,   -61,   -61,     4,   -61,   -10,
      39,   -61,    -9,     3,    25,    31,     3,   -61,   -61,   -61,
      34,   -61,   -61,    -5,    38,   -61,   -61,    42,    18,    48,
      50,   -61,    -7,   -61,   -61,   -61,   -61,   -61,   -61,   -11,
      59,   -61,    31,   -61,    61,    70,    15,   -61,   -61,   -61,
     -61,    64,   -61,   -61,   -61,   -61,    40,   -61,   -61,   -61,
      59,   -61,   -61,    65,   -61,   -61,   -61,   -61,    66,    69,
     -61,   -61,    46,    56,   -61,   -61,   -61,   -61,   -61,   -61,
     -61,   -61,     7,    72,   -61,   -61,    47,   -61,   -61,    82,
     -61,    33,   -61,     7,    21,    51,   -61,   -61,   -61,   -61,
      83,   -61,   -61,   -61,   -61,   -61,   -61,   -61,    15,    59,
     -61,   -61,   -61,   -61,    80,    84,   -61,   -61,    21,   -61,
      66,    49,   -61,   -61,   -61,   -61,   -61,   -61,    59,    59,
      59,    59,    59,    59,    36,   -61,   -61,   -61,   -61,   -61,
     -61,    86,    59,   -61
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -61,   -61,   -61,   -61,     1,   -61,    77,   -61,   -61,   -61,
      53,   -61,   -61,   -61,   -61,   -60,   -61,   -61,   -61,     5,
     -61,    -8,   -61,   -61,   -61,   -61,   -24,   -61,   -61,   -36,
     -61,   -61,   -61,   -61,   -61,   -61,   -61,   -61,   -61,   -61,
     -61,     6,   -17,   -61,   -61,   -61,   -61,   -61,   -61,    35,
     -18,   -61,   -61
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -92
static const yytype_int16 yytable[] =
{
      84,    28,    29,    69,    30,     5,     5,   -76,    31,    32,
      13,    33,    92,    16,    93,    34,    35,    36,    37,    38,
      77,    -5,     6,     6,    70,    78,   117,     1,   118,    39,
       4,    40,    41,    68,   -91,    11,    17,    97,    98,    19,
      29,    98,    14,    99,    59,    21,    99,   100,    26,   122,
     101,   102,   103,   127,   102,   103,    61,    63,   104,   105,
     106,   107,    64,    66,    66,    72,   128,    75,   135,   136,
     137,   138,   139,   140,   129,   130,    76,   131,    81,    85,
      86,    83,   143,    88,    89,    90,    95,    68,    96,   -46,
     123,   120,   142,    25,   124,    74,   108,   133,   141,   116,
     121,   125,   126,    87
};

static const yytype_uint8 yycheck[] =
{
      60,     6,     7,    14,     9,    15,    15,    14,    13,    14,
       9,    16,     5,    12,     7,    20,    21,    22,    23,    24,
       5,    31,    32,    32,    35,    10,     5,    30,     7,    34,
       0,    36,    37,    40,    41,    31,    33,     4,     5,    14,
       7,     5,     3,    10,     6,    14,    10,    14,    14,   109,
      17,    18,    19,     4,    18,    19,    14,    39,    25,    26,
      27,    28,    14,    14,    14,     6,    17,     6,   128,   129,
     130,   131,   132,   133,    25,    26,     6,    28,    14,    14,
      14,    41,   142,    14,    38,    29,    14,    40,     6,     6,
      10,    40,     6,    16,    10,    42,    91,   121,   134,    93,
     108,   118,   120,    68
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    30,    43,    44,     0,    15,    32,    45,    46,    49,
      50,    31,    47,    46,     3,    51,    46,    33,    48,    14,
      89,    14,    52,    53,    54,    48,    14,    94,     6,     7,
       9,    13,    14,    16,    20,    21,    22,    23,    24,    34,
      36,    37,    56,    58,    59,    60,    61,    76,    78,    79,
      80,    81,    85,    86,    87,    88,    91,    92,    93,     6,
      55,    14,    90,    39,    14,    62,    14,    68,    40,    14,
      35,    77,     6,    57,    52,     6,     6,     5,    10,    63,
      64,    14,    82,    41,    57,    14,    14,    91,    14,    38,
      29,    65,     5,     7,    83,    14,     6,     4,     5,    10,
      14,    17,    18,    19,    25,    26,    27,    28,    61,    66,
      69,    71,    72,    73,    74,    75,    83,     5,     7,    84,
      40,    63,    57,    10,    10,    84,    92,     4,    17,    25,
      26,    28,    67,    68,    70,    57,    57,    57,    57,    57,
      57,    71,     6,    57
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
        case 3:
#line 171 "./frogparser.y"
    {
  fprintf (stderr, "Found %c \n", (yyvsp[(1) - (1)]. character ));
;}
    break;

  case 4:
#line 178 "./frogparser.y"
    {
 
;}
    break;

  case 9:
#line 188 "./frogparser.y"
    {

;}
    break;

  case 10:
#line 195 "./frogparser.y"
    {

;}
    break;

  case 11:
#line 202 "./frogparser.y"
    {

  /*p_newstaff(frogsi, &$2); */
;}
    break;

  case 12:
#line 212 "./frogparser.y"
    {

  frogsi->currentstaffnum++;
  newstaff (frogsi, ADDFROMLOAD, DENEMO_NONE);
  frogsi->currentstaff = g_list_last (frogsi->thescore);
  n = 1;
  currentbar = 1;
  staffnum++;
  counter = 0;
  frogsi->cursor_x = 0;
  totaldurs = 0;
  beatnum = 0;
  currentbeat = 0;
;}
    break;

  case 13:
#line 230 "./frogparser.y"
    {

  g_string_assign (((DenemoStaff *) frogsi->currentstaff->data)->lily_name, (yyvsp[(1) - (4)]. string ));
  set_denemo_name (((DenemoStaff *) frogsi->currentstaff->data)->lily_name,
		   ((DenemoStaff *) frogsi->currentstaff->data)->denemo_name);
  ((DenemoStaff *) frogsi->currentstaff->data)->no_of_lines = (yyvsp[(2) - (4)]. number );
  ((DenemoStaff *) frogsi->currentstaff->data)->transposition = (yyvsp[(4) - (4)]. number );
  ((DenemoStaff *) frogsi->currentstaff->data)->pos_in_half_lines = (yyvsp[(3) - (4)]. number );


;}
    break;

  case 16:
#line 247 "./frogparser.y"
    {
 
  if (n != (yyvsp[(1) - (3)]. number ))
    {
      currentbar = (yyvsp[(1) - (3)]. number );
      if (!frogsi->currentmeasure->next)
	{
	  frogsi->currentmeasure = addmeasures
	    (frogsi, frogsi->currentmeasurenum, 1,1);
	}
      else
	{
	  frogsi->currentmeasure = frogsi->currentmeasure->next;
	}

      frogsi->currentmeasurenum++;
      frogsi->cursor_x = 0;
      
      totaldurs = 0;
      currentbeat = 0;
      beatnum = 0;
      
    }
  counter++;
  n = (yyvsp[(1) - (3)]. number );
  currentbeat = (yyvsp[(2) - (3)]. f );



;}
    break;

  case 17:
#line 281 "./frogparser.y"
    {
  (yyval. number ) = (yyvsp[(1) - (1)]. number );
;}
    break;

  case 18:
#line 288 "./frogparser.y"
    {
  (yyval. f ) = (yyvsp[(1) - (1)]. f );
;}
    break;

  case 20:
#line 295 "./frogparser.y"
    {

  DenemoObject *obj = (DenemoObject *)
    (frogsi->currentobject ? frogsi->currentobject->data : NULL);
  printf ("Found Slur\n");
  if (obj && (obj->type == CHORD))
    {
      if (strcmp ((yyvsp[(1) - (1)]. t_slur ).string, "slur_begin") == 0)
	{
	  ((chord *)obj->object)->slur_begin_p = 
	    !((chord *)obj->object)->slur_begin_p;
	  /*obj->u.chordval.slur_end_p == FALSE; */
	  printf ("Current start slur val: %d\n",
		  ((chord *)obj->object)->slur_begin_p);
	}
      else if (strcmp ((yyvsp[(1) - (1)]. t_slur ).string, "slur_end") == 0)
	{
	  ((chord *)obj->object)->slur_end_p =
	    !((chord *)obj->object)->slur_end_p;
	  /*obj->u.chordval.slur_begin_p == FALSE; */
	  printf ("Current end slur val: %d\n", 
		  ((chord *)obj->object)->slur_end_p);
	}
    }
;}
    break;

  case 21:
#line 321 "./frogparser.y"
    {
  newclef ((yyvsp[(1) - (1)]. string ));
;}
    break;

  case 23:
#line 325 "./frogparser.y"
    { ;}
    break;

  case 24:
#line 327 "./frogparser.y"
    {
  GString *dynamic = g_string_new((yyvsp[(1) - (1)]. string ));
  DenemoObject *obj = (DenemoObject *)
    (frogsi->currentobject ? frogsi->currentobject->data : NULL);
  add_dynamic(obj, dynamic);  
  
  
 /* newdynamic ($1);*/
;}
    break;

  case 27:
#line 340 "./frogparser.y"
    {
  DenemoObject *obj = (DenemoObject *)
    (frogsi->currentobject ? frogsi->currentobject->data : NULL);
  printf ("Found Hairpin\n");
  if (obj && (obj->type == CHORD))
    {
      if (strcmp ((yyvsp[(1) - (1)]. t_hairpin ).string, "cresc_begin") == 0)
	((chord *)obj->object)->crescendo_begin_p = 
	  !((chord *)obj->object)->crescendo_begin_p;
      else if (strcmp ((yyvsp[(1) - (1)]. t_hairpin ).string, "cresc_end") == 0)
	((chord *)obj->object)->crescendo_end_p = 
	  !((chord *)obj->object)->crescendo_end_p;
	 
      if (strcmp ((yyvsp[(1) - (1)]. t_hairpin ).string, "dim_begin") == 0)
	((chord *)obj->object)->diminuendo_begin_p =
	  !((chord *)obj->object)->diminuendo_begin_p;
      else if (strcmp ((yyvsp[(1) - (1)]. t_hairpin ).string, "dim_end") == 0)
	((chord *)obj->object)->diminuendo_end_p = 
	  !((chord *)obj->object)->diminuendo_end_p;
	
      
    }


;}
    break;

  case 28:
#line 367 "./frogparser.y"
    {
  (yyval. t_position ).xoff = (yyvsp[(1) - (3)]. f );
  (yyval. t_position ).yoff = (yyvsp[(3) - (3)]. f );
  
;}
    break;

  case 29:
#line 376 "./frogparser.y"
    {
  if (currentbeat == beatnum && n == currentbar)
    {
      totaldurs = beatnum;
    }
  else
    {
      beatnum = currentbeat;
    }

#ifdef DEBUG
  printf("JTF Duration %f\n", (yyvsp[(2) - (2)]. f ));
  printf("Current beat: %f \t Beat Number: %f\n",currentbeat, beatnum); 
#endif
  newnoteobj (&(yyvsp[(1) - (2)]. t_note ), (yyvsp[(2) - (2)]. f ), frogsi);
  /*$1.t_option = NULL;*/
  g_free((yyvsp[(1) - (2)]. t_note ).t_option);
  no_of_options = 0;
;}
    break;

  case 30:
#line 397 "./frogparser.y"
    {
  
  gint duration = 0;
  
  DenemoObject *newmudelaobj = NULL;
  if (currentbeat == beatnum && n == currentbar) 
    {
      totaldurs = beatnum;
    }
  else
    {
      beatnum = currentbeat;
    }
 

  duration = floattoduration ((yyvsp[(2) - (2)]. f ), is_tup);
#ifdef DEBUG
  printf("JTF Duration %f\t Denemo Duration: %d\n", (yyvsp[(2) - (2)]. f ),duration);
  printf("Current beat: %f \t Beat Number: %f\n",currentbeat, beatnum); 
#endif
   

  newmudelaobj = newchord (duration, (yyvsp[(1) - (2)]. t_rest ).dots,0);
 
  frogsi->currentmeasure->data = g_list_append
    ((objnode *)frogsi->currentmeasure->data,
     newmudelaobj);
  frogsi->currentobject = 
    g_list_last((objnode *)frogsi->currentmeasure->data);
  no_of_options = 0;
  /*g_free(newmudelaobj);*/

;}
    break;

  case 32:
#line 434 "./frogparser.y"
    {

  (yyval. t_rest ).rest = (yyvsp[(1) - (2)]. character );
  (yyval. t_rest ).dots = (yyvsp[(2) - (2)]. number );

;}
    break;

  case 33:
#line 442 "./frogparser.y"
    {
  (yyval. t_rest ).rest = (yyvsp[(1) - (1)]. character );
  (yyval. t_rest ).dots = 0;
;}
    break;

  case 34:
#line 450 "./frogparser.y"
    {
  (yyval. t_note ).t_option = NULL;
  (yyval. t_note ).t_pitch = (yyvsp[(1) - (4)]. t_pitch );
  strcpy ((yyval. t_note ).stemdir, (yyvsp[(2) - (4)]. string ));
  (yyval. t_note ).t_option = (yyvsp[(3) - (4)]. t_option );
  (yyval. t_note ).t_beamd = (yyvsp[(4) - (4)]. t_beamd );
  
  g_free((yyvsp[(3) - (4)]. t_option ));  
;}
    break;

  case 35:
#line 463 "./frogparser.y"
    {
  strcpy ((yyval. t_pitch ).notename, (yyvsp[(1) - (2)]. string ));
  (yyval. t_pitch ).octave = (yyvsp[(2) - (2)]. number );

;}
    break;

  case 36:
#line 470 "./frogparser.y"
    {
  (yyval. t_pitch ).number_of_lines = (yyvsp[(1) - (1)]. number );
;}
    break;

  case 37:
#line 477 "./frogparser.y"
    {
  (yyval. number ) = (yyvsp[(1) - (1)]. number );
;}
    break;

  case 38:
#line 484 "./frogparser.y"
    {
  strcpy ((yyval. string ), (yyvsp[(1) - (1)]. string ));
;}
    break;

  case 39:
#line 489 "./frogparser.y"
    {
;}
    break;

  case 40:
#line 495 "./frogparser.y"
    {
  strcpy ((yyval. string ), (yyvsp[(1) - (1)]. string ));
;}
    break;

  case 41:
#line 501 "./frogparser.y"
    {
  (yyval. t_option ) = (struct p_noteoption *)g_malloc(sizeof( struct p_noteoption));
  (yyval. t_option )->next = NULL;
  strcpy((yyval. t_option )->type, "\0");
  strcpy((yyval. t_option )->t_modifier.type, "\0");
  (yyval. t_option )->t_modifier.dots = 0;
  
 /*g_free(item);*/
;}
    break;

  case 42:
#line 511 "./frogparser.y"
    {
  optionlist *nitem = createoption((yyvsp[(2) - (3)]. t_modifier ));
  strcpy((yyval. t_option )->type,(yyvsp[(2) - (3)]. t_modifier ).type);
  
  insertoption(&(yyval. t_option ),nitem);
  nitem = NULL;
  /*g_free(nitem);*/
;}
    break;

  case 43:
#line 521 "./frogparser.y"
    {  strcpy ((yyval. t_modifier ).type, (yyvsp[(1) - (1)]. string )); ;}
    break;

  case 44:
#line 522 "./frogparser.y"
    {  strcpy ((yyval. t_modifier ).type, (yyvsp[(1) - (1)]. string )); ;}
    break;

  case 45:
#line 523 "./frogparser.y"
    { strcpy ((yyval. t_modifier ).type, (yyvsp[(1) - (1)]. string ));;}
    break;

  case 46:
#line 524 "./frogparser.y"
    {  
  strcpy((yyval. t_modifier ).type,"dots");
  (yyval. t_modifier ).dots = (yyvsp[(1) - (1)]. number );
;}
    break;

  case 47:
#line 528 "./frogparser.y"
    {  strcpy ((yyval. t_modifier ).type, (yyvsp[(1) - (1)]. string )); ;}
    break;

  case 48:
#line 529 "./frogparser.y"
    {  (yyval. t_modifier ).gracenote = (yyvsp[(1) - (1)]. t_grace ); ;}
    break;

  case 49:
#line 530 "./frogparser.y"
    {  strcpy ((yyval. t_modifier ).type, (yyvsp[(1) - (1)]. string )); ;}
    break;

  case 50:
#line 531 "./frogparser.y"
    {  strcpy ((yyval. t_modifier ).type, (yyvsp[(1) - (1)]. string )); ;}
    break;

  case 51:
#line 536 "./frogparser.y"
    {
  strcpy ((yyval. string ), (yyvsp[(1) - (1)]. string ));

;}
    break;

  case 52:
#line 542 "./frogparser.y"
    {
  (yyval. number ) = (yyvsp[(1) - (1)]. number );

;}
    break;

  case 53:
#line 550 "./frogparser.y"
    {
  (yyval. t_grace ).t_pitch = (yyvsp[(1) - (6)]. t_pitch );
  strcpy ((yyval. t_grace ).stemdir, (yyvsp[(2) - (6)]. string ));
  (yyval. t_grace ).option = (yyvsp[(3) - (6)]. t_graceoption );
  (yyval. t_grace ).t_beamd = (yyvsp[(4) - (6)]. t_beamd );
  (yyval. t_grace ).duration = (yyvsp[(5) - (6)]. f );
  (yyval. t_grace ).t_position = (yyvsp[(6) - (6)]. t_position );

;}
    break;

  case 54:
#line 563 "./frogparser.y"
    {
  strcpy ((yyval. t_graceoption ).type, (yyvsp[(1) - (2)]. string ));
  (yyval. t_graceoption ).t_position = (yyvsp[(2) - (2)]. t_position );

;}
    break;

  case 55:
#line 570 "./frogparser.y"
    {
  strcpy ((yyval. t_graceoption ).type, (yyvsp[(1) - (2)]. string ));
  (yyval. t_graceoption ).t_position = (yyvsp[(2) - (2)]. t_position );

;}
    break;

  case 56:
#line 577 "./frogparser.y"
    {
  strcpy ((yyval. t_graceoption ).type, (yyvsp[(1) - (2)]. string ));
  (yyval. t_graceoption ).t_position = (yyvsp[(2) - (2)]. t_position );

;}
    break;

  case 57:
#line 584 "./frogparser.y"
    {
  (yyval. t_graceoption ).dots = (yyvsp[(1) - (2)]. number );
  (yyval. t_graceoption ).t_position = (yyvsp[(2) - (2)]. t_position );
;}
    break;

  case 58:
#line 590 "./frogparser.y"
    {
  strcpy ((yyval. t_graceoption ).type, (yyvsp[(1) - (2)]. string ));
  (yyval. t_graceoption ).t_position = (yyvsp[(2) - (2)]. t_position );

;}
    break;

  case 59:
#line 597 "./frogparser.y"
    {
  strcpy ((yyval. t_graceoption ).type, (yyvsp[(1) - (2)]. string ));
  (yyval. t_graceoption ).t_position = (yyvsp[(2) - (2)]. t_position );
;}
    break;

  case 60:
#line 605 "./frogparser.y"
    {
  (yyval. t_beamd ).type = (yyvsp[(1) - (1)]. t_beamtype );
;}
    break;

  case 61:
#line 610 "./frogparser.y"
    {
  strcpy ((yyval. t_beamd ).direction, (yyvsp[(1) - (1)]. string ));
;}
    break;

  case 62:
#line 615 "./frogparser.y"
    {

;}
    break;

  case 63:
#line 622 "./frogparser.y"
    {
  strcpy ((yyval. t_beamtype ).btype, (yyvsp[(1) - (2)]. string ));
  strcpy ((yyval. t_beamtype ).direction, (yyvsp[(2) - (2)]. string ));

;}
    break;

  case 64:
#line 629 "./frogparser.y"
    {
  strcpy ((yyval. t_beamtype ).btype, (yyvsp[(1) - (2)]. string ));
  strcpy ((yyval. t_beamtype ).direction, (yyvsp[(2) - (2)]. string ));

;}
    break;

  case 65:
#line 638 "./frogparser.y"
    {

;}
    break;

  case 66:
#line 645 "./frogparser.y"
    {

;}
    break;

  case 67:
#line 652 "./frogparser.y"
    {

;}
    break;

  case 68:
#line 659 "./frogparser.y"
    {

  objnode *theobj = firstobjnode (frogsi->currentmeasure);
  DenemoObject *newmudelaobj = NULL;
  newmudelaobj = newtupopen ((yyvsp[(2) - (2)]. t_tupops ).numerator, (yyvsp[(2) - (2)]. t_tupops ).denominator);
  theobj = g_list_insert (theobj, newmudelaobj, counter);
  frogsi->cursor_x++;
  frogsi->currentmeasure->data = theobj;
  if (frogsi->cursor_appending)
    {
      frogsi->currentobject = g_list_last (theobj);
    }
  else
    {
      frogsi->currentobject = g_list_nth (theobj, frogsi->cursor_x);

    }
  is_tup = TRUE;
;}
    break;

  case 69:
#line 680 "./frogparser.y"
    {

  objnode *theobj = firstobjnode (frogsi->currentmeasure);
  DenemoObject *newmudelaobj = NULL;
  newmudelaobj = newtupclose ();
  theobj = g_list_insert (theobj, newmudelaobj, counter);
  frogsi->cursor_x++;
  frogsi->currentmeasure->data = theobj;
  if (frogsi->cursor_appending)
    {
      frogsi->currentobject = g_list_last (theobj);
    }
  else
    {
      frogsi->currentobject = g_list_nth (theobj, frogsi->cursor_x);

    }
  is_tup = FALSE;
;}
    break;

  case 70:
#line 703 "./frogparser.y"
    {
  (yyval. t_tupops ).numerator = (yyvsp[(1) - (2)]. number );
  (yyval. t_tupops ).denominator = (yyvsp[(2) - (2)]. number );
;}
    break;

  case 71:
#line 713 "./frogparser.y"
    {
  strcpy ((yyval. t_slur ).string, (yyvsp[(1) - (3)]. string ));
  (yyval. t_slur ).t_position = (yyvsp[(2) - (3)]. t_position );
  strcpy ((yyval. t_slur ).curve, (yyvsp[(3) - (3)]. string ));


;}
    break;

  case 72:
#line 722 "./frogparser.y"
    {
  strcpy ((yyval. t_hairpin ).string, (yyvsp[(1) - (1)]. string ));
;}
    break;

  case 74:
#line 727 "./frogparser.y"
    { ;}
    break;

  case 75:
#line 728 "./frogparser.y"
    { newkeysigobj ((yyvsp[(1) - (1)]. string )); ;}
    break;

  case 76:
#line 731 "./frogparser.y"
    { ;}
    break;

  case 77:
#line 734 "./frogparser.y"
    { ;}
    break;

  case 78:
#line 737 "./frogparser.y"
    { ;}
    break;

  case 79:
#line 738 "./frogparser.y"
    { ;}
    break;

  case 80:
#line 741 "./frogparser.y"
    { ;}
    break;

  case 81:
#line 742 "./frogparser.y"
    { ;}
    break;

  case 85:
#line 748 "./frogparser.y"
    {

;}
    break;

  case 86:
#line 755 "./frogparser.y"
    {

;}
    break;

  case 87:
#line 762 "./frogparser.y"
    {

;}
    break;

  case 88:
#line 769 "./frogparser.y"
    {
  (yyval. number ) = (yyvsp[(1) - (1)]. number );
;}
    break;

  case 89:
#line 776 "./frogparser.y"
    {
  (yyval. number ) = (yyvsp[(1) - (1)]. number );
;}
    break;

  case 90:
#line 783 "./frogparser.y"
    {
  (yyval. number ) = (yyvsp[(1) - (3)]. number );
;}
    break;

  case 91:
#line 788 "./frogparser.y"
    {
  (yyval. number ) = (yyvsp[(1) - (1)]. number );
;}
    break;

  case 92:
#line 795 "./frogparser.y"
    {
  newtimesig ((yyvsp[(1) - (3)]. number ), (yyvsp[(3) - (3)]. number ));
;}
    break;

  case 93:
#line 800 "./frogparser.y"
    {

;}
    break;

  case 94:
#line 807 "./frogparser.y"
    {

;}
    break;

  case 95:
#line 814 "./frogparser.y"
    {
  (yyval. number ) = (yyvsp[(1) - (1)]. number );
;}
    break;


/* Line 1267 of yacc.c.  */
#line 2363 "frogparser.tab.c"
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


#line 820 "./frogparser.y"
int
froginput (char *filename, DenemoScore *si)
{
  extern FILE *yyin;
#ifdef YYDEBUG
  //  yydebug =1;
#endif
  if ((yyin = fopen (filename, "r")) == NULL)
    {
      fprintf (stderr, "Cannot open the file: %s\n", filename);
      return -1;
    }
  else
    {
      fprintf (stderr, "In FROGINPUT");
      yy_setscore (si);
      while (!feof (yyin))
	{
	  yyparse ();
	}
    }
  fclose (yyin);

  return 0;
}

int
yyerror (char *errmsg)
{
  extern char *yytext;

  fprintf (stderr, "%d : %s at default %s\n", errcount, errmsg, yytext);
  return 0;

}

/*
 * Add a new note to the bar takes p_note structure with all the data 
 * for the note to be inserted
 *
 */
void
newnoteobj (struct p_note *thenote, gfloat length, DenemoScore *si)
{
  gint no_dots=0;
  gchar notehead[20];
  objnode *theobj = firstobjnode (si->currentmeasure);
  DenemoObject *newmudelaobj = NULL;
  /*  struct p_modifier *mod = NULL;*/
  struct p_noteoption *list = 0;
  note *newnote = NULL;
  gint duration = 0, notename = 0, enharmonic = 0;
  
  gboolean is_tie = FALSE;
  DenemoObject *curmudelaobj = (DenemoObject *)
    (si->currentobject ? si->currentobject->data : NULL);
  notename =
    fetchnotename (thenote->t_pitch.notename, thenote->t_pitch.octave);
  enharmonic = fetchenharmonic (thenote->t_pitch.notename);
  
  
  for(list = thenote->t_option; list; list = list->next)
    {
      

      /*printf("Modifier = %s  :  %d  \n",list->t_modifier.type, 
	     list->t_modifier.dots);*/
      if (!strcmp (list->t_modifier.type, "tie"))
	is_tie = TRUE;
      if (list->t_modifier.dots)
	no_dots = list->t_modifier.dots;
      
      if (!strcmp (list->t_modifier.type, "cross")
	  || !strcmp (list->t_modifier.type, "diamond")
	  || !strcmp (list->t_modifier.type, "harmonic"))
	{
	  strcpy (notehead,list->t_modifier.type);
	}
      else
	strcpy (notehead,"normal");
    }
  
  if (beatnum != totaldurs)
    {
      duration = floattoduration (length, is_tup);
      newmudelaobj = newchord (duration, no_dots,0);
      
      ((chord *)newmudelaobj->object)->is_tied = is_tie;
      for(list = thenote->t_option; list; list = list->next)
	{
	  
	  
	  if (strcmp (list->t_modifier.type, "accent") == 0)
	   ((chord *)newmudelaobj->object)->ornamentlist = 
				  insert_ornament_list(D_ACCENT,
					  					    ((chord *)newmudelaobj->object)->ornamentlist);
	  if (strcmp (list->t_modifier.type, "staccato") == 0)
	  ((chord *)newmudelaobj->object)->ornamentlist = 
				  insert_ornament_list(STACCATO,
					  					    ((chord *)newmudelaobj->object)->ornamentlist);
	  if (strcmp (list->t_modifier.type, "fermata") == 0)
	    ((chord *)newmudelaobj->object)->ornamentlist = 
				  insert_ornament_list(FERMATA,
					  					    ((chord *)newmudelaobj->object)->ornamentlist);
	  if (strcmp (list->t_modifier.type, "tenuto") == 0)
	  ((chord *)newmudelaobj->object)->ornamentlist = 
				  insert_ornament_list(TENUTO,
					  					    ((chord *)newmudelaobj->object)->ornamentlist);

	  if (strcmp (list->t_modifier.type, "trill") == 0)
	  ((chord *)newmudelaobj->object)->ornamentlist = 
				  insert_ornament_list(TRILL,
					  					    ((chord *)newmudelaobj->object)->ornamentlist);
	   
	  if (strcmp (list->t_modifier.type, "turn") == 0)
	    ((chord *)newmudelaobj->object)->ornamentlist = 
				  insert_ornament_list(TURN,
					  					    ((chord *)newmudelaobj->object)->ornamentlist);
	  if (strcmp (list->t_modifier.type, "mordent") == 0)
	    ((chord *)newmudelaobj->object)->ornamentlist = 
				  insert_ornament_list(MORDENT,
					  					    ((chord *)newmudelaobj->object)->ornamentlist);
	  if (strcmp (list->t_modifier.type, "staccatissimo") == 0)
	    ((chord *)newmudelaobj->object)->ornamentlist = 
				  insert_ornament_list(STACCATISSIMO,
					  					    ((chord *)newmudelaobj->object)->ornamentlist);
	  if (strcmp (list->t_modifier.type, "ubow") == 0)
		  ((chord *)newmudelaobj->object)->ornamentlist = 
				  insert_ornament_list(UBOW,
					  					    ((chord *)newmudelaobj->object)->ornamentlist);
	  if (strcmp (list->t_modifier.type, "dbow") == 0)	
	    ((chord *)newmudelaobj->object)->ornamentlist = 
				  insert_ornament_list(DBOW,
					  					    ((chord *)newmudelaobj->object)->ornamentlist);
		 
	}
      addtone (newmudelaobj, notename, enharmonic, cleftype);
      if(notehead)
	{
	  newnote = (note *)((chord *)newmudelaobj->object)->notes->data;
	  newnote->noteheadtype = setnoteheadtype (notehead);
	}
      theobj = g_list_insert (theobj, newmudelaobj, counter);
      si->cursor_x++;
      si->currentmeasure->data = theobj;
      if (si->cursor_appending)
	si->currentobject = g_list_last (theobj);
      else
	si->currentobject = g_list_nth (theobj, si->cursor_x);


    }
  else
    {

      addtone (curmudelaobj, notename, enharmonic, cleftype);
    }

  /* Should really do these two things once per measure, but anyway: */


  
}


static enum headtype
setnoteheadtype (gchar * type)
{
  if (strcmp (type, "cross") == 0)
    return DENEMO_CROSS_NOTEHEAD;
  else if (strcmp (type, "diamond") == 0)
    return DENEMO_DIAMOND_NOTEHEAD;
  else if (strcmp (type, "harmonic") == 0)
    return DENEMO_HARMONIC_NOTEHEAD;
  else
    return DENEMO_NORMAL_NOTEHEAD;
}

/*
 * Add new Clef at the beginning of the staff
 *
 */
static void
newclef (char *clefname)
{
  enum clefs clefstring;
  DenemoObject *clefobj;

  clefstring = cleftoenum (clefname);
  cleftype = clefstring;
  if (counter == 1)
    {
      ((DenemoStaff *) frogsi->currentstaff->data)->sclef = clefstring;
      find_leftmost_staffcontext ((DenemoStaff *)frogsi->currentstaff->data, frogsi);

    }
  else
    {

      clefobj = dnm_newclefobj (clefstring);
      frogsi->currentmeasure->data = g_list_append
	((objnode *)frogsi->currentmeasure->data, clefobj);

    }
}


/*
 * Add new Key Signature at the beginning of the staff
 *
 */
static void
newkeysigobj (char *keyname)
{
  DenemoObject *newobj = NULL;
  gboolean isminor = FALSE;
  gint keynum = 0;
  gint len = strlen (keyname);

  keynum = Keytoint (keyname);

  fprintf (stderr, "%d len \t %d keynum \n ", len, keynum);

  if (len == 4)
    {
      if (keyname[1] == 'm' && keyname[2] == 'i' && keyname[3] == 'n')
	{
	  if (counter == 2)
	    ((DenemoStaff *) frogsi->currentstaff->data)->skey_isminor = TRUE;
	  else
	    isminor = TRUE;
	}
    }
  else if (len == 5)
    {
      if (keyname[2] == 'm' && keyname[3] == 'i' && keyname[4] == 'n')
	{
	  if (counter == 2)
	    ((DenemoStaff *) frogsi->currentstaff->data)->skey_isminor = TRUE;
	  else
	    isminor = TRUE;

	}
    }
  if (counter == 2)
    {
      ((DenemoStaff *) frogsi->currentstaff->data)->skey = keynum;
      find_leftmost_allcontexts (frogsi);
    }
  else
    {

      newobj = dnm_newkeyobj (keynum, isminor, 0);
      frogsi->currentmeasure->data = g_list_append
	((objnode *)frogsi->currentmeasure->data, newobj);
    }
  initkeyaccs (((DenemoStaff *) frogsi->currentstaff->data)->skeyaccs, keynum);
}

/*
 * Add new Time Signature at the beginning of the staff
 *
 */
static void
newtimesig (gint upper, gint lower)
{
  DenemoObject *ret;
  if (counter == 3)
    {
      ((DenemoStaff *) frogsi->currentstaff->data)->stime1 = upper;
      ((DenemoStaff *) frogsi->currentstaff->data)->stime2 = lower;
      find_leftmost_staffcontext 
	((DenemoStaff *)frogsi->currentstaff->data, frogsi);
    }
  else
    {
      ret = dnm_newtimesigobj (upper, lower);
      frogsi->currentmeasure->data = g_list_append
	((objnode *)frogsi->currentmeasure->data, ret);
    }
}

/*
static void
newdynamic (gchar * type)
{
  DenemoObject *ret;

  ret = dynamic_new (type);
  frogsi->currentmeasure->data = g_list_append
    ((objnode *)frogsi->currentmeasure->data, ret);
}
*/

/* Set global Parser structure equal to the main scoreinfo structure */
void
yy_setscore (DenemoScore *si)
{
  frogsi = si;
  free_score (frogsi);
  frogsi->currentstaffnum = 0;

}


optionlist *createoption(struct p_modifier option)
{
  optionlist *newitem = (optionlist *)malloc(sizeof(optionlist));

  if(!newitem)
    return NULL;
  else {
    newitem->t_modifier = option;
    newitem->next = NULL;
  }
  return newitem;
}

void insertoption(optionlist **header, optionlist *newitem)
{
  newitem->next = *header;
  *header = newitem;

  return;
}


void emptylist(optionlist *head) 
{
  optionlist *itemdel = NULL;
  while(head != NULL) {
    itemdel = head;
    itemdel->next = NULL;
    free(itemdel);
    head = head->next;
   
  }
}

