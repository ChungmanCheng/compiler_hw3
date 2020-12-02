%{
/*
 * scanner.l
 *
 * lex input file for pascal scanner
 *
 */

#include <stdio.h>
#include "parser.h"

#define YY_USER_ACTION \
    chr_no += yyleng; \
    yylloc.first_line = line_no; \
    yylloc.first_column = chr_no - yyleng;

#define MAX_LINE_LENG      256
#define LIST       strcat(buffer, yytext)
#define LIST_FLUSH { if(opt_list) printf("%s", buffer); *buffer = 0; }
#define LOG(TYPE) { LIST; if (opt_list_token) fprintf(stderr, "token(type:%-10s) on line %4d, %3d : %s\n", #TYPE, line_no, chr_no - yyleng + 1, yytext); }
#define COMME(STR) { LIST; if (opt_list_token) fprintf(stderr, "[INFO ] line %4d:%3d comment string%s\n", line_no, chr_no - yyleng + 1,#STR); }

int opt_list = 1;
int opt_list_token = 0;
int line_no = 1, chr_no = 0;
char buffer[MAX_LINE_LENG];

%}

%option nounput
%option noinput

A [aA]
B [bB]
C [cC]
D [dD]
E [eE]
F [fF]
G [gG]
H [hH]
I [iI]
J [jJ]
K [kK]
L [lL]
M [mM]
N [nN]
O [oO]
P [pP]
Q [qQ]
R [rR]
S [sS]
T [tT]
U [uU]
V [vV]
W [wW]
X [xX]
Y [yY]
Z [zZ]

%x _comment
%x _token
%%
                             /* v could do something */
{P}{R}{O}{G}{R}{A}{M}       {LOG(KEYWORD); return(PROGRAM);    }
{V}{A}{R}                   {LOG(KEYWORD); return(VAR);        }
{A}{R}{R}{A}{Y}             {LOG(KEYWORD); return(ARRAY);      }
{O}{F}                      {LOG(KEYWORD); return(OF);         }
{I}{N}{T}{E}{G}{E}{R}       {LOG(KEYWORD); return(INTEGER);    }
{R}{E}{A}{L}                {LOG(KEYWORD); return(REAL);       }
{S}{T}{R}{I}{N}{G}          {LOG(KEYWORD); return(STRING);     }
{F}{U}{N}{C}{T}{I}{O}{N}    {LOG(KEYWORD); return(FUNCTION);   }
{P}{R}{O}{C}{E}{D}{U}{R}{E} {LOG(KEYWORD); return(PROCEDURE);  }
{B}{E}{G}{I}{N}             {LOG(KEYWORD); return(PBEGIN);     }
{E}{N}{D}                   {LOG(KEYWORD); return(END);        }
{I}{F}                      {LOG(KEYWORD); return(IF);         }
{T}{H}{E}{N}                {LOG(KEYWORD); return(THEN);       }
{E}{L}{S}{E}                {LOG(KEYWORD); return(ELSE);       }
{W}{H}{I}{L}{E}             {LOG(KEYWORD); return(WHILE);      }
{D}{O}                      {LOG(KEYWORD); return(DO);         }
{N}{O}{T}                   {LOG(KEYWORD); return(NOT);        }
{A}{N}{D}                   {LOG(KEYWORD); return(AND);        }
{O}{R}                      {LOG(KEYWORD); return(OR);         }

"("                         { LOG(KEYWORD); return(LPAREN);     }
")"                         { LOG(KEYWORD); return(RPAREN);     }
";"                         { LOG(KEYWORD); return(SEMICOLON);  }
"."                         { LOG(KEYWORD); return(DOT);        }
","                         { LOG(KEYWORD); return(COMMA);      }
":"                         { LOG(KEYWORD); return(COLON);      }
"["                         { LOG(KEYWORD); return(LBRACE);     }
"]"                         { LOG(KEYWORD); return(RBRACE);     }
".."                        { LOG(KEYWORD); return(DOTDOT);     }
":="                        { LOG(KEYWORD); return(ASSIGNMENT); }
"+"                         { LOG(KEYWORD); return(ADDOP);      }
"-"                         { LOG(KEYWORD); return(SUBOP);      }
"*"                         { LOG(KEYWORD); return(MULOP);      }
"/"                         { LOG(KEYWORD); return(DIVOP);      }
">"                         { LOG(KEYWORD); return(GTOP);       }
"<"                         { LOG(KEYWORD); return(LTOP);       }
"="                         { LOG(KEYWORD); return(EQOP);       }
">="                        { LOG(KEYWORD); return(GETOP);      }
"<="                        { LOG(KEYWORD); return(LETOP);      }
"!="                        { LOG(KEYWORD); return(NEQOP);      }

 /*
    yylval.text = strdup, strndup ... (yytext)
    yylval.dval = atoi, atof, strtod, strtol ... (yytext)
 */

  /* define identifier here */
[a-z]|([a-z][a-zA-Z0-9_]*[a-zA-Z0-9]) { yylval.text = strdup(yytext); LOG(IDENTIFIER); return(IDENTIFIER); }

  /* define INTEGERNUM, REALNUMBER, SCIENTIFIC here */
[0-9]+                 { yylval.val = atoi(yytext); LOG(NUMBER); return(INTEGERNUM); }
[0-9]+[.][0-9]+        { yylval.dval = atof(yytext); LOG(NUMBER); return(REALNUMBER); }
[0-9]+([.][0-9]+)?{E}[+-]?[0-9]+  { yylval.text = strdup(yytext); LOG(NUMBER); return(SCIENTIFIC); }

  /* define single/multiple line comment here */
[/][/][^\n]*            { COMME(); }
[/][*]                  { COMME(\ start); BEGIN(_comment); LIST_FLUSH; }
<_comment>(^[*]^[/]|^\n)* { LIST; }
<_comment>\n            { LIST; LIST_FLUSH; line_no++, chr_no = 0; }
<_comment>[*][/]        { COMME(\ end); BEGIN(INITIAL); }

  /* define string constant (LITERALSTR) here */
["][^"]*["]                    { LOG(STRING); return(LITERALSTR); }

  /* define pragma here */
[#][ \t]*"pragma"[ \t]*"list"[ \t]*"on"  { LIST; opt_list = 1; }
[#][ \t]*"pragma"[ \t]*"list"[ \t]*"off" { LIST; opt_list = 0; }
[#][ \t]*"pragma"[ \t]*"token"[ \t]*"on" { LIST; opt_list_token = 1; }
[#][ \t]*"pragma"[ \t]*"token"[ \t]*"off" { LIST; opt_list_token = 0; }

[ \t\f\r]    LIST;

\n {
  LIST;
  LIST_FLUSH;
  line_no++, chr_no = 0;
}

.  { LIST; fprintf(stderr, "[ERROR] line %4d:%3d lexical analyzer error %s\n", line_no, chr_no-(int)yyleng+1, yytext); }

