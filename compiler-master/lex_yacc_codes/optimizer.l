%{
#include <stdio.h>
#include <string.h>
#include "y.tab.h" 
%}

%%

[0-9]+                  { 
                            yylval.str = strdup(yytext); 
                            return NUMBER; 
                        }

[a-zA-Z_][a-zA-Z0-9_]* { 
                            yylval.str = strdup(yytext); 
                            return ID; 
                        }

[ \t\r]+                ; /* Ignore whitespace, TABS, AND CARRIAGE RETURNS */

\n                      { return '\n'; }

.                       { return *yytext; }

%%

int yywrap(void) {
    return 1;
}