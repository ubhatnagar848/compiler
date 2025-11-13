/* codegen.l: The lexer file */
%{
#include "y.tab.h"
#include <string.h>
extern YYSTYPE yylval;
%}

%%
[a-zA-Z][a-zA-Z0-9]* { 
    yylval.var = strdup(yytext); /* Copy the identifier string */
    return ID; 
}
":=" { return ASSIGN; }
"+"  { return '+'; }
"-"  { return '-'; }
"*"  { return '*'; }
"/"  { return '/'; }
"\n" { return '\n'; }
[ \t]+ ; /* Ignore whitespace */
.    { fprintf(stderr, "Error: Unknown character '%s'\n", yytext); }
%%

int yywrap(void) {
    return 1; /* Signal that there is no more input */
}