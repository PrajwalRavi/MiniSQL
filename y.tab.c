/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "tokens.y" /* yacc.c:339  */

	#include<stdio.h>
	#include <stdlib.h>
	#include <string.h>

	int ind_condition = 0, ind_and_or = 0, ind_result = 0, ind_field=0;
	int emp_size = 0,dept_size = 0;
	char *file1 = "EMP.txt";
	char *file2 = "DEPT.txt";
	char conditions[100][100], field_list[100][100];
	int joiner[10],joiners[10],results[100]={0};
	char emp_fields[6][10] = {"eid","ename","eage","eaddress","salary","deptno"};
	char dept_fields[4][10] = {"dnum", "dname", "dlocation"};

	int check_conditions()
	{
		for(int k = ind_and_or-1;k >=0;k--)
			joiners[ind_and_or-k-1] = joiner[k];
		char condition[100];
		int result = 0;
		// Iterate over each condition
		for(int i=0; i<ind_condition; i++)
		{
			result = 0;
			strcpy(condition, conditions[i]);
			char* field = strtok(condition," ");
			for(int i=0; i<6; i++)
				if(strcmp(emp_fields[i],field)!=0)
					result = 1;
			if(result==0)
				break;
		}
		if(result==1)
			return 1;
		result = 1;
		for(int i=0; i<ind_condition; i++)
		{
			result = 0;
			strcpy(condition, conditions[i]);
			char* field = strtok(condition," ");
			for(int i=0; i<3; i++)
				if(strcmp(dept_fields[i],field)!=0)
					result =  1;
			if(result==0)
				return 0;
			// if(!(strcmp(field,"eid") || strcmp(field,"ename") || strcmp(field,"eage") || strcmp(field,"eaddress") || strcmp(field,"salary") || strcmp(field,"deptno")))
			// 	return 0;
			// if(!(strcmp(field,"dnum") || strcmp(field,"dname") || strcmp(field,"dlocation")))
			// 	return 0;
		}
		
		return 1;
	}

	void Delete(char *file,int res[100])
	{
		FILE *fp_temp = fopen("temp_file.txt","w");
		FILE *fp = fopen(file,"r");
		char record[100],line[100];
		int row = -1;
		if(strcmp(file,"DEPT.txt") == 0)
		{
			FILE *fp1 = fopen("EMP.txt","r");
			while (fgets(line,100,fp)!=NULL)
			{
				char original_line[100];
				strcpy(original_line,line);
				row++;
				if(res[row])
				{
					char* dsaveptr;
					char *dfields = strtok_r(line," ",&dsaveptr);
					int ddeptno = atoi(dfields);
					while(fgets(record,100,fp1) != NULL)
					{	
						int num_field = 0;
						char *esaveptr;
						char *efields = strtok_r(record," ",&esaveptr);
						while(num_field != 5)
						{	
							efields = strtok_r(NULL," ",&esaveptr);
							num_field++;
						}
						int edeptno = atoi(efields);
						if(edeptno == ddeptno)
						{
							printf("Cannot delete a reference to a foreign key!!\n");
							fprintf(fp_temp, "%s",original_line);	
						}

					}
					
				}
				else
				{
					fprintf(fp_temp,"%s",line);
				}
			}

			fclose(fp1);	
		}

		else
		{
			while (fgets(line,100,fp)!=NULL)
			{
				row++;
				if(!res[row])
					fprintf(fp_temp, "%s",line );
			
			}
		}
		fclose(fp);
		fclose(fp_temp);
		fp = fopen(file,"w");
		fp_temp = fopen("temp_file.txt","r");
		while (fgets(line,100,fp_temp)!=NULL)
			fprintf(fp, "%s",line );
		fclose(fp);
		fclose(fp_temp);
	}
	int Result(char * file,int ind_condition)
	{
		// printf("I sdfam here!!!!!!!!!\n");

		FILE *fp  = fopen(file,"r");
		char line[100], original_line[100];
		char *field_val;
		int row = -1,i = ind_condition;
		while (fgets(line,100,fp)!=NULL)	// Iterate over each record
		{
			row++;
			// printf("%d\n",row);
			strcpy(original_line,line);
			int field_num = 0;
			char* saveptr1;
			field_val = strtok_r(line," ",&saveptr1);

			while(field_val!=NULL)	// Iterate over each field in the record
			{
				// printf("infinite\n");
				char field_name[10];
				if(strcmp(file,"EMP.txt") == 0)
					strcpy(field_name,emp_fields[field_num]);
				else strcpy(field_name,dept_fields[field_num]);
				char condition[100];
				char* saveptr2;
				strcpy(condition, conditions[i]);
				char* operand1 = strtok_r(condition," ",&saveptr2);
				char* operator = strtok_r(NULL," ",&saveptr2);
				char* operand2 = strtok_r(NULL," ",&saveptr2);
				if(strcmp(operand1,field_name)==0)
				{
					// Checkg for integer fields
					// printf("sdfdsdf\n");
					int j = strcmp(file,"EMP.txt")==0?3:2;
					if(field_num!=1 && field_num!=j)
					{
						int op = atoi(operand2);
						int val = atoi(field_val);
						if((strcmp(operator,"==")==0 && op==val)
							|| (strcmp(operator,"!=")==0 && op!=val)
							|| (strcmp(operator,">=")==0 && op<=val)
							|| (strcmp(operator,"<=")==0 && op>=val)
							|| (strcmp(operator,">")==0 && op<val)
							|| (strcmp(operator,"<")==0 && op>val)
							)
						{
							results[row] = 1;
							// printf("Remove%d\n",row);
						}
						else 
						{
							results[row] = 0;
							// printf("Keep%d\n",row);
						}
					}
					// For strings
					else if((strcmp(operator,"==")==0 && strcmp(operand2,field_val)==0)
						|| (strcmp(operator,"!=")==0 && strcmp(operand2,field_val))
						|| (strcmp(operator,">=")==0 && strcmp(field_val,operand2)>=0)
						|| (strcmp(operator,"<=")==0 && strcmp(field_val,operand2)<=0)
						|| (strcmp(operator,">")==0 && strcmp(field_val,operand2)>0)
						|| (strcmp(operator,"<")==0 && strcmp(field_val,operand2)<0)
						)
					{
						results[row] = 1;
						// printf("Remove%d\n",row);
					}
					else 
					{
						results[row] = 0;
						// printf("Keep%d\n",row);
					}

				}
			field_num++;
			field_val = strtok_r(NULL," ",&saveptr1);
			}
		}
		fclose(fp);
		// printf("%d\n",row);
		// for(int k = 0;k <= row;k++){
		// 	printf("%d ",results[k]);
		// }
		printf("\n");
		return row;
					
	}

	void Select(char *file,int res[100])
	{
		FILE *fp = fopen(file,"r");
		FILE *view = fopen("Result.txt","w");
		char line[100],original_line[100];
		int row = -1;
		int field_num = -1;
		while(fgets(line,100,fp) != NULL)
		{	
			row++;
			if(!res[row]) continue;
			// printf("%d\n",row);
			strcpy(original_line,line);
			char *saveptr;
			char *fields = strtok_r(line," ",&saveptr);
			field_num = 0;
			while(fields != NULL)
			{
				if(strcmp(file,"EMP.txt") == 0)
				{
					for(int k = 0; k <ind_field;k++)
					{
						if(strcmp(field_list[k],emp_fields[field_num]) == 0)
						{
							// printf("sfdsdgsd\n");
							printf("%s ",fields);
						}
					}
				}
				else
				{
					for(int k = 0; k <ind_field;k++)
					{
						if(strcmp(field_list[k],dept_fields[field_num]) == 0)
						{
							printf("%s ",fields);
						}
					}
				}
				fields = strtok_r(NULL," ",&saveptr);
				field_num++;

			}
			printf("\n");

		}
		fclose(fp);
		fclose(view);
	}
	int check_uniqueness(char* file_name, char* value)
	{
		char line[100];
		char* field_val;
		FILE* fp = fopen(file_name,"r");
		while (fgets(line,100,fp)!=NULL)	// Iterate over each record
		{
			field_val = strtok(line," ");
			if(strcmp(field_val,value)==0)
				return 0;
		}
		return 1;
	}

