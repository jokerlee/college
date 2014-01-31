%{
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

void install_num(char * token);
void install_str(char * token);
void install_opt(char * token);
void install_id(char * token);
int is_existed(string token);

vector<string>  id_table, kw_table, opt_table, num_table, str_table;
int lineCnt = 1, wlineCnt = 0, punctCnt = 0;
%}

/* Regex Defination */
ws	    [\t ]+
wl      ^[\t ]*\n
eol     \n
punct   [,;{}]
letter	[_A-Za-z]
digit	[0-9]
string  \".*[^\\]\"
char    '.*'
id	    {letter}({letter}|{digit})*
num	    -?({digit}+)|({digit}*(\.{digit}+)([Ee][+\-]?{digit}+)?)
opt     \(|\)|\.|\+[=+]?|-[-=]?|\*[=]?|\/[=]?|%[=]?|\[|\]|(![=]?)|(<[<=]?)|(>[>=]?)|(&[&=]?)|(\|[|=]?)|(^[=]?)|(sizeof)|(=[=]?)
macro   #.*{eol}
comment (\/\*[^\\]*\*\/)|(\/\/[^\n]*)

%%
{wl}            {wlineCnt++;}
{eol}           {lineCnt++;}
{punct}         {punctCnt++;}
{comment}       {fprintf(yyout, "{comment} ");}
{string}|{char} {install_str(yytext);}
{macro}         {fprintf(yyout, "{macro} ");}
{ws}           	{}
{id}	        {install_id(yytext);}
{num}	        {install_num(yytext);}
{opt}           {install_opt(yytext);}

%%



char keywords[100][10] = {
    "int", "char", "long", "float", "double", "auto", "register",
    "struct", "union", "const", "case", "switch", "default",
    "if", "then", "else", "for", "while", "break", "continue",
    "do", "signed", "unsigned", "short", "goto", "return", "void"
};


bool is_keyword(char * token)
{
    for (int i = 0; i < 100; ++i)
        if (strcmp(token, keywords[i]) == 0)
            return true;
    return false;
}

int is_existed(string token)
{
    for (int i = 0; i < id_table.size(); ++i)
        if (id_table[i] == token)
            return i;
    return -1;
}

void install_num(char * token)
{
    num_table.push_back(token);
    fprintf(yyout, "{num%d} ", num_table.size());
}

void install_str(char * token)
{
    str_table.push_back(token);
    fprintf(yyout, "{str%d} ", str_table.size());
}

void install_opt(char * token)
{
    opt_table.push_back(token);
    fprintf(yyout, "%s{opt} ", token);
}

void install_id(char * token)
{
    if (is_keyword(token))
    {
        kw_table.push_back(token);
        fprintf(yyout, "%s{kw} ", token);
    }
    else
    {
        int idx;
        if ((idx = is_existed(token)) != -1)
            fprintf(yyout, "{id%d} ", idx);
        else
        {
            id_table.push_back(token);
            fprintf(yyout, "{id%d} ", id_table.size());
        }
    }
}

int yywrap()
{
	return 1;
}

int main(int argc, char * argv[])
{
    yyin = fopen(argv[1], "r");
     
    /* Lexical Analysis */	
    yylex();
    
    /* print number of lines */
    fprintf(yyout, "\n\nTotally %d lines, %d white lines.",
            lineCnt + wlineCnt, wlineCnt);
    fprintf(yyout, " %d punctations, %d operators, %d keywords, %d identifiers.\n", 
            punctCnt, opt_table.size(), kw_table.size(), id_table.size());

    /* print identifiers */
    fprintf(yyout, "\nIdentifires:\n");
    for (int i = 0; i < id_table.size(); ++i)
        fprintf(yyout, "%s ", id_table[i].c_str());
    fprintf(yyout, "\n");

    /* print keywords */
    fprintf(yyout, "Keywords:\n");
    for (int i = 0; i < kw_table.size(); ++i)
        fprintf(yyout, "%s ", kw_table[i].c_str());
    fprintf(yyout, "\n");
    
    /* print operators*/
    fprintf(yyout, "Operators:\n");
    for (int i = 0; i < opt_table.size(); ++i)
        fprintf(yyout, "%s ", opt_table[i].c_str());
    fprintf(yyout, "\n");
    
    /* print numbers */
    fprintf(yyout, "Numbers:\n");
    for (int i = 0; i < num_table.size(); ++i)
        fprintf(yyout, "%s ", num_table[i].c_str());
    fprintf(yyout, "\n");

    /* print strings */
    fprintf(yyout, "Strings:\n");
    for (int i = 0; i < str_table.size(); ++i)
        fprintf(yyout, "%s\n", str_table[i].c_str());
    fprintf(yyout, "\n");
	
    fclose(yyin);
}
