/* ab.l */
%{
#include "mango.tab.h"
%}

%%
"a"     { return A_SYM; }
"b"     { return B_SYM; }
[ \t\r\n]+   { /* skip whitespace */ }
.       { fprintf(stderr, "Invalid symbol: %s\n", yytext); return 0; }
%%

int yywrap(void) { return 1; }
