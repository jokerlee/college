#ifndef _EXP2_SYMTAB_H_JACKAL_
#define _EXP2_SYMTAB_H_JACKAL_

#define SYM_NR 100

//enum type{INT, REAL};

struct symtab {
    char * name;
    double val;
}symtab[SYM_NR];

int yywarp(void);
int yyerror(char *s);
struct symtab * symlook(char * s);

#endif