#line 340 "y.tab.c" /* yacc.c:339  */

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
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    INSERT = 258,
    RECORD = 259,
    NUM = 260,
    GET = 261,
    AND = 262,
    OR = 263,
    UPDATE = 264,
    DELETE = 265,
    INTO = 266,
    SET = 267,
    TO = 268,
    WHERE = 269,
    FROM = 270,
    VAR = 271,
    STRING = 272,
    LB = 273,
    RB = 274,
    COLON = 275,
    REL_OP = 276
  };
#endif
/* Tokens.  */
#define INSERT 258
#define RECORD 259
#define NUM 260
#define GET 261
#define AND 262
#define OR 263
#define UPDATE 264
#define DELETE 265
#define INTO 266
#define SET 267
#define TO 268
#define WHERE 269
#define FROM 270
#define VAR 271
#define STRING 272
#define LB 273
#define RB 274
#define COLON 275
#define REL_OP 276

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 299 "tokens.y" /* yacc.c:355  */

		char str[200];              /* Ptr to constant string (strings are malloc'd) */
	

#line 427 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 444 "y.tab.c" /* yacc.c:358  */

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
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   48

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  22
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  9
/* YYNRULES -- Number of rules.  */
#define YYNRULES  19
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  52

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   276

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
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
      15,    16,    17,    18,    19,    20,    21
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   305,   305,   306,   307,   308,   309,   310,   311,   348,
     366,   430,   520,   521,   523,   530,   539,   540,   542,   543
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INSERT", "RECORD", "NUM", "GET", "AND",
  "OR", "UPDATE", "DELETE", "INTO", "SET", "TO", "WHERE", "FROM", "VAR",
  "STRING", "LB", "RB", "COLON", "REL_OP", "$accept", "STMT", "INS", "DEL",
  "SELECT", "CONDITIONS", "CONDITION", "JOINER", "FIELDLIST", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276
};
# endif

