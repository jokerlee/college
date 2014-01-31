%{
    #include "y.tab.h"
    #include "symtab.h"
    #include <stdlib.h>
    extern FILE * yyout;
%}

digit   [0-9]
letter  [_a-zA-Z]
integer {digit}+
real    ({digit}+)|({digit}*(\.{digit}+)([Ee][+\-]?{digit}+)?)
id      {letter}({letter}|{digit})*

%%

[ \t]+  {}
[\n]    { return '\n'; } 
"+"     { return '+'; }
"-"     { return '-'; }
"*"     { return '*'; }
"/"     { return '/'; }
"="     { return '='; }
"("     { return '('; }
")"     { return ')'; }

{integer}   {yylval.val = atoi(yytext); return NUM;}
{real}      {yylval.val = atof(yytext); return NUM;}
{id}        {yylval.symp = symlook(yytext); return NAME;}

.       { yyerror("syntax error."); return 0; }

%%

int yywrap()
{
    return 1;
}

int yyerror(char * s)
{
    fprintf(stderr, "%s\n", s);
    return 0;
}
