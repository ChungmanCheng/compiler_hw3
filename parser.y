%{
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "loc.h"
#include "ast.h"
#include "error.h"
#include "loc.h"
#include "addnode.h"
#include "argumentsnode.h"
#include "boolexpnode.h"
#include "compoundstatementnode.h"
#include "declarnode.h"
#include "explistnode.h"
#include "expnode.h"
#include "factornode.h"
#include "identlistnode.h"
#include "mulnode.h"
#include "optionalstatementsnode.h"
#include "optionalvarnode.h"
#include "parameterlistnode.h"
#include "procedstatementnode.h"
#include "prognode.h"
#include "relopnode.h"
#include "simpleexpnode.h"
#include "standtypenode.h"
#include "statementlistnode.h"
#include "statementnode.h"
#include "subdeclarnode.h"
#include "subheadnode.h"
#include "tailnode.h"
#include "termnode.h"
#include "typenode.h"
#include "varnode.h"
#include "numnode.h"

#define YYLTYPE LocType
#define MAX_LINE_LENG      256

extern int line_no, chr_no, opt_list;
extern char buffer[MAX_LINE_LENG];
extern FILE *yyin;        /* declared by lex */
extern char *yytext;      /* declared by lex */
extern int yyleng;

static Node* root = NULL;
int scope = 0;

extern int yylex(void);
static void yyerror(const char *msg);
%}

%locations

%token PROGRAM VAR ARRAY OF INTEGER REAL STRING FUNCTION PROCEDURE PBEGIN END IF THEN ELSE WHILE DO NOT AND OR

%token LPAREN RPAREN SEMICOLON DOT COMMA COLON LBRACE RBRACE DOTDOT ASSIGNMENT ADDOP SUBOP MULOP DIVOP LTOP GTOP EQOP GETOP LETOP NEQOP

%token IDENTIFIER REALNUMBER INTEGERNUM SCIENTIFIC LITERALSTR

%code requires{
    #include "ast.h"
}

%union {
    int val;
    char* text;
    double dval;
    Node* node;
}

%type <node> prog identifier_list declarations subprogram_declarations compound_statement type standard_type subprogram_declaration subprogram_head arguments parameter_list optinal_var optinal_statements statement_list statement variable tail procdure_statement expression_list expression boolexpression simple_expression term factor addop mulop relop num
%type <text> IDENTIFIER SCIENTIFIC LITERALSTR LPAREN RPAREN SEMICOLON DOT COMMA COLON LBRACE RBRACE DOTDOT ASSIGNMENT ADDOP SUBOP MULOP DIVOP LTOP GTOP EQOP GETOP LETOP NEQOP
%type <val> INTEGERNUM
%type <dval> REALNUMBER

%start prog

%%

    /* define your snytax here */

    /* @n return the sturct LocType of "n-th node", 
    ex: @1 return the PROGRAM nodes locType
       $n return the $$ result you assigned to the rule, ex: $1 
    */
    
prog: PROGRAM IDENTIFIER LPAREN identifier_list RPAREN SEMICOLON declarations subprogram_declarations compound_statement DOT { 
        /*
        yylval.val, yylval.text, yylval.dval to get the data (type defined in %union) you assigned by scanner.
        */
        // printf("program node is @ line: %d, column: %d\n", @1.first_line, @1.first_column);
        root = newProgNode( @1.first_line, @1.first_column, $2, $4, $7, $8, $9, @10.first_line, @10.first_column );
    }
    ;

identifier_list: IDENTIFIER { $$ = newIdentListNode( @1.first_line, @1.first_column, $1, NULL, @1.first_line, @1.first_column ); }
    | IDENTIFIER COMMA identifier_list { $$ = newIdentListNode( @1.first_line, @1.first_column, $1, $3, @1.first_line, @1.first_column ); }
    ;

declarations: declarations VAR identifier_list COLON type SEMICOLON { $$ = newDeclarNode( @1.first_line, @1.first_column, $1, $3, $5, @6.first_line, @6.first_column ); }
    | { $$ = NULL; }
    ;

type: standard_type { $$ = newTypeNode( @1.first_line, @1.first_column, $1, 0, 0, NULL, @1.first_line, @1.first_column ); }
    | ARRAY LBRACE INTEGERNUM DOTDOT INTEGERNUM RBRACE OF type { $$ = newTypeNode( @1.first_line, @1.first_column, NULL, $3, $5, $8, @8.first_line, @8.first_column ); }
    ;

standard_type: INTEGER { $$ = newStandTypeNode( @1.first_line, @1.first_column, 0, @1.first_line, @1.first_column ); }
    | REAL { $$ = newStandTypeNode( @1.first_line, @1.first_column, 1, @1.first_line, @1.first_column ); }
    | STRING { $$ = newStandTypeNode( @1.first_line, @1.first_column, 2, @1.first_line, @1.first_column ); }
    ;