#define YYPACT_NINF -26

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-26)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       1,     2,   -15,     8,     5,     1,     1,     1,     0,   -15,
       4,     6,   -26,   -26,   -26,   -26,    15,   -26,     7,    10,
      11,    13,    16,    -3,    17,    17,    12,    18,    14,    19,
       9,    20,    26,    21,    -2,   -26,   -26,   -26,    17,   -26,
      29,    22,   -26,   -26,   -26,    23,    24,    25,   -26,    27,
      28,   -26
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     2,     3,     4,     0,    19,
       0,     0,     1,     5,     6,     7,     0,    18,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      13,     0,     0,     0,     0,    11,    16,    17,     0,    10,
       0,     0,    15,    14,    12,     0,     0,     0,     9,     0,
       0,     8
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -26,     3,   -26,   -26,   -26,   -25,   -26,   -26,    32
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,     7,    29,    30,    38,    10
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      31,     9,    26,    42,     1,    12,     8,     2,    13,    14,
      15,     3,    11,    44,    27,    43,    36,    37,    16,    18,
      20,    19,     0,    21,     0,     0,    22,    24,    23,    32,
      25,    40,    41,    28,    45,    34,    49,    33,    46,    35,
      39,    17,    47,    50,    48,     0,     0,     0,    51
};

static const yytype_int8 yycheck[] =
{
      25,    16,     5,     5,     3,     0,     4,     6,     5,     6,
       7,    10,     4,    38,    17,    17,     7,     8,    18,    15,
       5,    15,    -1,    16,    -1,    -1,    16,    14,    17,    17,
      14,     5,    11,    16,     5,    21,    11,    19,    16,    20,
      20,     9,    19,    16,    20,    -1,    -1,    -1,    20
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     6,    10,    23,    24,    25,    26,     4,    16,
      30,     4,     0,    23,    23,    23,    18,    30,    15,    15,
       5,    16,    16,    17,    14,    14,     5,    17,    16,    27,
      28,    27,    17,    19,    21,    20,     7,     8,    29,    20,
       5,    11,     5,    17,    27,     5,    16,    19,    20,    11,
      16,    20
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    22,    23,    23,    23,    23,    23,    23,    24,    24,
      25,    26,    27,    27,    28,    28,    29,    29,    30,    30
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     2,     2,     2,    13,    10,
       7,     7,     3,     1,     3,     3,     1,     1,     2,     1
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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                                              );
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 305 "tokens.y" /* yacc.c:1646  */
    {printf("Statement executed succesfully.\n");}
#line 1541 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 306 "tokens.y" /* yacc.c:1646  */
    {printf("Statement executed succesfully.\n");}
