/* three_addr.l: (Final Version) Lexer for 3-Address Code Generation */
%{
#include "y.tab.h"
#include <stdlib.h>
#include <string.h>
void yyerror(char *);
%}

%%
[0-9]+                  { yylval.str = strdup(yytext); return NUM; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.str = strdup(yytext); return ID; }

"+"                     return '+';
"-"                     return '-';
"*"                     return '*';
"/"                     return '/';
"="                     return '=';
";"                     return ';';
"("                     return '(';
")"                     return ')';

[ \t\r]+                ; 
\n                      ; 

.                       { 
                          fprintf(stderr, "Error: Unexpected character '%c'\n", yytext[0]); 
                        }
%%

int yywrap(void) {
    return 1;
}