subprogram_declarations: subprogram_declarations subprogram_declaration SEMICOLON { $$ = newSubDeclarSNode( @1.first_line, @1.first_column, $1, $2, @3.first_line, @3.first_column ); }
    | { $$ = NULL; }
    ;

subprogram_declaration: subprogram_head declarations subprogram_declarations compound_statement { $$ = newSubDeclarNode( @1.first_line, @1.first_column, $1, $2, $3, $4, @4.first_line, @4.first_column ); }
    ;

subprogram_head: FUNCTION IDENTIFIER arguments COLON standard_type SEMICOLON { $$ = newSubHeadNode( @1.first_line, @1.first_column, 0, $2, $5, $3, @6.first_line, @6.first_column ); }
    | PROCEDURE IDENTIFIER arguments SEMICOLON { $$ = newSubHeadNode( @1.first_line, @1.first_column, 1, $2, NULL, $3, @4.first_line, @4.first_column ); }
    ;

arguments: LPAREN parameter_list RPAREN { $$ = newArgumentsNode( @1.first_line, @1.first_column, $2, @3.first_line, @3.first_column ); }
    | { $$ = NULL; }
    ;

parameter_list: optinal_var identifier_list COLON type { $$ = newParameterListNode( @1.first_line, @1.first_column, $1, $2, $4, NULL, @4.first_line, @4.first_column ); }
    | optinal_var identifier_list COLON type SEMICOLON parameter_list { $$ = newParameterListNode( @1.first_line, @1.first_column, $1, $2, $4, $6, @6.first_line, @6.first_column ); }
    ;

optinal_var: VAR { $$ = newOptionalVarNode( @1.first_line, @1.first_column ); }
    | { $$ = NULL; }
    ;

compound_statement: PBEGIN optinal_statements END { $$ = newCompoundStatementNode( @1.first_line, @1.first_column, $2, @3.first_line, @3.first_column ); }
    ;

optinal_statements: statement_list { $$ = newOptionalStatementSNode( @1.first_line, @1.first_column, $1, @1.first_line, @1.first_column ); }
    | { $$ = NULL; }
    ;

statement_list: statement { $$ = newStatementListNode( @1.first_line, @1.first_column, NULL, $1, @1.first_line, @1.first_column ); }
    | statement_list SEMICOLON statement { $$ = newStatementListNode( @1.first_line, @1.first_column, $1, $3, @1.first_line, @1.first_column ); }
    ;

statement: variable ASSIGNMENT expression { $$ = newStatementNode( @1.first_line, @1.first_column, 0, $1, $3, NULL, NULL, NULL, NULL, @3.first_line, @3.first_column ); }
    | procdure_statement { $$ = newStatementNode( @1.first_line, @1.first_column, 1, NULL, NULL, $1, NULL, NULL, NULL, @1.first_line, @1.first_column ); }
    | compound_statement { $$ = newStatementNode( @1.first_line, @1.first_column, 2, NULL, NULL, NULL, $1, NULL, NULL, @1.first_line, @1.first_column ); }
    | IF expression THEN statement ELSE statement { $$ = newStatementNode( @1.first_line, @1.first_column, 3, NULL, $2, NULL, NULL, $4, $6, @6.first_line, @6.first_column ); }
    | WHILE expression DO statement { $$ = newStatementNode( @1.first_line, @1.first_column, 4, NULL, $2, NULL, NULL, $4, NULL, @4.first_line, @4.first_column ); }
    | { $$ = NULL; }
    ;

variable: IDENTIFIER tail { $$ = newVarNode( @1.first_line, @1.first_column, $1, $2, @2.first_line, @2.first_column ); }
    ;

tail: LBRACE expression RBRACE tail { $$ = newTailNode( @1.first_line, @1.first_column, $2, $4, @4.first_line, @4.first_column ); }
    | { $$ = NULL; }
    ;

procdure_statement: IDENTIFIER { $$ = newProcedStatementNode( @1.first_line, @1.first_column, $1, NULL, @1.first_line, @1.first_column ); }
    | IDENTIFIER LPAREN expression_list RPAREN { $$ = newProcedStatementNode( @1.first_line, @1.first_column, $1, $3, @4.first_line, @4.first_column ); }
    ;

expression_list: expression { $$ = newExpListNode( @1.first_line, @1.first_column, NULL, $1, @1.first_line, @1.first_column ); }
    | expression_list COMMA expression { $$ = newExpListNode( @1.first_line, @1.first_column, $1, $3, @3.first_line, @3.first_column ); }
    ;

expression: boolexpression { $$ = newExpNode( @1.first_line, @1.first_column, $1, 0, NULL, @1.first_line, @1.first_column ); }
    | boolexpression AND boolexpression { $$ = newExpNode( @1.first_line, @1.first_column, $1, 1, $3, @3.first_line, @3.first_column ); }
    | boolexpression OR boolexpression { $$ = newExpNode( @1.first_line, @1.first_column, $1, 2, $3, @3.first_line, @3.first_column ); }
    ;