#line 1547 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 307 "tokens.y" /* yacc.c:1646  */
    {printf("Statement executed succesfully.\n");}
#line 1553 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 308 "tokens.y" /* yacc.c:1646  */
    {printf("Statement executed succesfully.\n");}
#line 1559 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 309 "tokens.y" /* yacc.c:1646  */
    {printf("Statement executed succesfully.\n");}
#line 1565 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 310 "tokens.y" /* yacc.c:1646  */
    {printf("Statement executed succesfully.\n");}
#line 1571 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 311 "tokens.y" /* yacc.c:1646  */
    {
		char *file_name = "EMP.txt";
		if(strcmp((yyvsp[-1].str),file_name))
		{
			printf("File doesn't exist\n");
			return 0;
		}
		if(!check_uniqueness(file_name,(yyvsp[-9].str)))
		{
			printf("Eid should be unique\n");
			return 0;
		}
		
		// Check foreign-key constraint
		FILE* dept_fp = fopen("DEPT.txt","r");
		char line[100];
		char* field_val;
		int flag = 1;
		while (fgets(line,100,dept_fp)!=NULL)	// Iterate over each record
		{
			field_val = strtok(line," ");
			if(strcmp(field_val,(yyvsp[-4].str))==0)
			{
				flag=0;
				break;
			}
		}
		if(flag)
		{
			printf("Foreign-key constraint violated\n");
			return 0;
		}

		FILE *fp = fopen((yyvsp[-1].str),"a");
		fprintf(fp, "%s %s %s %s %s %s\n",(yyvsp[-9].str),(yyvsp[-8].str),(yyvsp[-7].str),(yyvsp[-6].str),(yyvsp[-5].str),(yyvsp[-4].str) );
		emp_size++;
		fclose(fp);
	}
#line 1614 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 348 "tokens.y" /* yacc.c:1646  */
    {
		char *file_name = "DEPT.txt";
		if(strcmp((yyvsp[-1].str),file_name))
		{
			printf("File doesn't exist\n");
			return 0;
		}
		if(!check_uniqueness(file_name,(yyvsp[-6].str)))
		{
			printf("Deptno should be unique\n");
			return 0;
		}		
		FILE *fp = fopen((yyvsp[-1].str),"a");
		fprintf(fp, "%s %s %s\n",(yyvsp[-6].str),(yyvsp[-5].str),(yyvsp[-4].str));
		dept_size++;
		fclose(fp);
	}
#line 1636 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 366 "tokens.y" /* yacc.c:1646  */
    {
		if(strcmp((yyvsp[-3].str),"EMP.txt")!=0 && strcmp((yyvsp[-3].str),"DEPT.txt")!=0)
		{
			printf("File doesn't exist\n");
			return 0;
		}
		if(check_conditions()==0)
		{
			printf("Error in conditions\n");
			return 0; 
		}
		
		
		// Doing for Ands first
		if(ind_and_or==0)
		{
			int row = Result((yyvsp[-3].str),0);
			Delete((yyvsp[-3].str),results);
		}
		for(int o=0;o<ind_and_or;o++)
		{
			if(joiners[o]==0)
				continue;
			else
			{
				int and_r[100], row = -1;
				for(int ii=0;ii<100;ii++)
					and_r[ii]=1;
				while(joiners[o]==1)
				{
					for(int i=o; i<o+2; i++)
					{
						// printf("jkfnje\n");
						row = Result((yyvsp[-3].str),i);
						for(int k = 0;k<=row;k++)
						{
							and_r[k] *= results[k];
						}
					}
					o++;
				}
				Delete((yyvsp[-3].str),and_r);
		
		 	}
		 }

		// Doing  for Ors
		for(int o=0;o<ind_and_or;o++)
		{
			if(joiners[o]==1)
				continue;
			if(joiners[o]==0 && o==0)
			{
				int row = Result((yyvsp[-3].str),o);
				Delete((yyvsp[-3].str),results);
			}
			if(joiners[o]==0 && ((joiners[o+1]==0 && o+1<ind_and_or) || o==ind_and_or-1)) 
			{
				int row = Result((yyvsp[-3].str),o+1);
				Delete((yyvsp[-3].str),results);
			}		
		}
	}
