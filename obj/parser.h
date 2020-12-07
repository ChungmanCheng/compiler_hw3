/* A Bison parser, made by GNU Bison 3.7.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_OBJ_PARSER_H_INCLUDED
# define YY_YY_OBJ_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 62 "parser.y"

    #include "ast.h"

#line 53 "obj/parser.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    PROGRAM = 258,                 /* PROGRAM  */
    VAR = 259,                     /* VAR  */
    ARRAY = 260,                   /* ARRAY  */
    OF = 261,                      /* OF  */
    INTEGER = 262,                 /* INTEGER  */
    REAL = 263,                    /* REAL  */
    STRING = 264,                  /* STRING  */
    FUNCTION = 265,                /* FUNCTION  */
    PROCEDURE = 266,               /* PROCEDURE  */
    PBEGIN = 267,                  /* PBEGIN  */
    END = 268,                     /* END  */
    IF = 269,                      /* IF  */
    THEN = 270,                    /* THEN  */
    ELSE = 271,                    /* ELSE  */
    WHILE = 272,                   /* WHILE  */
    DO = 273,                      /* DO  */
    NOT = 274,                     /* NOT  */
    AND = 275,                     /* AND  */
    OR = 276,                      /* OR  */
    LPAREN = 277,                  /* LPAREN  */
    RPAREN = 278,                  /* RPAREN  */
    SEMICOLON = 279,               /* SEMICOLON  */
    DOT = 280,                     /* DOT  */
    COMMA = 281,                   /* COMMA  */
    COLON = 282,                   /* COLON  */
    LBRACE = 283,                  /* LBRACE  */
    RBRACE = 284,                  /* RBRACE  */
    DOTDOT = 285,                  /* DOTDOT  */
    ASSIGNMENT = 286,              /* ASSIGNMENT  */
    ADDOP = 287,                   /* ADDOP  */
    SUBOP = 288,                   /* SUBOP  */
    MULOP = 289,                   /* MULOP  */
    DIVOP = 290,                   /* DIVOP  */
    LTOP = 291,                    /* LTOP  */
    GTOP = 292,                    /* GTOP  */
    EQOP = 293,                    /* EQOP  */
    GETOP = 294,                   /* GETOP  */
    LETOP = 295,                   /* LETOP  */
    NEQOP = 296,                   /* NEQOP  */
    IDENTIFIER = 297,              /* IDENTIFIER  */
    REALNUMBER = 298,              /* REALNUMBER  */
    INTEGERNUM = 299,              /* INTEGERNUM  */
    SCIENTIFIC = 300,              /* SCIENTIFIC  */
    LITERALSTR = 301               /* LITERALSTR  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 66 "parser.y"

    int val;
    char* text;
    double dval;
    Node* node;

#line 123 "obj/parser.h"

};
typedef union YYSTYPE YYSTYPE;
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

#endif /* !YY_YY_OBJ_PARSER_H_INCLUDED  */
