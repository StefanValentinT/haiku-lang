/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1





# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    identifier = 258               /* identifier  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);



/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_identifier = 3,                 /* identifier  */
  YYSYMBOL_4_numeric_constant = 4,         /* numeric-constant  */
  YYSYMBOL_5_char_constant = 5,            /* char-constant  */
  YYSYMBOL_6_string_constant = 6,          /* string-constant  */
  YYSYMBOL_7_ = 7,                         /* '('  */
  YYSYMBOL_8_ = 8,                         /* ')'  */
  YYSYMBOL_9_struct_ = 9,                  /* "struct"  */
  YYSYMBOL_10_ = 10,                       /* '{'  */
  YYSYMBOL_11_ = 11,                       /* '}'  */
  YYSYMBOL_12_union_ = 12,                 /* "union"  */
  YYSYMBOL_13_ = 13,                       /* '['  */
  YYSYMBOL_14___ = 14,                     /* '_'  */
  YYSYMBOL_15_ = 15,                       /* ']'  */
  YYSYMBOL_16_ = 16,                       /* '.'  */
  YYSYMBOL_17_ = 17,                       /* "++"  */
  YYSYMBOL_18_ = 18,                       /* "--"  */
  YYSYMBOL_19_ = 19,                       /* ".*"  */
  YYSYMBOL_20_ = 20,                       /* ','  */
  YYSYMBOL_21_ = 21,                       /* '='  */
  YYSYMBOL_22_ = 22,                       /* '&'  */
  YYSYMBOL_23_ = 23,                       /* '-'  */
  YYSYMBOL_24_ = 24,                       /* '+'  */
  YYSYMBOL_25_ = 25,                       /* '!'  */
  YYSYMBOL_26_ = 26,                       /* '~'  */
  YYSYMBOL_27_ = 27,                       /* ':'  */
  YYSYMBOL_28_as_ = 28,                    /* "as"  */
  YYSYMBOL_29_i8_ = 29,                    /* "i8"  */
  YYSYMBOL_30_i16_ = 30,                   /* "i16"  */
  YYSYMBOL_31_i32_ = 31,                   /* "i32"  */
  YYSYMBOL_32_i64_ = 32,                   /* "i64"  */
  YYSYMBOL_33_u8_ = 33,                    /* "u8"  */
  YYSYMBOL_34_u16_ = 34,                   /* "u16"  */
  YYSYMBOL_35_u32_ = 35,                   /* "u32"  */
  YYSYMBOL_36_u64_ = 36,                   /* "u64"  */
  YYSYMBOL_37_f32_ = 37,                   /* "f32"  */
  YYSYMBOL_38_f64_ = 38,                   /* "f64"  */
  YYSYMBOL_39_ = 39,                       /* "->"  */
  YYSYMBOL_40_ = 40,                       /* '*'  */
  YYSYMBOL_41_ = 41,                       /* '/'  */
  YYSYMBOL_42_ = 42,                       /* '%'  */
  YYSYMBOL_43_ = 43,                       /* ">>"  */
  YYSYMBOL_44_ = 44,                       /* "<<"  */
  YYSYMBOL_45_ = 45,                       /* "=="  */
  YYSYMBOL_46_ = 46,                       /* "!="  */
  YYSYMBOL_47_ = 47,                       /* "<="  */
  YYSYMBOL_48_ = 48,                       /* "<"  */
  YYSYMBOL_49_ = 49,                       /* ">="  */
  YYSYMBOL_50_ = 50,                       /* ">"  */
  YYSYMBOL_51_and_ = 51,                   /* "and"  */
  YYSYMBOL_52_or_ = 52,                    /* "or"  */
  YYSYMBOL_53_if_ = 53,                    /* "if"  */
  YYSYMBOL_54_then_ = 54,                  /* "then"  */
  YYSYMBOL_55_else_ = 55,                  /* "else"  */
  YYSYMBOL_56_while_ = 56,                 /* "while"  */
  YYSYMBOL_57_do_ = 57,                    /* "do"  */
  YYSYMBOL_58_break_ = 58,                 /* "break"  */
  YYSYMBOL_59_continue_ = 59,              /* "continue"  */
  YYSYMBOL_60_return_ = 60,                /* "return"  */
  YYSYMBOL_61_defer_ = 61,                 /* "defer"  */
  YYSYMBOL_62_ = 62,                       /* ';'  */
  YYSYMBOL_63_fun_ = 63,                   /* "fun"  */
  YYSYMBOL_64_val_ = 64,                   /* "val"  */
  YYSYMBOL_65_var_ = 65,                   /* "var"  */
  YYSYMBOL_YYACCEPT = 66,                  /* $accept  */
  YYSYMBOL_atom = 67,                      /* atom  */
  YYSYMBOL_factor = 68,                    /* factor  */
  YYSYMBOL_postfix = 69,                   /* postfix  */
  YYSYMBOL_70_arg_list = 70,               /* arg-list  */
  YYSYMBOL_71_init_list = 71,              /* init-list  */
  YYSYMBOL_prefix = 72,                    /* prefix  */
  YYSYMBOL_73_unary_op = 73,               /* unary-op  */
  YYSYMBOL_74_binary_type = 74,            /* binary-type  */
  YYSYMBOL_type = 75,                      /* type  */
  YYSYMBOL_76_typed_list = 76,             /* typed-list  */
  YYSYMBOL_77_type_list = 77,              /* type-list  */
  YYSYMBOL_multiplicative = 78,            /* multiplicative  */
  YYSYMBOL_additive = 79,                  /* additive  */
  YYSYMBOL_shifting = 80,                  /* shifting  */
  YYSYMBOL_relational = 81,                /* relational  */
  YYSYMBOL_logical = 82,                   /* logical  */
  YYSYMBOL_83_control_flow = 83,           /* control-flow  */
  YYSYMBOL_formal = 84,                    /* formal  */
  YYSYMBOL_85_formals_list = 85,           /* formals-list  */
  YYSYMBOL_assignment = 86,                /* assignment  */
  YYSYMBOL_term = 87,                      /* term  */
  YYSYMBOL_declaration = 88,               /* declaration  */
  YYSYMBOL_statement = 89,                 /* statement  */
  YYSYMBOL_90_statement_list = 90,         /* statement-list  */
  YYSYMBOL_91_declaration_list = 91,       /* declaration-list  */
  YYSYMBOL_program = 92                    /* program  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   359

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  66
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  112
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  223

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   300


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    25,     2,     2,     2,    42,    22,     2,
       7,     8,    40,    24,    20,    23,    16,    41,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    27,    62,
       2,    21,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    13,     2,    15,     2,    14,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    10,     2,    11,    26,     2,     2,     2,
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
       5,     6,     9,    12,    17,    18,    19,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    63,    64,
      65
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    10,    10,    11,    12,    13,    16,    17,    18,    19,
      20,    21,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    39,    40,    43,    44,    47,    48,
      49,    50,    53,    53,    53,    53,    53,    56,    57,    58,
      61,    61,    61,    61,    62,    62,    62,    62,    63,    63,
      64,    65,    66,    67,    68,    69,    70,    73,    74,    77,
      78,    81,    82,    83,    84,    87,    88,    89,    92,    93,
      94,    97,    98,    99,   100,   101,   102,   103,   106,   107,
     108,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   127,   128,   131,   132,   135,
     136,   139,   142,   143,   144,   145,   148,   148,   151,   152,
     155,   156,   159
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "identifier",
  "numeric-constant", "char-constant", "string-constant", "'('", "')'",
  "\"struct\"", "'{'", "'}'", "\"union\"", "'['", "'_'", "']'", "'.'",
  "\"++\"", "\"--\"", "\".*\"", "','", "'='", "'&'", "'-'", "'+'", "'!'",
  "'~'", "':'", "\"as\"", "\"i8\"", "\"i16\"", "\"i32\"", "\"i64\"",
  "\"u8\"", "\"u16\"", "\"u32\"", "\"u64\"", "\"f32\"", "\"f64\"",
  "\"->\"", "'*'", "'/'", "'%'", "\">>\"", "\"<<\"", "\"==\"", "\"!=\"",
  "\"<=\"", "\"<\"", "\">=\"", "\">\"", "\"and\"", "\"or\"", "\"if\"",
  "\"then\"", "\"else\"", "\"while\"", "\"do\"", "\"break\"",
  "\"continue\"", "\"return\"", "\"defer\"", "';'", "\"fun\"", "\"val\"",
  "\"var\"", "$accept", "atom", "factor", "postfix", "arg-list",
  "init-list", "prefix", "unary-op", "binary-type", "type", "typed-list",
  "type-list", "multiplicative", "additive", "shifting", "relational",
  "logical", "control-flow", "formal", "formals-list", "assignment",
  "term", "declaration", "statement", "statement-list", "declaration-list",
  "program", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-68)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-107)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      81,    30,    34,    21,   -68,    80,    82,   101,    81,   -68,
     290,    23,   290,    23,   -68,    98,   -68,   -68,   -68,   290,
     117,   131,   119,     1,   314,   314,   -68,   -68,   -68,   -68,
     -68,   290,   290,   -68,   -68,   290,   290,    97,   -68,   -68,
      55,   -68,   314,   134,   -33,   140,   123,   226,   118,   -68,
     -68,   -68,    12,   164,   167,   129,   -68,   -68,   -68,   -68,
     -68,   -68,   -68,   -68,   -68,   -68,   172,   -68,   177,    64,
     180,   120,   -68,   137,   190,   -68,   -68,   141,   121,   187,
     189,   100,   -68,   -68,   151,   156,   -68,   -68,    79,   229,
     290,   216,   -68,   -68,   -68,   290,   -68,    23,    23,   314,
     314,   314,   314,   314,   314,   314,   314,   314,   314,   314,
     314,   314,   314,   314,   181,   -68,    -2,   136,   148,   206,
     290,   290,   203,   -68,    18,   -68,   -68,    58,   -68,   205,
     -68,    59,   215,   230,   290,   290,   199,   204,   -68,    20,
     -68,    43,   -68,   233,   -68,   -68,   -68,   -68,   134,   134,
     134,   -33,   -33,   140,   140,   123,   123,   123,   123,   123,
     123,   226,   226,    23,   210,    23,   217,   -68,    66,   -68,
      94,    23,   -68,   -68,   290,   -68,   242,   -68,   -68,   239,
     -68,   -68,   290,   290,   201,   -68,    23,   290,   218,   256,
     -68,   290,   -68,   -68,    23,   -68,    23,   -68,   257,   -68,
     -68,   -68,   241,   -68,    95,   110,   290,   -68,   -68,   290,
     -68,   -68,   -68,   -68,   240,   290,   -68,   -68,   -68,   -68,
      23,   -68,   -68
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,   110,   112,     0,     0,     0,     0,     1,
       0,     0,     0,     0,   111,     2,     3,     4,     5,     0,
       0,     0,     0,     0,     0,     0,    32,    33,    34,    35,
      36,     0,     0,    85,    86,     0,     0,     0,     6,    12,
      28,    37,     0,    61,    65,    68,    71,    78,    81,    99,
     101,   102,     0,     0,     0,     0,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,     0,   104,     0,     0,
       0,     0,    89,    99,     0,   107,   108,     0,     0,     0,
       0,    28,    30,    31,     0,     0,    87,    88,     0,     0,
       0,     0,    21,    22,    23,     0,    29,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    59,     0,     0,     0,     0,
       0,     0,     0,    13,     0,     7,     8,     0,    91,     0,
      10,     0,     0,     0,     0,     0,    95,     0,    97,     0,
      18,     0,    24,     0,    20,   100,    38,    39,    62,    63,
      64,    67,    66,    69,    70,    72,    73,    74,    75,    76,
      77,    79,    80,     0,     0,     0,     0,    50,     0,    52,
       0,     0,   103,   105,     0,    14,     0,     9,    90,     0,
     109,    11,     0,     0,    82,    84,     0,     0,     0,     0,
      19,     0,    17,    55,     0,    60,     0,    51,     0,    53,
      54,    26,     0,    92,     0,     0,     0,    96,    93,     0,
      98,    25,    56,    57,     0,     0,    16,    15,    83,    94,
       0,    27,    58
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -68,   -68,   -68,   -11,    -7,   -67,    -8,   -68,   -35,   -13,
     159,   -68,    69,    75,   248,    73,   -68,   -19,    89,   -68,
     184,    -9,   160,   152,   -68,   -68,   -68
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    38,    39,    40,   141,   124,    41,    42,    43,    66,
     168,   116,    44,    45,    46,    47,    48,    49,   138,   139,
      50,   142,    75,    76,    77,     4,     5
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      68,    51,    73,    67,   127,    79,   164,    99,   100,   101,
      70,   131,    74,    81,    81,    80,    82,    83,   165,    52,
     114,    53,    84,    85,    54,    55,    86,    87,   188,   175,
      52,    81,    53,     6,    96,    54,    55,     7,   176,   115,
     189,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,   190,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    89,   191,   148,   149,   150,   122,    90,   177,
     181,    91,    92,    93,    94,   123,    95,   197,   176,   176,
       9,   143,   136,     8,   146,   147,   198,   137,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    10,    88,   199,   216,    89,    69,    11,
      73,   172,   173,    90,   198,   191,    91,    92,    93,    94,
     179,   217,    12,   122,   122,   184,   185,    71,    13,    78,
     191,   126,   130,   119,    15,    16,    17,    18,    19,   166,
      20,    21,    72,    22,    23,     1,     2,   167,    24,    25,
     193,   166,   195,    26,    27,    28,    29,    30,   200,   169,
       3,    97,    98,   102,   103,   201,   104,   105,    14,   112,
     113,   151,   152,   207,   117,   204,   205,   118,   208,   153,
     154,   212,   211,   213,    31,   161,   162,    32,   125,    33,
      34,    35,    36,   120,    37,     1,     2,   218,   121,  -106,
     219,   128,   132,   129,   133,   134,   221,   222,    15,    16,
      17,    18,    19,   135,    20,    21,   178,    22,    23,   144,
     163,   171,    24,    25,   174,   182,   186,    26,    27,    28,
      29,    30,    15,    16,    17,    18,    19,   140,    20,    21,
     183,    22,    23,   187,   196,   202,    24,    25,   192,   194,
     203,    26,    27,    28,    29,    30,   206,   209,    31,   136,
     214,    32,   215,    33,    34,    35,    36,   220,    37,     1,
       2,   106,   107,   108,   109,   110,   111,   170,   210,   145,
       0,   180,    31,     0,     0,    32,     0,    33,    34,    35,
      36,     0,    37,    15,    16,    17,    18,    19,     0,    20,
      21,     0,    22,    23,     0,     0,     0,    24,    25,     0,
       0,     0,    26,    27,    28,    29,    30,    15,    16,    17,
      18,    19,     0,    20,     0,     0,    22,    23,     0,     0,
       0,    24,    25,     0,     0,     0,    26,    27,    28,    29,
      30,     0,     0,    31,     0,     0,    32,     0,    33,    34,
      35,    36,     0,    37,   155,   156,   157,   158,   159,   160
};

static const yytype_int16 yycheck[] =
{
      13,    10,    21,    12,    71,     4,     8,    40,    41,    42,
      19,    78,    21,    24,    25,    14,    24,    25,    20,     7,
       8,     9,    31,    32,    12,    13,    35,    36,     8,    11,
       7,    42,     9,     3,    42,    12,    13,     3,    20,    52,
      20,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,     8,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,     7,    20,    99,   100,   101,     3,    13,    11,
      11,    16,    17,    18,    19,    11,    21,    11,    20,    20,
       0,    90,     3,    62,    97,    98,    20,     8,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,    21,     7,    11,    11,     7,    10,    27,
     129,   120,   121,    13,    20,    20,    16,    17,    18,    19,
     129,    11,    21,     3,     3,   134,   135,    10,    27,    10,
      20,    11,    11,     4,     3,     4,     5,     6,     7,     3,
       9,    10,    11,    12,    13,    64,    65,    11,    17,    18,
     163,     3,   165,    22,    23,    24,    25,    26,   171,    11,
       0,    27,    28,    23,    24,   174,    43,    44,     8,    51,
      52,   102,   103,   186,    10,   182,   183,    10,   187,   104,
     105,   194,   191,   196,    53,   112,   113,    56,     8,    58,
      59,    60,    61,    21,    63,    64,    65,   206,    21,    62,
     209,    11,    15,    62,    15,    54,   215,   220,     3,     4,
       5,     6,     7,    57,     9,    10,    11,    12,    13,     3,
      39,    15,    17,    18,    21,    10,    27,    22,    23,    24,
      25,    26,     3,     4,     5,     6,     7,     8,     9,    10,
      10,    12,    13,    39,    27,     3,    17,    18,    15,    39,
      11,    22,    23,    24,    25,    26,    55,    39,    53,     3,
       3,    56,    21,    58,    59,    60,    61,    27,    63,    64,
      65,    45,    46,    47,    48,    49,    50,   118,   189,    95,
      -1,   129,    53,    -1,    -1,    56,    -1,    58,    59,    60,
      61,    -1,    63,     3,     4,     5,     6,     7,    -1,     9,
      10,    -1,    12,    13,    -1,    -1,    -1,    17,    18,    -1,
      -1,    -1,    22,    23,    24,    25,    26,     3,     4,     5,
       6,     7,    -1,     9,    -1,    -1,    12,    13,    -1,    -1,
      -1,    17,    18,    -1,    -1,    -1,    22,    23,    24,    25,
      26,    -1,    -1,    53,    -1,    -1,    56,    -1,    58,    59,
      60,    61,    -1,    63,   106,   107,   108,   109,   110,   111
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    64,    65,    88,    91,    92,     3,     3,    62,     0,
      21,    27,    21,    27,    88,     3,     4,     5,     6,     7,
       9,    10,    12,    13,    17,    18,    22,    23,    24,    25,
      26,    53,    56,    58,    59,    60,    61,    63,    67,    68,
      69,    72,    73,    74,    78,    79,    80,    81,    82,    83,
      86,    87,     7,     9,    12,    13,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    75,    87,    75,    10,
      87,    10,    11,    83,    87,    88,    89,    90,    10,     4,
      14,    69,    72,    72,    87,    87,    87,    87,     7,     7,
      13,    16,    17,    18,    19,    21,    72,    27,    28,    40,
      41,    42,    23,    24,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,     8,    75,    77,    10,    10,     4,
      21,    21,     3,    11,    71,     8,    11,    71,    11,    62,
      11,    71,    15,    15,    54,    57,     3,     8,    84,    85,
       8,    70,    87,    87,     3,    86,    75,    75,    74,    74,
      74,    78,    78,    79,    79,    80,    80,    80,    80,    80,
      80,    81,    81,    39,     8,    20,     3,    11,    76,    11,
      76,    15,    87,    87,    21,    11,    20,    11,    11,    87,
      89,    11,    10,    10,    87,    87,    27,    39,     8,    20,
       8,    20,    15,    75,    39,    75,    27,    11,    20,    11,
      75,    87,     3,    11,    70,    70,    55,    75,    87,    39,
      84,    87,    75,    75,     3,    21,    11,    11,    87,    87,
      27,    87,    75
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    66,    67,    67,    67,    67,    68,    68,    68,    68,
      68,    68,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    70,    70,    71,    71,    72,    72,
      72,    72,    73,    73,    73,    73,    73,    74,    74,    74,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    76,    76,    77,
      77,    78,    78,    78,    78,    79,    79,    79,    80,    80,
      80,    81,    81,    81,    81,    81,    81,    81,    82,    82,
      82,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    84,    84,    85,    85,    86,
      86,    87,    88,    88,    88,    88,    89,    89,    90,    90,
      91,    91,    92
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     3,     3,     4,
       3,     4,     1,     3,     4,     6,     6,     4,     3,     4,
       3,     2,     2,     2,     1,     3,     3,     5,     1,     2,
       2,     2,     1,     1,     1,     1,     1,     1,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     4,     3,     4,     4,     4,     5,     3,     5,     1,
       3,     1,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     3,     3,     1,     3,
       3,     1,     4,     6,     4,     1,     1,     2,     2,     2,
       4,     3,     5,     5,     6,     1,     3,     1,     3,     1,
       3,     1,     4,     6,     4,     6,     1,     1,     1,     3,
       1,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {

#line 1361 "grammar.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 162 "grammar.y"