#line 1704 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 430 "tokens.y" /* yacc.c:1646  */
    {
	if(strcmp((yyvsp[-3].str),"EMP.txt")!=0 && strcmp((yyvsp[-3].str),"DEPT.txt")!=0)
	{
		printf("File doesn't exist\n");
		return 0;
	}
	if(check_conditions()==0)
	{
		printf("Error in conditions\n");
		return 0; 
	}
	//Evaluate select for AND's first
	// FILE *fpres = fopen("Result.txt","r");
	int and_r[100],final_r[100];
	for(int ii=0;ii<100;ii++)
		final_r[ii]=1;
	// printf("%d\n",ind_and_or);
	int row = -1;
	if(ind_and_or==0)
	{
		int row = Result((yyvsp[-3].str),0);
		// printf("%d\n",row);
		// Select($4,results);
		for(int k = 0; k <= row ;k++)
	 		{
	 			final_r[k] = results[k];
	 			// printf("%d\n",results[k]);
	 		}

	}
	for(int o=0;o<ind_and_or;o++)
	{
		if(joiners[o]==0)
			continue;
		else
		{
			for(int ii=0;ii<100;ii++)
				and_r[ii]=1;
			while(joiners[o]==1)
			{
				for(int i=o; i<o+2; i++)
				{
					// printf("jkfnje\n");
					row = Result((yyvsp[-3].str),i);
					for(int k = 0;k<=row;k++)
					{
						and_r[k] *= results[k];
					}
				}
				o++;
			}
			for(int k = 0; k <=row ;k++)
			{
				final_r[k] |= and_r[k];
			}
	
	 	}
	 }
	 for(int o=0;o<ind_and_or;o++)
	 {
	 	if(joiners[o]==1)
	 		continue;
	 	if(joiners[o]==0 && o==0)
	 	{
	 		row = Result((yyvsp[-3].str),o);
	 		for(int k = 0; k <100;k++)
	 		{
	 			final_r[k] |= results[k];
	 		}
	 		
	 		// Delete($4,results);
	 	}
	 	if(joiners[o]==0 && ((joiners[o+1]==0 && o+1<ind_and_or) || o==ind_and_or-1)) 
	 	{
	 		row = Result((yyvsp[-3].str),o+1);
	 		for(int k = 0; k <100;k++)
	 		{
	 			final_r[k] |= results[k];
	 		}
	 		
	 		// Delete($4,results);
	 	}		
	 }
	 for(int k = 0;k<=row;k++)
	 {
	 	printf("%d\n",final_r[k]);
	 }
	 Select((yyvsp[-3].str),final_r);
}
#line 1798 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 520 "tokens.y" /* yacc.c:1646  */
    {strcpy(conditions[ind_condition++],(yyvsp[-2].str));}
#line 1804 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 521 "tokens.y" /* yacc.c:1646  */
    {strcpy(conditions[ind_condition++],(yyvsp[0].str));}
#line 1810 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 523 "tokens.y" /* yacc.c:1646  */
    {
		strcpy((yyval.str),(yyvsp[-2].str));
		strcat((yyval.str)," ");
		strcat((yyval.str),(yyvsp[-1].str));
		strcat((yyval.str)," ");
		strcat((yyval.str),(yyvsp[0].str));
		}
#line 1822 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 530 "tokens.y" /* yacc.c:1646  */
    {
		strcpy((yyval.str),(yyvsp[-2].str));
		strcat((yyval.str)," ");
		strcat((yyval.str),(yyvsp[-1].str));
		strcat((yyval.str)," ");
		strcat((yyval.str),(yyvsp[0].str));
		}
#line 1834 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 539 "tokens.y" /* yacc.c:1646  */
    { joiner[ind_and_or++] = 1; }
#line 1840 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 540 "tokens.y" /* yacc.c:1646  */
    { joiner[ind_and_or++] = 0; }
#line 1846 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 542 "tokens.y" /* yacc.c:1646  */
    {strcpy(field_list[ind_field++],(yyvsp[-1].str));}
#line 1852 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 543 "tokens.y" /* yacc.c:1646  */
    {strcpy(field_list[ind_field++],(yyvsp[0].str)); }
#line 1858 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1862 "y.tab.c" /* yacc.c:1646  */
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
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 544 "tokens.y" /* yacc.c:1906  */