boolexpression: simple_expression { $$ = newBoolExpNode( @1.first_line, @1.first_column, $1, NULL, NULL, @1.first_line, @1.first_column ); }
    | simple_expression relop simple_expression { $$ = newBoolExpNode( @1.first_line, @1.first_column, $1, $2, $3, @3.first_line, @3.first_column ); }
    ;

simple_expression: term { $$ = newSimpleExpNode( @1.first_line, @1.first_column, NULL, NULL, $1, @1.first_line, @1.first_column ); }
    | simple_expression addop term { $$ = newSimpleExpNode( @1.first_line, @1.first_column, $1, $2, $3, @3.first_line, @3.first_column ); }
    ;

term: factor { $$ = newTermNode( @1.first_line, @1.first_column, NULL, NULL, $1, @1.first_line, @1.first_column ); }
    | term mulop factor { $$ = newTermNode( @1.first_line, @1.first_column, $1, $2, $3, @3.first_line, @3.first_column ); }
    ;

factor: IDENTIFIER tail { $$ = newFactorNode( @1.first_line, @1.first_column, 0, $1, NULL, NULL, NULL, NULL, @2.first_line, @2.first_column ); }
    | IDENTIFIER LPAREN expression_list RPAREN { $$ = newFactorNode( @1.first_line, @1.first_column, 1, $1, $3, NULL, NULL, NULL, @4.first_line, @4.first_column ); }
    | num { $$ = newFactorNode( @1.first_line, @1.first_column, 2, NULL, NULL, $1, NULL, NULL, @1.first_line, @1.first_column ); }
    | LITERALSTR { $$ = newFactorNode( @1.first_line, @1.first_column, 3, $1, NULL, NULL, NULL, NULL, @1.first_line, @1.first_column ); }
    | LPAREN expression RPAREN { $$ = newFactorNode( @1.first_line, @1.first_column, 4, NULL, NULL, NULL, $2, NULL, @3.first_line, @3.first_column ); }
    | NOT factor { $$ = newFactorNode( @1.first_line, @1.first_column, 5, NULL, NULL, NULL, NULL, NULL, @2.first_line, @2.first_column ); }
    | SUBOP factor { $$ = newFactorNode( @1.first_line, @1.first_column, 6, NULL, NULL, NULL, NULL, $2, @2.first_line, @2.first_column ); }
    ;

addop: ADDOP { $$ = newAddNode( @1.first_line, @1.first_column, 1, @1.first_line, @1.first_column ); }
    | SUBOP { $$ = newAddNode( @1.first_line, @1.first_column, 0, @1.first_line, @1.first_column ); }
    ;

mulop: MULOP { $$ = newMulNode( @1.first_line, @1.first_column, 0, @1.first_line, @1.first_column ); }
    | DIVOP { $$ = newMulNode( @1.first_line, @1.first_column, 1, @1.first_line, @1.first_column ); }
    ;

relop: LTOP { $$ = newRelopNode( @1.first_line, @1.first_column, 0, @1.first_line, @1.first_column ); }
    | GTOP { $$ = newRelopNode( @1.first_line, @1.first_column, 1, @1.first_line, @1.first_column ); }
    | EQOP { $$ = newRelopNode( @1.first_line, @1.first_column, 2, @1.first_line, @1.first_column ); }
    | GETOP { $$ = newRelopNode( @1.first_line, @1.first_column, 3, @1.first_line, @1.first_column ); }
    | LETOP { $$ = newRelopNode( @1.first_line, @1.first_column, 4, @1.first_line, @1.first_column ); }
    | NEQOP { $$ = newRelopNode( @1.first_line, @1.first_column, 5, @1.first_line, @1.first_column ); }
    ;

num: REALNUMBER { $$ = newNumNode( @1.first_line, @1.first_column, 0, $1, NULL, @1.first_line, @1.first_column ); }
    | INTEGERNUM { $$ = newNumNode( @1.first_line, @1.first_column, 1, $1, NULL, @1.first_line, @1.first_column ); }
    | SCIENTIFIC { $$ = newNumNode( @1.first_line, @1.first_column, 2, 0, $1, @1.first_line, @1.first_column ); }
    ;

%%

void yyerror(const char *msg) {
    fprintf(stderr,
            "[ERROR] line %4d:%3d %s, Unmatched token: %s\n",
            line_no, chr_no-(int)yyleng+1, buffer, yytext);
}

int main(int argc, const char *argv[]) {

    if(argc > 2)
        fprintf( stderr, "Usage: ./parser [filename]\n" ), exit(0);

    FILE *fp = argc == 1 ? stdin : fopen(argv[1], "r");

    if(fp == NULL)
        fprintf( stderr, "Open file error\n" ), exit(-1);

    yyin = fp;
    yyparse();

    if (root){
        // construct symbol by travsersing AST
        root->visit(root);
    }

    return 0;
}
