%{
    #include "symtab.h"
    #include <stdio.h>
    #include <string.h>
    
    extern FILE * yyout;
%}

%union {
    double val;
    struct symtab * symp;
}

%token <val> NUM
%token <symp> NAME

%type <val> FACT
%type <val> EXPR
%type <val> TERM

%%

LINE : LINE EXPR '\n'
     | EXPR '\n'
     | LINE '\n'
     | '\n'
     ;
/*
STAT : NAME '=' EXPR { $1->val = $3; yprintf("id = expr"); }
     | EXPR { yprintf(""); }
     ;
*/

EXPR : EXPR '+' TERM { $$ = $1 + $3; yprintf("E -> E + T"); }
     | EXPR '-' TERM { $$ = $1 - $3; yprintf("E -> E - T"); }
     | TERM { $$ = $1; yprintf("E -> T"); }
     ;

TERM : TERM '*' FACT  { $$ = $1 * $3; yprintf("T -> T * F"); }  
     | TERM '/' FACT        
         {            
            if ($3 == 0.0)
                yyerror("Error, divide by zero.");
            else         
                $$ = $1 / $3;
            yprintf("T -> T / F");
         }          
     | FACT { $$ = $1; yprintf("T -> F"); }
     ;

FACT : NAME { $$ = $1->val; yprintf("F -> id"); }
     | '(' EXPR ')' { $$ = $2; yprintf("F -> (E)"); }
     | NUM { yprintf("F -> num"); }
     ;
%%

#include "lex.yy.c"

int yprintf(char * s)
{
    fprintf(yyout, "%s\n", s);
}

struct symtab * symlook(char * s)
{
    char * p;
    struct symtab * sp;
    for (sp = symtab; sp < &symtab[SYM_NR]; ++sp) {
        if (sp->name && !strcmp(sp->name, s))
            return sp;
        
        if (!sp->name) {
            sp->name = strdup(s);
            return sp;
        }
    }
    yyerror("Too many symbols.");
    exit(1);
}


int main(int argc, char * argv[])
{
    yyin = stdin;
    yyout = stdout;
    while (!feof(yyin)) {
        yyparse();
    }

    return 0;
}
